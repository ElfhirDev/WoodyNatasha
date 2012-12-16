#include <iostream>
#include <typeinfo>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "Eigen/SVD"

#include "MathIO.hpp"
#include "draw.hpp"
#include "ttt.hpp"
#include "Tensor3d.hpp"

using namespace std;


int main(int argc, char *argv[])
{
  // init SDL image
  if(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) == -1){
    std::cerr << "error IMG_Init" << std::endl;
    return (EXIT_FAILURE);
  }

  // load some images
  SDL_Surface *image1 = IMG_Load("input/image1.jpg");
  SDL_Surface *image2 = IMG_Load("input/image2.jpg");
  SDL_Surface *image3 = IMG_Load("input/image3.jpg");
  if(image1 == 0 || image2 == 0 || image3 == 0){
    std::cerr << "error loading images" << std::endl;
    cerr << "    Be sure your image are in input folder," << endl;
    cerr << "and you call them like this 'input/image.jpg'." << endl;
    cerr << "The code in if(argc>=3) scope may be not good, about at line 24 in main.cpp" << endl << endl;
    return (EXIT_FAILURE);
  }

  // init screen surface
  if(SDL_Init(SDL_INIT_VIDEO) == -1){
    std::cerr << "error SDL_Init" << std::endl;
    return (EXIT_FAILURE);
  }

  // create a screen surface that will include the 3 images
  SDL_Surface *screen = SDL_SetVideoMode(image1->w + image2->w + image3->w, image1->h, 32, SDL_HWSURFACE);
  SDL_WM_SetCaption("Trifocal Tensor", NULL);

  // bibd the images on the surface  
  SDL_Rect imageOffset;
  imageOffset.x = 0;
  imageOffset.y = 0;
  SDL_BlitSurface(image1, NULL, screen, &imageOffset);
  imageOffset.x = image1->w;
  SDL_BlitSurface(image2, NULL, screen, &imageOffset);
  imageOffset.x = image1->w + image2->w;
  SDL_BlitSurface(image3, NULL, screen, &imageOffset);

  // load the point lists
  Eigen::MatrixXd list1;
  Eigen::MatrixXd list2;
  Eigen::MatrixXd list3;
  
  // load 
  const char* nameList1 = "input/list1.list";
  const char* nameList2 = "input/list2.list";
  const char* nameList3 = "input/list3.list";
  
  // see MathIO.hpp 
  kn::loadMatrix(list1, nameList1);
  kn::loadMatrix(list2, nameList2);
  kn::loadMatrix(list3, nameList3);

  // MatrixX where the user will draw - but not the third, it's trifocalTensor who will do it.
  Eigen::MatrixXd list_user1;
  Eigen::MatrixXd list_user2;
  Eigen::MatrixXd list_user3;

  const char* nameList_user1 = "input/list-user/list1.list";
  const char* nameList_user2 = "input/list-user/list2.list";
  const char* nameList_user3 = "input/list-user/list3.list";

  kn::loadMatrix(list_user1, nameList_user1);
  kn::loadMatrix(list_user2, nameList_user2);
  kn::loadMatrix(list_user3, nameList_user3); 

  // some colors
  Uint32 red  = 0xffff0000;
  Uint32 blue = 0xff0000ff;
  Uint32 yellow = 0xffffff00;

 // Uint32 alpha = SDL_MapRGBA(image1->format, 255, 255, 255, 255);

  SDL_SetAlpha(image1, SDL_SRCALPHA, SDL_ALPHA_TRANSPARENT);



  // display everything
  SDL_Flip(screen);
  
	bool done = true;
	bool listWrite = false;    
	double xClick;
	double yClick;
	SDL_Event event;
	
	// ---------- Test zone --------------	
	Tensor3d Titi(list1, list2, list3);
	Titi.printTensor3d();

	// Matrix A ctor : 28rows, 27 col. Diagonaly filled ; out of it, initialized with 0
	Eigen::MatrixXd A = Titi.buildMatrixA(list1, list2, list3);

