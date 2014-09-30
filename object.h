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
    
    Sprite objectSprite;
    
public:
    // Constructor/Destructor
    Object();
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
    
    void setObjectSprite(float w, float h, const char *s);

    // Functions
    void renderObject(void);
    bool collideObject(float x, float y, float width, float height);
    
};

#endif /* defined(__opengl_series__object__) */
