/*
 *
 *
 *
 */
 
#include "Tensor3d.hpp"
#include "MathIO.hpp"

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

void Tensor3d::setLij(unsigned int i, unsigned int j, double tvalue) {L(i,j) = tvalue;}
void Tensor3d::setMij(unsigned int i, unsigned int j, double tvalue) {M(i,j) = tvalue;}
void Tensor3d::setNij(unsigned int i, unsigned int j, double tvalue) {N(i,j) = tvalue;}

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

void Tensor3d::setVal(VectorXd t) {
	for(int i = 0; i<27 ; ++i) {
		if(i<9)
			if(i<3)
				setLij(0,i,t(i));
			else if(i >= 3 && i < 6)
				setLij(1,i-3,t(i));
			else if(i >= 6 && i < 9)
				setLij(2,i-6,t(i));
			else{}

		else if(i >= 9 && i<18)
			if(i >= 9 && i<12)
				setMij(0,i-9,t(i));
			else if(i >= 12 && i < 15 )
				setMij(1,i-12,t(i));
			else if(i >= 15 && i < 15)
				setMij(2,i-15,t(i));
			else{}
			
		else if(i >= 18 && i<27) 
			if(i >= 18 && i<21)
				setNij(0,i-18,t(i));
			else if(i >= 21 && i < 24)
				setNij(1,i-21,t(i));
			else if(i >= 24 && i < 27)
				setNij(2,i-24,t(i));
			else{}
		else {}
	}
	
	return;
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
	Eigen::MatrixXd A = MatrixXd::Zero(28,27);
	

	// For each points
	for(int p = 0; p<7; ++p) {

		// For each coords of a points - seems like playing with x,y,z
		for(int k = 0; k<3 ; ++k) {

			// 4 equations - seems like playing with x and y values combination - xx, xy, yx, yy -
			for(int i = 0; i<2; ++i) {
				for(int l = 0; l<2; ++l) {

					if(k == 0) {
						if(i==0 && l==0) {
							A(4*p + 2*i + l, 6) = L1(p,k) * (  L2(p,i)*L3(p,2) );
							A(4*p + 2*i + l, 0) = L1(p,k) * ( -L2(p,2)*L3(p,2) );
							A(4*p + 2*i + l, 8) = L1(p,k) * ( -L2(p,i)*L3(p,l) );
							A(4*p + 2*i + l, 2) = L1(p,k) * (  L2(p,2)*L3(p,l) );
						}
						else if(i==0 && l==1) {
							A(4*p + 2*i + l, 7) = L1(p,k) * (  L2(p,i)*L3(p,2) );
							A(4*p + 2*i + l, 1) = L1(p,k) * ( -L2(p,2)*L3(p,2) );
							A(4*p + 2*i + l, 8) = L1(p,k) * ( -L2(p,i)*L3(p,l) );
							A(4*p + 2*i + l, 2) = L1(p,k) * (  L2(p,2)*L3(p,l) );
						}
						else if(i==1 && l==0) {
							A(4*p + 2*i + l, 6) = L1(p,k) * (  L2(p,i)*L3(p,2) );
							A(4*p + 2*i + l, 3) = L1(p,k) * ( -L2(p,2)*L3(p,2) );
							A(4*p + 2*i + l, 8) = L1(p,k) * ( -L2(p,i)*L3(p,l) );
							A(4*p + 2*i + l, 5) = L1(p,k) * (  L2(p,2)*L3(p,l) );	
						}
						else if(i==1 && l==1) {
							A(4*p + 2*i + l, 7) = L1(p,k) * (  L2(p,i)*L3(p,2) );
							A(4*p + 2*i + l, 4) = L1(p,k) * ( -L2(p,2)*L3(p,2) );
							A(4*p + 2*i + l, 8) = L1(p,k) * ( -L2(p,i)*L3(p,l) );
							A(4*p + 2*i + l, 5) = L1(p,k) * (  L2(p,2)*L3(p,l) );	
						}
						else {}
					}

					else if(k==1) {
						if(i==0 && l==0) {
							A(4*p + 2*i + l, 15) = L1(p,k) * (  L2(p,i)*L3(p,2) );
							A(4*p + 2*i + l,  9) = L1(p,k) * ( -L2(p,2)*L3(p,2) );
							A(4*p + 2*i + l, 17) = L1(p,k) * ( -L2(p,i)*L3(p,l) );
							A(4*p + 2*i + l, 11) = L1(p,k) * (  L2(p,2)*L3(p,l) );
						}
						else if(i==0 && l==1) {
							A(4*p + 2*i + l, 16) = L1(p,k) * (  L2(p,i)*L3(p,2) );
							A(4*p + 2*i + l, 10) = L1(p,k) * ( -L2(p,2)*L3(p,2) );
							A(4*p + 2*i + l, 17) = L1(p,k) * ( -L2(p,i)*L3(p,l) );
							A(4*p + 2*i + l, 11) = L1(p,k) * (  L2(p,2)*L3(p,l) );
						}
						else if(i==1 && l==0) {
							A(4*p + 2*i + l, 15) = L1(p,k) * (  L2(p,i)*L3(p,2) );
							A(4*p + 2*i + l, 12) = L1(p,k) * ( -L2(p,2)*L3(p,2) );
							A(4*p + 2*i + l, 17) = L1(p,k) * ( -L2(p,i)*L3(p,l) );
							A(4*p + 2*i + l, 14) = L1(p,k) * (  L2(p,2)*L3(p,l) );	
						}
						else if(i==1 && l==1) {
							A(4*p + 2*i + l, 16) = L1(p,k) * (  L2(p,i)*L3(p,2) );
							A(4*p + 2*i + l, 13) = L1(p,k) * ( -L2(p,2)*L3(p,2) );
							A(4*p + 2*i + l, 17) = L1(p,k) * ( -L2(p,i)*L3(p,l) );
							A(4*p + 2*i + l, 14) = L1(p,k) * (  L2(p,2)*L3(p,l) );	
						}
						else {}

					}		

					else if(k==2) {
						if(i==0 && l==0) {
							A(4*p + 2*i + l, 24) = L1(p,k) * (  L2(p,i)*L3(p,2) );
							A(4*p + 2*i + l, 18) = L1(p,k) * ( -L2(p,2)*L3(p,2) );
							A(4*p + 2*i + l, 26) = L1(p,k) * ( -L2(p,i)*L3(p,l) );
							A(4*p + 2*i + l, 20) = L1(p,k) * (  L2(p,2)*L3(p,l) );
						}
						else if(i==0 && l==1) {
							A(4*p + 2*i + l, 25) = L1(p,k) * (  L2(p,i)*L3(p,2) );
							A(4*p + 2*i + l, 19) = L1(p,k) * ( -L2(p,2)*L3(p,2) );
							A(4*p + 2*i + l, 26) = L1(p,k) * ( -L2(p,i)*L3(p,l) );
							A(4*p + 2*i + l, 20) = L1(p,k) * (  L2(p,2)*L3(p,l) );
						}
						else if(i==1 && l==0) {
							A(4*p + 2*i + l, 24) = L1(p,k) * (  L2(p,i)*L3(p,2) );
							A(4*p + 2*i + l, 21) = L1(p,k) * ( -L2(p,2)*L3(p,2) );
							A(4*p + 2*i + l, 26) = L1(p,k) * ( -L2(p,i)*L3(p,l) );
							A(4*p + 2*i + l, 23) = L1(p,k) * (  L2(p,2)*L3(p,l) );	
						}
						else if(i==1 && l==1) {
							A(4*p + 2*i + l, 25) = L1(p,k) * (  L2(p,i)*L3(p,2) );
							A(4*p + 2*i + l, 22) = L1(p,k) * ( -L2(p,2)*L3(p,2) );
							A(4*p + 2*i + l, 26) = L1(p,k) * ( -L2(p,i)*L3(p,l) );
							A(4*p + 2*i + l, 23) = L1(p,k) * (  L2(p,2)*L3(p,l) );	
						}
						else {}
					}
					else {}		


				} // end for l
			} // end for i
 
		} // end for k

	} // end for p

	return A;
}

