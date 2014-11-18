//
//  goomba.cpp
//  opengl-series
//
//  Created by Matthew Correia on 2014-10-28.
//
//

#include "goomba.h"

Goomba::Goomba() {
    isJumping = false;
}

Goomba::~Goomba() {
    
}

void Goomba::initializeSprite() {
    GLuint tex_2d = SOIL_load_OGL_texture
	(
     "goombaDead.png",
     SOIL_LOAD_AUTO,
     SOIL_CREATE_NEW_ID,
     SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
     );
    
    goombaSpriteDead = Sprite();
    goombaSpriteDead.initializeSprite(tex_2d, 0, 0, width, height);
    
    if( 0 == tex_2d )
    {
        printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
    }
    
    tex_2d = SOIL_load_OGL_texture
	(
     "goombaIdle.png",
     SOIL_LOAD_AUTO,
     SOIL_CREATE_NEW_ID,
     SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
     );
    
    goombaSpriteIdle = Sprite();
    goombaSpriteIdle.initializeSprite(tex_2d, 0, 0, width, height);
    
    if( 0 == tex_2d )
    {
        printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
    }
    
    tex_2d = SOIL_load_OGL_texture
	(
     "goombaRun.png",
     SOIL_LOAD_AUTO,
     SOIL_CREATE_NEW_ID,
     SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
     );
    
    goombaSpriteRun = Sprite();
    goombaSpriteRun.initializeSprite(tex_2d, 0, 0, width, height);
    
    if( 0 == tex_2d )
    {
        printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
    }
    
}

void Goomba::killGoomba() {
    if (enemyState != eDEAD) {
        enemyState = eDEAD;
        isJumping = true;
        enemyPosition.velY = 5.0f;
    }
}

void Goomba::updatePosition(float maxWidth, float maxHeight, Object* objects, int numObjects, Player *player) {
    
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
            //            }
            break;
        }
    }
    
    if (enemyState != eDEAD && collideEnemy(player->getPosition(), player->getWidth(), player->getHeight())) {
        player->decreaseLives();
    }
    
    
        if (enemyPosition.posY + (height / 2) < maxHeight) {
            enemyPosition.posY -= enemyPosition.velY;
            enemyPosition.velY += gravity;
    
            for (int i = 0 ; i < numObjects; i++) {
                Object* currentObject = &objects[i];
                if (currentObject->collideObject(enemyPosition, width / 2, height - 1.0f)) {
                    enemyPosition.posY = previousPosition.posY;
                    enemyPosition.velY = 0.0f;
                    break;
                }
            }
        }
    
    //TODO: Magic Number Floor Boundry
    if (enemyPosition.posY + (height / 2) > maxHeight && enemyState != eDEAD) {
        enemyPosition.posY = maxHeight - 7.0f;
        isJumping = false;
        enemyPosition.velY = 0.0f;
    }
    
    // Check Screen Boundries
    if (enemyPosition.posX + (width / 2) > maxWidth + (width * 2)) {
        enemyState = eDEAD;
    }
    if (enemyPosition.posX - (width / 2) < -(width * 2)) {
        enemyState = eDEAD;
    }
//    if (enemyPosition.posY + (height / 2) > maxHeight) {
//        enemyState = eDEAD;
//    }
//    if (enemyPosition.posY - (height / 2) < 0) {
//        enemyState = eDEAD;
//    }
    
}

bool Goomba::collideEnemy(Position playerPosition, float playerWidth, float playerHeight) {
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

void Goomba::updateEnemyAnimation(float time) {
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

void Goomba::renderEnemy(void) {
    
    glEnable(GL_TEXTURE_2D);
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    if (enemyState == eIDLE) {
        glBindTexture(GL_TEXTURE_2D, goombaSpriteIdle.getID());
    } else if (enemyState == eRIGHT) {
        if (toggleRun) {
            glBindTexture(GL_TEXTURE_2D, goombaSpriteRun.getID());
            if (elapsedTime > (float)(FPS/50.0f)) {
                toggleRun = false;
                elapsedTime = 0.0;
            }
        } else {
            glBindTexture(GL_TEXTURE_2D, goombaSpriteIdle.getID());
            if (elapsedTime > (float)(FPS/50.0f)) {
                toggleRun = true;
                elapsedTime = 0.0;
            }
        }
    } else if (enemyState == eLEFT) {
        if (toggleRun) {
            glBindTexture(GL_TEXTURE_2D, goombaSpriteRun.getID());
            if (elapsedTime > (float)(FPS/50.0f)) {
                toggleRun = false;
                elapsedTime = 0.0;
            }
        } else {
            glBindTexture(GL_TEXTURE_2D, goombaSpriteIdle.getID());
            if (elapsedTime > (float)(FPS/50.0f)) {
                toggleRun = true;
                elapsedTime = 0.0;
            }
        }
    } else if (enemyState == eDEAD) {
        glBindTexture(GL_TEXTURE_2D, goombaSpriteDead.getID());
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