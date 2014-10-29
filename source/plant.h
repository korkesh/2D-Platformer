//
//  plant.h
//  opengl-series
//
//  Created by Matthew Correia on 2014-10-29.
//
//

#ifndef __opengl_series__plant__
#define __opengl_series__plant__

#include <iostream>
#include "sharedHeaders.h"
#include "enemy.h"

class Player;

class Plant : public Enemy {
    bool isJumping;
    float landTime;

    // Sprite
    Sprite plantSpriteJump[4];
    int plantSpriteIndex;
    
public:
    // Constructor/Destructor
    Plant();
    ~Plant();
    
    void initializeSprite();
    
    //Position
    void updatePosition(float maxWidth, float maxHeight,  Object* objects, int numObjects, Player *player);
    bool collideEnemy(Position playerPosition, float playerWidth, float playerHeight);
    
    // Render
    void renderEnemy(void);
    
    // Animation
    void updateEnemyAnimation(float time);
};

#endif /* defined(__opengl_series__plant__) */
