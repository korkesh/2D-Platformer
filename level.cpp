//
//  level.cpp
//  opengl-series
//
//  Created by Matthew Correia on 2014-09-23.
//
//

#include "level.h"

void readstr(FILE *f, char *string)
{
	do
	{
		fgets(string, 255, f);
	} while (/*(string[0] == '/') ||*/ (string[0] == '\n') || (string[0] == '\r'));
    
	return;
}

Level::Level(float x, float y, float w, float h, bool c) {
    posX = x;
    posY = y;
    
    width = w;
    height = h;
    
    collision = c;
    
    objects = NULL;
    numObjects = 0;
}

Level::~Level() {
    
}

void Level::loadLevelFromFile(const char* file) {
	float x, y, w, h;
    int c, l;
    char s [255] = "";
    
	FILE *filein;
	char oneline[255];
	filein = fopen(file, "rt"); // File To Load World Data From
    
	readstr(filein, oneline);
	sscanf(oneline, "NUMOBJECTS %d\n", &numObjects);
    
	objects = new Object[numObjects];
	for (int i = 0; i < numObjects; i++)
	{
        readstr(filein, oneline);
        sscanf(oneline, "%f %f %f %f %d %d %s", &x, &y, &w, &h, &c, &l, s);
        objects[i] = Object(x, y, w, h, c, l, s);
	}
    
	fclose(filein);
	return;
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
    
    tex_2d = SOIL_load_OGL_texture
	(
     "/Users/Korkesh/2D-Platformer/resources/grass.png",
     SOIL_LOAD_AUTO,
     SOIL_CREATE_NEW_ID,
     SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
     );
    
    levelSpriteGroundTop = Sprite();
    levelSpriteGroundTop.initializeSprite(tex_2d, 0, 0, 68, 9);
    
    if( 0 == tex_2d )
    {
        printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
    }
    
    tex_2d = SOIL_load_OGL_texture
	(
     "/Users/Korkesh/2D-Platformer/resources/ground.png",
     SOIL_LOAD_AUTO,
     SOIL_CREATE_NEW_ID,
     SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
     );
    
    levelSpriteGroundBottom = Sprite();
    levelSpriteGroundBottom.initializeSprite(tex_2d, 0, 0, 68, 15);
    
    if( 0 == tex_2d )
    {
        printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
    }
    
    //test.setObjectSprite(16, 16, "/Users/Korkesh/2D-Platformer/resources/qBlock.png");
}

void Level::renderLevel() {
    
    glEnable(GL_TEXTURE_2D);
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    // Background
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
    
    // Grass
    glBindTexture(GL_TEXTURE_2D, levelSpriteGroundTop.getID());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f);
    glVertex2f(0, height);
    
    glTexCoord2f(0.0f, 0.0f);
    glVertex2f(0, height + 10.0f);
    
    glTexCoord2f(width / levelSpriteGroundTop.getWidth(), 0.0f);
    glVertex2f(width, height + 10.0f);
    
    glTexCoord2f(width / levelSpriteGroundTop.getWidth(), 1.0f);
    glVertex2f(width, height);
    glEnd();
    
    // Ground
    glBindTexture(GL_TEXTURE_2D, levelSpriteGroundBottom.getID());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 300.0f);
    glVertex2f(0, height + 10.0f);
    
    glTexCoord2f(0.0f, 0.0f);
    glVertex2f(0, height + 300.0f);
    
    glTexCoord2f(width / levelSpriteGroundTop.getWidth(), 0.0f);
    glVertex2f(width, height + 300.0f);
    
    glTexCoord2f(width / levelSpriteGroundTop.getWidth(), 300.0f);
    glVertex2f(width, height + 10.0f);
    glEnd();
    
    glDisable(GL_TEXTURE_2D);
    glClear(GL_DEPTH_BUFFER_BIT);
    
    drawLevel();
}

void Level::drawLevel() {
    glColor3f(1.0, 1.0, 1.0);
	for (int i = 0; i < numObjects; i++)
	{
        glPushMatrix();
        
        objects[i].renderObject();
        
        glPopMatrix();
	}
	return;
}