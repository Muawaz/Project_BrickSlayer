//============================================================================
// Name        : brickSlayerITC.cpp
// Author      : Sibt ul Hussain
// Version     :
// Copyright   : (c) Reserved
// Description : Basic 2D game of Brick Slayer...
//============================================================================

#ifndef BSLAYER_CPP_
#define BSLAYER_CPP_
#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include<string>
#include<cmath> // for basic math functions such as cos, sin, sqrt
#include<sstream>
using namespace std;

//defining some MACROS

#define MAX(A,B) ((A) > (B) ? (A):(B)) // finds max of two numbers
#define MIN(A,B) ((A) < (B) ? (A):(B)) // find min of two numbers
#define ABS(A) ((A) < (0) ? -(A):(A))  // find ABS of a given number

// define some constants
// constant FPS (Frame per second) is  used to specify
// number of frames per second in your game.. if FPS is small 
// your objects will move slowly and if large your objects
// will move faster, see the Timer function below for further help

#define FPS 80 // frame per seconds

// define another constant to hold ASCII for Escape key.
#define KEY_ESC 27 // A

// define some colors as 2D arrays, we have five pre-defined colors here..
// you can add many more if you wish..

float colors[5][3] = { { 1 / 255.0, 164 / 255.0, 164 / 255.0 }, { 215 / 255.0, 0
		/ 255.0, 96 / 255.0 }, { 208 / 255.0, 209 / 255.0, 2 / 255.0 }, { 0
		/ 255.0, 161 / 255.0, 203 / 255.0 }, { 50 / 255.0, 116 / 255.0, 44
		/ 255.0 } };
int L = 350;
int H = 10;
// int Heights = 300;
// int lengths = 150;

float theta0 = 0;
float theta1 = 10;


int flag = 0 ;
const int size_x = 40;
const int size_y = 20;
int GO_UP = 2 ;
int mid_x = 400 ;
int mid_y = 35 ;
int x_axis = 790;
int y_axis = 590;
int base_x;
int base_y = 20;
float dev_x;
int dev_y = (-250 / (base_y - L)) * mid_y;

//ARRAY(x) and ARRAY(y) coordinates
int arr_length[80] ; int arr_height[60] ;
int heart_x[3]={715,730,745};
int heart_y[3]={570,570,570};
int temp = 0 ;

int Base_Flag = 0;
// BASE LEFT
int Base_Left = 0;
int Bound_Left = 0;
int Upper_Bound = 0;
int down_up = 0;	
int Bound_Right = 0;
int count = 0 ;

// BASE RIGHT
int Base_Right = 0;
int B_Right = 0;
int	U_Bound = 0;
int	B_Left = 0;
int	Bases_Left = 0;

// BASE UP

int Base_Up = 0;

// PREVIOUS MID X , Y
int Pre_mid_x = 100;
int Pre_mid_y = 35;
int Del_mid_x = 0;
int Del_mid_y = 0 ;

// BRICKS DETECTION :

int Brick_Up = 0;
int Brick_Down = 0;
int Brick_Left = 0;
int Brick_Right = 0;
int Del_Bricks_mid_x = 0;
int Del_Bricks_mid_y = 0;
float Pre_Bricks_mid_x = 0;
float Pre_Bricks_mid_y = 0;

// mids
int Brick_mid_x = 150;
int Brick_mid_y = 250;

const int Brick_Gap_x = 82; 
const int Brick_Gap_y = 32;

int coordinate_x = 0;
int coordinate_y = 0;
int vanish = 0;
int score = 0;
int lives = 3;
int restart = 0;
int a = 0;
int gamecontrol = 0 ;

const int speed_x = 3;
const int speed_y = 3;

string number ; 
// defining some utility functions...
/*
 * This function converts an input angle from degree to radians */