// not used.
Eigen::MatrixXi Tensor3d::aroundMatrixA(Eigen::MatrixXd &A) {
	Eigen::MatrixXi newA(28,27);
	for(int i = 0; i < 28; ++i) {
		for(int j = 0; j < 27; ++j) {
			newA(i,j) = (int)A(i,j);
		}
	}

	return newA;
}




Eigen::MatrixXd Tensor3d::transfertTo1(Eigen::MatrixXd LI, Eigen::MatrixXd LJ) {
	Eigen::MatrixXd A2 = MatrixXd::Zero(4,2);
	Eigen::VectorXd X2 = MatrixXd::Zero(2,1);
	Eigen::VectorXd b = MatrixXd::Zero(4,1);

	int end = LI.rows() - 1 ;
	
	for(int i = 0; i<2; ++i) {
		for(int l = 0; l<2; ++l) {
				
			if(i==0 && l==0) {
				A2(2*i + l, 0) = ( LJ(end,2) * ( LI(end,i)*getVal(2,l,0) - LI(end,2)*getVal(i,l,0 ) ) );
				A2(2*i + l, 1) = ( LJ(end,2) * ( LI(end,i)*getVal(2,l,1) - LI(end,2)*getVal(i,l,1 ) ) );
			}
			else if(i==0 && l==1) {
				A2(2*i + l, 0) = ( LJ(end,2) * ( LI(end,i)*getVal(2,l,0) - LI(end,2)*getVal(i,l,0 ) ) );
				A2(2*i + l, 1) = ( LJ(end,2) * ( LI(end,i)*getVal(2,l,1) - LI(end,2)*getVal(i,l,1 ) ) );
			}
			else if(i==1 && l==0) {
				A2(2*i + l, 0) = ( LJ(end,2) * ( LI(end,i)*getVal(2,l,0) - LI(end,2)*getVal(i,l,0 ) ) );
				A2(2*i + l, 1) = ( LJ(end,2) * ( LI(end,i)*getVal(2,l,1) - LI(end,2)*getVal(i,l,1 ) ) );
			}
			else if(i==1 && l==1) {
				A2(2*i + l, 0) = ( LJ(end,2) * ( LI(end,i)*getVal(2,l,0) - LI(end,2)*getVal(i,l,0 ) ) );
				A2(2*i + l, 1) = ( LJ(end,2) * ( LI(end,i)*getVal(2,l,1) - LI(end,2)*getVal(i,l,1 ) ) );
			}
			else {}

			b(2*i + l) =  -( LI(end,i)*LJ(end,2)*getVal(2,l,2) - LI(end,2)*LJ(end,2)*getVal(i,l,2) - LI(end,i)*LJ(end,l)*getVal(2,2,2) + LI(end,2)*LJ(end,l)*getVal(i,2,2) );
		}
			
	}



	// SVD decomposition of A2
	JacobiSVD<MatrixXd> svd(A2, ComputeThinU | ComputeThinV);

	X2 = svd.solve(b);
	
	// Not necessary. Just for checking.
	kn::saveMatrix(A2, "input/save/A2.list");
	kn::saveMatrix(X2, "input/save/X2-transfert.list");
	kn::saveMatrix(b, "input/save/b.list");


	return X2;
}


