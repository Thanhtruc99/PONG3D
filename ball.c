//ball.c
#include <GL/glut.h>
#include <math.h>
#include "ball.h"
#include "panel.h"

extern Vector3f playerPosition;
extern Vector3f panelPosition;



#define MAX_BALL_SPEED 0.3

Ball ball = {0.0, 0.0, 0.0, 1.0, 0.1, {0.5, 0.5, 0.5}};
Vector3f BallDirection = {1.0, 1.0, 1.0};

int startBallMovement = 0;
int playerScore = 0;
int machineScore = 0;
int gameStarted = 0;

void drawBall() {
    if (startBallMovement) {
        // Move the ball
        ball.x += ball.speed * BallDirection.x;
        ball.y += ball.speed * BallDirection.y;
        ball.z += ball.speed * BallDirection.z;

        // Check collisions
        checkCollisions();
    }

    glEnable(GL_LIGHTING); // Activer l'éclairage
    glEnable(GL_LIGHT0);   // Activer la source de lumière

    // Position et intensité de la lumière
    GLfloat light_position[] = { 2.0, 2.0, 5.0, 1.0 };
    GLfloat light_intensity[] = { 1.0, 1.0, 1.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_intensity);

    // Lumière ambiante
    GLfloat ambient_light[] = { 0.2, 0.2, 0.2, 1.0 };  // Ajustez les valeurs selon vos besoins
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient_light);

    // Matériau pour la balle
    GLfloat material_ambient[] = { 1.0, 0.0, 0.0, 1.0 }; // Rouge
    GLfloat material_diffuse[] = { 1.0, 0.0, 0.0, 1.0 };
    GLfloat material_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat material_shininess[] = { 50.0 };

    glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, material_shininess);

    // Draw the ball
    glPushMatrix();
    glRotatef(rotationAngleX, 1.0, 0.0, 0.0);
    glRotatef(rotationAngleZ, 0.0, 0.0, 1.0);
    glTranslatef(ball.x, ball.y, ball.z);
    glutSolidSphere(ball.radius, 50, 50);
    glPopMatrix();

    glDisable(GL_LIGHT0); // Désactiver la source de lumière
    glDisable(GL_LIGHTING); // Désactiver l'éclairage
}

void start(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        startBallMovement = 1;
        gameStarted = 0;
    }
}

void timer(int value) {
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

void resetGame() {
    startBallMovement = 0;
    ball.x = 0.0;
    ball.y = 0.0;
    ball.z = 0.0;
    BallDirection.x = 1.0;
    BallDirection.y = 1.0;
    BallDirection.z = 1.0;
    ball.speed = 0.1;
}

void newGame() {
    startBallMovement = 0;
    ball.x = 0.0;
    ball.y = 0.0;
    ball.z = 0.0;
    BallDirection.x = 1.0;
    BallDirection.y = 1.0;
    BallDirection.z = 1.0;
    ball.speed = 0.1;

    playerScore = 0;
    machineScore = 0;
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'q':
            rotationAngleX += 5.0;
            break;
        case 's':
            rotationAngleX -= 5.0;
            break;
        case 27:
            exit(0);
            break;

        case ' ': // Spacebar
            newGame();
            break;
    }

    glutPostRedisplay();
}

void checkCollisions() {
    // Check collision with the player's panel
    if (ball.x + ball.radius > playerPosition.x - 1.5 &&
        ball.x - ball.radius < playerPosition.x + 1.5 &&
        ball.y + ball.radius > playerPosition.y - 2.0 &&
        ball.y - ball.radius < playerPosition.y + 2.0 &&
        ball.z + ball.radius > -height + playerPosition.z &&
        ball.z - ball.radius < -height + playerPosition.z + 1.0) {
        
        // Reverse only the Z direction if the ball is moving towards the panel
        if (BallDirection.z != 0) {
            BallDirection.z = -BallDirection.z;

            // Increase the ball speed up to the maximum speed
            if (ball.speed < MAX_BALL_SPEED) {
                ball.speed += 0.02; // You can adjust the increment as needed
            }
        }
        glutPostRedisplay();
    }

    // Check collision with the machine's panel
    if (ball.x + ball.radius > panelPosition.x - 1.5 &&
        ball.x - ball.radius < panelPosition.x + 1.5 &&
        ball.y + ball.radius > panelPosition.y - 2.0 &&
        ball.y - ball.radius < panelPosition.y + 2.0 &&
        ball.z + ball.radius > height + panelPosition.z &&
        ball.z - ball.radius < height + panelPosition.z + 1.0) {
        BallDirection.z = -BallDirection.z;
        glutPostRedisplay();  // Trigger redisplay in case of collision
    }

    // Check if the ball hits the tunnel walls
    if (ball.x + ball.radius > halfWidth || ball.x - ball.radius < -halfWidth) {
        BallDirection.x = -BallDirection.x;
        glutPostRedisplay();  // Trigger redisplay in case of collision
    }
    if (ball.y + ball.radius > halfWidth * 1.5 || ball.y - ball.radius < -halfWidth * 1.5) {
        BallDirection.y = -BallDirection.y;
        glutPostRedisplay();  // Trigger redisplay in case of collision
    }

    // Check if the ball hits the front or back walls
    if (ball.z + ball.radius > height + 0.2 || ball.z - ball.radius < -height - 0.2) {
        startBallMovement = 0; 
    }
    if (ball.z + ball.radius > height + 0.2){
        playerScore += 1;
        resetGame();
    }
    if (ball.z - ball.radius < -height - 0.2){
        machineScore +=1;
        resetGame();
    }
    
}

void moveAIPanel() {
    panelPosition.x = ball.x * 0.5;
    panelPosition.y = ball.y * 0.5; 
}