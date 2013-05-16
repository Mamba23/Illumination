#ifndef __OBJECT__
#define __OBJECT__
#include "ClassMatrix.h"

class Object {
public:

	Vector Kd, Ks;
	double Ka, ns;
	Vector coord;							//that is coordinate of the figure center  
	int color;
	Object ():coord(4), color(0x000000) {}
	Object (Vector v, int c):coord(v), color(c) {}

	void SetFactor (Vector &v1, Vector &v2, double a, double b) {
		Kd = Vector(v1);
		Ks = Vector(v2);
		Ka = a;
		ns = b;
	}

	virtual Vector *cross (Vector &P0, Vector &ray, int number)=0;
	virtual Vector normal (Vector &point)=0;

};

class Sphere: public Object {
public:

	double R;

	Sphere (): R(0) {}

	Sphere (Vector v, int c, double r):Object(v,c), R(r) {}

	void Set(Vector v, int c, double r) {
		coord = v;
		color = c;
		R = r;
	}


	Vector *cross (Vector &P0, Vector &ray, int number) {
		Vector dP = coord - P0;
		Vector J = dP - ray*(ray*dP);
		Vector *result = NULL;
		double D = R*R - J*J;//((ray*dP)*(ray*dP)) - dP*dP + R*R;
		if (D < 0) {return NULL;}
		double s1 = ray*dP + sqrt(D);	
		double s2 = ray*dP - sqrt(D);
		if (number == 0) {
			if (s1 <= 1e-10) {return NULL;}
			result = new Vector(P0 + ray*s1);
			return result;
		} else {
			if (s2 <= 1e-10) {return NULL;}
			result = new Vector(P0 + ray*s2);
			return result;
		}
	}

	Vector normal (Vector &point) {
		Vector V (point - coord);
		V.Normalize();
		return V;
	}
};

class Flat: public Object {

public:

	Vector N;
	double Lx, Ly, Lz;
	Flat (): Lx(0), Ly(0) {}

	Flat (Vector v, Vector Norm, int c, double q, double w, double r):Object(v,c), N(Norm), Lx(q), Ly(w), Lz(r) {}

	void Set(Vector v, Vector Norm, int c, double q, double w, double r) {
		coord = v;
		double along = absolut(Norm); 
		N = Vector(Norm[0]/along,Norm[1]/along,Norm[2]/along,Norm[3]/along);
		color = c;
		Lx = q;
		Ly = w;
		Lz = r;
	}

	Vector *cross (Vector &P0, Vector &ray, int number = 0) {
		double N1 = N*P0,						//если 0, то начало луча в плоскости.
			N2 = N*ray;							// если 0, то вектор в плоскости.
		Vector *result = NULL;
		if (N2 == 0.0) {return NULL;}
		double s = abs(N1 / N2); 
		Vector v(P0 + ray*(s));
		if (((abs(v[0] - coord[0]) - Lx/2) >= 0.0000001 ) || abs((v[1] - coord[1]) - Ly/2 >= 0.0000001) || (abs(v[2] - coord[2])- Lz/2 >= 0.0000001 )) {
			return NULL;
		}
		double X = N*v;
		if (abs(X) < 1e-10 && abs(s)>1e-10) {
			result = new Vector (P0 + ray*(s));
			return result;
		} else {
			return NULL;
		}
	}

	//Vector CalcIntensive (Vector &ray, Vector &point, Vector &light) {
	//	Vector L = light - point;
	//	L = L*(1/absolut(L));
	//}

	Vector normal (Vector &point) {
		double dl = sqrtl(N[0]*N[0] + N[1]*N[1] + N[2]*N[2]);
		return Vector(N[0]/dl, N[1]/dl, N[2]/dl, 0);
	}

};

#endif