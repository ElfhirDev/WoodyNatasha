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
 