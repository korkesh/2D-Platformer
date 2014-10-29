//
//  player.cpp
//  opengl-series
//
//  Created by Matthew Correia on 2014-09-17.
//
//

#include "player.h"
#include "goomba.h"

Player::Player(void) {
    playerPosition.posX = 50.0f;
    playerPosition.posY = HEIGHT - 165;
    playerPosition.velX = 4.0f;
    playerPosition.velY = 0.0f;
    
    width = 14;
    height = 20;
    
    lives = 5;
    gravity = -0.5f;
    
    playerState = IDLE;
    isJumping = false;
    isCrouching = false;
    
    toggleRun = true;
}

void Player::initializeSprite() {
    GLuint tex_2d = SOIL_load_OGL_texture
	(
     "marioDead.png",
     SOIL_LOAD_AUTO,
     SOIL_CREATE_NEW_ID,
     SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
     );
    
    playerSpriteDead = Sprite();
    playerSpriteDead.initializeSprite(tex_2d, 0, 0, width, height);
    
    if( 0 == tex_2d )
    {
        printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
    }
    
    tex_2d = SOIL_load_OGL_texture
	(
     "marioidle.png",
     SOIL_LOAD_AUTO,
     SOIL_CREATE_NEW_ID,
     SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
     );
    
    playerSpriteIdle = Sprite();
    playerSpriteIdle.initializeSprite(tex_2d, 0, 0, width, height);
    
    if( 0 == tex_2d )
    {
        printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
    }
    
    tex_2d = SOIL_load_OGL_texture
	(
     "mario.png",
     SOIL_LOAD_AUTO,
     SOIL_CREATE_NEW_ID,
     SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
     );
    
    playerSpriteIdleRight = Sprite();
    playerSpriteIdleRight.initializeSprite(tex_2d, 0, 0, width, height);
    
    if( 0 == tex_2d )
    {
        printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
    }
    
    tex_2d = SOIL_load_OGL_texture
	(
     "marioRun.png",
     SOIL_LOAD_AUTO,
     SOIL_CREATE_NEW_ID,
     SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
     );
    
    playerSpriteRunRight = Sprite();
    playerSpriteRunRight.initializeSprite(tex_2d, 0, 0, width, height);
    
    if( 0 == tex_2d )
    {
        printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
    }
    
    tex_2d = SOIL_load_OGL_texture
	(
     "marioIdleLeft.png",
     SOIL_LOAD_AUTO,
     SOIL_CREATE_NEW_ID,
     SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
     );
    
    playerSpriteIdleLeft = Sprite();
    playerSpriteIdleLeft.initializeSprite(tex_2d, 0, 0, width, height);
    
    if( 0 == tex_2d )
    {
        printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
    }
    
    tex_2d = SOIL_load_OGL_texture
	(
     "marioRunLeft.png",
     SOIL_LOAD_AUTO,
     SOIL_CREATE_NEW_ID,
     SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
     );
    
    playerSpriteRunLeft = Sprite();
    playerSpriteRunLeft.initializeSprite(tex_2d, 0, 0, width, height);
    
    if( 0 == tex_2d )
    {
        printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
    }
    
    tex_2d = SOIL_load_OGL_texture
	(
     "marioJumpRight.png",
     SOIL_LOAD_AUTO,
     SOIL_CREATE_NEW_ID,
     SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
     );
    
    playerSpriteJumpRight = Sprite();
    playerSpriteJumpRight.initializeSprite(tex_2d, 0, 0, width, height);
    
    if( 0 == tex_2d )
    {
        printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
    }
    
    tex_2d = SOIL_load_OGL_texture
	(
     "marioJumpLeft.png",
     SOIL_LOAD_AUTO,
     SOIL_CREATE_NEW_ID,
     SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
     );
    
    playerSpriteJumpLeft = Sprite();
    playerSpriteJumpLeft.initializeSprite(tex_2d, 0, 0, width, height);
    
    if( 0 == tex_2d )
    {
        printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
    }
    
    tex_2d = SOIL_load_OGL_texture
	(
     "marioCrouchRight.png",
     SOIL_LOAD_AUTO,
     SOIL_CREATE_NEW_ID,
     SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
     );
    
    playerSpriteCrouchRight = Sprite();
    playerSpriteCrouchRight.initializeSprite(tex_2d, 0, 0, width, height);
    
    if( 0 == tex_2d )
    {
        printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
    }
    
    tex_2d = SOIL_load_OGL_texture
	(
     "marioCrouchLeft.png",
     SOIL_LOAD_AUTO,
     SOIL_CREATE_NEW_ID,
     SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
     );
    
    playerSpriteCrouchLeft = Sprite();
    playerSpriteCrouchLeft.initializeSprite(tex_2d, 0, 0, width, height);
    
    if( 0 == tex_2d )
    {
        printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
    }
}

Player::~Player(void) {
    
}

