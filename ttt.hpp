#ifndef __TTT__
#define __TTT__

#include "Eigen/Dense"
#include <iostream>

/** Add a row, initialized at x,y, and  1      doubles
 *  param The list to modify
 *  param the x and y coords, integers.
 *
 */
void appendMatrixXd(Eigen::MatrixXd &list, int x, int y);

/** Add a row, initialized at x,y, and  1      integers
 *  param The list to modify
 *  param the x and y coords, integers.
 *
 */
void appendMatrixXi(Eigen::MatrixXi &list, int x, int y);


/** Show help when executing with h option :
 *	" ./trifocal h    "
 *
 */
void print_help();


#endif //__TTT__