/*

// Other version of transfertTo1, not bad but differently precise.
// 
Eigen::MatrixXd Tensor3d::transfertTo1(Eigen::MatrixXd LI, Eigen::MatrixXd LJ) {
	Eigen::MatrixXd A = MatrixXd::Zero(4,2);
	Eigen::VectorXd X2 = MatrixXd::Zero(2,1);
	Eigen::VectorXd b = MatrixXd::Zero(4,1);

	int end = LI.rows() - 1 ;

	for(int i = 0; i<2; ++i) {
		for(int l = 0; l<2; ++l) {
				
			if(i==0 && l==0) {
				A(2*i + l, 0) = ( LI(end,i)*LJ(end,2)*getVal(2,l,0) - LI(end,2)*LJ(end,2)*getVal(i,l,0) - LI(end,i)*LJ(end,l)*getVal(2,2,0) + LI(end,2)*LJ(end,l)*getVal(i,2,0) );
				A(2*i + l, 1) = ( LI(end,i)*LJ(end,2)*getVal(2,l,1) - LI(end,2)*LJ(end,2)*getVal(i,l,1) - LI(end,i)*LJ(end,l)*getVal(2,2,1) + LI(end,2)*LJ(end,l)*getVal(i,2,1) );
			}
			else if(i==0 && l==1) {
				A(2*i + l, 0) = ( LI(end,i)*LJ(end,2)*getVal(2,l,0) - LI(end,2)*LJ(end,2)*getVal(i,l,0) - LI(end,i)*LJ(end,l)*getVal(2,2,0) + LI(end,2)*LJ(end,l)*getVal(i,2,0) );
				A(2*i + l, 1) = ( LI(end,i)*LJ(end,2)*getVal(2,l,1) - LI(end,2)*LJ(end,2)*getVal(i,l,1) - LI(end,i)*LJ(end,l)*getVal(2,2,1) + LI(end,2)*LJ(end,l)*getVal(i,2,1) );			}
			else if(i==1 && l==0) {
				A(2*i + l, 0) = ( LI(end,i)*LJ(end,2)*getVal(2,l,0) - LI(end,2)*LJ(end,2)*getVal(i,l,0) - LI(end,i)*LJ(end,l)*getVal(2,2,0) + LI(end,2)*LJ(end,l)*getVal(i,2,0) );
				A(2*i + l, 1) = ( LI(end,i)*LJ(end,2)*getVal(2,l,1) - LI(end,2)*LJ(end,2)*getVal(i,l,1) - LI(end,i)*LJ(end,l)*getVal(2,2,1) + LI(end,2)*LJ(end,l)*getVal(i,2,1) );			}
			else if(i==1 && l==1) {
				A(2*i + l, 0) = ( LI(end,i)*LJ(end,2)*getVal(2,l,0) - LI(end,2)*LJ(end,2)*getVal(i,l,0) - LI(end,i)*LJ(end,l)*getVal(2,2,0) + LI(end,2)*LJ(end,l)*getVal(i,2,0) );
				A(2*i + l, 1) = ( LI(end,i)*LJ(end,2)*getVal(2,l,1) - LI(end,2)*LJ(end,2)*getVal(i,l,1) - LI(end,i)*LJ(end,l)*getVal(2,2,1) + LI(end,2)*LJ(end,l)*getVal(i,2,1) );			}
			else {}

			b(2*i + l) =  - ( LI(end,i)*LJ(end,2)*getVal(2,l,2) - LI(end,2)*LJ(end,2)*getVal(i,l,2) - LI(end,i)*LJ(end,l)*getVal(2,2,2) + LI(end,2)*LJ(end,l)*getVal(i,2,2) );
		}
			
	}



	// SVD decomposition of A2
	JacobiSVD<MatrixXd> svd(A, ComputeThinU | ComputeThinV);

	X2 = svd.solve(b);
	
	kn::saveMatrix(A, "input/save/A.list");
	kn::saveMatrix(X2, "input/save/X2-transfert.list");
	kn::saveMatrix(b, "input/save/b.list");


	return X2;
}

*/




 Eigen::MatrixXd Tensor3d::transfertTo3(Eigen::MatrixXd LI, Eigen::MatrixXd LJ) {
 	Eigen::MatrixXd A = MatrixXd::Zero(4,2);


 	return A;
 }

 Eigen::MatrixXd Tensor3d::transfertTo2(Eigen::MatrixXd LI, Eigen::MatrixXd LJ) {
 	Eigen::MatrixXd A = MatrixXd::Zero(4,2);

 	return A;
 }
 
 
 
 
 