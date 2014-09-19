//
//  player.cpp
//  opengl-series
//
//  Created by Matthew Correia on 2014-09-17.
//
//

#include "player.h"

Player::Player(void) {
    playerPosition.posX = WIDTH / 2;
    playerPosition.posY = HEIGHT - 165;
    playerPosition.velX = 7.0f;
    playerPosition.velY = 0.0f;
    
    width = 25.0f;
    height = 25.0f;;
    
    lives = 5;
    gravity = -0.5f;
    
    playerState = IDLE;
    isJumping = false;
}

Player::~Player(void) {
    
}

void Player::updatePosition(void) {
    
    switch (playerState) {
        /*case UP:
            playerPosition.posY -= playerPosition.velY;
            break;
        case DOWN:
            playerPosition.posY += playerPosition.velY;
            break;*/
        case LEFT:
            playerPosition.posX -= playerPosition.velX;
            break;
        case RIGHT:
            playerPosition.posX += playerPosition.velX;
            break;
        default:
            break;
    }
    
    // Apply Gravity
    if (isJumping) {
        playerPosition.posY -= playerPosition.velY;
        playerPosition.velY += gravity;
    }
    
    //TODO: Magic Number Floor Boundry
    if (playerPosition.posY - (height / 2) > HEIGHT - 170) {
        playerPosition.posY = HEIGHT - 165;
        isJumping = false;
    }

    // Check Screen Boundries
    if (playerPosition.posX + (width / 2) > WIDTH) {
        playerPosition.posX = WIDTH - (width / 2);
    }
    if (playerPosition.posX - (width / 2) < 0) {
        playerPosition.posX = 0 + (width / 2);
    }
    if (playerPosition.posY + (height / 2) > HEIGHT) {
        playerPosition.posY = HEIGHT - (height / 2);
    }
    if (playerPosition.posY - (height / 2) < 0) {
        playerPosition.posY = 0 + (height / 2);
    }
}

void Player::renderPlayer(void) {
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, marioSprite);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
        glTexCoord2f(1.0f, 0.0f);
        glVertex2f(playerPosition.posX - (width / 2), playerPosition.posY + (height / 2));
    
        glTexCoord2f(1.0f, 1.0f);
        glVertex2f(playerPosition.posX - (width / 2), playerPosition.posY - (height / 2));
    
        glTexCoord2f(0.0f, 1.0f);
        glVertex2f(playerPosition.posX + (width / 2), playerPosition.posY - (height / 2));
    
        glTexCoord2f(0.0f, 0.0f);
        glVertex2f(playerPosition.posX + (width / 2), playerPosition.posY + (height / 2));
    glEnd();
    
    glDisable(GL_TEXTURE_2D);

}
