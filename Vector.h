#ifndef __VECTOR__
#define __VECTOR__
#include <iostream>

//--------------------------------------------------------------����� ������-------------------------------------------------------------
class Vector {
public:
	int num;
	double *Elm;
	Vector() {
		num = 0;
		Elm = 0;
	} // ����������� �� ���������

	//---------------------------���������� �����������---------------------------
	Vector(const Vector& V) {
		num = V.num;
		Elm = new double[num];	
		for (int i = 0; i < num; i++) {
			Elm[i] = V.Elm[i];
		}
	}

	~Vector () {
		num = 0;
		if (Elm) {delete []Elm;}
	}

	//---------------------------����������� ��������� �������---------------------------
	Vector(unsigned int size) {
		num = size;
		Elm = new double[num];
		PutZero();
	}

	//------------------------------����������� � ��������� ������������ � ���������� ----------------------
	Vector(double a1, double a2) {
		num = 2;
		Elm = new double[num];
		Elm[0] = a1;
		Elm[1] = a2;
	}

	//------------------------------����������� � ��������� ������������ � ���������� ----------------------
	Vector(double a1, double a2, double a3) {
		num = 3;
		Elm = new double[num];
		Elm[0] = a1;
		Elm[1] = a2;
		Elm[2] = a3;
	}


	//------------------------------����������� � ��������� ������������ � ���������� ----------------------
	Vector(double a1, double a2, double a3, double a4) {
		num = 4;
		Elm = new double[num];
		Elm[0] = a1;
		Elm[1] = a2;
		Elm[2] = a3;
		Elm[3] = a4;
	}

	//---------------------------�������� ��������-------------------------
	Vector Vector::operator + (Vector& V) {
		Vector Result(*this);
		for (int i = 0; i < Result.num; i++) {
			Result.Elm[i] = Result[i] + V[i];
		}
		return Result;
	}
	
	//---------------------------��������� ��������-------------------------
	Vector Vector::operator - (Vector& V) {
		Vector Result(*this);
		for (unsigned i = 0; i < Result.num; i++) {
			Result.Elm[i] = Result[i] - V[i];
		}
		return Result;
	}
	
	//---------------------------�������� ����� -------------------------------
	Vector &Vector::operator = (const Vector& V) {
		if (Elm) {
			delete []Elm; 
			Elm = NULL;
		}
		if (&V == NULL) {
			num = 0;
			Elm = NULL;
			return *this;
		}
		num = V.num;
		Elm = new double [num];
		for (int i = 0; i < num; i++) {
			Elm[i] = V.Elm[i];
		}
		return *this;
	}

	//---------------------------��������� ������������-------------------------
	double Vector::operator * (const Vector& V) {
		double result = 0;
		if (num != V.num) return 0;
		for (int i = 0; i < num; i++){
			result += Elm[i] * V.Elm[i];
		}
		return result;
	}

	//---------------------------������������ ������� �� ������-------------------------
	friend Vector operator * (Vector& V, double c) {
		Vector New(V.num);
		for(int i = 0; i < V.num; i++){
			New.Elm[i] = V[i]*c;
		}
		return New;
	}

	//---------------------------������������ ������� �� ������-------------------------
	friend Vector operator * (double c,Vector& V) {
		Vector New(V.num);
		for(int i = 0; i < V.num; i++){
			New.Elm[i] = V[i]*c;
		}
		return New;
	}


	//---------------------------�������� ������-------------------------
	friend std::ostream& operator << (std::ostream& out, Vector& V){
		for (int i = 0; i < V.Size_Of(); i++){
			out<<" "<<V[i]<<" "<<std::endl;
		}  
		return out;
	}

	//--------------------------������� ��������� ������--------------------------
	void PutZero(){
		for (int i = 0; i < num; i++){
			Elm[i] = 0;
		}
	}

	//--------------------------������������ �������--------------------------------
	void Normalize() {
		double sum = 0.0;
		for(int i=0; i<Size_Of(); i++){
			sum += Elm[i]*Elm[i];
		}
		double result = sqrtl(sum);

		for (int i = 0; i < num; ++i) {
			Elm[i] /=result; 
		}
	}
	//--------------------------������ ������ ������, �������� ��������, �������� 0--------------------------
	Vector &Set_Size(unsigned newsize){
		if (newsize == num) return *this;
		double *A = 0;
		if (newsize > 0) A = new double[newsize];
		for (int i = 0; i < newsize; i++){
			if (i < num){
				A[i] = Elm[i];
			}else{
				A[i] = 0;
			
			}
		}
		if (num != 0) delete []Elm;
		Elm = A;
		num = newsize;
		return *this;
	}

	//--------------------------���-��� ��-��� � ������--------------------------
	unsigned int Size_Of(){	return num;	} 

	//--------------------------������ � ��������--------------------------
	double operator [](unsigned ind){
		return Elm[ind];
	}
};

	//--------------------------������ �������--------------------------
	double absolut(Vector& V){
		double sum = 0.0;
		for(int i=0; i<V.Size_Of(); i++){
			sum += V.Elm[i]*V.Elm[i];
		}
		double result = sqrtl(sum); 
		return (result);
	}

	//---------------------------��������� ������������-------------------------
	Vector Multiple(Vector& V1, Vector& V2) {
		if (V1.num != V2.num) return 0;
		Vector result(V1.num);
		if (result.num != V1.num) return 0;
		if (result.num != V2.num) return 0;
		if (V2.num != 4) return 0;
		result.Elm[0] = (V1.Elm[1]*V2.Elm[2] - V1.Elm[2]*V2.Elm[1]);
		result.Elm[1] = (V1.Elm[0]*V2.Elm[2] - V1.Elm[2]*V2.Elm[0]);
		result.Elm[2] = (V1.Elm[0]*V2.Elm[1] - V1.Elm[1]*V2.Elm[0]);
		result.Elm[3] = 0;

		return result;
	}
#endif