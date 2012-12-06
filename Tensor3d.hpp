#ifndef __TENSOR3D_H__
#define __TENSOR3D_H__

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
		void hydrate(MatrixXd &L, MatrixXd &M, MatrixXd &N);
		MatrixXd getL();
		MatrixXd getM();
		MatrixXd getN();
		void setL(MatrixXd A);
		void setM(MatrixXd B);
		void setN(MatrixXd C);
				
		/* Access at element of Tensor, T(i,j,k)
 		 * return double
 		 */
		double operator()(unsigned int i, unsigned int j, unsigned int k) {
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
				break	;	
			}	
			
			return res;
		}
	
};


#endif //__TENSOR3D_H__