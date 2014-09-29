//
//  sprite.h
//  opengl-series
//
//  Created by Matthew Correia on 2014-09-23.
//
//

#ifndef __opengl_series__sprite__
#define __opengl_series__sprite__

#include "sharedHeaders.h"

class Sprite
{
	GLuint textureID;
    
	int posX;
    int posY;
    int width;
    int height;
	
public:
    Sprite();
    ~Sprite();
    
    GLuint getID() { return textureID; }
    int getWidth() { return width; }
    int getHeight() { return height; }

    void initializeSprite(GLuint textureID, int x, int y, int w, int h);
    
};

#endif /* defined(__opengl_series__sprite__) */
