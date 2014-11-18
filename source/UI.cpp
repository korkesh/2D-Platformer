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

int health = 100;

Sprite *playerSpriteIdle = NULL;
Sprite *titlegroundSprite = NULL;


void drawMenu()
{
    glEnable(GL_TEXTURE_2D);
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Background
    if (titlegroundSprite == NULL) {
        GLuint tex_2d = SOIL_load_OGL_texture
        (
         "title.png",
         SOIL_LOAD_AUTO,
         SOIL_CREATE_NEW_ID,
         SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
         );
        
        titlegroundSprite = new Sprite();
        titlegroundSprite->initializeSprite(tex_2d, 0, 0, 388.0f, 132.0f);
        
        if( 0 == tex_2d )
        {
            printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
        }
    }
    
    glBindTexture(GL_TEXTURE_2D, titlegroundSprite->getID());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f);
    glVertex2f(100.0f, 50.0f);
    
    glTexCoord2f(0.0f, 0.0f);
    glVertex2f(100.0f, 182.0f);
    
    glTexCoord2f(1.0f, 0.0f);
    glVertex2f(388.0f, 182.0f);
    
    glTexCoord2f(1.0f, 1.0f);
    glVertex2f(388.0f, 50.0f);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glClear(GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, WIDTH, HEIGHT, 0, 0, 1);
    
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glColor3f(0.0, 0.0, 0.0);
    glRasterPos2i(175.0f, 200.0f);
    
    std::stringstream ss;
    ss << "PRESS ENTER TO START";
    
    std::string s = ss.str();
    void * font = GLUT_BITMAP_TIMES_ROMAN_24;
    for (std::string::iterator i = s.begin(); i != s.end(); ++i)
    {
        char c = *i;
        glutBitmapCharacter(font, c);
    }
    
    ss.str("");
    glRasterPos2i(140.0f, 230.0f);
    ss << "COLLECT ALL THREE COINS TO WIN!";
    
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

void drawDeath(Player &player) {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2i(50, 50);

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
    glVertex2f(245, 177);
    
    glTexCoord2f(0.0f, 1.0f);
    glVertex2f(245, 157);
    
    glTexCoord2f(1.0f, 1.0f);
    glVertex2f(230, 157);
    
    glTexCoord2f(1.0f, 0.0f);
    glVertex2f(230, 177);
    glEnd();
    
    glDisable(GL_TEXTURE_2D);
    glClear(GL_DEPTH_BUFFER_BIT);
    
    std::stringstream ss;

    ss.str("");
    glRasterPos2i(255, 175);
    ss << "x" << player.getLives();
    
    std::string s = ss.str();
    void * font = GLUT_BITMAP_TIMES_ROMAN_24;
    for (std::string::iterator i = s.begin(); i != s.end(); ++i)
    {
        char c = *i;
        glutBitmapCharacter(font, c);
    }
}

void drawGameOver(void) {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2i(50, 50);
    
    std::stringstream ss;
    
    ss.str("");
    glRasterPos2i(220, 175);
    ss << "GAME OVER";
    
    std::string s = ss.str();
    void * font = GLUT_BITMAP_TIMES_ROMAN_24;
    for (std::string::iterator i = s.begin(); i != s.end(); ++i)
    {
        char c = *i;
        glutBitmapCharacter(font, c);
    }
    
    ss.str("");
    glRasterPos2i(170, 230);
    ss << "PRESS ENTER TO CONTINUE";
    
    s = ss.str();
    for (std::string::iterator i = s.begin(); i != s.end(); ++i)
    {
        char c = *i;
        glutBitmapCharacter(font, c);
    }
    
}

void drawWin(Player &player) {
    glEnable(GL_TEXTURE_2D);
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    // Background
    if (titlegroundSprite == NULL) {
        GLuint tex_2d = SOIL_load_OGL_texture
        (
         "title.png",
         SOIL_LOAD_AUTO,
         SOIL_CREATE_NEW_ID,
         SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
         );
        
        titlegroundSprite = new Sprite();
        titlegroundSprite->initializeSprite(tex_2d, 0, 0, 388.0f, 132.0f);
        
        if( 0 == tex_2d )
        {
            printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
        }
    }
    
    glBindTexture(GL_TEXTURE_2D, titlegroundSprite->getID());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f);
    glVertex2f(100.0f, 50.0f);
    
    glTexCoord2f(0.0f, 0.0f);
    glVertex2f(100.0f, 182.0f);
    
    glTexCoord2f(1.0f, 0.0f);
    glVertex2f(388.0f, 182.0f);
    
    glTexCoord2f(1.0f, 1.0f);
    glVertex2f(388.0f, 50.0f);
    glEnd();
    
    glDisable(GL_TEXTURE_2D);
    glClear(GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, WIDTH, HEIGHT, 0, 0, 1);
    
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    
    glColor3f(0.0, 0.0, 0.0);
    glRasterPos2i(175.0f, 200.0f);
    
    std::stringstream ss;
    ss << "PRESS ENTER TO START";
    
    std::string s = ss.str();
    void * font = GLUT_BITMAP_TIMES_ROMAN_24;
    for (std::string::iterator i = s.begin(); i != s.end(); ++i)
    {
        char c = *i;
        glutBitmapCharacter(font, c);
    }
    
    ss.str("");
    glRasterPos2i(140.0f, 230.0f);
    ss << "YOU COLLECTED ALL THREE COINS!";
    
    s = ss.str();
    for (std::string::iterator i = s.begin(); i != s.end(); ++i)
    {
        char c = *i;
        glutBitmapCharacter(font, c);
    }
    
    ss.str("");
    glRasterPos2i(200.0f, 250.0f);
    ss << "SCORE: " << player.getPlayerScore();
    
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
    ss << player.getPlayerScore();
    
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