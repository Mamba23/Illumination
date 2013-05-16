#define _WIN32_WINNT 0x0500
#include <iostream>

#include "App.h"
#include "GfxWin.h"
#include <math.h>
#include "object.h"
#include "bmp.h"

Vector Lights[] = {Vector(0,75,-150,1)};
Vector Il[] = {Vector(750,750,750)};
Vector Ia = Vector(50,50,50);


int WIDTH = 800, HEIGHT = 600; 
int WinBitmap::BitMapWidth = WIDTH, WinBitmap::BitMapHeight = HEIGHT;
#define PI 3.14159265

class MyWin: public GfxWindow {

public:

	MyWin(int x, int y, int width, int height, char *Name):GfxWindow(x,y, width, height,Name) {

		buffer = new unsigned char [width*height*3];
		memset(buffer, 0x35, width*height*3);

		CreateData();
		CreateScene();
		SetBuffer(buffer);
		//write_bmp("qwer.bmp", WIDTH, HEIGHT,buffer);
	}

	void OnPaint() {
		SetBuffer(buffer);
		GfxWindow::OnPaint(); 
	}

	void CreateData () {

		spheres = new Sphere [2];
		spheres[0].Set(Vector(40,-65,-200,1),0xA01000, 15);
		spheres[1].Set(Vector(0,-58,-200,1),0x00A010, 22);

		flats = new Flat[6];

		flats[0].Set(Vector (0,-80,-200,1),Vector(0,1,0,80), 0x707070, 200, 0, 200);
		flats[1].Set(Vector (0, 80,-200,1),Vector(0,-1,0, 80), 0x707070, 200, 0, 200);
		flats[2].Set(Vector (100, 0,-200,1),Vector(-1, 0,0,100), 0x151590, 0, 160, 200);
		flats[3].Set(Vector (-100,0,-200,1),Vector(1,0,0,100), 0x901515, 0, 160, 200);
		flats[4].Set(Vector (0,0,-300,1),Vector(0,0,1,300), 0x707070, 200, 160, 0);
		flats[5].Set(Vector (0,0,-20,1),Vector(0,0,-1,-20), 0x000000, 200, 160, 0);

		flats[0].SetFactor(Vector(0.3,0.3,0.3), Vector(0.7,0.7,0.7), 0.12, 15.0);
		flats[1].SetFactor(Vector(0.7,0.7,0.7), Vector(0.5,0.5,0.5), 0.7, 3.0);
		flats[2].SetFactor(Vector(0.3,0.3,0.3), Vector(0.1,0.1,0.1), 0.1, 1.0);
		flats[3].SetFactor(Vector(0.3,0.3,0.3), Vector(0.1,0.1,0.1), 0.1, 1.0);
		flats[4].SetFactor(Vector(0.3,0.3,0.3), Vector(0.2,0.2,0.2), 0.15, 15.0);
		flats[5].SetFactor(Vector(0.1,0.1,0.1), Vector(0.2,0.2,0.2), 0.2, 1.0);
		
		spheres[0].SetFactor(Vector(0.3,0.3,0.3), Vector(0.2,0.2,0.2), 0.2, 30.0);
		spheres[1].SetFactor(Vector(0.3,0.3,0.3), Vector(0.3,0.3,0.3), 0.2, 30.0);


		alpha = 60;
		beta = 76;
		n = -80;
		f = -9000;

		Zot = -100;


		Camera = Vector (0,0,0,1);
		Center = Vector (1,1,1,1);
		X = Vector (1,0,0,0);
		Y = Vector (0,1,0,0);
		Z = Vector (0,0,1,0);

		W = Camera - Center;
		W.Normalize();
		U = Multiple(W,Y);
		U .Normalize();
		V = Multiple(W,U);

		Mp = Matrix(3, 3, 2*tan(beta*PI/360)*(-Zot)/(WIDTH - 1), 0.0, - tan(beta*PI/360)*(-Zot),
						  0.0, -2*tan(alpha*PI/360)*(-Zot)/(HEIGHT - 1), tan(alpha*PI/360)*(-Zot),
						  0.0,			0.0,			1.0);

		Mc = Matrix(4, 4, X*U, X*V, X*W, 0,
						  Y*U, Y*V, Y*W, 0,
						  Z*U, Z*V, Z*W, 0,
						
						  (Camera*(-1))*U, Camera*(-1)*V, Camera*(-1)*W, 1);
	}

	void CreateScene () {

		//Vector f = spheres[0].coord;
		//f = f*(1/absolut(f));
		//f.Set_Size(3);
		//Vector C = !Mp*f;
		//int c = FindCross (f);

		for (int i = 0; i < HEIGHT; ++i) {
			for (int j = 0; j < WIDTH; ++j) {
				Vector v = ( Mp * Vector(j,i,1));
				Vector ray(v[0],v[1], Zot, 0);
				ray.Normalize();
				Vector *I = (FindIntens(ray));
				if (I) {
					int index = ((HEIGHT-1-i)*WIDTH + j)*3;
					buffer[index + 0] = (I->Elm[0]<256)? unsigned char(I->Elm[0]):255;
					buffer[index + 1] = (I->Elm[1]<256)? unsigned char(I->Elm[1]):255;
					buffer[index + 2] = (I->Elm[2]<256)? unsigned char(I->Elm[2]):255;
					delete I;
				}
			}
		}

	}

