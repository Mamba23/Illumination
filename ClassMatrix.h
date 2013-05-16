#include <string.h>
#include <fstream>
#include <iostream>
#include "Vector.h"
#ifndef _CLASS_MATRIX_
#define _CLASS_MATRIX_
	

//--------------------------------------------------------------����� �������-------------------------------------------------------------
class Matrix{
private: 
	Vector *Mrows; // ������ �����
	unsigned int cols, rows; // ������, ������
public:
	//---------------------------����������� �� ���������-------------------------
	Matrix(){
		cols = 0;
		rows = 0;
		Mrows = 0;
	}

	//---------------------------����������� ����������-------------------------
	Matrix(const Matrix& M){
		cols = M.cols;
		rows = M.rows;
		Mrows = new Vector[rows];
		for(int i = 0; i < rows; i++){
			Mrows[i].Set_Size(cols);
			for(int j = 0; j < cols; j++){
				Mrows[i].Elm[j] = M.Mrows[i][j];
			}
		}
	}

	//---------------------------����������� � �������� ��������---------------------------
	Matrix(unsigned int cols_t, unsigned int rows_t){
		cols = cols_t;
		rows = rows_t;
		Mrows = new Vector[rows];
		for(int i = 0; i < rows; i++){
			Mrows[i].Set_Size(cols);
		}
	}
	//------------------------------����������� � ��������� ������������ � ���������� ----------------------
	Matrix( double a11, double a12,
			double a21, double a22){
		cols = 2;
		rows = 2;
		Mrows = new Vector[rows];
		for(int i = 0; i < rows; i++){
			Mrows[i].Set_Size(cols);
		}
		Mrows[0].Elm[0] = a11; Mrows[0].Elm[1] = a12; 
		Mrows[1].Elm[0] = a21; Mrows[1].Elm[1] = a22;
	}

	//------------------------------����������� � ��������� ������������ � ���������� ----------------------
	Matrix(unsigned int cols_t,unsigned int rows_t, double a11, double a12, double a13,
													double a21, double a22, double a23,
													double a31, double a32, double a33){
		cols = cols_t;
		rows = rows_t;
		Mrows = new Vector[rows];
		for(int i = 0; i < rows; i++){
			Mrows[i].Set_Size(cols);
		}
		Mrows[0].Elm[0] = a11; Mrows[0].Elm[1] = a12; Mrows[0].Elm[2] = a13;
		Mrows[1].Elm[0] = a21; Mrows[1].Elm[1] = a22; Mrows[1].Elm[2] = a23;
		Mrows[2].Elm[0] = a31; Mrows[2].Elm[1] = a32; Mrows[2].Elm[2] = a33;
	}

	//------------------------------����������� � ��������� ������������ � ���������� ----------------------
	Matrix(unsigned int cols_t,unsigned int rows_t, double a11, double a12, double a13, double a14,
													double a21, double a22, double a23, double a24,
													double a31, double a32, double a33, double a34,
													double a41, double a42, double a43, double a44){
		cols = cols_t;
		rows = rows_t;
		Mrows = new Vector[rows];
		for(int i = 0; i < rows; i++){
			Mrows[i].Set_Size(cols);
		}
		Mrows[0].Elm[0] = a11; Mrows[0].Elm[1] = a12; Mrows[0].Elm[2] = a13; Mrows[0].Elm[3] = a14;
		Mrows[1].Elm[0] = a21; Mrows[1].Elm[1] = a22; Mrows[1].Elm[2] = a23; Mrows[1].Elm[3] = a24;
		Mrows[2].Elm[0] = a31; Mrows[2].Elm[1] = a32; Mrows[2].Elm[2] = a33; Mrows[2].Elm[3] = a34;
		Mrows[3].Elm[0] = a41; Mrows[3].Elm[1] = a42; Mrows[3].Elm[2] = a43; Mrows[3].Elm[3] = a44;
	}
	//---------------------------��������� ���-�� ��������-------------------------
	unsigned int Get_cols(){ return cols;}

	//---------------------------��������� ���-�� �����-------------------------
	unsigned int Get_rows(){ return rows;}

	//---------------------------����������---------------------------
	~Matrix(){
		if(rows != 0) delete []Mrows;
	}

	//---------------------------�������, ���������� ������ �������---------------------------
	Matrix& Matrix::Set_Size(unsigned int new_cols, unsigned int new_rows){
		if ((cols == new_cols) && (rows == new_rows)){ return *this; }
		Vector *A = 0;
		if (new_rows){
			A = new Vector[new_rows]; //������� �������
		}
		for (int i = 0; i < new_rows; i++){
			A[i].Set_Size(new_cols);
			for(int j = 0; j < new_cols; j++){
				if ((i < rows) && (j < cols)){
					A[i].Elm[j] = Mrows[i][j];
				}else A[i].Elm[j] = 0;
			}
		}
		if (rows != 0){ delete []Mrows;}
		Mrows = A;
		cols = new_cols;
		rows = new_rows;
		return *this;
	}

