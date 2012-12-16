/*
 *
 *
 *
 */
 
#include "Tensor3d.hpp"

Tensor3d::Tensor3d(MatrixXd L1, MatrixXd L2, MatrixXd L3)
{
	// Tensor3d : 3 x 3 x 3   i.e 3 matrix 3x3, initialized with 0
	this->L = MatrixXd::Zero(3,3);
	this->M = MatrixXd::Zero(3,3);
	this->N = MatrixXd::Zero(3,3);

	this->Adouble = buildMatrixA(L1, L2, L3);

}

MatrixXd Tensor3d::getL() {return L;}
MatrixXd Tensor3d::getM() {return M;}
MatrixXd Tensor3d::getN() {return N;}

void Tensor3d::setL(MatrixXd L1) { L = L1;}
void Tensor3d::setM(MatrixXd L2) { M = L2;}
void Tensor3d::setN(MatrixXd L3) { N = L3;}

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
Eigen::MatrixXd Tensor3d::buildMatrixA(MatrixXd L1, MatrixXd L2, MatrixXd L3) {
	Eigen::MatrixXd A(28,27);
	int inc = 0;

	// For each points
	for(int p = 0; p<7; ++p) {

		// For each coords of a points - seems like playing with x,y,z
		for(int k = 0; k<3 ; ++k) {

			// 4 equations - seems like playing with x and y values combination - xx, xy, yx, yy -
			for(int i = 0; i<2; ++i) {
				for(int l = 0; l<2; ++l) {

					// As written on the paper :
					// A(4*p + 2*i +l, 4*p + 2*i ) = L1(p,k) * (  L2(p,0)*L3(p,2)*this->getVal(2,l,k)  -  L2(p,2)*L3(p,2)*this->getVal(i,l,k)  -  L2(p,i)*L3(p,l)*this->getVal(2,2,k)  +  L2(p,2)*L3(p,l)*this->getVal(i,2,k)  );
					//
					// Other solutions
					// 4*p + i + l  = {0;27}       9*k + (i+l) + 3*inc = {0;26}  - what is 'inc' ?


					// there are 27 columns, divided by the 3 values that k can have 
					// how to fill 9 cols ? i+l = {0;2}, it will provide 3 values ; Now we will have to
					// add a step of 3 for columns n°3,4,5 and a step of 6 for columns n°6,7,8
					// So 3*inc with inc = {0;2} ; inc is independant from i,l,k,p.
					// And then k = 1, so inc = 0 for restart. And also for k = 2.

					if(inc == 2) { inc = 0; }
					if(i+l == 2) { ++inc; }

					A(4*p + 2*i + l, 9*k + (i+l) + 3*inc) = L1(p,k) * (  L2(p,0)*L3(p,2)  -  L2(p,2)*L3(p,2)  -  L2(p,i)*L3(p,l)  +  L2(p,2)*L3(p,l)  );


				}
			}

		}

	}

	return A;
}


Eigen::MatrixXi Tensor3d::aroundMatrixA(Eigen::MatrixXd &A) {
	Eigen::MatrixXi newA(28,27);
	for(int i = 0; i < 28; ++i) {
		for(int j = 0; j < 27; ++j) {
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

 
 
 
 
 
 