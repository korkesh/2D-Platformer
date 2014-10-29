//
//  goomba.h
//  opengl-series
//
//  Created by Matthew Correia on 2014-10-28.
//
//

#ifndef __opengl_series__goomba__
#define __opengl_series__goomba__

#include <iostream>
#include "enemy.h"

class Player;

class Goomba : public Enemy {
    bool isJumping;
    
    // Sprite
    Sprite goombaSpriteDead;
    Sprite goombaSpriteIdle;
    Sprite goombaSpriteRun;
    
public:
    // Constructor/Destructor
    Goomba();
    ~Goomba();
    
    void initializeSprite();
    
    void killGoomba();
    
    //Position
    void updatePosition(float maxWidth, float maxHeight,  Object* objects, int numObjects, Player *player);
    bool collideEnemy(Position playerPosition, float playerWidth, float playerHeight);
    
    // Render
    void renderEnemy(void);
    
    // Animation
    void updateEnemyAnimation(float time);
};

#endif /* defined(__opengl_series__goomba__) */
