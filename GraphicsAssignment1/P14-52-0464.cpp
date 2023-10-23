#include <cmath>
#include <stdio.h>
#include <string.h>
#include <glut.h>
#include <cstdlib>
#include <ctime>
#include <iostream>


int playerLives = 5; // Initial number of lives of the player

int maxHealth = 100; // Initial health bar of the player
int playerHealth = 100; // Initial health bar of the player

int gameScore = 0; // Initial score of the player

int remainingTime = 100; // Initial time of the game

float playerX = 500;  // Initial el X
float playerY = 300;  // Initial el Y
float playerHeight = 150;
float playerSize = 20;  //hagm el player
float playerRotation = 0.0f; // Initial rotation angle of el player

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
const int numPowerUpSpeed = 2; // 3adad powerupSpeed ely fe el game
const int numPowerUpDouble = 3;
float goalX = 50.0f;
float goalY = 25.0f;
float goalHover = 10.0f;
float goalHoverSpeed = 0.2f;

float collectableX[numCollectables]; //  X coordinates
float collectableY[numCollectables]; //  Y coordinates
float rotationCollectableAngle = 0.0f; 

bool collectableCollected[numCollectables]; // 3ashan lama el player yel3ab yeb2a el collectable msh mawgood fe el game tany
//
float powerUpSpeedX[numPowerUpSpeed]; //  X coordinates PowerUpSpeed
float powerUpSpeedY[numPowerUpSpeed]; //  Y coordinates PowerUpSpeed

float powerUpSpeedHover[numPowerUpSpeed]; 
bool powerUpSpeedCollected[numPowerUpSpeed]; // 3ashan lama el player yakhod powerup yeb2a el powerUpSpeed msh mawgood fe el game tany
bool powerUpSpeedMovingRight[numPowerUpSpeed];


float powerUpDoubleX[numPowerUpDouble]; //  X coordinates PowerUpDouble
float powerUpDoubleY[numPowerUpDouble]; //  Y coordinates PowerUpDouble
bool powerUpDoubleCollected[numPowerUpDouble]; // 3ashan lama el player yakhod powerup yeb2a el powerUpDouble msh mawgood fe el game tany
float powerUpDoubleHover[numPowerUpDouble];
bool powerUpDoubleMovingRight[numPowerUpDouble];

float leftBoundaryRandomX = 100.0f;
float rightBoundaryRandomX = 900.0f;
float topBoundaryRandomY = 500.0f;
float bottomBoundaryRandomY = 100.0f;

enum GameState { PLAYING, LOSE, WIN };


 GameState gameState = PLAYING;

 int playerSpeed = 10;

 int speedBoostDuration = 10;
bool isSpeedBoostActive = false;
int speedBoostRemainingTime = 0;
int speedBoost = 10;

int doubleBoostDuration = 10;
bool isDoubleBoostActive = false;
int doubleBoostRemainingTime = 0;
int doubleBoost = 2;

// hena ba3mel el background animation (outer space)
const int numberOfStars = 1000;
float starX[numberOfStars];
float starY[numberOfStars];



void InitializeStars() {
	for (int i = 0; i < numberOfStars; i++) {
		starX[i] = static_cast<float>(rand() % 1000);
		starY[i] = static_cast<float>(rand() % 600);
	}
}
void DrawStars() {
		glColor3f(1.0f, 1.0f, 1.0f); 
	glPointSize(2);
	glBegin(GL_POINTS);
	for (int i = 0; i < numberOfStars; i++) {
		glVertex2f(starX[i], starY[i]);
	}
	glEnd();

}


void DisableDoubleBoost(int value) {
	isDoubleBoostActive = false;
	doubleBoostRemainingTime = 0;
	doubleBoost = 1;
}

void ApplyDoubleBoost() {
	if (!isDoubleBoostActive) {
		isDoubleBoostActive = true;
		doubleBoostRemainingTime = doubleBoostDuration;
		doubleBoost = 2;
	}
	glutTimerFunc(1000 * doubleBoostDuration, DisableDoubleBoost, 0);
}

