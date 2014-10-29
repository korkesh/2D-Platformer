//
//  enemy.h
//  opengl-series
//
//  Created by Matthew Correia on 2014-10-28.
//
//

#ifndef __opengl_series__enemy__
#define __opengl_series__enemy__

#include <iostream>
#include "sharedHeaders.h"
#include "sprite.h"
#include "object.h"
#include "player.h"

enum Enemy_State {eIDLE, eLEFT, eRIGHT, eDEAD};

class Enemy {
protected:
    // Position
    Position enemyPosition;
    
    // Size
    float width;
    float height;
    
    // Misc
    int health;
    float gravity;

    // State
    Enemy_State enemyState;
    
    // Sprite
    Sprite enemySpriteIdle;
    Sprite enemySpriteRun;
    
    // Animation
    float elapsedTime;
    bool toggleRun;

public:
    // Constructor/Destructor
    Enemy(void);
    ~Enemy(void);
    
    // Setters/Getters
    void setPosition(float x, float y) { enemyPosition.posX = x; enemyPosition.posY = y; }
    Position getPosition(void) { return enemyPosition; }
    void setVelY(float s) { enemyPosition.velY = s; }
    float getVelY(void) { return enemyPosition.velY; }
    float getVelX(void) { return enemyPosition.velX; }
    
    void setSize(float w, float h) { width = w; height = h; }
    float getWidth(void) { return width; }
    float getHeight(void) { return height; }
    
    void setHealth(int h) { health = h; }
    
    void setState(Enemy_State state) { enemyState = state; }
    Enemy_State getState(void) { return enemyState; }
    
    virtual void initializeSprite() = 0;
    
    //Position
    virtual void updatePosition(float maxWidth, float maxHeight,  Object* objects, int numObjects, Player* player) = 0;
    virtual bool collideEnemy(Position playerPosition, float playerWidth, float playerHeight) = 0;
    // Render
    virtual void renderEnemy(void) = 0;
    
    // Animation
    virtual void updateEnemyAnimation(float time) = 0;
};
#endif /* defined(__opengl_series__enemy__) */
