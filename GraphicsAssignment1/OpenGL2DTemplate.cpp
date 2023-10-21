#include <cmath>
#include <stdio.h>
#include <string.h>
#include <glut.h>
#include <cstdlib>
#include <ctime>
#include <iostream>


int playerLives = 5; // Initial number of lives of the player

int gameScore = 0; // Initial score of the player

int remainingTime = 300; // Initial time of the game

float playerX = 500;  // Initial el X
float playerY = 300;  // Initial el Y
float playerSize = 20;  //hagm el player

float leftBoundaryX = 0.0f;
float rightBoundaryX = 1000.0f;
float topBoundaryY = 600.0f;
float bottomBoundaryY = 0.0f;

float obstacleX1 = 200.0f;
float obstacleY1 = 100.0f;

float obstacleX2 = 900.0f;
float obstacleY2 = 150.0f;

float obstacleX3 = 400.0f;
float obstacleY3 = 500.0f;

float obstacleX4 = 100.0f;
float obstacleY4 = 490.0f;

float obstacleX5 = 530.0f;
float obstacleY5 = 230.0f;

const int numCollectables = 5.0f; // 3adad el collectables ely fe el game
const int numPowerUps = 5; // 3adad powerups ely fe el game



float collectableX[numCollectables]; //  X coordinates
float collectableY[numCollectables]; //  Y coordinates
//
float powerUpX[numPowerUps]; //  X coordinates
float powerUpY[numPowerUps]; //  Y coordinates


float leftBoundaryRandomX = 100.0f;
float rightBoundaryRandomX = 900.0f;
float topBoundaryRandomY = 500.0f;
float bottomBoundaryRandomY = 100.0f;





//if statement gowaha elgame b flag esmo Lose maslan then when the game ends hayrooh lel else part

//this is the method used to print text in OpenGL
//there are three parameters,
//the first two are the coordinates where the text is display,
//the third coordinate is the string containing the text to display
void print(int x, int y, char* string)
{
	int len, i;

	//set the position of the text in the window using the x and y coordinates
	glRasterPos2f(x, y);

	//get the length of the string to display
	len = (int)strlen(string);

	//loop to display character by character
	for (i = 0; i < len; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
	}
}

void Timer(int value) {
	remainingTime--;
	glutPostRedisplay();
	glutTimerFunc(1000, Timer, 0);
}

void DrawObstacles() {
	glColor3f(0.5f, 0.5f, 0.5f); 
	glBegin(GL_QUADS);

	// Obstacle 1
	glVertex2f(obstacleX1 - 10, obstacleY1 - 10);
	glVertex2f(obstacleX1 + 10, obstacleY1 - 10);
	glVertex2f(obstacleX1 + 10, obstacleY1 + 10);
	glVertex2f(obstacleX1 - 10, obstacleY1 + 10);

	// Obstacle 2
	glVertex2f(obstacleX2 - 10, obstacleY2 - 10);
	glVertex2f(obstacleX2 + 10, obstacleY2 - 10);
	glVertex2f(obstacleX2 + 10, obstacleY2 + 10);
	glVertex2f(obstacleX2 - 10, obstacleY2 + 10);

	// Obstacle 3
	glVertex2f(obstacleX3 - 10, obstacleY3 - 10);
	glVertex2f(obstacleX3 + 10, obstacleY3 - 10);
	glVertex2f(obstacleX3 + 10, obstacleY3 + 10);
	glVertex2f(obstacleX3 - 10, obstacleY3 + 10);

	//Obstacle 4

	glVertex2f(obstacleX4 - 10, obstacleY4 - 10);
	glVertex2f(obstacleX4 + 10, obstacleY4 - 10);
	glVertex2f(obstacleX4 + 10, obstacleY4 + 10);
	glVertex2f(obstacleX4 - 10, obstacleY4 + 10);

	//Obstacle 5
	glVertex2f(obstacleX5 - 10, obstacleY5 - 10);
	glVertex2f(obstacleX5 + 10, obstacleY5 - 10);
	glVertex2f(obstacleX5 + 10, obstacleY5 + 10);
	glVertex2f(obstacleX5 - 10, obstacleY5 + 10);
	

	glEnd();

	//  crosses inside the obstacles (lines)
	glColor3f(1.0f, 1.0f, 1.0f); 
	glLineWidth(2.0f);

	// Cross inside obstacle 1
	glBegin(GL_LINES);
	glVertex2f(obstacleX1 - 10, obstacleY1 - 10);
	glVertex2f(obstacleX1 + 10, obstacleY1 + 10);
	glEnd();

	glBegin(GL_LINES);
	glVertex2f(obstacleX1 - 10, obstacleY1 + 10);
	glVertex2f(obstacleX1 + 10, obstacleY1 - 10);
	glEnd();

	// Cross inside obstacle 2
	glBegin(GL_LINES);
	glVertex2f(obstacleX2 - 10, obstacleY2 - 10);
	glVertex2f(obstacleX2 + 10, obstacleY2 + 10);
	glEnd();

	glBegin(GL_LINES);
	glVertex2f(obstacleX2 - 10, obstacleY2 + 10);
	glVertex2f(obstacleX2 + 10, obstacleY2 - 10);
	glEnd();

	// Cross inside obstacle 3
	glBegin(GL_LINES);
	glVertex2f(obstacleX3 - 10, obstacleY3 - 10);
	glVertex2f(obstacleX3 + 10, obstacleY3 + 10);
	glEnd();
	
	glBegin(GL_LINES);
	glVertex2f(obstacleX3 - 10, obstacleY3 + 10);
	glVertex2f(obstacleX3 + 10, obstacleY3 - 10);

	// Cross inside obstacle 4
	glBegin(GL_LINES);
	glVertex2f(obstacleX4 - 10, obstacleY4 - 10);
	glVertex2f(obstacleX4 + 10, obstacleY4 + 10);
	glEnd();

	glBegin(GL_LINES);
	glVertex2f(obstacleX4 - 10, obstacleY4 + 10);
	glVertex2f(obstacleX4 + 10, obstacleY4 - 10);
	glEnd();

	// Cross inside obstacle 5
	glBegin(GL_LINES);
	glVertex2f(obstacleX5 - 10, obstacleY5 - 10);
	glVertex2f(obstacleX5 + 10, obstacleY5 + 10);
	glEnd();

	glBegin(GL_LINES);
	glVertex2f(obstacleX5 - 10, obstacleY5 + 10);
	glVertex2f(obstacleX5 + 10, obstacleY5 - 10);
	glEnd();

}


