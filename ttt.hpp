#ifndef __TTT__
#define __TTT__

#include "Eigen/Dense"

/** Add a row, initialized at x,y, and  1 
 *  param The list to modify
 *  param the x and y coords, integers.
 *
 */
void appendMatrix(Eigen::MatrixXd &list, int x, int y);

#endif //__TTT__