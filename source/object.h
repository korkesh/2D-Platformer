//
//  object.h
//  opengl-series
//
//  Created by Matthew Correia on 2014-09-30.
//
//

#ifndef __opengl_series__object__
#define __opengl_series__object__

#include <iostream>
#include "sharedHeaders.h"
#include "sprite.h"

class Object {
    // Object Parameters
    Position objectPosition;
    float objectWidth;
    float objectHeight;
    
    int objectID;
    
    // Toggles
    bool collide;
    bool lethal; // Levels of lethality?
    bool fallThrough;
    bool render;
    
    Sprite objectSprite;
    
public:
    // Constructor/Destructor
    Object();
    Object(float x, float y, float w, float h, bool c, bool l, bool f, const char *s);
    ~Object();
    
    // Setters & Getters
    void setObjectPosition(float x, float y) { objectPosition.posX = x; objectPosition.posY = y; }
    Position getObjectPosition(void) { return objectPosition; }
    
    void setObjectWidth(float w) { objectWidth = w; }
    float getObjectWidth(void) { return objectWidth; }
    
    void setObjectHeight(float h) { objectHeight = h; }
    float getObjectHeight(void) { return objectHeight; }
    
    void setCollide(bool c) { collide = c; }
    void setLethal(bool l) { lethal = l; }
    void setRender(bool r) { render = r; }
    bool getFallThrough(void) { return fallThrough; }
    
    void setObjectSprite(float w, float h, const char *s);

    // Functions
    void renderObject(void);
    bool collideObject(Position playerPosition, float playerWidth, float playerHeight);
    
};

#endif /* defined(__opengl_series__object__) */
