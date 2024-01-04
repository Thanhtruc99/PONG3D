//panel.c
#include <GL/glut.h>
#include "panel.h"
#include "tunnel.h"
#include <math.h>

#define PI 3.1415926535898


extern Vector3f cameraPosition;
extern float cameraAngle;
extern float rotationAngleX;
extern float rotationAngleZ;

Vector3f playerPosition = {0.0, 0.0, 0.0};
Vector3f panelPosition = {0.0, 0.0, 0.0};


void drawPanel() {
    glPushMatrix(); // Save the current matrix
    glRotatef(rotationAngleX, 1.0, 0.0, 0.0); // Rotation autour de l'axe X (gauche-droite)
    glRotatef(rotationAngleZ, 0.0, 0.0, 1.0);
    glColor4f(1.0, 1.0, 1.0, 0.3); // Blanc transparent
    glBegin(GL_QUADS);

    // Panneau avant (machine)
    glVertex3f(-1.5 + panelPosition.x, -2.0 + panelPosition.y, height + panelPosition.z);
    glVertex3f(1.5 + panelPosition.x, -2.0 + panelPosition.y, height + panelPosition.z);
    glVertex3f(1.5 + panelPosition.x, 2.0 + panelPosition.y, height + panelPosition.z);
    glVertex3f(-1.5 + panelPosition.x, 2.0 + panelPosition.y, height + panelPosition.z);
    glEnd();

    glColor3f(0.0, 2.0, 1.0); 
    glLineWidth(15.0);      
    // Machine
    glBegin(GL_LINE_LOOP);
    glVertex3f(-1.5 + panelPosition.x, -2.0 + panelPosition.y, height + panelPosition.z);
    glVertex3f(1.5 + panelPosition.x, -2.0 + panelPosition.y, height + panelPosition.z);
    glVertex3f(1.5 + panelPosition.x, 2.0 + panelPosition.y, height + panelPosition.z);
    glVertex3f(-1.5 + panelPosition.x, 2.0 + panelPosition.y, height + panelPosition.z);
    glEnd();

    glPushMatrix();
    glPopMatrix();

    glPopMatrix(); // Restore the previous matrix
}

void drawPlayer() {
    glPushMatrix();
    glRotatef(rotationAngleX, 1.0, 0.0, 0.0);
    glRotatef(rotationAngleZ, 0.0, 0.0, 1.0);    
    glTranslatef(playerPosition.x, playerPosition.y, -height);

    glColor3f(0.0, 2.0, 1.0); 
    glLineWidth(15.0);  

    // Active le test de profondeur pour voir les deux faces
    glEnable(GL_DEPTH_TEST);

    // Désactive le culling face pour voir les deux côtés du panneau
    glDisable(GL_CULL_FACE);

    // Dessinez le panneau en mode fil de fer avec des bords
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBegin(GL_QUADS);
    // Face avant
    glVertex3f(-1.5, -2.0, 0.0);
    glVertex3f(1.5, -2.0, 0.0);
    glVertex3f(1.5, 2.0, 0.0);
    glVertex3f(-1.5, 2.0, 0.0);

    // Face arrière
    glVertex3f(-1.5, 2.0, 0.0);
    glVertex3f(1.5, 2.0, 0.0);
    glVertex3f(1.5, -2.0, 0.0);
    glVertex3f(-1.5, -2.0, 0.0);
    glEnd();

    // Réactive le culling face après avoir dessiné le panneau
    glEnable(GL_CULL_FACE);

    // Désactive le test de profondeur après avoir dessiné le panneau
    glDisable(GL_DEPTH_TEST);

    // Revenez au mode de rendu normal
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glPopMatrix();
}

void playerMove(int x, int y) {
    // Décalage des coordonnées de la souris par rapport au centre de la fenêtre
    float mouseY = glutGet(GLUT_WINDOW_WIDTH) / 2 - x;
    float mouseX = y - glutGet(GLUT_WINDOW_HEIGHT) / 2;

    // Limitez la position du joueur à la face avant du tunnel
    float maxX = halfWidth - 1.5;
    float minX = -halfWidth + 1.5;
    float maxY = halfWidth * 1.5 - 2.0;
    float minY = -halfWidth * 1.5 + 2.0;

    // Mettez à jour les positions du joueur
    playerPosition.y = fmin(fmax(mouseY / 100.0, minY), maxY);
    playerPosition.x = fmin(fmax(mouseX / 100.0, minX), maxX);

    glutPostRedisplay();
}


