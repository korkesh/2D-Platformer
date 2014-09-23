//
//  sprite.h
//  opengl-series
//
//  Created by Matthew Correia on 2014-09-23.
//
//

#ifndef __opengl_series__sprite__
#define __opengl_series__sprite__

#include "sharedHeaders.h"

class Sprite
{
	GLuint m_iTexture;
	int m_iX, m_iY, m_iWidth, m_iHeight;
	
public:
    
	Sprite(GLuint texture_id, int x, int y, int width, int height)
	{
		m_iTexture = texture_id;
		m_iX = x;
		m_iY = y;
		m_iWidth = width;
		m_iHeight = height;
	}
    
	void draw(float dest_X, float dest_Y)
	{
		GLfloat drawColor[] = {1.0f, 1.0f, 1.0f};
		
		if (m_iTexture <= 0) return;
        
		glBegin(GL_QUADS);
        
        glBindTexture(GL_TEXTURE_2D, m_iTexture);
        
        glColor3fv(drawColor);
        glVertex3f(dest_X, dest_Y, 0.f);
        glTexCoord2f(0.0f, 1.0f);
        
        glColor3fv(drawColor);
        glVertex3f(dest_X, dest_Y + m_iHeight, 0.f);
        glTexCoord2f(1.0f, 1.0f);
        
        glColor3fv(drawColor);
        glVertex3f(dest_X + m_iWidth, dest_Y + m_iHeight, 0.f);
        glTexCoord2f(1.0f, 0.0f);
        
        glColor3fv(drawColor);
        glVertex3f(dest_X + m_iWidth, dest_Y, 0.f);
        glTexCoord2f(0.0f, 0.0f);
        
		glEnd();
	}
	
};

#endif /* defined(__opengl_series__sprite__) */
