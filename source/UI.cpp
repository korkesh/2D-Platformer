//
//  UI.cpp
//  openGLTutorial
//
//  Created by Matthew Correia on 2014-07-15.
//  Copyright (c) 2014 Matthew Correia. All rights reserved.
//

#include <sstream>

#include "UI.h"
#include "sprite.h"
#include "player.h"

int score = -2;
int health = 100;

Sprite *playerSpriteIdle = NULL;

void drawMenu()
{
    
}

void drawUI(Player &player) {
    
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, 1024, 768, 0, 0, 1);
    
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2i(50, 50);
    
    std::stringstream ss;
    ss << "MARIO";
    
    std::string s = ss.str();
    void * font = GLUT_BITMAP_TIMES_ROMAN_24;
    for (std::string::iterator i = s.begin(); i != s.end(); ++i)
    {
        char c = *i;
        glutBitmapCharacter(font, c);
    }
    
    ss.str("");
    glRasterPos2i(900, 50);
    ss << "WORLD";
    
    s = ss.str();
    for (std::string::iterator i = s.begin(); i != s.end(); ++i)
    {
        char c = *i;
        glutBitmapCharacter(font, c);
    }
    
    ss.str("");
    glRasterPos2i(50, 75);
    ss << "0000000";
    
    s = ss.str();
    for (std::string::iterator i = s.begin(); i != s.end(); ++i)
    {
        char c = *i;
        glutBitmapCharacter(font, c);
    }
    
    if (playerSpriteIdle == NULL) {
        
        GLuint tex_2d = SOIL_load_OGL_texture
        (
         "marioidle.png",
         SOIL_LOAD_AUTO,
         SOIL_CREATE_NEW_ID,
         SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
         );
        
        playerSpriteIdle = new Sprite();
        playerSpriteIdle->initializeSprite(tex_2d, 0, 0, 15.0f, 20.0f);
        
        if( 0 == tex_2d )
        {
            printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
        }
    }
    glEnable(GL_TEXTURE_2D);
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D, playerSpriteIdle->getID());
    
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex2f(290, 77);
    
    glTexCoord2f(0.0f, 1.0f);
    glVertex2f(290, 57);
    
    glTexCoord2f(1.0f, 1.0f);
    glVertex2f(275, 57);
    
    glTexCoord2f(1.0f, 0.0f);
    glVertex2f(275, 77);
    glEnd();
    
    glDisable(GL_TEXTURE_2D);
    glClear(GL_DEPTH_BUFFER_BIT);

    
    ss.str("");
    glRasterPos2i(300, 75);
    ss << "x" << player.getLives();
    
    s = ss.str();
    for (std::string::iterator i = s.begin(); i != s.end(); ++i)
    {
        char c = *i;
        glutBitmapCharacter(font, c);
    }
    
    
    ss.str("");
    glRasterPos2i(924, 75);
    ss << "1-1";
    
    s = ss.str();
    for (std::string::iterator i = s.begin(); i != s.end(); ++i)
    {
        char c = *i;
        glutBitmapCharacter(font, c);
    }
    
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
}