void UpdateDoubleBoost() {
	if (isDoubleBoostActive) {
		doubleBoostRemainingTime--;
		if (doubleBoostRemainingTime == 0) {
			isDoubleBoostActive = false;
		}
	}
}




void DisableSpeedBoost(int value) {
	isSpeedBoostActive = false;
	speedBoostRemainingTime = 0;
	playerSpeed = 10;
}


void ApplySpeedBoost() {
	if (!isSpeedBoostActive) {
		isSpeedBoostActive = true;
		speedBoostRemainingTime = speedBoostDuration;
		
	}
	glutTimerFunc(1000 * speedBoostDuration, DisableSpeedBoost, 0);
}


void UpdateSpeedBoost() {
	if (isSpeedBoostActive) {
		speedBoostRemainingTime--;
		if (speedBoostRemainingTime == 0) {
			isSpeedBoostActive = false;
		}
	}
}



//if statement gowaha elgame b flag esmo Lose maslan then when the game ends hayrooh lel else part (doc menrit aaletly keda fel lab)

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

	if (gameState == PLAYING && isSpeedBoostActive) {
		speedBoostRemainingTime--;

		if (speedBoostRemainingTime <= 0) {
			DisableSpeedBoost(0);
		}
	}
	if (gameState == PLAYING && isDoubleBoostActive) {
		doubleBoostRemainingTime--;
		if (doubleBoostRemainingTime <= 0) {
			DisableDoubleBoost(0);
		}
	}
	if (remainingTime == 0) {
		gameState = LOSE;
	}
}



void DrawCollectables(float x, float y, float rotationAngle) {
	rotationAngle += 1.0f;
	glColor3f(0.5f, 0.5f, 0.5f);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++) {
		float angle = (i+rotationAngle) * 3.1415926f / 180;
		float cx = cosf(angle) * 10;
		float cy = sinf(angle) * 10;
		
		glVertex2f(x + cx, y + cy);
		
	}
	glEnd();

	glColor3f(0.8f, 0.0f, 0.0f); 
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++) {
		float angle = (i + rotationAngle) * 3.14159265f / 180.0f;
		float cx = 5 * cosf(angle);
		float cy = 5 * sinf(angle);
		glVertex2f(x + cx, y + cy);
	}
	glEnd();

	glColor3f(0.5f, 0.5f, 0.5f); 
	glLineWidth(2.0f);
	glBegin(GL_LINES);
	for (int i = 0; i < 360; i += 30) {
		float angle = (i + rotationAngle) * 3.14159265f / 180.0f;
		float cx1 = 10 * cosf(angle);
		float cy1 = 10 * sinf(angle);
		float cx2 = 12 * cosf(angle);
		float cy2 = 12 * sinf(angle);
		glVertex2f(x + cx1, y + cy1);
		glVertex2f(x + cx2, y + cy2);
	}
	glEnd();
}
void CollectablesRotationTimer(int value) {
	rotationCollectableAngle += 1.0f;  
	glutPostRedisplay();
	glutTimerFunc(16, CollectablesRotationTimer, 0);  
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
	glPushMatrix();
	glTranslatef(playerX, playerY, 0.0f);
	glRotatef(playerRotation, 0.0f, 0.0f, 1.0f);

	// Hasameeh Wall-E <3
	
	// Raso (Quad)
	glColor3f(0.5451f, 0.5529f, 0.5529f);
	glBegin(GL_QUADS);
	glVertex2f( 10,  30);
	glVertex2f( - 10,  30);
	glVertex2f( 10, 40);
	glVertex2f( -10,  40);
	glEnd();

	// 3eeno (point)
	glColor3f(0.0f, 0.0f, 1.0f); 
	glPointSize(5);
	glBegin(GL_POINTS);
	glVertex2f( - 5,  + 35); // Left eye
	glVertex2f( + 5,  + 35); // Right eye
	glEnd();

	// Gesmo (quad)
	glColor3f(0.0f, 0.5f, 1.0f); 
	glBegin(GL_QUADS);
	glVertex2f( - 10,  - 20);
	glVertex2f( + 10,  - 20);
	glVertex2f( + 10,  + 20);
	glVertex2f( - 10,  + 20);
	glEnd();


	//Connection raso b gesmo (line)
	glLineWidth(2.0f); 
	glColor3f(0.5451f, 0.5529f, 0.5529f);
	glBegin(GL_LINES);
	glVertex2f(0,  + 40);
	glVertex2f(0,  + 20);
	glEnd();

	// Regleeh (triangle)
	glColor3f(0.0f, 0.5f, 0.0f); 
	glBegin(GL_TRIANGLES);
	glVertex2f( - 10,  - 20);
	glVertex2f( + 10,  - 20);
	glVertex2f(0,  - 30); 
	glEnd();

	// Dera3o (line)
	glLineWidth(5);
	glColor3f(0.5451f, 0.5529f, 0.5529f);
	glBegin(GL_LINES);
	// Left arm
	glVertex2f( - 10, 0);
	glVertex2f( - 20,  - 10);
	// Right arm
	glVertex2f( + 10, 0);
	glVertex2f( + 20,  - 10);
	glEnd();

	glPopMatrix();
}