float Deg2rad(float degree) {
	return (degree / 180.0) * M_PI;
}
// seed the random numbers generator by current time (see the documentation of srand for further help)...
void InitRandomizer() {
	srand((unsigned int) time(0)); // time(0) returns number of seconds elapsed since January 1, 1970.
}
//This function returns a random value within the specified range of [rmin, rmax] ...
long GetRandInRange(const long &rmin, const long &rmax) {
	long range = rmax - rmin; // find the range
	long value = (rand() % (long) range) + rmin; // translate the generated number ...
//	cout << value << endl << flush;
	return value;
}

/*To draw a triangle we need three vertices with each vertex having 2-coordinates [x, y] and a color for the triangle.
 * This function takes 4 arguments first three arguments (3 vertices + 1 color) to
 * draw the triangle with the given color.
 * */
 void DrawString(int x, int y, const string & score, float * color) {
	//  A pointer to a font style..
	//  Fonts supported by GLUT are: GLUT_BITMAP_8_BY_13,
	//  GLUT_BITMAP_9_BY_15, GLUT_BITMAP_TIMES_ROMAN_10,
	//  GLUT_BITMAP_TIMES_ROMAN_24, GLUT_BITMAP_HELVETICA_10,
	//  GLUT_BITMAP_HELVETICA_12, and GLUT_BITMAP_HELVETICA_18.
	GLvoid *font_style = GLUT_BITMAP_TIMES_ROMAN_24;
	if (color)
		glColor3fv(color);
	glRasterPos3f(x, y, 1);
	//  Draw the characters one by one
	for (unsigned int i = 0; i < score.size(); i++)
		glutBitmapCharacter(font_style, score[i]);
}


void DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3,
		float color[]) {
	glColor3fv(color); // Set the triangle colour
	// ask library to draw triangle at given position...

	glBegin(GL_TRIANGLES);
	/*Draw triangle using given three vertices...*/
	glVertex4i(x1, y1, 0, 1);
	glVertex4i(x2, y2, 0, 1);
	glVertex4i(x3, y3, 0, 1);
	glEnd();
}
void DrawRectangle(int x , int y)
{
	DrawTriangle(x + 100, y, x, y + 10 , x , y, colors[4]);
	DrawTriangle(x + 100, y, x, y + 10 , x + 100  , y + 10, colors[4]);	
}

void LIVES (int x , int y ,int c)
{
	DrawTriangle(x + 10, y, x, y + 10 , x , y, colors[c]);
	DrawTriangle(x + 10, y, x, y + 10 , x + 10  , y + 10, colors[c]);	
}



void DrawBricks(int  x , int y , int c)
{
	DrawTriangle(x - 40 , y - 15 , x + 40 , y - 15 , x - 40 , y + 15, colors[c]);
	DrawTriangle(x + 40 , y - 15 , x + 40 , y + 15 , x - 40  , y + 15, colors[c]);	

}
void GameOver(int  x , int y , int c)
{
	DrawTriangle(790, 4, 10, 2 ,10 , 650, colors[c]);
	DrawTriangle(10, 650, 790, 650 , 790  ,4, colors[c]);	

}



void DrawSector(float a, float b)
{
	float theta = Deg2rad(a);
		float theta2 = Deg2rad(b);
		DrawTriangle(mid_x, mid_y, mid_x + 10 * cos(theta),
				mid_y + 10 * sin(theta), mid_x + 10 * cos(theta2),
				mid_y + 10 * sin(theta2), colors[0]);
}

void DrawCircle(int mid_x , int mid_y)
{
	for (int i = 0; i < 37; ++i)
	{
		DrawSector(theta0, theta1);
		theta0 += 10;
		theta1 += 10;
	}
}

