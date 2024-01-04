//ball.h
#ifndef BALL_H
#define BALL_H
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include "tunnel.h" 
#include "panel.h"

typedef struct {
    float x, y, z;
    float radius;
    float speed;
    Vector3f direction;
} Ball;


extern float rotationAngleX;
extern float rotationAngleZ;

extern Ball ball;
extern Vector3f BallDirection;
extern int startBallMovement;
extern int playerScore;
extern int machineScore;
extern int gameStarted;

void drawBall();

void start();
void timer();

void resetGame();
void newGame();
void keyboard(unsigned char key, int x, int y);
void checkCollisions();

void moveAIPanel();


#endif // BALL_H
