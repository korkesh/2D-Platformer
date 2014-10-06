//
//  level.h
//  opengl-series
//
//  Created by Matthew Correia on 2014-09-23.
//
//

#ifndef __opengl_series__level__
#define __opengl_series__level__

#include <iostream>
#include "sharedHeaders.h"
#include "sprite.h"
#include "object.h"

class Level {
    float posX;
    float posY;
    
    float width;
    float height;
    
    bool collision;
    
    Sprite levelSprite;
    Sprite levelSpriteGroundTop;
    Sprite levelSpriteGroundBottom;
    
    Object test;
    
public:
    Level(float x = 0, float y = 0, float w = 0, float h = 0, bool c = false);
    ~Level();
    
    float getLevelWidth(void) { return width; }
    float getLevelHeight(void) { return height; }
    
    void setLevelSprite(float w, float h);
    
    Object getObjectList(void) { return test; }
    
    void renderLevel(void);
};

#endif /* defined(__opengl_series__level__) */
