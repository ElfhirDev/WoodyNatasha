#ifndef __TENSOR3D_H__
#define __TENSOR3D_H__

#include <iostream>
#include "MathIO.hpp"
#include "Eigen/Dense" 


class Tensor3d {

	private:
		
	protected:
	
		MatrixXd L;
		MatrixXd M;
		MatrixXd N; 
		
	
	public:
		Tensor3d();
		Tensor3d(MatrixXd A, MatrixXd B, MatrixXd C);
		
		MatrixXd getL();
		MatrixXd getM();
		MatrixXd getN();
		void setL(MatrixXd A);
		void setM(MatrixXd B);
		void setN(MatrixXd C);
		
		int getRows();
		
		double getVal(unsigned int i, unsigned int j, unsigned int k);
		
		void printTensor3d();
				
		/* Access at element of Tensor, T(i,j,k)
 		 * return double
 		 */
		double operator()(unsigned int i, unsigned int j, unsigned int k);

		Eigen::MatrixXd buildMatrixA();
		Eigen::MatrixXi aroundMatrixA(Eigen::MatrixXd &A);

		Eigen::MatrixXi transfert(MatrixXi list1, MatrixXi list2);
};


#endif //__TENSOR3D_H__