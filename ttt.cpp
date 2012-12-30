/** Trifocal Tensor tools
 * Functions here are dedicated for this project.
 * They aren't really re-usable, their name and signature are dedicated
 * to this project.
 *
 */

#include "ttt.hpp"

void appendMatrixXd(Eigen::MatrixXd &list, int x, int y) {
	int newSizeRow = list.rows() + 1;
	list.conservativeResize(newSizeRow, 3);
	list.row(newSizeRow - 1) << x, y, 1;
}

void appendMatrixXi(Eigen::MatrixXi &list, int x, int y) {
	int newSizeRow = list.rows() + 1;
	list.conservativeResize(newSizeRow, 3);
	list.row(newSizeRow - 1) << x, y, 1;
}


void print_help() {

	std::cout << std::endl << std::endl << std::endl;

	std::cout << "      Help page -- Trifocal Tensor -- WoodyNatasha    " << std::endl << std::endl << std::endl;

	std::cout << "      This program runs a trifocal tensor, aiming to locate points on an image," << std::endl << std::endl;
	std::cout << "      knowing two previous points on two other images." << std::endl;

	std::cout << "   You can runs this program with './trifocal' command, it will charge" << std::endl; 
	std::cout << "   3 images samples that you can test." << std::endl << std::endl;

	std::cout << "   Otherwise, you can runs this program with" << std::endl;
	std::cout << "   './trifocal image1.jpg image2.jpg image3.jpg ' command." << std::endl;

	std::cout << "   Use the name you want and have for these images." << std::endl;
	std::cout << "   WARNING : These images should be in the 'input/' directory of this program; " << std::endl;
	std::cout << "   Be sure using .jpg or .png" << std::endl;
	std::cout << "   WARNING : These images should be 400px * 300px." << std::endl << std::endl << std::endl;

	std::cout << "   However, running this program with other images would" << std::endl;
	std::cout << "   be wrong if you don't use pre-built lists points." << std::endl;
	std::cout << "   You can runs this programm with :" << std::endl;
	std::cout << "   './trifocal image1.jpg image2.jpg image3.jpg list1.list list2.list list3.list ' command." << std::endl;
	std::cout << "   WARNING : These lists should be in the 'input/list_user/' directory of this program;" << std::endl;
	std::cout << std::endl << std::endl;
	std::cout << "   When the program runs:  " << std::endl;
	std::cout << "   Press 'q' or 'suppr' or 'Echap' for closing it." << std::endl;
	std::cout << ">>>Press 'l' for clicking on images." << std::endl;
	std::cout << "   WARNING : you should click on one image then on the other." << std::endl;
	std::cout << "   Press 'o' for showing a joke." << std::endl;
	std::cout << std::endl << std::endl;

}
