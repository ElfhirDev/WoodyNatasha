/** Trifocal Tensor tools
 * Functions here are dedicated for this project.
 * They aren't really re-usable, their name and signature are dedicated
 * to this project.
 *
 */

#include "ttt.hpp"

void appendMatrix(Eigen::MatrixXd &list, int x, int y) {
	int newSizeRow = list.rows() + 1;
  list.conservativeResize(newSizeRow, 3);
  list.row(newSizeRow - 1) << x, y, 1;
}
