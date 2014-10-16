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
    
	int numObjects;
	Object* objects;
    
public:
    Level(float x = 0, float y = 0, float w = 0, float h = 0, bool c = false);
    ~Level();
    
    float getLevelWidth(void) { return width; }
    float getLevelHeight(void) { return height; }
    
    void setLevelSprite(float w, float h);
    
    Object* getObjects(void) { return objects; }
    int getNumObjects(void) { return numObjects; }
    
    void renderLevel(void);
    
    void loadLevelFromFile(const char* file);
    void drawLevel();
    bool checkCollisions(Position playerPosition, float playerWidth, float playerHeight);

};

#endif /* defined(__opengl_series__level__) */