void REFLECTION()
{

	Pre_mid_x = mid_x;
	 Pre_mid_y = mid_y;

	
	// FLAGS : 

	if (GO_UP == 1 )
	{
		mid_y+=5;
		
	}

	if (mid_y == 560)
	{
		GO_UP = 0;
		
	}

	if (mid_x >= L && mid_x <= L + 100 && mid_y <= 25)
	{

		dev_x = (mid_x  / 10.0) - (L / 10.0) - 5 ;

		Base_Flag = 1;
		Upper_Bound = 0;
		Bound_Left = 0;
		Bound_Right = 0;
		restart=0;
	}
	

		
	// SUPER GENERIC :

	// WALL LEFT DETECTION
	if (mid_x <= 10)
	{
		Base_Up = 0;
		Base_Right = 0;
		Base_Left = 0;
		Bound_Left = 1;
		Upper_Bound = 0;
		Bound_Right = 0;
		Base_Flag =0;
		restart=0;
	}
	// UPPER WALL DETECTION:
	if (mid_y >= 560)
	{
		Base_Right = 0;
		Base_Up =  0;
		Upper_Bound = 1;	
		Bound_Left = 0;	
		Base_Left = 0; 
		Bound_Right = 0;
		Base_Flag =0;
		restart=0;

			}

	// RIGHT WALL DETECTION :
	if (mid_x >= 790)
	{
		Base_Right = 0;
		Base_Up = 0;
		Bound_Right = 1;
		Upper_Bound = 0;
		Bound_Left = 0;
		Base_Left = 0;
		Base_Flag =0;
		restart=0;
	}

	// PREVIOUS X , Y

	// BRICKs :
	

		for (int i = 0 ; i < temp ; i++)
		{
			if (( mid_x >= arr_length[i] - size_x && mid_x <= arr_length[i] + size_x ) && ( mid_y >= arr_height[i] - size_y && mid_y <= arr_height[i] - 10   ) )
		{
			Brick_Down = 1;
			// cout << "DDDDDDDDDDDDDDOOOOOOOOOOOOOOOOOOOOOOOOOOOOWWWWWWWWWWWWWWWWWNNNNNNNNNNNNNNNNNNNNNNNNN" << endl ;
			Brick_Up = 0 ;
			Brick_Right = 0 ;
			Brick_Left = 0;
			GO_UP = 0;
			Base_Right = 0;
			Base_Up = 0;
			Bound_Right = 0;
			Upper_Bound = 0;
			Bound_Left = 0;
			Base_Left = 0;
			Base_Flag =0;
			restart=0;

			coordinate_x=arr_length[i];
			coordinate_y=arr_height[i];
			
			arr_length[i]=-150;
			arr_height[i]=-150;
			vanish=1;
			score=score+5;

			// cout<<"ALLLLLLLLLLLL"<<endl;
		}
		if (( mid_x >= arr_length[i] - size_x && mid_x <= arr_length[i] + size_x ) && ( mid_y >= arr_height[i] + size_y && mid_y <= arr_height[i] + 25   ) )
		{

			Brick_Down = 0 ;
			Base_Right = 0;
			Base_Up = 0;
			Bound_Right = 0;
			Upper_Bound = 0;
			Bound_Left = 0;
			Base_Left = 0;
			Base_Flag =0;
			Brick_Left = 0;
			Brick_Up = 1;
			restart=0;
			// cout<<"UUUUUUUUUUUUUUUUUUPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP"<<endl;
			
			coordinate_x=arr_length[i];
			coordinate_y=arr_height[i];
			
			arr_length[i]=-150;
			arr_height[i]=-150;
			vanish=1;
			score=score+5;



		}
		// l e f t
	if (mid_x >= arr_length[i] - size_x - 20  && mid_x <= arr_length[i] - size_x  &&  mid_y >= arr_height[i] - size_y && mid_y <= arr_height[i] + size_y   ) 
		{
			Brick_Down = 0 ;
			Base_Right = 0;
			Base_Up = 0;
			Bound_Right = 0;
			Upper_Bound = 0;
			Bound_Left = 0;
			Base_Left = 0;
			Base_Flag =0;
			Brick_Left = 1;
			restart=0;
			// cout<<"LLLLLLLLLLLLLLLLLLLEEEEEEEEEEEEEEEEEEEEEFFFFFFFFFFFFFFFFFFFFFTTTTTTTTTTTT"<<endl;

			coordinate_x=arr_length[i];
			coordinate_y=arr_height[i];
			
			arr_length[i]=-150;
			arr_height[i]=-150;
			vanish=1;
			score=score+5;



		}
	
	if (mid_x >= arr_length[i] + size_x && mid_x <= arr_length[i] + size_x + 10  && mid_y >= arr_height[i] - size_y   && mid_y <= arr_height[i] + size_y + 10  )
		{
			Brick_Down = 0 ;
			Base_Right = 0;
			Base_Up = 0;
			Bound_Right = 0;
			Upper_Bound = 0;
			Bound_Left = 0;
			Base_Left = 0;
			Base_Flag =0;
			Brick_Left = 0;
			Brick_Right = 1;
			restart=0;
			// cout<<"RRRRRRRRRRRRRRRRRIIIIIIIIIIIIIIIIIIGGGGGGGGGGGGGGHHHHHHHHHHHHHHHHHHHHHHHTTTTTTTTTTTTTTTTTTTTT"<<endl;

			coordinate_x=arr_length[i];
			coordinate_y=arr_height[i];
			
			arr_length[i]=-150;
			arr_height[i]=-150;
			vanish=1;
			score=score+5;


		}

/*	if(mid_x >= arr_length[i] - size_x && mid_x <= arr_length[i] + size_x && mid_y >= arr_height[i] - size_y && mid_y <= arr_height[i] + size_y )
		{
			coordinate_x=arr_length[i];
			coordinate_y=arr_height[i];

			arr_length[i]=-10;
			arr_height[i]=-10;
			vanish=1;
		}
*/

	}



	////// L   I    V    E      S
	if(mid_y <=10)
		{
			lives--;
			mid_x = 400;
			mid_y = 200;
			L = 350 ;
			GO_UP = 0;
			Upper_Bound = 1;	
		
			restart=1;
			
				heart_x[a] = -30;
				heart_y[a] = -30;
			
			a++;
		}

		
		
		// IMPLEMENTATIONS :

	if (Base_Flag == 1)
	{
			

			mid_x =mid_x+ dev_x;
			mid_y+=3;
	}	

	else if ((Upper_Bound == 1 && GO_UP == 0 && Del_mid_x == 0) or restart==1 /*/&& mid_x <= 255 && mid_x >= 655 && mid_y <= 355 && mid_y >= 517/*/ )
	{

		mid_y-=speed_y;
		// cout<<"ooooooopppppppppppppppppppppppppppppppppppppppppppppppoooooooooooooooo"<<endl;
	}
	else if (Upper_Bound == 1 && Del_mid_x != 0   )

	{
		// cout<<"KKKKKKKKSSSSSSSSSSSSSSSS"<<endl;
		if (Del_mid_x < 0)
		
		{
			mid_y-=speed_y;
			mid_x-=speed_x;
		}
		else if (Del_mid_x > 0)
		{
			mid_y-=speed_y;
			mid_x+=speed_x;
		}
	
	}

	
	else if (Bound_Left == 1) 
	{
		if (Del_mid_y > 0)
		{
			mid_x+=speed_x;
			mid_y+=speed_y;
		
		}
		else if( Del_mid_y < 0) 
		{
			mid_x+=speed_x;
			mid_y-=speed_y;
			
		}
		

	}
	else if (Bound_Right == 1)
	{
		if (Del_mid_y < 0)
		{
			mid_x-=speed_x;
			mid_y-=speed_y;
			
		}
		else if (Del_mid_y > 0)
		{
			mid_x-=speed_x;
			mid_y+=speed_y;
		
		}
		
	}
	else if (Brick_Down == 1)
		{
			if (Del_mid_x < 0)
		
			{
				mid_y-=speed_y;
				mid_x-=speed_x;
			}
			else if (Del_mid_x > 0)
			{
				mid_y-=speed_y;
				mid_x+=speed_x;
			}
			else if (Del_mid_x == 0 )
			{
				
				// Upper_Bound = 1;
				// GO_UP = 0 ;
				mid_y-=speed_y;
				// cout<<"5444444444444444444444444444,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,"<<endl;
			
			}
			// cout<<"DDDDDDDDDDDDDDDOOOOOOOOOOOOOOOOOOOOWWWWWWWWWWWWWWWWWWWWWWNNNNNNNNNNNNNNNNNNNNNNNNN................................................................"<<endl;
			
		}
	else if (Brick_Up == 1)
	{
		if (Del_mid_x < 0)
		
			{
				mid_y+=speed_y;
				mid_x-=speed_x;
			}
			else if (Del_mid_x > 0)
			{
				mid_y+=speed_y;
				mid_x+=speed_x;
			}
			// else if (mid_y == 0)
			// {

			// 	mid_y+=5;
			// }
	// cout<<"UUUUUUUUUUUUUPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP"<<endl; 

	}

	else if (Brick_Left == 1)
	{
		// cout<<"LLLLLLLLLLLLLLLLLLLEEEEEEEEEEEEEEEEEEEEEFFFFFFFFFFFFFFFFFFFFFTTTTTTTTTTTT"<<endl;


		if (Del_mid_y < 0)
		{
			mid_x-=speed_x;
			mid_y-=speed_y;
			
		}
		else if (Del_mid_y > 0)
		{
			mid_x-=speed_x;
			mid_y+=speed_y;
		
		}

	}	

	else if (Brick_Right == 1)
	{
		// cout<<"RRRRRRRRRRRRRRRRRIIIIIIIIIIIIIIIIIIGGGGGGGGGGGGGGHHHHHHHHHHHHHHHHHHHHHHHTTTTTTTTTTTTTTTTTTTTT"<<endl;


		if (Del_mid_y < 0)
		{
			mid_x+=speed_x;
			mid_y-=speed_y;
			
		}
		else if (Del_mid_y > 0)
		{
			mid_x+=speed_x;
			mid_y+=speed_y;
		
		}
	}

	


	
	
	/// CHANGE DEL:
	Del_mid_x = mid_x - Pre_mid_x;
	Del_mid_y = mid_y - Pre_mid_y;
	// cout<<"Del x = "<<Del_mid_x<<endl;
	// cout<<"Del y = "<<Del_mid_y<<endl;
	

	
}
/*
 * Write two  + functions DrawRectangle and DrawBricksphere
 * */

