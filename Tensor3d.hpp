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

		MatrixXd Adouble;
		MatrixXi A;
		
	
	public:
		Tensor3d();
		Tensor3d(MatrixXd L1, MatrixXd L2, MatrixXd L3);
		
		MatrixXd getL();
		MatrixXd getM();
		MatrixXd getN();
		void setL(MatrixXd L1);
		void setM(MatrixXd L2);
		void setN(MatrixXd L3);
		
		int getRows();
		
		double getVal(unsigned int i, unsigned int j, unsigned int k);
		
		void printTensor3d();
				
		/* Access at element of Tensor, T(i,j,k)
 		 * return double
 		 */
		double operator()(unsigned int i, unsigned int j, unsigned int k);

		Eigen::MatrixXd buildMatrixA(MatrixXd L1, MatrixXd L2, MatrixXd L3);
		Eigen::MatrixXi aroundMatrixA(Eigen::MatrixXd &A);

		Eigen::MatrixXi transfert(MatrixXi list1, MatrixXi list2);
};


#endif //__TENSOR3D_H__