//
//  generateWorld.h
//  openGLTutorial
//
//  Created by Matthew Correia on 2014-07-12.
//  Copyright (c) 2014 Matthew Correia. All rights reserved.
//

#ifndef __openGLTutorial__generateWorld__
#define __openGLTutorial__generateWorld__

#include <iostream>
#include "sharedHeaders.h"

void SetupWorld();
void drawSceneFromFile();
bool checkCollisions(Position playerPosition, float playerWidth, float playerHeight);

#endif /* defined(__openGLTutorial__generateWorld__) */