	Vector *Intens (Vector &light, Vector &point, Object *obj) {
		Vector L (light - point);
		double DL = absolut(L);
		L.Normalize();
		Vector *result;
		double l = FindCross(point,L);
		if (l!=0.0) {
			if (l < DL) {
				result = new Vector (obj->Ka * Ia);
				result->Elm[0] += obj->color >>16; 
				result->Elm[1] += obj->color >>8 & 0x0000FF;
				result->Elm[2] += obj->color & 0x0000FF; 
				return result;
			}
		}
		Vector N (obj->normal(point));
		Vector V(-point[0],-point[1],-point[2], 0) ;
		V.Normalize();
		//Vector RayMirror = U-N*(2*(U*N));
		Vector R ((2.0*(L*N))*N - L);
		Vector H(L+V); 
		H.Normalize();
		double dl = 1/pow((point[0]*point[0]+point[1]*point[1]+point[2]*point[2]),0.1);
		result = new Vector(3);
		double cosf = (N*H),
			cosa = (N*L);
		if (cosf < 0.0) {
			cosf = 0.0;
		} else {
			cosf = pow((cosf),obj->ns);
		}
		if (cosa < 0.0) {
			cosa = 0.0;
		}
		result->Elm[0] = Ia.Elm[0]*obj->Ka + Il[0].Elm[0]*dl*((obj->Kd[0]*cosa) + (obj->Ks[0]*cosf)) + double(obj->color >>16); 
		result->Elm[1] = obj->Ka*Ia.Elm[1] + Il[0].Elm[1]*dl*((obj->Kd[1]*cosa) + (obj->Ks[1]*cosf)) + double(obj->color >>8 & 0x0000FF);
		result->Elm[2] = obj->Ka*Ia.Elm[2] + Il[0].Elm[2]*dl*((obj->Kd[2]*cosa) + (obj->Ks[2]*cosf)) + double(obj->color & 0x0000FF); 

		return result ;
	}


	Vector *FindIntens (Vector &ray) {
		Object *obj;
		double s = f;
		double s1 = 0.0, s2 = 0.0;
		Vector *V1 = NULL,*V2 = NULL, *V3 = NULL, *V = NULL;
		for (int i = 0; i < 2; ++i) {

			V1 = spheres[i].cross(Camera, ray, 0);
			V2 = spheres[i].cross(Camera, ray, 1);

			if (V1) {
				if ((s < (s1 = -absolut(*V1))) && (V1->operator[](2) < n)) {
					if (V) delete V;
					V = V1;
					V1 = NULL;
					obj = &spheres[i]; 
					s = s1;
				} else {
					delete V1;
					V1 = NULL;

				}
			}
			if (V2) { 
				if ((s < (s2 = -absolut(*V2))) && (V2->operator[](2) < n)) {
					if (V) delete V;
					V = V2;
					V2 = NULL;
					obj = &spheres[i]; 
					s = s2;
				} else {
					delete V2;
					V2 = NULL;
				}
			}
		}

		for (int i = 0; i < 5; ++i) {

			V3 = flats[i].cross(Camera, ray);
			if (V3) {
				if  ((s < (s1 = -absolut(*V3))) && (V3->operator[](2) < n)) {
					if (V) delete V;
					if (i==0) {
						int j = 0;
					}
					V = V3;
					V3 = NULL;
					obj = &flats[i];
					s = s1;
				} else {
					delete V3;
					V3 = NULL;

				}
			}

		}


		V = Intens(Lights[0],*V,obj);
		if (V1) {delete V1;}
		if (V2) {delete V2;}	
		if (V3) {delete V3;}	

		return V;
	}

	double FindCross (Vector &point,Vector &ray) {
		double s = f;
		double s1 = 0.0, s2 = 0.0;
		Vector *V1 = NULL,*V2 = NULL, *V3 = NULL;
		for (int i = 0; i < 2; ++i) {

			V1 = spheres[i].cross(point, ray, 0);
			V2 = spheres[i].cross(point, ray, 1);

			if (V1) { 
				if ((s < (s1 = -absolut(*V1-point))) && (V1->operator[](2) < n)) {
					s = s1;
				}
				delete V1;
				V1 = NULL;
			}
			if (V2) { 
				if ((s < (s2 = -absolut(*V2-point))) && (V2->operator[](2) < n)) {
					s = s2;
				}
				delete V2;
				V2 = NULL;
			}
		}

		for (int i = 0; i < 5; ++i) {

			V3 = flats[i].cross(point, ray);
			if (V3) { 
				if ((s < (s1 = -absolut(*V3-point))) && (V3->operator[](2) < n)) {
					s = s1;
				}
				delete V3;
				V3 = NULL;
			}

		}

		if (V1) {delete V1;}
		if (V2) {delete V2;}	
		if (V3) {delete V3;}	

		if (s == -9000.0) {
			return 0.0;
		}
		return -s;
	}

private:

	unsigned char *buffer;

	Sphere *spheres;
	Flat *flats;

	Vector Camera;
	Vector Center;								// it is center of pruncated pyramid of observation
	Vector X, Y, Z;	
	Vector W, U, V;

	int alpha, beta;
	int n, f; 
	int Zot; 

	Matrix Mp, Mc;								// Mp - transformation from coord of device to flat of observation

};


int WINAPI WinMain(HINSTANCE hThisInst, HINSTANCE hPrevInst, LPSTR lpszArgs, int nWinMode) {
//int main() {

	App a;
	GfxWindow* win  = 
		new MyWin(100, 100, WIDTH + 6 ,HEIGHT + 28, "Ray Trace");
	a.SetMainWindow(win);

	/// 1 секунда
//	win->SetDelta(0.01f);
	//ShowWindow(GetConsoleWindow(),false);
	win->Show(true);
	return a.Run();
}