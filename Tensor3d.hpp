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

		double getL(unsigned int, unsigned int);

		void setL(MatrixXd L1);
		void setM(MatrixXd L2);
		void setN(MatrixXd L3);

		void setLij(unsigned int i, unsigned int j, double tvalue);
		void setMij(unsigned int i, unsigned int j, double tvalue);
		void setNij(unsigned int i, unsigned int j, double tvalue);
		
		int getRows();
		
		// Acces to our tensor element.
		double getVal(unsigned int i, unsigned int j, unsigned int k);

		// Fill the Tensor correctly by providing a Vector, which should havee 27 rows.
		void setVal(VectorXd t);
		
		void printTensor3d();
				

 		// Acces to our tensor element.
		double operator()(unsigned int i, unsigned int j, unsigned int k);


		Eigen::MatrixXd buildMatrixA(MatrixXd L1, MatrixXd L2, MatrixXd L3);

		Eigen::MatrixXd transfertTo3(MatrixXd list1, MatrixXd list2);
		Eigen::MatrixXd transfertTo1(MatrixXd list2, MatrixXd list3);
		Eigen::MatrixXd transfertTo2(MatrixXd list1, MatrixXd list3);

};


#endif //__TENSOR3D_H__