bool isColliding(float x, float y) {

	float obstaclePositionsX[] = { obstacleX1, obstacleX2, obstacleX3, obstacleX4, obstacleX5 };
	float obstaclePositionsY[] = { obstacleY1, obstacleY2, obstacleY3, obstacleY4, obstacleY5 };
	

	for (int i = 0; i < 5; i++) {
		float distance = sqrt(pow(x - obstaclePositionsX[i], 2) + pow(y - obstaclePositionsY[i], 2));
		if (distance <= 30.0f) {
			return true;  // Colliding with an obstacle.
		}
	}

	return false;  // No collision with obstacles.
}

void GenerateRandomPosition(float& x, float& y) {
	do{
	x = static_cast<float>(rand() % static_cast<int>(rightBoundaryRandomX - leftBoundaryRandomX) + leftBoundaryRandomX);
	y = static_cast<float>(rand() % static_cast<int>(topBoundaryRandomY - bottomBoundaryRandomY) + bottomBoundaryRandomY);
		} while (isColliding(x, y));
}

void DrawSpeedBoostPowerup(float x, float y) {
	//glColor3f(0.5f, 0.8f, 1.0f); // Light blue color

	//// First triangle
	//glBegin(GL_TRIANGLES);
	//glVertex2f(x, y);
	//glVertex2f(x - 10.0f, y - 20.0f);
	//glVertex2f(x + 10.0f, y - 20.0f);
	//glEnd();

	//// Second triangle
	//glBegin(GL_TRIANGLES);
	//glVertex2f(x, y);
	//glVertex2f(x + 20.0f, y - 10.0f);
	//glVertex2f(x + 20.0f, y + 10.0f);
	//glEnd();

	//// Third triangle
	//glBegin(GL_TRIANGLES);
	//glVertex2f(x, y);
	//glVertex2f(x + 10.0f, y + 20.0f);
	//glVertex2f(x - 10.0f, y + 20.0f);
	//glEnd();

	//// Fourth triangle
	//glBegin(GL_TRIANGLES);
	//glVertex2f(x, y);
	//glVertex2f(x - 20.0f, y + 10.0f);
	//glVertex2f(x - 20.0f, y - 10.0f);
	//glEnd();
	glColor3f(0.2f, 0.2f, 0.8f); 
	glBegin(GL_QUADS);
	glVertex2f(x - 12.5, y - 12.5);
	glVertex2f(x + 12.5, y - 12.5);
	glVertex2f(x + 12.5, y + 12.5);
	glVertex2f(x - 12.5, y + 12.5);
	glEnd();

	glColor3f(0.5f, 0.8f, 1.0f);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++) {
		float angle = i * 3.1415926f / 180;
		float cx = cosf(angle) * 10;
		float cy = sinf(angle) * 10;

		glVertex2f(x + cx, y + cy);

	}
	glEnd();

	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++) {
		float angle = i * 3.14159265f / 180.0f;
		float cx = 5 * cosf(angle);
		float cy = 5 * sinf(angle);
		glVertex2f(x + cx, y + cy);
	}
	glEnd();

	glColor3f(0.5f, 0.8f, 1.0f);
	glLineWidth(2.0f);
	glBegin(GL_LINES);
	for (int i = 0; i < 360; i += 30) {
		float angle = i * 3.14159265f / 180.0f;
		float cx1 = 10 * cosf(angle);
		float cy1 = 10 * sinf(angle);
		float cx2 = 12 * cosf(angle);
		float cy2 = 12 * sinf(angle);
		glVertex2f(x + cx1, y + cy1);
		glVertex2f(x + cx2, y + cy2);
	}
	glEnd();
}

