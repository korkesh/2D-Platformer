//
//  koopa.h
//  opengl-series
//
//  Created by Matthew Correia on 2014-10-28.
//
//

#ifndef __opengl_series__koopa__
#define __opengl_series__koopa__

#include <iostream>
#include "enemy.h"

class Player;

class Koopa : public Enemy {
    bool isJumping;
    bool isTurning;
    bool isShell;
    
    // Sprite
    Sprite koopaSpriteTurnLeft;
    Sprite koopaSpriteTurnRight;
    Sprite koopaSpriteWalkLeft;
    Sprite koopaSpriteWalkRight;
    Sprite koopaSpriteIdleLeft;
    Sprite koopaSpriteIdleRight;
    Sprite koopaSpriteShell[4];
    
    int koopaSpriteIndex;
    
public:
    // Constructor/Destructor
    Koopa();
    ~Koopa();
    
    void initializeSprite();
    
    void killKoopa(Player_State playerState);
    
    //Position
    void updatePosition(float maxWidth, float maxHeight,  Object* objects, int numObjects, Player *player);
    bool collideEnemy(Position playerPosition, float playerWidth, float playerHeight);
    
    // Render
    void renderEnemy(void);
    
    // Animation
    void updateEnemyAnimation(float time);
};


#endif /* defined(__opengl_series__goomba__) */
