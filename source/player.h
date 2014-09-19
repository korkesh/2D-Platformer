//
//  player.h
//  opengl-series
//
//  Created by Matthew Correia on 2014-09-17.
//
//

#ifndef __opengl_series__player__
#define __opengl_series__player__

#include <iostream>
#include "sharedHeaders.h"

enum Player_State {IDLE, DEAD, UP, DOWN, LEFT, RIGHT};

class Player {
    // Position
    Position playerPosition;
    
    // Size
    float width;
    float height;
    
    // Misc
    int lives;
    float gravity;
    
    // State
    Player_State playerState;
    bool isJumping;
    
public:
    // Constructor/Destructor
    Player(void);
    ~Player(void);
    
    // Setters/Getters
    void setPosition(float x, float y) { playerPosition.posX = x; playerPosition.posY = y; }
    Position getPoition(void) { return playerPosition; }
    void setVelY(float s) { playerPosition.velY = s; }
    float getVelY(void) { return playerPosition.velY; }
    
    void setSize(float w, float h) { width = w; height = h; }
    float getWidth(void) { return width; }
    float getHeight(void) { return height; }
    
    void setLives(int l) { lives = l; }
    void increaseLives(void) { lives += 1; }
    int getLives(void) { return lives; }
    
    float getGravity(void) { return gravity; }
    
    void setState(Player_State state) { playerState = state; }
    Player_State getState(void) { return playerState; }
    
    void setIsJumping(bool b) { isJumping = b; }
    bool getIsJumping(void) { return isJumping; }

    
    //Position
    void updatePosition(void);
    
    
    // Render
    void renderPlayer(void);
    
};

#endif /* defined(__opengl_series__player__) */
