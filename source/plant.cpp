//
//  plant.cpp
//  opengl-series
//
//  Created by Matthew Correia on 2014-10-29.
//
//

#include "plant.h"

Plant::Plant() {
    isJumping = true;
    landTime = -1.0f;
    plantSpriteIndex = 0;
    
    enemyPosition.posX = 1200.0f;
    enemyPosition.velY = 8.0f;
    
    gravity = -0.5f;
    
    width = 16.0f;
    height = 21.0f;
}

Plant::~Plant() {
    
}

void Plant::initializeSprite() {
    GLuint tex_2d = SOIL_load_OGL_texture
	(
     "plantJump1.png",
     SOIL_LOAD_AUTO,
     SOIL_CREATE_NEW_ID,
     SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
     );
    
    plantSpriteJump[0] = Sprite();
    plantSpriteJump[0].initializeSprite(tex_2d, 0, 0, width, height);
    
    if( 0 == tex_2d )
    {
        printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
    }
    
    tex_2d = SOIL_load_OGL_texture
	(
     "plantJump2.png",
     SOIL_LOAD_AUTO,
     SOIL_CREATE_NEW_ID,
     SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
     );
    
    plantSpriteJump[1] = Sprite();
    plantSpriteJump[1].initializeSprite(tex_2d, 0, 0, width, height);
    
    if( 0 == tex_2d )
    {
        printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
    }
    
    tex_2d = SOIL_load_OGL_texture
	(
     "plantJump3.png",
     SOIL_LOAD_AUTO,
     SOIL_CREATE_NEW_ID,
     SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
     );
    
    plantSpriteJump[2] = Sprite();
    plantSpriteJump[2].initializeSprite(tex_2d, 0, 0, width, height);
    
    if( 0 == tex_2d )
    {
        printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
    }
    
    tex_2d = SOIL_load_OGL_texture
	(
     "plantJump4.png",
     SOIL_LOAD_AUTO,
     SOIL_CREATE_NEW_ID,
     SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
     );
    
    plantSpriteJump[3] = Sprite();
    plantSpriteJump[3].initializeSprite(tex_2d, 0, 0, width, height);
    
    if( 0 == tex_2d )
    {
        printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
    }
    
}

void Plant::updatePosition(float maxWidth, float maxHeight, Object* objects, int numObjects, Player *player) {
    
    Position previousPosition = enemyPosition;
    
    // Apply Gravity
    if (isJumping) {
        enemyPosition.posY -= enemyPosition.velY;
        enemyPosition.velY += gravity;
    }
    
    if (enemyState == eDEAD) {
        return;
    }
    
    // Test for collision with objects
    if (enemyState != eDEAD && collideEnemy(player->getPosition(), player->getWidth(), player->getHeight())) {
        player->decreaseLives();
    }
    
    // Check Boundry
    if (enemyPosition.posY + (height / 2) > maxHeight) {
        isJumping = true;
        enemyPosition.velY = 8.0f;
    }
    
}

bool Plant::collideEnemy(Position playerPosition, float playerWidth, float playerHeight) {
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

void Plant::updateEnemyAnimation(float time) {
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

void Plant::renderEnemy(void) {
    glEnable(GL_TEXTURE_2D);
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glBindTexture(GL_TEXTURE_2D, plantSpriteJump[plantSpriteIndex].getID());
    if (elapsedTime > (float)(FPS/120.0f)) {
        plantSpriteIndex += 1;
        
        if (plantSpriteIndex >= 4) {
            plantSpriteIndex = 0;
        }
        
        elapsedTime = 0.0;
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