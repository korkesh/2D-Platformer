//
//  sharedHeaders.h
//  opengl-series
//
//  Created by Matthew Correia on 2014-09-17.
//
//

#ifndef opengl_series_sharedHeaders_h
#define opengl_series_sharedHeaders_h

#include "sharedConstants.h"

// Structures
struct Position {
    float posX;
    float posY;
    
    float velX;
    float velY;
};

// Library Headers
#include <GL/glew.h>
#include <GLUT/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string>
#include <OpenAL/al.h>
#include <OpenAL/alc.h>
#include <cstdlib>
#include <ctime>
#include "SOIL.h"

// Local Headers
#include "player.h"
#include "generateWorld.h"
#include "texture.h"
#include "algebra.hpp"
#include "sound.h"
#include "UI.h"
#include "shadowMapping.h"
#include "soundEffects.h"
#include "sprite.h"



#endif
