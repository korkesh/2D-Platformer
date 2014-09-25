//
//  level.cpp
//  opengl-series
//
//  Created by Matthew Correia on 2014-09-23.
//
//

#include "level.h"

Level::Level(float x, float y, float w, float h, bool c) {
    posX = x;
    posY = y;
    
    width = w;
    height = h;
    
    collision = c;
}

Level::~Level() {
    
}

void Level::setLevelSprite(float w, float h) {
    GLuint tex_2d = SOIL_load_OGL_texture
	(
     "/Users/Korkesh/2D-Platformer/resources/sky.png",
     SOIL_LOAD_AUTO,
     SOIL_CREATE_NEW_ID,
     SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
     );
    
    levelSprite = Sprite();
    levelSprite.initializeSprite(tex_2d, 0, 0, w, h);
    
    if( 0 == tex_2d )
    {
        printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
    }
}

void Level::renderLevel() {
    
    glEnable(GL_TEXTURE_2D);
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glBindTexture(GL_TEXTURE_2D, levelSprite.getID());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f);
    glVertex2f(0.0f, 0.0f);
    
    glTexCoord2f(0.0f, 0.0f);
    glVertex2f(0.0f, height);
    
    glTexCoord2f(3.0f, 0.0f);
    glVertex2f(width, height);
    
    glTexCoord2f(3.0f, 1.0f);
    glVertex2f(width, 0.0f);
    glEnd();
    
    glDisable(GL_TEXTURE_2D);

    
}