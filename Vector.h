#ifndef __VECTOR__
#define __VECTOR__
#include <iostream>

//--------------------------------------------------------------Класс Вектор-------------------------------------------------------------
class Vector {
public:
	int num;
	double *Elm;
	Vector() {
		num = 0;
		Elm = 0;
	} // конструктор по умолчанию

	//---------------------------Копирующий конструктор---------------------------
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

	//---------------------------Конструктор заданного размера---------------------------
	Vector(unsigned int size) {
		num = size;
		Elm = new double[num];
		PutZero();
	}

	//------------------------------Конструктор с заданными размерностью и значениями ----------------------
	Vector(double a1, double a2) {
		num = 2;
		Elm = new double[num];
		Elm[0] = a1;
		Elm[1] = a2;
	}

	//------------------------------Конструктор с заданными размерностью и значениями ----------------------
	Vector(double a1, double a2, double a3) {
		num = 3;
		Elm = new double[num];
		Elm[0] = a1;
		Elm[1] = a2;
		Elm[2] = a3;
	}


	//------------------------------Конструктор с заданными размерностью и значениями ----------------------
	Vector(double a1, double a2, double a3, double a4) {
		num = 4;
		Elm = new double[num];
		Elm[0] = a1;
		Elm[1] = a2;
		Elm[2] = a3;
		Elm[3] = a4;
	}

	//---------------------------Сложение векторов-------------------------
	Vector Vector::operator + (Vector& V) {
		Vector Result(*this);
		for (int i = 0; i < Result.num; i++) {
			Result.Elm[i] = Result[i] + V[i];
		}
		return Result;
	}
	
	//---------------------------Вычитание векторов-------------------------
	Vector Vector::operator - (Vector& V) {
		Vector Result(*this);
		for (unsigned i = 0; i < Result.num; i++) {
			Result.Elm[i] = Result[i] - V[i];
		}
		return Result;
	}
	
	//---------------------------Оператор равно -------------------------------
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

	//---------------------------Скалярное произведение-------------------------
	double Vector::operator * (const Vector& V) {
		double result = 0;
		if (num != V.num) return 0;
		for (int i = 0; i < num; i++){
			result += Elm[i] * V.Elm[i];
		}
		return result;
	}

	//---------------------------Произведение вектора на скаляр-------------------------
	friend Vector operator * (Vector& V, double c) {
		Vector New(V.num);
		for(int i = 0; i < V.num; i++){
			New.Elm[i] = V[i]*c;
		}
		return New;
	}

	//---------------------------Произведение вектора на скаляр-------------------------
	friend Vector operator * (double c,Vector& V) {
		Vector New(V.num);
		for(int i = 0; i < V.num; i++){
			New.Elm[i] = V[i]*c;
		}
		return New;
	}


	//---------------------------Оператор вывода-------------------------
	friend std::ostream& operator << (std::ostream& out, Vector& V){
		for (int i = 0; i < V.Size_Of(); i++){
			out<<" "<<V[i]<<" "<<std::endl;
		}  
		return out;
	}

	//--------------------------Функция обнуления строки--------------------------
	void PutZero(){
		for (int i = 0; i < num; i++){
			Elm[i] = 0;
		}
	}

	//--------------------------Нормализация вектора--------------------------------
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
	//--------------------------Меняем размер строки, сохраняя значения, добавляя 0--------------------------
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

	//--------------------------Кол-вво эл-тов в строке--------------------------
	unsigned int Size_Of(){	return num;	} 

	//--------------------------Доступ к элементу--------------------------
	double operator [](unsigned ind){
		return Elm[ind];
	}
};

	//--------------------------Модуль вектора--------------------------
	double absolut(Vector& V){
		double sum = 0.0;
		for(int i=0; i<V.Size_Of(); i++){
			sum += V.Elm[i]*V.Elm[i];
		}
		double result = sqrtl(sum); 
		return (result);
	}

	//---------------------------Векторное произведение-------------------------
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