void DrawSceneBoundaries() {
	//  scene boundaries using lines
	glColor3f(0.7f, 0.45f, 0.39f); 
	glLineWidth(30.0f);

	// Left boundary
	glBegin(GL_LINES);
	glVertex2f(leftBoundaryX, topBoundaryY);
	glVertex2f(leftBoundaryX, bottomBoundaryY);
	glEnd();

	// Top boundary
	glBegin(GL_LINES);
	glVertex2f(leftBoundaryX, topBoundaryY);
	glVertex2f(rightBoundaryX, topBoundaryY);
	glEnd();

	// Right boundary
	glBegin(GL_LINES);
	glVertex2f(rightBoundaryX, topBoundaryY);
	glVertex2f(rightBoundaryX, bottomBoundaryY);
	glEnd();

	// Bottom boundary
	glBegin(GL_LINES);
	glVertex2f(leftBoundaryX, bottomBoundaryY);
	glVertex2f(rightBoundaryX, bottomBoundaryY);
	glEnd();

	//  green points inside the boundaries
	glColor3f(0.0f, 1.0f, 0.0f); 
	glPointSize(10); 

	//  point inside the left boundary
	glBegin(GL_POINTS);
	glVertex2f(leftBoundaryX , (topBoundaryY + bottomBoundaryY) / 2);
	glEnd();

	// point inside the top boundary
	glBegin(GL_POINTS);
	glVertex2f((leftBoundaryX + rightBoundaryX) / 2, topBoundaryY);
	glEnd();

	// point inside the right boundary
	glBegin(GL_POINTS);
	glVertex2f(rightBoundaryX, (topBoundaryY + bottomBoundaryY) / 2);
	glEnd();

	// point inside the bottom boundary
	glBegin(GL_POINTS);
	glVertex2f((leftBoundaryX + rightBoundaryX) / 2, bottomBoundaryY );
	glEnd();
}


void DrawPlayer() {

	// Hasameeh Wall-E <3
	
	// Raso (Quad)
	glColor3f(1.0f, 0.0f, 0.0f); 
	glBegin(GL_QUADS);
	glVertex2f(playerX - 10, playerY + 30);
	glVertex2f(playerX + 10, playerY + 30);
	glVertex2f(playerX + 10, playerY + 40);
	glVertex2f(playerX - 10, playerY + 40);
	glEnd();

	// 3eeno (point)
	glColor3f(0.0f, 0.0f, 0.0f); // Black color
	glPointSize(5);
	glBegin(GL_POINTS);
	glVertex2f(playerX - 5, playerY + 35); // Left eye
	glVertex2f(playerX + 5, playerY + 35); // Right eye
	glEnd();

	// Gesmo (quad)
	glColor3f(0.0f, 0.0f, 1.0f); 
	glBegin(GL_QUADS);
	glVertex2f(playerX - 10, playerY - 20);
	glVertex2f(playerX + 10, playerY - 20);
	glVertex2f(playerX + 10, playerY + 20);
	glVertex2f(playerX - 10, playerY + 20);
	glEnd();


	//Connection raso b gesmo (line)
	glLineWidth(2.0f); 

	
	glColor3f(0.0f, 0.0f, 0.0f); 
	glBegin(GL_LINES);
	glVertex2f(playerX, playerY + 40);
	glVertex2f(playerX, playerY + 20);
	glEnd();

	// Regleeh (triangle)
	glColor3f(0.0f, 1.0f, 0.0f); 
	glBegin(GL_TRIANGLES);
	glVertex2f(playerX - 10, playerY - 20);
	glVertex2f(playerX + 10, playerY - 20);
	glVertex2f(playerX, playerY - 30); 
	glEnd();

	// Dera3o (line)
	glLineWidth(5);
	glColor3f(0.0f, 0.0f, 0.0f); 
	glBegin(GL_LINES);
	// Left arm
	glVertex2f(playerX - 10, playerY);
	glVertex2f(playerX - 20, playerY - 10);
	// Right arm
	glVertex2f(playerX + 10, playerY);
	glVertex2f(playerX + 20, playerY - 10);
	glEnd();
}

