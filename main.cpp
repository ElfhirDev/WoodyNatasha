
#include <typeinfo>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <cstring>

#include "Eigen/SVD"

#include "MathIO.hpp"
#include "draw.hpp"
#include "ttt.hpp"
#include "Tensor3d.hpp"

using namespace std;


int main(int argc, char *argv[]) {

	// init SDL image
	if(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) == -1){
		std::cerr << "error IMG_Init" << std::endl;
		return (EXIT_FAILURE);
	}

	// load some images
	SDL_Surface *image1;
	SDL_Surface *image2;
	SDL_Surface *image3;
	
	string input1("input/");
  	string input2("input/");
  	string input3("input/");

  if(argc >= 3 && argc <=6) {

  	input1.append(argv[1]);
  	input2.append(argv[2]);
  	input3.append(argv[3]);


  	cout << input1 << endl;


	image1 = IMG_Load(input1.c_str());
  	image2 = IMG_Load(input2.c_str());
  	image3 = IMG_Load(input3.c_str());
  }
  else if (argc == 2) {
  	string help(argv[1]);

  	string h = "-h";

  	if (help.compare(h) == 1) {

  		print_help();
  	}

  	input1.append("image1.jpg");
  	input2.append("image2.jpg");
  	input3.append("image3.jpg");

	image1 = IMG_Load(input1.c_str());
  	image2 = IMG_Load(input2.c_str());
  	image3 = IMG_Load(input3.c_str());
  }

  else {

  	input1.append("image1.jpg");
  	input2.append("image2.jpg");
  	input3.append("image3.jpg");

	image1 = IMG_Load(input1.c_str());
  	image2 = IMG_Load(input2.c_str());
  	image3 = IMG_Load(input3.c_str());
  }

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
  
  // see MathIO.hpp ; it loads the points from a file in matrix of "list"
  kn::loadMatrix(list1, nameList1);
  kn::loadMatrix(list2, nameList2);
  kn::loadMatrix(list3, nameList3);

  // MatrixX where the user will add xClick and yClick and 1 at the end. One of them will be filled by transfert.
  // For the beginning it's list_user3.
  Eigen::MatrixXd list_user1;
  Eigen::MatrixXd list_user2;
  Eigen::MatrixXd list_user3;

  // Useless list_user ... 
  const char* nameList_user1 = "input/list-user/list1.list";
  const char* nameList_user2 = "input/list-user/list2.list";
  const char* nameList_user3 = "input/list-user/list3.list";

  kn::loadMatrix(list_user1, nameList_user1);
  kn::loadMatrix(list_user2, nameList_user2);
  kn::loadMatrix(list_user3, nameList_user3); 

  // some colors ; used in fill_circle, set_pixel ; hexadecimal as webcolor.
  Uint32 red  = 0xffff0000;
  Uint32 blue = 0xff0000ff;
  Uint32 yellow = 0xffffff00;
  Uint32 cream = 0xffe6e6fa;

 // Old tentative to put pixel transparent. Not effective, but au cas où.
 // Uint32 alpha = SDL_MapRGBA(image1->format, 255, 255, 255, 255);

  // idem.
  SDL_SetAlpha(image1, SDL_SRCALPHA, SDL_ALPHA_TRANSPARENT);



  // display everything
  SDL_Flip(screen);
  
  	// done for while render, listWrite for right to clic - type 'l'
    // count1 and count2 for the right to do the transfer : not before clicking on the 2 first images.
  	// temp1 and temp2 for testing something but ...
	bool done = true;
	bool listWrite = false;    
	double xClick;
	double yClick;
	int count1 = 0;
	int count2 = 0;
	int temp1 = 0;
	int temp2 = 0;
	SDL_Event event;
	
	// ---------- Test zone --------------	
	// Titi is our object Tensor3d.
	Tensor3d Titi(list1, list2, list3);
	

	// Matrix A ctor : 28rows, 27 col. Diagonaly filled ; out of it, initialized with 0
	// See Tensor3d.cpp
	Eigen::MatrixXd A = Titi.buildMatrixA(list1, list2, list3);


	// SVD decomposition of A
	// See Eigen3 doc
	JacobiSVD<MatrixXd> svd(A, ComputeThinU | ComputeThinV);
	
	VectorXd t = MatrixXd::Zero(27,1);

	
	for(int i = 0; i<27 ; ++i) {
		t(i) = svd.matrixV()(i,26);
	}
	

	// Set values in Tensor Titi for each Matrix L, M, N.
	Titi.setVal(t);

	// Titi.printTensor3d();

	VectorXd X2;

	
	while (done) {

		if(count1 > 0 && count2 > 0) {
			
			X2 = Titi.transfertTo1(list2, list3);


/*
			cout << "  svd2.matrixV rows : " << svd2.matrixV().rows() << "  svd2.matrixV cols : " << svd2.matrixV().cols() << endl;
			cout << "  svd2.matrixU rows : " << svd2.matrixU().rows() << "  svd2.matrixU cols : " << svd2.matrixU().cols() << endl;
*/	


			/*
			X2(0) = V(0,1);
			X2(1) = V(1,1);
			*/

			
			count1 = 0;
			count2 = 0;

			temp1 = X2(0);
			temp2 = X2(1);

			
			appendMatrixXd(list1, temp1, temp2);
			
		}

		for(int i=0; i<list1.rows(); ++i) {
		  	if(i<7) {
		    	fill_circle(screen, list1(i,0), list1(i,1), 0, red);
		    }
		    else
		    	//fill_circle(screen, list1(i,0), list1(i,1), 3, red);
		    	draw_grid(screen, list1(i,0), list1(i,1), cream);
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
			else {
				
				fill_circle(screen, list3(i,0)+image1->w+image2->w, list3(i,1), 3, yellow);
				
				
				
				//set_pixel(screen, list3(i,0)+image1->w+image2->w, list3(i,1), red);

			}
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

									cout << "Point add to list1" << endl;
									
									cout << list1 << endl;

									
								}
								
								else if(xClick >= 400 && xClick <= 799) {
									
									xClick -= 400; // correctif;
									
									appendMatrixXd(list2, xClick, yClick);
									
									cout << "Point add to list2" << endl;

									cout << list2 << endl;
									
									++count1;

								}
								else if(xClick >= 800) {

									xClick -= 800; // correctif;
									
									appendMatrixXd(list3, xClick, yClick);

									cout << list3 << endl;

									cout << "Point add to list2" << endl;

									++count2;
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
  
  kn::saveMatrix(X2, "input/save/X2.list");

  

  // quit sdl
  SDL_FreeSurface(image1); 
  SDL_FreeSurface(image2); 
  SDL_FreeSurface(image3); 
  IMG_Quit();
  SDL_Quit();  // it frees screen, so don't call "SDL_FreeSurface(screen);"

  return (EXIT_SUCCESS);
}



