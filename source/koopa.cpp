//
//  goomba.cpp
//  opengl-series
//
//  Created by Matthew Correia on 2014-10-28.
//
//

#include "koopa.h"

Koopa::Koopa() {
    isJumping = false;
    isTurning = false;
    isShell = false;
    
    enemyPosition.posX = 1100.0f;
    
    width = 16.0f;
    height = 27.0f;
    
    koopaSpriteIndex = 0;
}

Koopa::~Koopa() {
    
}

void Koopa::initializeSprite() {
    GLuint tex_2d = SOIL_load_OGL_texture
    (
     "koopaTurnLeft.png",
     SOIL_LOAD_AUTO,
     SOIL_CREATE_NEW_ID,
     SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
     );
    
    koopaSpriteTurnLeft = Sprite();
    koopaSpriteTurnLeft.initializeSprite(tex_2d, 0, 0, width, height);
    
    if( 0 == tex_2d )
    {
        printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
    }
    
    tex_2d = SOIL_load_OGL_texture
    (
     "koopaTurnRight.png",
     SOIL_LOAD_AUTO,
     SOIL_CREATE_NEW_ID,
     SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
     );
    
    koopaSpriteTurnRight = Sprite();
    koopaSpriteTurnRight.initializeSprite(tex_2d, 0, 0, width, height);
    
    if( 0 == tex_2d )
    {
        printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
    }
    
    tex_2d = SOIL_load_OGL_texture
    (
     "koopaWalkLeft.png",
     SOIL_LOAD_AUTO,
     SOIL_CREATE_NEW_ID,
     SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
     );
    
    koopaSpriteWalkLeft = Sprite();
    koopaSpriteWalkLeft.initializeSprite(tex_2d, 0, 0, width, height);
    
    if( 0 == tex_2d )
    {
        printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
    }
    
    tex_2d = SOIL_load_OGL_texture
    (
     "koopaWalkRight.png",
     SOIL_LOAD_AUTO,
     SOIL_CREATE_NEW_ID,
     SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
     );
    
    koopaSpriteWalkRight = Sprite();
    koopaSpriteWalkRight.initializeSprite(tex_2d, 0, 0, width, height);
    
    if( 0 == tex_2d )
    {
        printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
    }
    
    tex_2d = SOIL_load_OGL_texture
    (
     "koopaIdleLeft.png",
     SOIL_LOAD_AUTO,
     SOIL_CREATE_NEW_ID,
     SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
     );
    
    koopaSpriteIdleLeft = Sprite();
    koopaSpriteIdleLeft.initializeSprite(tex_2d, 0, 0, width, height);
    
    if( 0 == tex_2d )
    {
        printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
    }
    
    tex_2d = SOIL_load_OGL_texture
    (
     "koopaIdleRight.png",
     SOIL_LOAD_AUTO,
     SOIL_CREATE_NEW_ID,
     SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
     );
    
    koopaSpriteIdleRight = Sprite();
    koopaSpriteIdleRight.initializeSprite(tex_2d, 0, 0, width, height);
    
    if( 0 == tex_2d )
    {
        printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
    }

    tex_2d = SOIL_load_OGL_texture
    (
     "koopaShell1.png",
     SOIL_LOAD_AUTO,
     SOIL_CREATE_NEW_ID,
     SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
     );
    
    koopaSpriteShell[0] = Sprite();
    koopaSpriteShell[0].initializeSprite(tex_2d, 0, 0, width, height);
    
    if( 0 == tex_2d )
    {
        printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
    }
    
    tex_2d = SOIL_load_OGL_texture
    (
     "koopaShell2.png",
     SOIL_LOAD_AUTO,
     SOIL_CREATE_NEW_ID,
     SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
     );
    
    koopaSpriteShell[1] = Sprite();
    koopaSpriteShell[1].initializeSprite(tex_2d, 0, 0, width, height);
    
    if( 0 == tex_2d )
    {
        printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
    }
    
    tex_2d = SOIL_load_OGL_texture
    (
     "koopaShell3.png",
     SOIL_LOAD_AUTO,
     SOIL_CREATE_NEW_ID,
     SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
     );
    
    koopaSpriteShell[2] = Sprite();
    koopaSpriteShell[2].initializeSprite(tex_2d, 0, 0, width, height);
    
    if( 0 == tex_2d )
    {
        printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
    }
    
    tex_2d = SOIL_load_OGL_texture
    (
     "koopaShell4.png",
     SOIL_LOAD_AUTO,
     SOIL_CREATE_NEW_ID,
     SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
     );
    
    koopaSpriteShell[3] = Sprite();
    koopaSpriteShell[3].initializeSprite(tex_2d, 0, 0, width, height);
    
    if( 0 == tex_2d )
    {
        printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
    }
}