void Player::updatePosition(float maxWidth, float maxHeight, Object* objects, int numObjects, Goomba *goomba) {
    
    Position previousPosition = playerPosition;
    
    if (!isCrouching) {
        switch (playerState) {
            case LEFT:
                playerPosition.posX -= playerPosition.velX;
                break;
            case RIGHT:
                playerPosition.posX += playerPosition.velX;
                break;
            default:
                break;
        }
    }
    
    // Apply Gravity
    if (isJumping) {
        playerPosition.posY -= playerPosition.velY;
        playerPosition.velY += gravity;
    }
    
    if (playerState == DEAD) {
        return;
    }
    
    // Test for collision with objects
    bool collide = false;
    for (int i = 0 ; i < numObjects; i++) {
        Object* currentObject = &objects[i];
        if (currentObject->collideObject(playerPosition, width / 2, height - 1.0f)) {
            collide = true;
            if (isJumping && playerPosition.velY >= 0) {
                if (currentObject->getFallThrough()) {
                    continue;
                }
                /** Reposition Player directly Under Collided Object **/
                playerPosition = previousPosition;
                playerPosition.posY = currentObject->getObjectPosition().posY + (currentObject->getObjectHeight() / 2) + (height / 2);
                playerPosition.velY = 0;
            } else if (playerPosition.velY < 0) {
                if (currentObject->getFallThrough() &&
                    ((playerPosition.posY > (currentObject->getObjectPosition().posY + (currentObject->getObjectHeight() / 2))))) {
                    playerPosition.posX = previousPosition.posX;
                    continue;
                }
                playerPosition = previousPosition;
               // playerPosition.velY = 0.0;
                isJumping = false;
            } else {
                playerPosition = previousPosition;
            }
            break;
        }
    }
    
    // Test collision with Goomba
    if (goomba->collideEnemy(playerPosition, width, height) && playerPosition.velY < 0) {
        goomba->killGoomba();
    }
    
    if (!isJumping && playerPosition.posY + (height / 2) < maxHeight) {
        playerPosition.posY -= playerPosition.velY;
        playerPosition.velY += gravity;
        
        for (int i = 0 ; i < numObjects; i++) {
            Object* currentObject = &objects[i];
            if (currentObject->collideObject(playerPosition, width / 2, height - 1.0f)) {
                if (currentObject->getFallThrough() && isCrouching) {
                    break;
                }
                playerPosition.posY = previousPosition.posY;
                playerPosition.velY = 0.0f;
                break;
            }
        }
    }
    
    //TODO: Magic Number Floor Boundry
    if (playerPosition.posY + (height / 2) > maxHeight) {
        playerPosition.posY = maxHeight;
        isJumping = false;
        playerPosition.velY = 0.0f;
    }
    
    // Check Screen Boundries
    if (playerPosition.posX + (width / 2) > maxWidth) {
        playerPosition.posX = maxWidth - (width / 2);
    }
    if (playerPosition.posX - (width / 2) < 0) {
        playerPosition.posX = 0 + (width / 2);
    }
    if (playerPosition.posY + (height / 2) > maxHeight) {
        playerPosition.posY = maxHeight - (height / 2);
    }
    if (playerPosition.posY - (height / 2) < 0) {
        playerPosition.posY = 0 + (height / 2);
    }
    
}

void Player::updatePlayerAnimation(float time) {
    if (time < 0) {
		return;
	}
	
	elapsedTime += time;
	if (elapsedTime < 1000000000) {
		elapsedTime -= (int)elapsedTime;
	}
	else {
		elapsedTime = 0;
	}
}

void Player::renderPlayer(void) {
    glEnable(GL_TEXTURE_2D);
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    if (playerState == IDLE) {
        if (isJumping) {
            glBindTexture(GL_TEXTURE_2D, playerSpriteJumpRight.getID());
        } else if (isCrouching) {
            glBindTexture(GL_TEXTURE_2D, playerSpriteCrouchRight.getID());
        } else {
            glBindTexture(GL_TEXTURE_2D, playerSpriteIdle.getID());
        }
    } else if (playerState == RIGHT) {
        if (isJumping) {
            glBindTexture(GL_TEXTURE_2D, playerSpriteJumpRight.getID());
        } else if (isCrouching) {
            glBindTexture(GL_TEXTURE_2D, playerSpriteCrouchRight.getID());
        } else {
            if (toggleRun) {
                glBindTexture(GL_TEXTURE_2D, playerSpriteRunRight.getID());
                if (elapsedTime > (float)(FPS/250.0f)) {
                    toggleRun = false;
                    elapsedTime = 0.0;
                }
            } else {
                glBindTexture(GL_TEXTURE_2D, playerSpriteIdleRight.getID());
                if (elapsedTime > (float)(FPS/250.0f)) {
                    toggleRun = true;
                    elapsedTime = 0.0;
                }
            }
        }
    } else if (playerState == LEFT) {
        if (isJumping) {
            glBindTexture(GL_TEXTURE_2D, playerSpriteJumpLeft.getID());
        } else if (isCrouching) {
            glBindTexture(GL_TEXTURE_2D, playerSpriteCrouchLeft.getID());
        } else {
            if (toggleRun) {
                glBindTexture(GL_TEXTURE_2D, playerSpriteRunLeft.getID());
                if (elapsedTime > (float)(FPS/250.0f)) {
                    toggleRun = false;
                    elapsedTime = 0.0;
                }
            } else {
                glBindTexture(GL_TEXTURE_2D, playerSpriteIdleLeft.getID());
                if (elapsedTime > (float)(FPS/250.0f)) {
                    toggleRun = true;
                    elapsedTime = 0.0;
                }
            }
        }
    } else if (playerState == DEAD) {
        glBindTexture(GL_TEXTURE_2D, playerSpriteDead.getID());
    }
    
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f);
        glVertex2f(playerPosition.posX - (width / 2), playerPosition.posY + (height / 2));
    
        glTexCoord2f(0.0f, 1.0f);
        glVertex2f(playerPosition.posX - (width / 2), playerPosition.posY - (height / 2));
    
        glTexCoord2f(1.0f, 1.0f);
        glVertex2f(playerPosition.posX + (width / 2), playerPosition.posY - (height / 2));
    
        glTexCoord2f(1.0f, 0.0f);
        glVertex2f(playerPosition.posX + (width / 2), playerPosition.posY + (height / 2));
    glEnd();
        
    glDisable(GL_TEXTURE_2D);
    glClear(GL_DEPTH_BUFFER_BIT);
}
