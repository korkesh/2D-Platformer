//
//  UI.cpp
//  openGLTutorial
//
//  Created by Matthew Correia on 2014-07-15.
//  Copyright (c) 2014 Matthew Correia. All rights reserved.
//

#include <GLUT/GLUT.h>
#include <sstream>

#include "UI.h"
#include "texture.h"

#define WIDTH (1024)
#define HEIGHT (768)

int score = -2;
int health = 100;

void drawMenu()
{
    
}

void drawUI() {
    glDisable(GL_LIGHTING);
    
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0.0, WIDTH, 0.0, HEIGHT);
    
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
}