void PowerUpSpeedHoverTimer(int value) {
	for (int i = 0; i < numPowerUpSpeed; i++) {
		if (powerUpSpeedMovingRight[i]) {
			powerUpSpeedX[i] += 0.05f;
			if (powerUpSpeedX[i] > powerUpSpeedHover[i] + 1.0f) {
				powerUpSpeedMovingRight[i] = false;
			}
		}
		else {
			powerUpSpeedX[i] -= 0.05f;
			if (powerUpSpeedX[i] < powerUpSpeedHover[i] - 1.0f) {
				powerUpSpeedMovingRight[i] = true;
			}
		}
	}
	glutTimerFunc(16, PowerUpSpeedHoverTimer, 0);
}

void DrawDoubleScoreBoostPowerup(float x, float y) {
	glColor3f(0.7f, 0.7f, 0.5f);
	glBegin(GL_QUADS);
	glVertex2f(x - 12.5, y - 12.5);
	glVertex2f(x + 12.5, y - 12.5);
	glVertex2f(x + 12.5, y + 12.5);
	glVertex2f(x - 12.5, y + 12.5);
	glEnd();

	glColor3f(1.0f, 1.0f, 0.5f);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++) {
		float angle = i * 3.1415926f / 180;
		float cx = cosf(angle) * 10;
		float cy = sinf(angle) * 10;

		glVertex2f(x + cx, y + cy);

	}
	glEnd();

	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++) {
		float angle = i * 3.14159265f / 180.0f;
		float cx = 5 * cosf(angle);
		float cy = 5 * sinf(angle);
		glVertex2f(x + cx, y + cy);
	}
	glEnd();

	glColor3f(0.5f, 0.5f, 0.5f);
	glLineWidth(2.0f);
	glBegin(GL_LINES);
	for (int i = 0; i < 360; i += 30) {
		float angle = i * 3.14159265f / 180.0f;
		float cx1 = 10 * cosf(angle);
		float cy1 = 10 * sinf(angle);
		float cx2 = 12 * cosf(angle);
		float cy2 = 12 * sinf(angle);
		glVertex2f(x + cx1, y + cy1);
		glVertex2f(x + cx2, y + cy2);
	}
	glEnd();
}

void PowerUpDoubleHoverTimer(int value) {
	for (int i = 0; i < numPowerUpDouble; i++) {
		if (powerUpDoubleMovingRight[i]) {
			powerUpDoubleX[i] += 0.05f;
			if (powerUpDoubleX[i] > powerUpDoubleHover[i] + 1.0f) {
				powerUpDoubleMovingRight[i] = false;
			}
		}
		else {
			powerUpDoubleX[i] -= 0.05f;
			if (powerUpDoubleX[i] < powerUpDoubleHover[i] - 1.0f) {
				powerUpDoubleMovingRight[i] = true;
			}
		}
	}
	glutTimerFunc(16, PowerUpDoubleHoverTimer, 0);
}