/*
 * Main Canvas drawing function.
 * */
void Display()/**/{
	
	// set the background color using function glClearColor.
	// to change the background play with the red, green and blue values below.
	// Note that r, g and b values must be in the range [0,1] where 0 means dim rid and 1 means pure red and so on.
	// DEVIATION :
	
	if (gamecontrol == 0)
{
			glClearColor(1/*Red Component*/, 1.0/*Green Component*/,
			1.0/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear(GL_COLOR_BUFFER_BIT); //Update the colors

	//write your drawing commands here u call your drawing functions...


	

		stringstream convert; // stringstream used for the conversion
	
		convert << score;//add the value of Number to the characters in the stream
	
		number = convert.str();//set Result to the content of the stream
	REFLECTION();

	DrawRectangle ( L , H ); //

	DrawCircle (mid_x , mid_y);

	DrawString( 20, 570, "S C O R E : ", colors[3])	;
	DrawString( 150, 570, number , colors[1])	;
	DrawString( 600, 570, "L I V E S : ", colors[3])	;
	
	for(int index=0 ;index<3 ;index++)
	{	

		LIVES (heart_x[index] , heart_y[index] , 7 );
		
	}
	DrawString (0 , 555 , "------------------------------------------------------------------------------" , colors[4]) ; 
	
	//DrawBricks ( lengths , Heights , 2); //
	// DrawBricks ( lengths , Heights + 25 , 3 ); //
	// DrawBricks ( lengths + 80, Heights , 4); //
	// DrawBricks ( lengths + 80 , Heights + 25 , 5 ); //
	
		//DrawBricks( Brick_mid_x, Brick_mid_y , 4 );
	

		for(int i = 0 ; i < temp ; i ++)
		{
			DrawBricks( arr_length[i], arr_height[i], 5 );
		}

		if(vanish==1)
		
		{
				DrawBricks( coordinate_x, coordinate_y, 3 );	

		}

	
	
	// void Bricks( Lengths , Heights) 
		// MENU
	if (flag == 0) 
	{
		GameOver(10 , 10 , 5) ;
		DrawString( 200, 340, "PRESS 'A' TO START THE GAME", colors[3]) ; // sey below the NonPrintable-Key Function to Understand 
	}
	if (flag == 1)
	{
		//DrawSquare( 0 , 0 , 750 ,colors[WHITE]) ;
		GameOver(10 , 10 , 5) ;
		DrawString( 280, 500, "PF BrickSlayer GAME", colors[3]) ;
		DrawString( 280, 360, "N  - NEW GAME", colors[3]) ; // Every time when N is pressed flag will be 11 and game will start
		DrawString( 280, 330, "C  - CONTROLS", colors[3]) ; // if C is pressed the flag value will be 2 and below given menu will be displayed
		DrawString( 310, 300, "H  - HELP", colors[3]) ; // same the case as C 
		DrawString( 310, 270, "Esc- EXIT", colors[3]) ;
		DrawString( 200, 200, "Use these keys for respective options", colors[3]) ;
	}
	if (flag == 2)
	{
		//DrawSquare( 0 , 0 , 750 ,colors[WHITE]) ;
		GameOver(10 , 10 , 5) ;
		DrawString( 280, 400, "GAME CONTROLS", colors[3]) ;
		//DrawString( 260, 370, "Move Up     -   Up Arrow Key", colors[3]) ;
		DrawString( 260, 340, "Move Left   -   Left Arrow Key", colors[3]) ;
		DrawString( 260, 310, "Move Right  -   Right Arrow Key", colors[3]) ;
	//	DrawString( 260, 280, "Move Down   -   Down Arrow Key", colors[3]) ;
	//	DrawString( 260, 250, "Fire  - B OR b key", colors[BLACK]) ;
		DrawString( 260, 220, "Exit Game   -   Esc Key", colors[3]) ;
		DrawString( 240, 140, "Press 'A' to go back to Main Menu", colors[3]) ; // every time A is pressed Flag will be 0 
	}
	if (lives == 0)
	{
		
		GameOver(10 , 10 , 5) ;//
		//DrawString( 300, 300, "G A M E ----  O V E R ", colors[3])	;
		DrawString( 280, 340, "GAME OVER ",colors[3]) ;
		DrawString( 280, 320, "Your Score was: ", colors[3]) ;
		string String = static_cast<ostringstream*>( &(ostringstream() << score) )->str() ;	  
		DrawString( 450, 320, String, colors[3]) ;
		gamecontrol = 1 ;
	}
	
	//DrawBricks ( lengths + 50 , Heights + 25 , 4 ); //
	
	glutSwapBuffers(); // do not modify this line..
}
}
/* Function sets canvas size (drawing area) in pixels...
 *  that is what dimensions (x and y) your game will have
 *  Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)
 * */
void SetCanvasSize(int width, int height) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
}

