//
//  sprite.cpp
//  opengl-series
//
//  Created by Matthew Correia on 2014-09-23.
//
//

#include "sprite.h"

Sprite::Sprite() {
    textureID = -1;
    posX = 0;
    posY = 0;
    width = 0;
    height = 0;
}

Sprite::~Sprite() {
    
}

void Sprite::initializeSprite(GLuint id, int x, int y, int w, int h) {
    textureID = id;
    posX = x;
    posY = y;
    width = w;
    height = h;
}