	//---------------------------��������� ������---------------------------
	void PutZero(); 

	//---------------------------����� �������� � ��������� ���������--------------------------
	double Matrix::Search_Elm(double now, bool compare, unsigned &I, unsigned &J, unsigned begin_i, unsigned begin_j){
		if ((!cols) || (!rows)){ return 0;}
		if ((begin_i >= rows) || (begin_j >= cols)){ return 0;}
		for (unsigned i = begin_i; i < rows; i++){
			for (unsigned j = begin_j; j < cols; j++){
				if (compare == true){
					if (Mrows[i][i] == now) {
						I = i;
						J = j;  
						return 1;
					}
				}else{
					if (Mrows[i][j] != now) {
					I = i;
					J = j;
					return 1;
					}
				}
			}
		}
		return 0;
	}
	
	//---------------------------������ ��� ������� �������---------------------------
	Matrix& Matrix::SwapCol(unsigned int c1, unsigned int c2){
		if ((c1 >= cols) || (c2 >= cols) || (c1 == c2)){ return *this;}
		double A;
		for (int i = 0; i < rows; i++){
			A = Mrows[i][c1];
			Mrows[i].Elm[c1] = Mrows[i][c2];
			Mrows[i].Elm[c2] = A;
		}
		return *this;
	}

	//---------------------------������ ��� ������ �������---------------------------
	Matrix& Matrix::SwapRow(unsigned int r1, unsigned int r2){
		if ((r1 >= rows) || (r2 >= rows) || (r1 == r2)){ return *this;}
		Vector A = Mrows[r1];
		Mrows[r1] = Mrows[r2];
		Mrows[r2] = A;
		return *this;
	} 

	//---------------------------�������� [], ������ � ����---------------------------
	Vector& Matrix::operator [](unsigned int ind){
		return Mrows[ind];
	}
/*
const CVector& CTable::operator [](unsigned uIndex) const{
  return items[uIndex];
};
*/

	//---------------------------�������� ������---------------------------
	friend std::ostream& operator<<(std::ostream& out, Matrix& T){
		for(int i = 0; i < T.rows; i++){
			for (int j = 0; j < T.cols; j++){
				out<<T.Mrows[i][j]<<"\t"<<"\t";
			}
			out<<std::endl;
		}
		return out;
	}

	//---------------------------�������� �����, ���� ������� ������� �� �� 0 �����/��������---------------------------
	friend std::istream& operator >> (std::istream& in, Matrix& T){
		if((T.cols == 0) || (T.rows == 0)){ return in;}
		for(int i = 0; i < T.rows; i++){
			for (int j = 0; j < T.cols; j++) {
				std::cout<<"Enter element number["<<i<<", "<<j<<"] = ";
				in>>T.Mrows[i].Elm[j];
			}
		}
		if (in.peek() == '\n') in.ignore();
		return in;
	}

	//---------------------------�������� ������������---------------------------
	Matrix& Matrix::operator = (const Matrix& T){
		Set_Size(T.cols, T.rows);
		for(int i = 0; i < rows; i++)
			Mrows[i] = T.Mrows[i];
		//  for (unsigned i = 0; i < cols; i++)
		//    for (unsigned y = 0; y < rows; y++)
		//      items[x][y] = t.items[x][y];
		return *this;
	}

	//---------------------------���������� ������������---------------------------
	double Matrix::Determinant(){ 
		/* TODO : ��������� ������ */
		if (cols != rows){ return 0; }
		if (cols == 0){ return 0;}
		Matrix M = *this;
		if (cols == 1){ return M[0][0];}
		if (cols == 2){ return (M[0][0] * M[1][1] - M[1][0] * M[0][1]);}
		bool sign = false; // ���� ������������
		double det = 1.0; // ������������
		double A;
		unsigned int x, y;
		for(int i = 0; i < rows; i++){ // ���� �� ���� ������� ���������
			if (M[i][i] == 0){ // ���� ������� �� ��������� ����� 0, �� ���� �� ������� ������� � �������
				if (!M.Search_Elm(0, false, x, y, i, i)){ return 0;} // ���� ��� �������� �������, �� ���. = 0
				if (i != x){ // ������ i-�� ������ � x-��
					M.SwapRow(i, x);				
					sign = !sign;
				}
				if (i != y){ // ������ i-�� ������� � y-��
					M.SwapCol(i, y);
					sign = !sign;
				} // ����� �������, � m[i][i], ������ ��������� �������.
			} // ������� ������� m[i][i] �� ������������
			det *= M[i][i];
			A = M[i][i];
			for (x = i; x < cols; x++){
				M[i].Elm[x] = M[i][x] / A;
			} // ����� ������� m[i][i] ������ ����� 1, �������� ��� �������� ������� ��� (i, i)-�� ��� ������ ��������� � ���. �������������
			for (y = i + 1; y < rows; y++){
				A = M[y][i];
				for (x = i; x < cols; x++){
					M[y].Elm[x] -= (M[i][x]*A);
				}
			}
		}
		if (sign){ return det*(-1);}
		return det;
	}

