//
//  generateWorld.cpp
//  openGLTutorial
//
//  Created by Matthew Correia on 2014-07-12.
//  Copyright (c) 2014 Matthew Correia. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <fstream>

#include "generateWorld.h"
#include "object.h"

#define EPSILON (0.9999)

typedef struct Vertex
{
	float x, y, z;
	float u, v;
} vertex;

typedef struct Square
{
	vertex vertex[4];
    GLuint texture;
} square;

typedef struct Level
{
	int numObjects;
	Object* objects;
} sector;


Level level1;

void readstr(FILE *f, char *string)
{
	do
	{
		fgets(string, 255, f);
	} while (/*(string[0] == '/') ||*/ (string[0] == '\n') || (string[0] == '\r'));
    
	return;
}

void SetupWorld()
{
	float x, y, w, h;
    int c, l;
    const char* s = "/Users/Korkesh/2D-Platformer/resources/qBlock.png";
    
    int t;
	int numObjects;
	FILE *filein;
	char oneline[255];
	filein = fopen("/Users/Korkesh/2D-Platformer/resources/level1.txt", "rt"); // File To Load World Data From
    
	readstr(filein, oneline);
	sscanf(oneline, "NUMOBJECTS %d\n", &numObjects);
    
	level1.objects = new Object[numObjects];
	level1.numObjects = numObjects;
	for (int i = 0; i < numObjects; i++)
	{
        readstr(filein, oneline);
        sscanf(oneline, "%f %f %f %f %d %d", &x, &y, &w, &h, &c, &l);
//        readstr(filein, oneline);
//        sscanf(oneline, "%s", s);
        level1.objects[i] = Object(x, y, w, h, c, l, s);
	}
    
	fclose(filein);
	return;
}

void drawSceneFromFile()
{
	int numObjects;
    numObjects = level1.numObjects;
	
    glColor3f(1.0, 1.0, 1.0);
	// Process Each Object
	for (int i = 0; i < numObjects; i++)
	{
        glPushMatrix();
        
        level1.objects[i].renderObject();
        
        glPopMatrix();
	}
	return;
}

bool checkCollisions(Position playerPosition, float playerWidth, float playerHeight)
{
    
    bool collide = false;

    int numObjects;
    numObjects = level1.numObjects;
	
	// Process Each Object
	for (int i = 0; i < numObjects; i++)
	{
        if (level1.objects[i].collideObject(playerPosition, playerWidth, playerHeight)) {
            collide = true;
        }
    }
    
    return collide;
}


