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

/* Access at element of Tensor, T(i,j,k)
 * return double
 */
double Tensor3d::operator()(unsigned int i, unsigned int j, unsigned int k) {
	int res = 123456789;
	switch(k) {
		case 0:
			res = L(i,j);
		break;
		case 1:
			res = M(i,j);
		break;
		case 2:
			res = N(i,j);
		break;
		default: // Only 3 x 3 x 3 tensor, but user will never use this directly.
			res = -123456789;
		break;	
	}	
	
	return res;
}



void Tensor3d::printTensor3d() {
	std::cout << "   Tensor3d :" << std::endl;
	for(int k = 0; k<3 ; ++k) {
		for(int i = 0; i<getRows() ; ++i) {		
				std::cout << " " << getVal(i,0,k) << " " << getVal(i,1,k) << " " << getVal(i,2,k) << std::endl;
		}
		std::cout << std::endl;
	}

}

// This is sparta !!
Eigen::MatrixXd Tensor3d::buildMatrixA() {
	Eigen::MatrixXd A(27,28);

	// Now check the math subject with Natasha;
	// We will have to fill that matrix with dirty things like numbers and ...
	// that's all. Using some for and for boucles (about 4 according to Aurelien, we will see!)
	//
	// And some SVD ... from Eigen


	return A;
}

Eigen::MatrixXi Tensor3d::aroundMatrixA(Eigen::MatrixXd &A) {
	Eigen::MatrixXi newA(27,28);
	for(int i = 0; i < 27; ++i) {
		for(int j = 0; j < 28; ++j) {
			newA(i,j) = (int)A(i,j);
			// Maybe around or ceil or floor function ?
		}
	}

	return newA;
}


Eigen::MatrixXi Tensor3d::transfert(MatrixXi list1, MatrixXi list2) {
	Eigen::MatrixXi list3;

	// Using the MatrixXi newA = leTensor.aroundMatrixA(leTensor.buildMatrixA());
	// with Some SVD ... too

	return list3;
}

 
 
 
 
 
 