//
//  enemy.cpp
//  opengl-series
//
//  Created by Matthew Correia on 2014-10-28.
//
//

#include "enemy.h"

Enemy::Enemy(void) {
    enemyPosition.posX = 500.0f;
    enemyPosition.posY = HEIGHT - 58;
    enemyPosition.velX = 1.0f;
    enemyPosition.velY = 0.0f;
    
    width = 16;
    height = 16;
    
    health = 1;
    gravity = -0.5f;

    enemyState = eIDLE;
    toggleRun = true;
}

Enemy::~Enemy(void) {
    
}