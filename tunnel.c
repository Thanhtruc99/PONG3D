//tunnel.c
#include <GL/glut.h>
#include "tunnel.h"
#include <math.h>

Vector3f cameraPosition = {0.0, 0.0, -30.0};
float cameraAngle = 0.0;
float rotationAngleX = 0.0;
float rotationAngleZ = 0.0;


float halfWidth = 5.0;
float height = 20.0;

void drawTunnel() {
    glPushMatrix(); // Save the current matrix
    glRotatef(rotationAngleX, 1.0, 0.0, 0.0); // Rotation autour de l'axe X (gauche-droite)
    glRotatef(rotationAngleZ, 0.0, 0.0, 1.0);

    glEnable(GL_CULL_FACE);

    glBegin(GL_QUADS);

    glColor4f(0.0, 1.0, 2.0, 0.8);
    // Fond (transparence)
    glVertex3f(-halfWidth, -halfWidth * 1.5, -height);
    glVertex3f(-halfWidth, -halfWidth * 1.5, height);
    glVertex3f(-halfWidth, halfWidth * 1.5, height);
    glVertex3f(-halfWidth, halfWidth * 1.5, -height);

    // Dessus (transparence)
    glVertex3f(halfWidth, -halfWidth * 1.5, -height);
    glVertex3f(halfWidth, -halfWidth * 1.5, height);
    glVertex3f(halfWidth, halfWidth * 1.5, height);
    glVertex3f(halfWidth, halfWidth * 1.5, -height);

    // Côté gauche (transparence)
    glColor4f(1.0, 1.0, 1.0, 0.6);
    glVertex3f(-halfWidth, halfWidth * 1.5, -height);
    glVertex3f(halfWidth, halfWidth * 1.5, -height);
    glVertex3f(halfWidth, halfWidth * 1.5, height);
    glVertex3f(-halfWidth, halfWidth * 1.5, height);

    // Côté droit (transparence)
    glVertex3f(-halfWidth, -halfWidth * 1.5, -height);
    glVertex3f(halfWidth, -halfWidth * 1.5, -height);
    glVertex3f(halfWidth, -halfWidth * 1.5, height);
    glVertex3f(-halfWidth, -halfWidth * 1.5, height);

    glEnd();

    // Dessinez les bords bleus (sans transparence)
    glColor3f(0.0, 0.0, 1.0);
    glLineWidth(15.0);       

    glBegin(GL_LINE_LOOP);
    glVertex3f(-halfWidth, -halfWidth * 1.5, -height);
    glVertex3f(-halfWidth, -halfWidth * 1.5, height);
    glVertex3f(-halfWidth, halfWidth * 1.5, height);
    glVertex3f(-halfWidth, halfWidth * 1.5, -height);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex3f(halfWidth, -halfWidth * 1.5, -height);
    glVertex3f(halfWidth, -halfWidth * 1.5, height);
    glVertex3f(halfWidth, halfWidth * 1.5, height);
    glVertex3f(halfWidth, halfWidth * 1.5, -height);
    glEnd();

    glBegin(GL_LINES);
    glVertex3f(-halfWidth, -halfWidth * 1.5, -height);
    glVertex3f(halfWidth, -halfWidth * 1.5, -height);

    glVertex3f(-halfWidth, -halfWidth * 1.5, height);
    glVertex3f(halfWidth, -halfWidth * 1.5, height);

    glVertex3f(-halfWidth, halfWidth * 1.5, height);
    glVertex3f(halfWidth, halfWidth * 1.5, height);

    glVertex3f(-halfWidth, halfWidth * 1.5, -height);
    glVertex3f(halfWidth, halfWidth * 1.5, -height);
    glEnd();

    glPopMatrix(); // Restore the previous matrix
}

void updateCamera() {
    glLoadIdentity();
    gluLookAt(cameraPosition.x, cameraPosition.y, cameraPosition.z,
              cameraPosition.x + cos(cameraAngle), cameraPosition.y + sin(cameraAngle), 0.0,
              0.0, 0.0, 1.0);
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (double)w / (double)h, 0.1, 100.0); 
    glMatrixMode(GL_MODELVIEW);
}