/*
	cout << "   A matrix : " << endl;
	for(int i = 0; i<28; ++i) {
		for(int j = 0; j<27; ++j) {
			cout << " " << A(i,j);
		}
		cout << endl;
	}
*/	
	// SVD decomposition of A
	JacobiSVD<MatrixXd> svd(A, ComputeThinU | ComputeThinV);

	// Creation of Vector 28 elts = 0;
	VectorXd ZeroZero = MatrixXd::Zero(28,1);

	// Solving equations with least square
	//
	MatrixXd t =  svd.solve(ZeroZero);
	
	//VectorXd t = svd.matrixU();


	cout << "List1 :" << list1 << endl;
	cout << "List2 :" << list2 << endl;
	cout << "List3 :" << list3 << endl;
	
	while (done) {

		for(int i=0; i<list1.rows(); ++i) {
		  	if(i<7) {
		    	fill_circle(screen, list1(i,0), list1(i,1), 0, red);
		    }
		    else
		    	fill_circle(screen, list1(i,0), list1(i,1), 3, red);
		}

		// draw points on image2
		for(int i=0; i<list2.rows(); ++i) {
			if(i<7) {
				fill_circle(screen, list2(i,0)+image1->w, list2(i,1), 0, blue);
			}
			else
				fill_circle(screen, list2(i,0)+image1->w, list2(i,1), 3, blue);
		}
		
		// draw points on image3
		for(int i=0; i<list3.rows(); ++i) {
		    if(i<7) {
		    	fill_circle(screen, list3(i,0)+image1->w+image2->w, list3(i,1), 0, yellow);
			}
			else
				fill_circle(screen, list3(i,0)+image1->w+image2->w, list3(i,1), 3, yellow);
		}

		

		// display everything
  		SDL_Flip(screen);
		
		SDL_WaitEvent(&event);
		switch(event.type) {
		    case SDL_QUIT:
		        done = false;
		    break;
		    
		    case SDL_KEYDOWN :
					switch(event.key.keysym.sym) {
						case 'q':
						case SDLK_DELETE :
							done = false;
						break;
						
						case 'l':
							
  							
							if(listWrite == false){
								listWrite = true;								
								cout << "Beginning writting mode" << endl;
							}
							else {
  								listWrite = false;
								cout << "Ending writting mode" << endl;
								
							}
							
						break;

						case 'o':
							cout << "Je suis une variable" << endl;
							
							

						break;
						
						default:
						break;
					}
					
				case SDL_MOUSEBUTTONDOWN :
					if(event.button.state == SDL_PRESSED && listWrite == true) {
						xClick = (double)event.button.x;
						yClick = (double)event.button.y;
						
						switch(event.button.button) {
							case SDL_BUTTON_LEFT:
								
								if(xClick <= 399) {

									appendMatrixXd(list1, xClick, yClick);
									appendMatrixXd(list_user1, xClick, yClick);

									cout << "Point add to list1" << endl;
									
									cout << list1 << endl;


								}
								
								else if(xClick >= 400 && xClick <= 799) {
									
									xClick -= 400; // correctif;
									
									appendMatrixXd(list2, xClick, yClick);
									appendMatrixXd(list_user2, xClick, yClick);
									
									cout << "Point add to list2" << endl;
									
									cout << list2 << endl;
								}
								else if(xClick >= 800) {
									cout << "You should click on the 1s and 2nd images," << endl << "else invert images in the folder." << endl;
								}
								  							

							break;
								
							case SDL_BUTTON_RIGHT:
															
								cout << "xClick: " << xClick << "  yClick: " << yClick << endl;
								
							break;		
							
							default:
							break;			
						}
					}
					else if(event.button.state == SDL_PRESSED && listWrite == false) {						
						xClick = (double)event.button.x;
						yClick = (double)event.button.y;
						cout << "xClick: " << xClick << "  yClick: " << yClick << endl;
					}
					else {}
				break;
					
				default:
				break;
				
		}	// end switch(event)	
	} // end while(done)  
  
  // save a list

  kn::saveMatrix(list_user1,"input/save/savelist1.list");
  kn::saveMatrix(list_user2,"input/save/savelist2.list");
  kn::saveMatrix(list_user3,"input/save/savelist3.list");

  kn::saveMatrix(A, "input/save/A.list");
  kn::saveMatrix(t, "input/save/t.list");

  // quit sdl
  SDL_FreeSurface(image1); 
  SDL_FreeSurface(image2); 
  SDL_FreeSurface(image3); 
  IMG_Quit();
  SDL_Quit();

  return EXIT_SUCCESS;
}