void InitializeCollectablesAndPowerUps() {
	for (int i = 0; i < numCollectables; i++) {
		GenerateRandomPosition(collectableX[i], collectableY[i]);
		collectableCollected[i] = false;
	}
	for (int i = 0; i < numPowerUpSpeed; i++) {
		GenerateRandomPosition(powerUpSpeedX[i], powerUpSpeedY[i]);

		powerUpSpeedCollected[i] = false;
	}
	for (int i = 0; i < numPowerUpSpeed; i++) {
		powerUpSpeedHover[i] = powerUpSpeedX[i];
		powerUpSpeedMovingRight[i] = true; 
	}
	for (int i = 0; i < numPowerUpDouble; i++) {
		GenerateRandomPosition(powerUpDoubleX[i], powerUpDoubleY[i]);
		powerUpDoubleCollected[i] = false;
	}
	for (int i = 0; i < numPowerUpDouble; i++) {
		powerUpDoubleHover[i] = powerUpDoubleX[i];
		powerUpDoubleMovingRight[i] = true;
	}
}


void KeyboardMove(unsigned char key, int x, int y) { 

		int currentSpeed = playerSpeed;
		if (isSpeedBoostActive) {
			currentSpeed  = 3 * playerSpeed;
		}
		switch (key) {
		case 'w':
			if (playerY < topBoundaryY - 40.0f) {
				playerY += currentSpeed;
				playerRotation = 0.0f;
			}
			break;
		case 's':
			if (playerY > bottomBoundaryY + 30.0f) {
				playerY -= currentSpeed;
				playerRotation = 180.0f;
			}
			break;
		case 'a':
			if (playerX > leftBoundaryX + 25.0f) {
				playerX -= currentSpeed;
				playerRotation = 90.0f;
			}
			break;
		case 'd':
			if (playerX < rightBoundaryX - 25.0f) {
				playerX += currentSpeed;
				playerRotation = 270.0f;
			}
			break;
		}
	
	glutPostRedisplay();
}



void CheckCollisionWithCollectable() {
	for (int i = 0; i < numCollectables; i++) {
		float distance = sqrt(pow(playerX - collectableX[i], 2) + pow(playerY - collectableY[i], 2));
		if (distance < 20.0f) {
			if (collectableCollected[i] == false) {
				if (isDoubleBoostActive == true) {
					gameScore =  gameScore + (50*doubleBoost);
				}
				else {
					gameScore += 50;
				}
			
			collectableCollected[i] = true;
		}
		
		}
	}
}