/*This function is called (automatically) whenever any non-printable key (such as up-arrow, down-arraw)
 * is pressed from the keyboard
 *
 * You will have to add the necessary code here when the arrow keys are pressed or any other key is pressed...
 *
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 *
 * */

void NonPrintableKeys(int key, int x, int y) {
	if (key == GLUT_KEY_LEFT /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/) {
		// what to do when left key is pressed...
		if (L > 0)
		{
			L-=10;	
			base_x = (2*L + 100) / 2;
			

		}
		

	} else if (key == GLUT_KEY_RIGHT /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/) {
		if (L < 700)
		{
			L+=10;	
			base_x = (2*L + 100) / 2;
			
		}	
		

	} else if (key == GLUT_KEY_UP/*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/) {
		 
	}

	else if (key == GLUT_KEY_DOWN/*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/) {
		

	}

	/* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
	 * this function*/
	
	 glutPostRedisplay();
	 
}

/*This function is called (automatically) whenever any printable key (such as x,b, enter, etc.)
 * is pressed from the keyboard
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 * */
void PrintableKeys(unsigned char key, int x, int y) {
	if (key == KEY_ESC/* Escape key ASCII*/) {
		exit(1); // exit the program when escape key is pressed.
	}
	if (key == 'A' || key == 'a')
	{ 
		flag = 1 ; // flag = 1 means that the second mneu is called
	}   
	if (key == 'N' || key == 'n')
	{
		flag = 11 ;  // flag = 11 means game is started
	}
	if (key == 'C' || key == 'c')
	{
		flag = 2 ; // controls or help menu
	}
	if (key == 'H' || key == 'h')
	{
		flag = 2 ; // controls or help menu 
	}

	if (key == 32)
	{
		if (count == 0 && flag == 11)
		{
			GO_UP = 1 ;
			count = 1 ;
		} 
	}

	 
}

/*
 * This function is called after every 1000.0/FPS milliseconds 
 * (FPS is defined on in the beginning).
 * You can use this function to animate objects and control the
 * speed of different moving objects by varying the constant FPS.
 *
 * */
void Timer(int m) {

	// implement your functionality here

	// once again we tell the library to call our Timer function after next 1000/FPS
	glutTimerFunc(1000.0 / FPS, Timer, 0);
	glutPostRedisplay();
}

/*
 * our gateway main function
 * */
int main(int argc, char*argv[]) {
	int width = 800, height = 600; // i have set my window size to be 800 x 600

	for (int i = 0; i < 7; ++i)
	{
		for(int j = 0 ; j < 8 ; ++j)
		{
			arr_length[temp] = Brick_mid_x + (i * Brick_Gap_x );
			arr_height[temp] = Brick_mid_y + (j * Brick_Gap_y );
			temp++;
		}
	}

/*	for (int i = 0,j=0 ; i < 400 and j < 150 ; i += 82 , j += 27 )
	{
	
		arr_length[temp] = lengths + i ;
		arr_height[temp] = Heights + j ;
		temp ++ ;
		cout << "FIRST" << arr_length[temp] << endl ;
		cout << "SECOND" << arr_height[temp] << endl ;
		//DrawBricks (lengths + 80 , Heights , 1) ;
		}
*/	
	// cout << "TEMP" << temp << endl ;

	InitRandomizer(); // seed the random number generator...
	glutInit(&argc, argv); // initialize the graphics library...

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
	glutInitWindowPosition(50, 50); // set the initial position of our window
	glutInitWindowSize(width, height); // set the size of our window
	glutCreateWindow("ITCs Brick Slayer"); // set the title of our game window
	SetCanvasSize(width, height); // set the number of pixels...

	// Register your functions to the library,
	// you are telling the library names of function to call for different tasks.
	glutDisplayFunc(Display); // tell library which function to call for drawing Canvas.
	glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
	glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
	// This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
	glutTimerFunc(1000.0 / FPS, Timer, 0);

	// now handle the control to library and it will call our registered functions when
	// it deems necessary...
	glutMainLoop();
	return 1;
}
#endif /* BSLAYER_CPP_ */
