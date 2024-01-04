//main.c 
#include <GL/glut.h>
#include <stdio.h>
#include "ball.h"
#include "panel.h"
#include "tunnel.h"


#define PI 3.1415926535898
#define MAX_BALL_SPEED 0.3


extern Vector3f cameraPosition;
extern float cameraAngle;
extern float rotationAngleX;
extern float rotationAngleZ;


extern Vector3f playerPosition;
extern Vector3f panelPosition;

extern Ball ball;
extern Vector3f BallDirection;
extern int startBallMovement;
extern int playerScore;
extern int machineScore;
extern int gameStarted;

void drawPanel();
void playerMove(int x, int y);
void drawPlayer();
void drawTunnel();
void moveAIPanel();
void drawBall();
void checkCollisions();
void start();

void timer();
void keyboard(unsigned char key, int x, int y);


void updateCamera();
void reshape();


void drawScores() {
    // Draw player score
    glColor3f(1.0, 1.0, 1.0);  // White
    glRasterPos2f(10, 29);
    char playerScoreText[20];
    snprintf(playerScoreText, sizeof(playerScoreText), "Player: %d", playerScore);
    for (int i = 0; playerScoreText[i] != '\0'; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, playerScoreText[i]);
    }

    // Draw machine score
    glColor3f(1.0, 1.0, 1.0);  // White
    glRasterPos2f(-10, 29);
    char machineScoreText[20];
    snprintf(machineScoreText, sizeof(machineScoreText), "Machine: %d", machineScore);
    for (int i = 0; machineScoreText[i] != '\0'; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, machineScoreText[i]);
    }
}



void gameRule() {

    glColor3f(1.0, 1.0, 1.0);  // White
    glRasterPos2f(-10, -24);
    char ruleText[50];
    snprintf(ruleText, sizeof(ruleText),"How to play: \n");


    for (int i = 0; ruleText[i] != '\n'; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ruleText[i]);
    }
}
void gameRule1() {

    glColor3f(1.0, 1.0, 1.0);  // White
    glRasterPos2f(-6, -24);
    char ruleText1[50];
    snprintf(ruleText1, sizeof(ruleText1),"Click to start\n");


    for (int i = 0; ruleText1[i] != '\n'; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ruleText1[i]);
    }
}
void gameRule2() {

    glColor3f(1.0, 1.0, 1.0);  // White
    glRasterPos2f(-4, -24);
    char ruleText2[50];
    snprintf(ruleText2, sizeof(ruleText2),"Mouse control\n");


    for (int i = 0; ruleText2[i] != '\n'; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ruleText2[i]);
    }
}
void gameRule3() {

    glColor3f(1.0, 1.0, 1.0);  // White
    glRasterPos2f(-2, -24);
    char ruleText3[50];
    snprintf(ruleText3, sizeof(ruleText3),"Space to reset\n");


    for (int i = 0; ruleText3[i] != '\n'; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ruleText3[i]);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    updateCamera();
    drawTunnel();
    moveAIPanel();
    drawPanel();
    drawBall();

    drawPlayer();
    drawScores();
    gameRule();
    gameRule1();
    gameRule2();
    gameRule3();

    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1100, 600);
    glutCreateWindow("PONG 3D");

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutPassiveMotionFunc(playerMove);
    glutMouseFunc(start);
    glutTimerFunc(0, timer, 0);
    glutKeyboardFunc(keyboard);

    glutMainLoop();

    return 0;
}
