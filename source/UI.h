//
//  UI.h
//  openGLTutorial
//
//  Created by Matthew Correia on 2014-07-15.
//  Copyright (c) 2014 Matthew Correia. All rights reserved.
//

#ifndef __openGLTutorial__UI__
#define __openGLTutorial__UI__

#include <iostream>
#include "sharedHeaders.h"

class Player;

extern int score;
void drawUI(Player &player);
void drawMenu();
void drawDeath(Player &player);
void drawGameOver(void);
void drawWin(Player &player);

#endif /* defined(__openGLTutorial__UI__) */
