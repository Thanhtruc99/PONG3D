//tunnel.h
#ifndef TUNNEL_H
#define TUNNEL_H
#include <math.h>

typedef struct {
    float x, y, z;
} Vector3f;

extern float halfWidth;
extern float height;

extern Vector3f cameraPosition;
extern float cameraAngle;
extern float rotationAngleX;
extern float rotationAngleZ;
extern Vector3f playerPosition;
extern Vector3f panelPosition;

void drawTunnel();
void updateCamera();
void reshape(int w, int h);

#endif // TUNNEL_H
