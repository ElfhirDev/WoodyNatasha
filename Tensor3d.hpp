#ifndef __TENSOR3_H__
#define __TENSOR3_H__

#include "MathIO.hpp"
#include "Eigen/Dense" 


class Tensor3d {
	
	public:
		Tensor3();
		Tensor3(MatrixXd);
		int operator()(unsigned int i, unsigned int j, unsigned int k);	
		float operator()(unsigned int i, unsigned int j, unsigned int k);
		
		void hydrate(MatrixXd &L, MatrixXd &M, MatrixXd &N);	
		
	protected:
	private:
		MatrixXi A;
		MatrixXi B;
		MatrixXi C; 
		MatrixXd L;
		MatrixXd M;
		MatrixXd N; 
};

/* Access at element of Tensor, T(i,j,k)
 * return int
 */
int Tensor3::operator()(unsigned int i, unsigned int j, unsigned int k) 
{
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

/* Access at element of Tensor, T(i,j,k)
 * return float
 */
float Tensor3::operator()(unsigned int i, unsigned int j, unsigned int k) 
{
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


#endif //__TENSOR_H__