void Koopa::killKoopa(Player_State playerState) {
    if (!isShell) {
        enemyState = eIDLE;
        enemyPosition.velX = 0.0f;
        isShell = true;
        width = 16.0f;
        height = 16.0f;
        enemyPosition.posY = enemyPosition.posY + 11.0f;
        return;
    }
    
    if (isShell && enemyPosition.velX != 0.0f) {
        enemyState = eIDLE;
        enemyPosition.velX = 0.0f;
        return;
    }
    
    if (isShell && (playerState == LEFT || playerState == IDLE)) {
        enemyPosition.velX = 2.0f;
        enemyState = eLEFT;
    } else if (isShell && playerState == RIGHT) {
        enemyPosition.velX = 2.0f;
        enemyState = eRIGHT;
    }
}

void Koopa::updatePosition(float maxWidth, float maxHeight, Object* objects, int numObjects, Player *player) {
    
    Position previousPosition = enemyPosition;
    
    switch (enemyState) {
        case eLEFT:
            enemyPosition.posX -= enemyPosition.velX;
            break;
        case eRIGHT:
            enemyPosition.posX += enemyPosition.velX;
            break;
        default:
            break;
    }
    
    // Apply Gravity
    if (isJumping) {
        enemyPosition.posY -= enemyPosition.velY;
        enemyPosition.velY += gravity;
    }
    
    if (enemyState == eDEAD) {
        return;
    }
    
    // Test for collision with objects
    bool collide = false;
    for (int i = 0 ; i < numObjects; i++) {
        Object* currentObject = &objects[i];
        if (currentObject->collideObject(enemyPosition, width / 2, height - 1.0f)) {
            collide = true;
            //            if (isJumping && enemyPosition.velY >= 0) {
            //                if (currentObject->getFallThrough()) {
            //                    continue;
            //                }
            //                /** Reposition Player directly Under Collided Object **/
            //                enemyPosition = previousPosition;
            //                enemyPosition.posY = currentObject->getObjectPosition().posY + (currentObject->getObjectHeight() / 2) + (height / 2);
            //                enemyPosition.velY = 0;
            //            } else if (playerPosition.velY < 0) {
            //                if (currentObject->getFallThrough() &&
            //                    ((enemyPosition.posY > (currentObject->getObjectPosition().posY + (currentObject->getObjectHeight() / 2))))) {
            //                    enemyPosition.posX = previousPosition.posX;
            //                    continue;
            //                }
            //                enemyPosition = previousPosition;
            //                // playerPosition.velY = 0.0;
            //                isJumping = false;
            //            } else {
            enemyPosition = previousPosition;
            if (isTurning == false) {
                isTurning = true;
                elapsedTime = 0.0;
            }

            //            }
            break;
        }
    }
    
    if (enemyState != eDEAD && collideEnemy(player->getPosition(), player->getWidth(), player->getHeight()) && player->getVelY() != 8.0f ) {
        player->decreaseLives();
    }
    
    
    //    if (/*!isJumping &&*/ enemyPosition.posY + (height / 2) < maxHeight) {
    //        enemyPosition.posY -= enemyPosition.velY;
    //        enemyPosition.velY += gravity;
    //
    //        for (int i = 0 ; i < numObjects; i++) {
    //            Object* currentObject = &objects[i];
    //            if (currentObject->collideObject(enemyPosition, width / 2, height - 1.0f)) {
    //                enemyPosition.posY = previousPosition.posY;
    //                enemyPosition.velY = 0.0f;
    //                break;
    //            }
    //        }
    //    }
    
    //TODO: Magic Number Floor Boundry
    if (enemyPosition.posY + (height / 2) > maxHeight && enemyState != eDEAD) {
        enemyPosition.posY = maxHeight;
        isJumping = false;
    }
    
    // Check Screen Boundries
    if (enemyPosition.posX + (width / 2) > maxWidth + (width * 2)) {
        enemyState = eDEAD;
    }
    if (enemyPosition.posX - (width / 2) < -(width * 2)) {
        enemyState = eDEAD;
    }
    if (enemyPosition.posY + (height / 2) > maxHeight) {
        enemyPosition.posY = maxHeight - (height / 2);
    }
    if (enemyPosition.posY - (height / 2) < 0) {
        enemyPosition.posY = 0 + (height / 2);
    }

}