void CheckCollisionWithObstacles() {
	float distance1 = sqrt(pow(playerX - obstacleX1, 2) + pow(playerY - obstacleY1, 2));
	float distance2 = sqrt(pow(playerX - obstacleX2, 2) + pow(playerY - obstacleY2, 2));
	float distance3 = sqrt(pow(playerX - obstacleX3, 2) + pow(playerY - obstacleY3, 2));
	float distance4 = sqrt(pow(playerX - obstacleX4, 2) + pow(playerY - obstacleY4, 2));
	float distance5 = sqrt(pow(playerX - obstacleX5, 2) + pow(playerY - obstacleY5, 2));

	if (distance1 < 35.0f || distance2 < 35.0f || distance3 < 35.0f || distance4 < 35.0f || distance5 < 35.0f) {
		playerHealth -= 20;
		playerLives -= 1;
		playerX = 500.0f; 
		playerY = 300.0f;

		if (playerHealth <= 0) {
			gameState = LOSE;
			
		/*	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
			glClear(GL_COLOR_BUFFER_BIT);
				glColor3f(1, 0, 0);
				char* p0s[20];
				sprintf((char*)p0s, "GameOver, Your Score: %d", gameScore);
				print(500, 300, (char*)p0s); */
		}
	}

}
void CheckCollisionWithSceneBoundaries() {
	if (playerX < leftBoundaryX + 25.0f || playerX > rightBoundaryX - 25.0f || playerY < bottomBoundaryY + 40.0f || playerY > topBoundaryY - 50.0f) {
		// Implement collision handling here
		// For example, reset player position or decrease health
		playerHealth -= 20;
		playerLives -= 1;
		playerX = 500.0f; // Reset player X-coordinate
		playerY = 300.0f; // Reset player Y-coordinate
		if (playerHealth <= 0) {
			gameState = LOSE;
			
		/*	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			glColor3f(1, 0, 0);
			char* p0s[20];
			sprintf((char*)p0s, "GameOver, Your Score: %d", gameScore);
			print(500, 300, (char*)p0s);*/
		}

	}
}
void CheckCollisionWithPowerUps() {
	for (int i = 0; i < numPowerUpSpeed; i++) {
		float distance = sqrt(pow(playerX - powerUpSpeedX[i], 2) + pow(playerY - powerUpSpeedY[i], 2));
		if (distance < 20.0f) {
			if (powerUpSpeedCollected[i] == false) {
				ApplySpeedBoost();
				powerUpSpeedCollected[i] = true;
			}
			
		}
	}
	for (int i = 0; i < numPowerUpDouble; i++) {
		float distance = sqrt(pow(playerX - powerUpDoubleX[i], 2) + pow(playerY - powerUpDoubleY[i], 2));
		if (distance < 20.0f) {
			if (powerUpDoubleCollected[i] == false) {
				ApplyDoubleBoost();
				powerUpDoubleCollected[i] = true;
			}

		}
	}
}
void DrawGoal(float x, float y) {
	
	glColor3f(1.0f, 0.84f, 0.0f); // loon gold

	
	glBegin(GL_QUADS);
	glVertex2f(x - 20, y);
	glVertex2f(x + 20, y);
	glVertex2f(x + 20, y + 20);
	glVertex2f(x - 20, y + 20);
	glEnd();

	
	glBegin(GL_QUADS);
	glVertex2f(x - 15, y + 20);
	glVertex2f(x + 15, y + 20);
	glVertex2f(x + 15, y + 35);
	glVertex2f(x - 15, y + 35);
	glEnd();

	
	glBegin(GL_QUADS);
	glVertex2f(x - 10, y + 35);
	glVertex2f(x + 10, y + 35);
	glVertex2f(x + 10, y + 50);
	glVertex2f(x - 10, y + 50);
	glEnd();

	
	glBegin(GL_LINES);
	glVertex2f(x, y + 50);
	glVertex2f(x, y + 65);
	glEnd();
}

void GoalTimer(int value) {
	goalY += goalHoverSpeed;
	if (goalY >= 20.0f + goalHover || goalY <= 20.0f - goalHover) {
		goalHoverSpeed *= -1;
	}
	glutTimerFunc(16, GoalTimer, 0);
	glutPostRedisplay();
}







void DrawPlayerLiveAndHealth() {
	glPushMatrix();
	glTranslatef(50, 570, 0);
	float healthPercentage = 200 * static_cast<float>(playerHealth) / maxHealth;
	
	glColor3f(0.8f, 0.2f, 0.2f); 
	glBegin(GL_QUADS);
	glVertex2f(0, 0);
	glVertex2f(200, 0);
	glVertex2f(200, 20);
	glVertex2f(0, 20);
	glEnd();

	glColor3f(0.2f, 0.8f, 0.2f); 
	glBegin(GL_QUADS);
	glVertex2f(0, 0);
	glVertex2f(healthPercentage, 0);
	glVertex2f(healthPercentage, 20);
	glVertex2f(0, 20);
	glEnd();

	glPopMatrix();

	glColor3f(0.0f, 1.0f, 0.0f); // Green color
	char livesText[50];
	sprintf(livesText, "Lives: %d", playerLives);
	print(10, 570 - 20, livesText);

}

void CheckCollisionWithGoal() {
	float distance = sqrt(pow(playerX - goalX, 2) + pow(playerY - goalY, 2));
	if (distance < 20.0f) {
			gameState = WIN;
		/*glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(0, 1, 0);
		char* p0s[20];
		sprintf((char*)p0s, "You Win!, Your Score: %d", gameScore);
		print(500, 300, (char*)p0s);*/
		
	}
}