	// ������� ������� ���. ��������� ������� �������
	
	Vector Matrix::SolveSLAU(int size, Vector &B) {
		Vector X(size), column(size);
		double detA = Determinant();
		for (int i = 0; i < size; ++i) {
			for ( int j = 0; j < size; ++j) {
				column.Elm[j] = this->Mrows[j].Elm[i];
				this->Mrows[j].Elm[i] = B.Elm [j];
			}
			X.Elm[i] = Determinant()/detA;
			for ( int j = 0; j < size; ++j) {
				this->Mrows[j].Elm[i] = column.Elm[j];
			}
		}
		return X;
	}

	//---------------------------���� �������---------------------------
	unsigned Matrix::Matrix_Rang() {
		if (!cols || !rows) { return 0;}
		Matrix M = *this;
		if(cols == 1) { return 1;}
		double A;
		unsigned int i;
		unsigned int x, y;
		unsigned int end_i = (cols > rows)? rows : cols; // �������� �������
		for(i = 0; i < end_i; i++) {// ���� �� ���� ������� ���������
			if (M[i][i] == 0){   // ���� ������� �� ��������� ����� 0, �� ���� �� ������� ������� � �������
				if (!M.Search_Elm(0, false, x, y, i, i)){ break;} // ���� ��� �������� �������, ��������� ����
				if (i != x) M.SwapRow(i, x); // ������ i-�� ������ � y-��
				if (i != y) M.SwapCol(i, y);     // ������ i-�� ������� � x-��
			} // M[i][i] ������ != 0.
			A = M[i][i];
			for (y = i; y < cols; y++){
				M[i].Elm[y] = M[i][y] / A;
			} // M[i][i] ������ = 1
			for (x = i + 1; x < rows; x++){ // �������� ��� �������� ������� ��� (i, i)-�� � ������ �� ����, ��� ������ ��������� � ���. �������������
				A = M[x][i];
				for (y = i; y < cols; y++){
					M[x].Elm[y] -= (M[i][y]*A);
				}
			}
			for (y = i + 1; y < cols; y++){
				A = M[i][y];
				for (x = i; x < rows; x++)
					M[x].Elm[y] -= (M[x][i]*A);
			}
		}
		unsigned int count = 0; // ������� ������� �������� �� ������� ���������
		for (i = 0; i < end_i; i++){
			if (M[i][i] == 0){ break;
			} else {
				count++;
			}
			if (!count) count++;  
			return count;
		}
	}

	//---------------------------I,J ����� �������---------------------------
	Matrix Matrix::MinorIJ (unsigned int i, unsigned int j){
		if ((i >= this->cols) || (j >= this->rows)){ return *this;}
		Matrix M(this->rows-1, this->cols-1);
		if ((!M.cols) || (!M.rows)){ return M;}
		unsigned i1, j1;
		for (unsigned i2 = 0; i2 < M.rows; i2++){
			for (unsigned j2 =0; j2 < M.cols; j2++){
				if (i2 < i){ 
					i1 = i2;
				}else{
					i1 = i2 + 1;
				}
				if (j2 < j){
					j1 = j2;
				}else{
					j1 = j2 + 1;
				}
				M[i2].Elm[j2] = this->operator[](i1)[j1];
			}
		}
		return M;
	}

	//---------------------------���������������� �������---------------------------
	Matrix& Matrix::Transponation(){
		if (!cols || !rows){ return *this;}
		Matrix &M = *this;
		Matrix M2(rows, cols);
		for (int x = 0; x < cols; x++){
			for (int y = x + 1; y < rows; y++){
				M2[y].Elm[x] = M[x][y];
			}
		}
		M = M2;
		return *this;
	}