void GenerateRandomPosition(float& x, float& y) {
	x = static_cast<float>(rand() % static_cast<int>(rightBoundaryRandomX - leftBoundaryRandomX) + leftBoundaryRandomX);
	y = static_cast<float>(rand() % static_cast<int>(topBoundaryRandomY - bottomBoundaryRandomY) + bottomBoundaryRandomY);
}

void InitializeCollectablesAndPowerUps() {
	for (int i = 0; i < numCollectables; i++) {
		GenerateRandomPosition(collectableX[i], collectableY[i]);
	}
	for (int i = 0; i < numPowerUps; i++) {
		GenerateRandomPosition(powerUpX[i], powerUpY[i]);
	}

}


void KeyboardMove(unsigned char key, int x, int y) {
	switch (key) {
	case 'w':
		if (playerY < topBoundaryY - 40.0f) {
			playerY += 10;
		}
		break;
	case 's':
		if (playerY > bottomBoundaryY + 30.0f) {
			playerY -= 10;
		}
		break;
	case 'a':
		if (playerX > leftBoundaryX + 25.0f) {
			playerX -= 10;
		}
		break;
	case 'd':
		if (playerX < rightBoundaryX - 25.0f) {
			playerX += 10;
		}
		break;
	}
	glutPostRedisplay();		

}

void Display() {
	glClear(GL_COLOR_BUFFER_BIT);


	// El health bar ely fo2
	glColor3f(0.0f, 1.0f, 0.0f); // Green color
	for (int i = 0; i < playerLives; i++) {
		glBegin(GL_QUADS);
		glVertex2f(10 + i * 20, 570);          // Top-left corner
		glVertex2f(30 + i * 20, 570);          // Top-right corner
		glVertex2f(30 + i * 20, 590);          // Bottom-right corner
		glVertex2f(10 + i * 20, 590);          // Bottom-left corner
		glEnd();
	}

	// Fadel kam live 
	glColor3f(1.0f, 0.0f, 0.0f); 
	char livesText[50];
	sprintf(livesText, "Lives: %d", playerLives);
	print(10, 570 - 20, livesText);



	// El gamescore ely fo2
	glColor3f(0.0f, 0.0f, 0.0f); 
	char scoreText[50];
	sprintf(scoreText, "Score: %d", gameScore);
	print(500, 570, scoreText);

	// Time 
	char timeText[50];
	sprintf(timeText, "Time: %d s", remainingTime);
	print(850,570, timeText);

	//Print el Collectables w el Powerups

	for (int i = 0; i < numCollectables; i++) {
		glColor3f(1.0f, 0.0f, 0.0f); // Red color
		glPointSize(10);
		glBegin(GL_POINTS);
		glVertex2f(collectableX[i], collectableY[i]);
		glEnd();
		
	}

	for (int i = 0; i < numPowerUps; i++) {
		glColor3f(0.0f, 0.0f, 1.0f); // Blue color
		glPointSize(10);
		glBegin(GL_POINTS);
		glVertex2f(powerUpX[i], powerUpY[i]);
		glEnd();
	}

	// THIS WILL BE USED TO SHOW THE SCORE AFTER END GAME.
	/*	glColor3f(1, 0, 0);
	char* p0s[20];
	sprintf((char*)p0s, "Score: %d", 50);
	print(500, 300, (char*)p0s); */

	 DrawPlayer();
	 DrawObstacles();
	 DrawSceneBoundaries();

	glFlush();
}


void main(int argc, char** argr) {
	glutInit(&argc, argr);

	glutInitWindowSize(1000, 600);

	glutCreateWindow("PowerCollect: The Quest for Prizes");
	glutDisplayFunc(Display);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	gluOrtho2D(0.0, 1000, 0.0, 600);
	glutTimerFunc(1000, Timer, 0);
	glutKeyboardFunc(KeyboardMove);
	srand(static_cast<unsigned>(time(nullptr)));
	InitializeCollectablesAndPowerUps();


	glutMainLoop();
}
