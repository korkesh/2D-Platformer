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
#include "sprite.h"

class Object;
class Goomba;
class Koopa;

enum Player_State {IDLE, DEAD, UP, DOWN, LEFT, RIGHT, RESPAWN, GAMEOVER};

class Player {
    // Position
    Position playerPosition;
    
    // Size
    float width;
    float height;
    
    // Misc
    int lives;
    float gravity;
    int playerScore;
    int coins;
    
    // State
    Player_State playerState;
    bool isJumping;
    bool isCrouching;
    bool toggleRun;
    
    // Sprite
    Sprite playerSpriteDead;
    Sprite playerSpriteIdle;
    Sprite playerSpriteIdleRight;
    Sprite playerSpriteRunRight;
    Sprite playerSpriteIdleLeft;
    Sprite playerSpriteRunLeft;
    Sprite playerSpriteJumpLeft;
    Sprite playerSpriteJumpRight;
    Sprite playerSpriteCrouchLeft;
    Sprite playerSpriteCrouchRight;

    // Animation
    float elapsedTime;
    
public:
    // Constructor/Destructor
    Player(void);
    ~Player(void);
    
    // Setters/Getters
    void setPosition(float x, float y) { playerPosition.posX = x; playerPosition.posY = y; }
    Position getPosition(void) { return playerPosition; }
    void setVelY(float s) { playerPosition.velY = s; }
    float getVelY(void) { return playerPosition.velY; }
    float getVelX(void) { return playerPosition.velX; }
    
    void setSize(float w, float h) { width = w; height = h; }
    float getWidth(void) { return width; }
    float getHeight(void) { return height; }
    
    void setLives(int l) { lives = l; }
    void increaseLives(void) { lives += 1; }
    void decreaseLives(void) {
        if (playerState == DEAD) return;
        lives -= 1;
        playerState = DEAD;
        isJumping = true;
        playerPosition.velY = 5.0f;
        if (lives == 0) {
            playerState = GAMEOVER;
        }
    }
    int getLives(void) { return lives; }
    
    float getGravity(void) { return gravity; }
    
    void setPlayerScore(int s) { playerScore = s; }
    int getPlayerScore(void) { return playerScore; }

    void setCoins(int s) { coins = s; }
    int getCoins(void) {return coins; }
    
    void setState(Player_State state) { playerState = state; }
    Player_State getState(void) { return playerState; }
    
    void setIsJumping(bool b) { isJumping = b; }
    bool getIsJumping(void) { return isJumping; }

    void setIsCrouching(bool c) { isCrouching = c; }
    bool getIsCrouching(void) { return isCrouching; }
    
    void initializeSprite();
    
    //Position
    void updatePosition(float maxWidth, float maxHeight,  Object* objects, int numObjects, Goomba *goomba, Goomba *goomba2, Koopa *koopa);
    
    // Render
    void renderPlayer(void);
    
    // Animation
    void updatePlayerAnimation(float time);
};

#endif /* defined(__opengl_series__player__) */