	//---------------------------�������� ������---------------------------
	Matrix Matrix::operator +(const Matrix& M){
		Matrix NewM(M);
		if (!this->cols || !this->rows || !M.cols || !M.rows){ return *this;}
		if ((this->cols != M.cols) || (this->rows != M.rows)){ return *this;}
		NewM.Set_Size(this->rows, this->cols);
		for (int i = 0; i < this->rows; i++){
			for (int j = 0; j < this->cols; j++){
				NewM[i].Elm[j] = ((NewM[i][j]) + (this->operator[](i)[j]));
			}
		}
		return NewM;
	}

	//---------------------------��������� ������---------------------------
	Matrix Matrix::operator -(const Matrix &M){
		Matrix NewM(M);
		if (!this->cols || !this->rows || !M.cols || !M.rows){ return *this;}
		if ((this->cols != M.cols) || (this->rows != M.rows)){ return *this;}
		NewM.Set_Size(this->rows, this->cols);
		for (int i = 0; i < this->rows; i++){
			for (int j = 0; j < this->cols; j++){
				NewM[i].Elm[j] = ((this->operator[](i)[j]) - (NewM[i][j]));
			}
		}	
		return NewM;
	}

	//---------------------------��������� �������---------------------------
	Matrix Matrix::operator !(){
		Matrix M(*this);
		if (!M.Get_cols() || !M.Get_rows()){ return M;}
		if (!M.Determinant()){ return M;}
		Matrix Inv(M.Get_rows(), M.Get_rows());
		double k;
		unsigned x, y;
		for(int i = 0; i < Inv.Get_rows(); i++){
			Inv[i].Elm[i] = 1;
		}	
		for(int i = 0; i < M.Get_rows(); i++){
			if (M[i][i] == 0){ 
				if (!M.Search_Elm(0, false, x, y, i, i)){ break;} // ���� ��� �������� �������, ��������� ����
				if (i != x){
					M.SwapRow(i, x); // ������ i-�� ������ � x-��
					Inv.SwapRow(i, x);
				}
				if (i != y){ 
					M.SwapCol(i, y); // ������ i-�� ������� � y-��
					Inv.SwapCol(i, y);
				}// A[i][i] ������ != 0
			}
			k = M[i][i]; // ������� ������� A[i][i]
			for(y = 0; y < cols; y++){
				M[i].Elm[y] = M[i][y] / k;
				Inv[i].Elm[y] = Inv[i][y] / k;
			}//  A[i][i] ������ = 1
			for(x = 0; x < rows; x++){ // �������� ��� �������� ������� ��� � ��� (i, i)-��, ��� ������ ��������� � ���. �������������
				if (x == i) continue;
				k =	M[x][i];
				for (y = 0; y < cols; y++){
					M[x].Elm[y] -= (M[i][y]*k);
					Inv[x].Elm[y] -= (Inv[i][y]*k);
				}
			}
		}
		return Inv;
	}

	//---------------------------��������� ������---------------------------
	Matrix Matrix::operator * (Matrix& M){
		Matrix NewM;
		unsigned int w, h;
		if (!this->cols || !this->rows || !M.cols || !M.rows){ return NewM;}
		if (this->cols != M.rows){ return NewM;}
		NewM.Set_Size(this->rows, M.cols);
		h = NewM.rows;
		w = NewM.cols;
		double elm;
		for (int i = 0; i < h; i++){
			for (int j = 0; j < w; j++){
				elm= 0;
				for(int k = 0; k < this->cols; k++){
					double x1 = this->operator[](i)[k],
						x2 = M[k][j];
					elm += x1*x2;
						//this->operator[](i)[k] * M[k][j];
				}
				NewM[i].Elm[j] = elm;
			}
		}
		return NewM;
	}

	//---------------------------��������� ������� �� ������---------------------------
	friend Vector operator * (Matrix& M,  Vector& V){
		Vector NewV;
		if (!M.Get_cols() || !M.Get_rows() || (M.Get_cols() != V.Size_Of()));
		unsigned int w = M.Get_cols();
		unsigned int h = M.Get_rows();
		NewV.Set_Size(h);
		double elm;
		for(int i = 0; i < h; i++){
			elm = 0;
			for(int j = 0; j < w; j++){
				elm += M[i][j]*V[j];
			}
			NewV.Elm[i] = elm;
		}
		return NewV;
	}

	//--------------------------��������� ������� �� ������---------------------------
	friend Matrix operator * (const int& c, const Matrix& M){
		Matrix NewM(M);
		for (unsigned i = 0; i < NewM.rows; i++){
			for (unsigned j = 0; j < NewM.cols; j++){
				NewM[i].Elm[j] = c * NewM[i][j];
			}
		}
		return NewM;
		}
	};

#endif