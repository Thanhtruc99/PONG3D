//panel.h
#ifndef PANEL_H
#define PANEL_H
#include <math.h>
#include "tunnel.h"


extern Vector3f playerPosition;
extern Vector3f panelPosition;

void drawPanel();
void playerMove(int x, int y);
void drawPlayer();
void moveAIPanel();


#endif // PANEL_H
