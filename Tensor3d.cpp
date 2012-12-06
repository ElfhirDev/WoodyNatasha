/*
 *
 *
 *
 */
 
#include "Tensor3d.hpp"

Tensor3d::Tensor3d(MatrixXd A, MatrixXd B, MatrixXd C)
{
	this->L = A;
	this->M = B;
	this->N = C;
}

MatrixXd Tensor3d::getL() {return L;}
MatrixXd Tensor3d::getM() {return M;}
MatrixXd Tensor3d::getN() {return N;}

void Tensor3d::setL(MatrixXd A) { L = A;}
void Tensor3d::setM(MatrixXd B) { M = B;}
void Tensor3d::setN(MatrixXd C) { N = C;}

/* Hoping that the tensor3d is full (^_^),
 * because L, M and N should have the same size.
 */
int Tensor3d::getRows() {
	return L.rows();
}

double Tensor3d::getVal(unsigned int i, unsigned int j, unsigned int k) {
	double res = 123456789;
	MatrixXd tmp;
	switch(k) {
		case 0:
			tmp = getL();
			res = tmp(i,j);
		break;
		case 1:
			tmp = getM();
			res = tmp(i,j);
		break;
		case 2:
			tmp = getN();
			res = tmp(i,j);
		break;
		default: // Only 3 x 3 x 3 tensor, but user will never use this directly.
			res = -123456789;
		break	;	
	}	
			
	return res;
}

void Tensor3d::printTensor3d() {
	std::cout << "   Tensor3d :" << endl;
	for(int k = 0; k<3 ; ++k) {
		for(int i = 0; i<getRows() ; ++i) {		
				std::cout << " " << getVal(i,0,k) << " " << getVal(i,1,k) << " " << getVal(i,2,k) << std::endl;
		}
		std::cout << std::endl;
	}

}
 
 
 
 
 
 