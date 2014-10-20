//
//  object.cpp
//  opengl-series
//
//  Created by Matthew Correia on 2014-09-30.
//
//

#include "object.h"

Object::Object() {
    objectPosition.posX = 0.0f;
    objectPosition.posY = 0.0f;
    objectPosition.velX = 0.0f;
    objectPosition.velY = 0.0f;
    
    objectWidth = 0.0f;
    objectHeight = 0.0f;
    
    objectID = 0;
    
    bool collide = true;
    bool lethal = false;
    
}

Object::Object(float x, float y, float w, float h, bool c, bool l, const char *s) {
    objectPosition.posX = x;
    objectPosition.posY = y;
    objectPosition.velX = 0.0f;
    objectPosition.velY = 0.0f;
    
    objectWidth = w;
    objectHeight = h;
    
    objectID = 0;
    
    bool collide = c;
    bool lethal = l;

    setObjectSprite(w, h, s);
}


Object::~Object() {
    
}

void Object::setObjectSprite(float w, float h, const char *s) {
    GLuint tex_2d = SOIL_load_OGL_texture
	(
     s,
     SOIL_LOAD_AUTO,
     SOIL_CREATE_NEW_ID,
     SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
     );
    
    objectSprite = Sprite();
    objectSprite.initializeSprite(tex_2d, 0, 0, w, h);
    
    if( 0 == tex_2d )
    {
        printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
    }
    
}

void Object::renderObject(void) {
    glEnable(GL_TEXTURE_2D);
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    // Background
    glBindTexture(GL_TEXTURE_2D, objectSprite.getID());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f);
    glVertex2f(objectPosition.posX - (objectWidth / 2), objectPosition.posY - (objectHeight / 2));
    
    glTexCoord2f(0.0f, 0.0f);
    glVertex2f(objectPosition.posX - (objectWidth / 2), objectPosition.posY + (objectHeight / 2));
    
    glTexCoord2f(1.0f, 0.0f);
    glVertex2f(objectPosition.posX + (objectWidth / 2), objectPosition.posY + (objectHeight / 2));
    
    glTexCoord2f(1.0f, 1.0f);
    glVertex2f(objectPosition.posX + (objectWidth / 2), objectPosition.posY - (objectHeight / 2));
    glEnd();
    
    glDisable(GL_TEXTURE_2D);
    glClear(GL_DEPTH_BUFFER_BIT);

}

bool Object::collideObject(Position playerPosition, float playerWidth, float playerHeight) {
    // Check if collision is possible
    if (collide == false) {
        return false;
    }
    
    float leftA, leftB;
    float rightA, rightB;
    float topA, topB;
    float bottomA, bottomB;
    
    leftA = objectPosition.posX - (objectWidth / 2);
    rightA = objectPosition.posX + (objectWidth / 2);
    topA = objectPosition.posY - (objectHeight / 2);
    bottomA = objectPosition.posY + (objectHeight / 2);
    
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