void StarTimer(int value) {
	for (int i = 0; i < numberOfStars; i++) {
		starY[i] -= 0.1f;
		if (starY[i] < 0) {
			starY[i] = 600;
		}
	}

	glutPostRedisplay();
	glutTimerFunc(16, StarTimer, 0);
}
void Display() {
	
	if (gameState == PLAYING) {
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		



		// El gamescore ely fo2
		glColor3f(1.0f, 1.0f, 1.0f);
		char scoreText[50];
		sprintf(scoreText, "Score: %d", gameScore);
		print(500, 570, scoreText);

		// Time 
		char timeText[50];
		sprintf(timeText, "Time: %d s", remainingTime);
		print(850, 570, timeText);

		//Print el Collectables w el Powerups

		for (int i = 0; i < numCollectables; i++) {
			if (collectableCollected[i] == false) {
				//glColor3f(1.0f, 0.0f, 0.0f); // Red color
				//glPointSize(10);
				//glBegin(GL_POINTS);
				//glVertex2f(collectableX[i], collectableY[i]);
				//glEnd();
				DrawCollectables(collectableX[i], collectableY[i], rotationCollectableAngle);	
			
			}

		}

		for (int i = 0; i < numPowerUpSpeed; i++) {
			if (powerUpSpeedCollected[i] == false) {
				//glColor3f(0.0f, 0.0f, 1.0f); // Blue color
				//glPointSize(10);
				//glBegin(GL_POINTS);
				//glVertex2f(powerUpSpeedX[i], powerUpSpeedY[i]);
				//glEnd();
				DrawSpeedBoostPowerup(powerUpSpeedX[i], powerUpSpeedY[i]);
			}
		}

		for (int i = 0; i < numPowerUpDouble; i++) {
			if (powerUpDoubleCollected[i] == false) {
				//glColor3f(0.4f, 0.5f, 0.7f); // Blue color
				//glPointSize(10);
				//glBegin(GL_POINTS);
				//glVertex2f(powerUpDoubleX[i], powerUpDoubleY[i]);
				//glEnd();
				DrawDoubleScoreBoostPowerup(powerUpDoubleX[i], powerUpDoubleY[i]);
			}
		}
		

		// THIS WILL BE USED TO SHOW THE SCORE AFTER END GAME.
		/*	glColor3f(1, 0, 0);
		char* p0s[20];
		sprintf((char*)p0s, "Score: %d", 50);
		print(500, 300, (char*)p0s); */
		DrawGoal(goalX, goalY);
		DrawPlayer();
		DrawStars();
		glutSwapBuffers();
		DrawObstacles();
		DrawSceneBoundaries();
		CheckCollisionWithCollectable();
		DrawPlayerLiveAndHealth();
		CheckCollisionWithObstacles();
		CheckCollisionWithSceneBoundaries();
		CheckCollisionWithGoal();
		CheckCollisionWithPowerUps();
	}
	else if (gameState == WIN) {
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(0.0f, 1.0f, 0.0f); // Green color
		char winText[50];
		sprintf(winText, "You Win!, Your Score: %d", gameScore);
		print(500, 300, winText);

	}
	else if (gameState == LOSE) {
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(1.0f, 0.0f, 0.0f); // Red color
		char loseText[50];
		sprintf(loseText, "You Lose!, Your Score: %d", gameScore);
		print(500, 300, loseText);

	}
		glFlush();
	
	
	
}


void main(int argc, char** argr) {
	glutInit(&argc, argr);

	glutInitWindowSize(1000, 600);

	glutCreateWindow("PowerCollect: Galactic Prize Quest");
	glutDisplayFunc(Display);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	gluOrtho2D(0.0, 1000, 0.0, 600);
	glutTimerFunc(1000, Timer, 0);
	glutKeyboardFunc(KeyboardMove);
	srand(static_cast<unsigned>(time(nullptr)));
	InitializeStars();	
	InitializeCollectablesAndPowerUps();
	glutTimerFunc(0, StarTimer, 0);
	glutTimerFunc(0, CollectablesRotationTimer, 0);
	glutTimerFunc(16, GoalTimer, 0);
	glutTimerFunc(16, PowerUpSpeedHoverTimer, 0);
	glutTimerFunc(16, PowerUpDoubleHoverTimer, 0);


	glutMainLoop();
}