bool Koopa::collideEnemy(Position playerPosition, float playerWidth, float playerHeight) {
    float leftA, leftB;
    float rightA, rightB;
    float topA, topB;
    float bottomA, bottomB;
    
    leftA = enemyPosition.posX - (width / 2);
    rightA = enemyPosition.posX + (width / 2);
    topA = enemyPosition.posY - (height / 2);
    bottomA = enemyPosition.posY + (height / 2);
    
    leftB = playerPosition.posX - (playerWidth / 2);
    rightB = playerPosition.posX + (playerWidth / 2);
    topB = playerPosition.posY - (playerHeight / 2);
    bottomB = playerPosition.posY + (playerHeight / 2);
    
    
    if( bottomA < topB )
    {
        return false;
    }
    
    if( topA > bottomB )
    {
        return false;
    }
    
    if( rightA < leftB )
    {
        return false;
    }
    
    if( leftA > rightB )
    {
        return false;
    }
    
    return true;
}

void Koopa::updateEnemyAnimation(float time) {
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

void Koopa::renderEnemy(void) {
    
    glEnable(GL_TEXTURE_2D);
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    if (isTurning && (elapsedTime > (float)(FPS/100.0f) || isShell)) {
        if (enemyState == eRIGHT) {
            enemyState = eLEFT;
            isTurning = false;
        } else if (enemyState == eLEFT) {
            enemyState = eRIGHT;
            isTurning = false;
        }
        
        elapsedTime = 0.0;
    }
    
    if (isShell) {
        if (enemyState == eIDLE) {
            glBindTexture(GL_TEXTURE_2D, koopaSpriteShell[0].getID());
        } else {
            glBindTexture(GL_TEXTURE_2D, koopaSpriteShell[koopaSpriteIndex].getID());
            if (elapsedTime > (float)(FPS/120.0f)) {
                koopaSpriteIndex += 1;
                
                if (koopaSpriteIndex >= 4) {
                    koopaSpriteIndex = 0;
                }
                
                elapsedTime = 0.0;
            }
        }
    } else {
        if (enemyState == eRIGHT) {
            if (toggleRun) {
                glBindTexture(GL_TEXTURE_2D, koopaSpriteWalkRight.getID());
                if (isTurning) {
                    glBindTexture(GL_TEXTURE_2D, koopaSpriteTurnRight.getID());
                }
                if (elapsedTime > (float)(FPS/50.0f)) {
                    toggleRun = false;
                    elapsedTime = 0.0;
                }
            } else {
                glBindTexture(GL_TEXTURE_2D, koopaSpriteIdleRight.getID());
                if (isTurning) {
                    glBindTexture(GL_TEXTURE_2D, koopaSpriteTurnRight.getID());
                }
                if (elapsedTime > (float)(FPS/50.0f)) {
                    toggleRun = true;
                    elapsedTime = 0.0;
                }
            }
        } else if (enemyState == eLEFT) {
            if (toggleRun) {
                glBindTexture(GL_TEXTURE_2D, koopaSpriteWalkLeft.getID());
                if (isTurning) {
                    glBindTexture(GL_TEXTURE_2D, koopaSpriteTurnLeft.getID());
                }
                if (elapsedTime > (float)(FPS/50.0f)) {
                    toggleRun = false;
                    elapsedTime = 0.0;
                }
            } else {
                glBindTexture(GL_TEXTURE_2D, koopaSpriteIdleLeft.getID());
                if (isTurning) {
                    glBindTexture(GL_TEXTURE_2D, koopaSpriteTurnLeft.getID());
                }
                if (elapsedTime > (float)(FPS/50.0f)) {
                    toggleRun = true;
                    elapsedTime = 0.0;
                }
            }
        } else if (enemyState == eDEAD) {
            glBindTexture(GL_TEXTURE_2D, koopaSpriteIdleLeft.getID());
        }
    }
    
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex2f(enemyPosition.posX - (width / 2), enemyPosition.posY + (height / 2));
    
    glTexCoord2f(0.0f, 1.0f);
    glVertex2f(enemyPosition.posX - (width / 2), enemyPosition.posY - (height / 2));
    
    glTexCoord2f(1.0f, 1.0f);
    glVertex2f(enemyPosition.posX + (width / 2), enemyPosition.posY - (height / 2));
    
    glTexCoord2f(1.0f, 0.0f);
    glVertex2f(enemyPosition.posX + (width / 2), enemyPosition.posY + (height / 2));
    glEnd();
    
    glDisable(GL_TEXTURE_2D);
    glClear(GL_DEPTH_BUFFER_BIT);
}