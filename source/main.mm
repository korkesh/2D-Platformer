#include "sharedHeaders.h"
#include "player.h"
#include "level.h"
#include "enemy.h"
#include "goomba.h"
#include "koopa.h"
#include "plant.h"

#pragma mark Globals

Player player;
Level level;

Goomba goomba;
Goomba goomba2;
Plant plant;
Koopa koopa;

SoundEngine soundEngine;
Object pipe;

float prevXpos = 0, prevYpos = 1.5, prevZpos = 15;
float lastx = WIDTH/2, lasty = HEIGHT/2;

float xpos = 0.0f, ypos = 0.0, zpos = 0.0;

bool displayMenu = true;
bool displayRespawn = false;
bool displayGameOver = false;
bool displayWin = false;
float deathTime = 0.0f;


void init (void);

#pragma mark Render & Update

//====================================================
// Camera
// Purpose: Update Camera Position
//====================================================
void camera (void) {
    float playerOffset = player.getPosition().posX;
    
    if (/*playerOffset < level.getLevelWidth() - (WIDTH / 2) &&*/ playerOffset > WIDTH / 2) {
        glTranslatef(-playerOffset + (WIDTH/2), 0.0f, 0.0f);
    }
    
}


//====================================================
// Display
// Purpose: Main Rendering Function
//====================================================
void display (void) {
 	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 	glMatrixMode(GL_MODELVIEW);
 	glLoadIdentity();
    
    if (displayMenu) {
        level.renderLevel();
        drawMenu();
        glutSwapBuffers();
    } else if (displayRespawn) {
        drawDeath(player);
        glutSwapBuffers();
    } else if (displayGameOver) {
        drawGameOver();
        glutSwapBuffers();
    } else if (displayWin) {
        level.renderLevel();
        drawWin(player);
        glutSwapBuffers();
    } else {
        // Adjust Camera
        camera();
        
        // Render Scene
        level.renderLevel();
        drawUI(player);
        
        // Render Enemies
        goomba.renderEnemy();
        goomba2.renderEnemy();
        plant.renderEnemy();
        koopa.renderEnemy();
        pipe.renderObject();
        
        // Render Player
        player.renderPlayer();
        
        glutSwapBuffers(); //swap the buffers
    }
}

//====================================================
// Update
// Purpose: Update According to FPS
// Input: 0
//====================================================
void update (int t) {
    if (displayRespawn) {
        deathTime += FPS / 1000.0f;
        if (deathTime < 1000000000) {
            deathTime -= (int)deathTime;
        }
        else {
            deathTime = 0;
        }
    }
    
    if (deathTime > 0.9f && displayRespawn) {
        deathTime = 0;
        displayRespawn = false;
    }
    
    if (!displayMenu && !displayRespawn & !displayGameOver) {
        goomba.updatePosition(level.getLevelWidth(), level.getLevelHeight(), level.getObjects(), level.getNumObjects(), &player);
        goomba.updateEnemyAnimation(FPS / 1000.0f);
        
        goomba2.updatePosition(level.getLevelWidth(), level.getLevelHeight(), level.getObjects(), level.getNumObjects(), &player);
        goomba2.updateEnemyAnimation(FPS / 1000.0f);
        
        plant.updatePosition(level.getLevelWidth(), level.getLevelHeight(), level.getObjects(), level.getNumObjects(), &player);
        plant.updateEnemyAnimation(FPS / 1000.0f);
        
        koopa.updatePosition(level.getLevelWidth(), level.getLevelHeight(), level.getObjects(), level.getNumObjects(), &player);
        koopa.updateEnemyAnimation(FPS / 1000.0f);
        
        player.updatePosition(level.getLevelWidth(), level.getLevelHeight(), level.getObjects(), level.getNumObjects(), &goomba, &goomba2, &koopa);
        player.updatePlayerAnimation(FPS / 1000.0f);
        
        if (player.getCoins() >= 3) {
            displayWin = true;
        }
        
        if (player.getState() == RESPAWN) {
            displayRespawn = true;
            deathTime = 0.0f;
            
            level.loadLevelFromFile("level1.txt");
            
            player.setPosition(50.0f, level.getLevelHeight());
            player.setState(IDLE);
            player.setPlayerScore(0);
            player.setCoins(0);
            
            goomba = Goomba();
            goomba.initializeSprite();
            goomba.setState(eLEFT);
            
            goomba2 = Goomba();
            goomba2.initializeSprite();
            goomba2.setState(eLEFT);
            goomba2.setPosition(250.0f, 259.0f);

            koopa = Koopa();
            koopa.initializeSprite();
            koopa.setState(eRIGHT);
            
            plant = Plant();
            plant.initializeSprite();
            
        }
        
        if (player.getState() == GAMEOVER) {
            displayGameOver = true;
        }
    }
    
	glutPostRedisplay();
	glutTimerFunc(FPS, update, 0);
}

#pragma mark Input

//====================================================
// Keyboard
// Purpose: Process User Keyboard Inputs
// Input: key pressed, mouse co-ordinates <x,y>
//====================================================
void keyboard (unsigned char key, int x, int y) {
    
    if (key == KEY_ENTER) {
        if (displayMenu) {
            displayMenu = false;
            return;
        }
        if (displayWin) {
            displayWin = false;
            level = Level(0, 0, WIDTH * 4, HEIGHT - 50.0f);
            level.setLevelSprite(WIDTH, HEIGHT - 50.0f);
            level.loadLevelFromFile("level1.txt");
            
            player = Player();
            player.initializeSprite();
            player.setPosition(player.getPosition().posX, level.getLevelHeight());
            player.setPlayerScore(0);
            player.setCoins(0);
            
            goomba = Goomba();
            goomba.initializeSprite();
            goomba.setState(eLEFT);
            
            goomba2 = Goomba();
            goomba2.initializeSprite();
            goomba2.setState(eLEFT);
            goomba2.setPosition(250.0f, 259.0f);
            
            koopa = Koopa();
            koopa.initializeSprite();
            koopa.setState(eRIGHT);
            
            plant = Plant();
            plant.initializeSprite();
            
            return;
        }
        if (displayGameOver) {
            level = Level(0, 0, WIDTH * 4, HEIGHT - 50.0f);
            level.setLevelSprite(WIDTH, HEIGHT - 50.0f);
            level.loadLevelFromFile("level1.txt");
            
            player = Player();
            player.initializeSprite();
            player.setPosition(player.getPosition().posX, level.getLevelHeight());
            player.setPlayerScore(0);
            player.setCoins(0);

            goomba = Goomba();
            goomba.initializeSprite();
            goomba.setState(eLEFT);
            
            goomba2 = Goomba();
            goomba2.initializeSprite();
            goomba2.setState(eLEFT);
            goomba2.setPosition(250.0f, 259.0f);

            koopa = Koopa();
            koopa.initializeSprite();
            koopa.setState(eRIGHT);
            
            plant = Plant();
            plant.initializeSprite();
            
            displayGameOver = false;
            return;
        }
    }
    
    if (key == KEY_ESC)
    {
        exit(0);
    }
    
    if (displayMenu) {
        return;
    }
    
    if (key =='w')
    {
        if (player.getState() == DEAD || player.getState() == RESPAWN) {
            return;
        }
        if (!player.getIsJumping()) {
            player.setIsJumping(true);
            player.setVelY(9.0f);
        }
    }
    
    if (key =='s')
    {
        if (player.getState() == DEAD || player.getState() == RESPAWN) {
            return;
        }
        player.setIsCrouching(true);
    }
    
    if (key =='d')
    {
        if (player.getState() == DEAD || player.getState() == RESPAWN) {
            return;
        }
        player.setState(RIGHT);
    }
    
    if (key =='a')
    {
        if (player.getState() == DEAD || player.getState() == RESPAWN) {
            return;
        }
        player.setState(LEFT);
    }
    
    if (key == KEY_SPACE)
    {
        if (player.getState() == DEAD || player.getState() == RESPAWN) {
            return;
        }
        if (!player.getIsJumping()) {
            player.setIsJumping(true);
            player.setVelY(9.0f);
        }
    }
}

//====================================================
// KeyboardUp
// Purpose: Process User Keyboard Inputs (Release)
// Input: key pressed, mouse co-ordinates <x,y>
//====================================================
void keyboardUp (unsigned char key, int x, int y) {
    if (key =='w' && player.getState() == UP)
    {
        player.setState(IDLE);
    }
    
    if (key =='s' && player.getIsCrouching())
    {
        player.setIsCrouching(false);
        player.setState(IDLE);
    }
    
    if (key =='d' && player.getState() == RIGHT)
    {
        player.setState(IDLE);
    }
    
    if (key =='a' && player.getState() == LEFT)
    {
        player.setState(IDLE);
    }
}


#pragma mark Initialization & Main Loop

//====================================================
// Enable
// Purpose: Enable OpenGL Parameters
//====================================================
void enable (void) {
    glEnable (GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
}

//====================================================
// Init
// Purpose: Load assets, data structures, etc.
//====================================================
void init (void) {
    enable(); // Enable OpenGL Parameters
    level = Level(0, 0, WIDTH * 4, HEIGHT - 50.0f);
    level.setLevelSprite(WIDTH, HEIGHT - 50.0f);
    level.loadLevelFromFile("level1.txt");
    
    pipe = Object(1200, 318, 32, 32, 1, 0, 0, "pipe.png");
    
    player = Player();
    player.initializeSprite();
    player.setPosition(player.getPosition().posX, level.getLevelHeight());
    
    goomba = Goomba();
    goomba.initializeSprite();
    goomba.setState(eLEFT);
    
    goomba2 = Goomba();
    goomba2.initializeSprite();
    goomba2.setState(eLEFT);
    goomba2.setPosition(250.0f, 259.0f);

    koopa = Koopa();
    koopa.initializeSprite();
    koopa.setState(eRIGHT);
    
    plant = Plant();
    plant.initializeSprite();
    
    soundEngine = SoundEngine();
    soundEngine.sound(0, 0, 0, "SuperMarioBros.wav", true);
    
    glClearColor(0.0, 0.0, 0.0, 1.0);
 	glViewport(0, 0, WIDTH, HEIGHT);
    
 	glMatrixMode(GL_PROJECTION);
 	glLoadIdentity();
    glOrtho(0, WIDTH, HEIGHT, 0, 0, 1);
    
    soundEngine.playSound(soundEngine.getSound()[soundEngine.getSoundMap().find("SuperMarioBros.wav")->second]);

}


//====================================================
// Setup
// Purpose: Set Up GLEW Environment
//====================================================
void setup (void) {
    // initialise GLEW
    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK)
        throw std::runtime_error("glewInit failed");
    
    // GLEW throws some errors, so discard all the errors so far
    while(glGetError() != GL_NO_ERROR) {}
    
    // make sure OpenGL version 3.2 API is available
    if(!GLEW_VERSION_3_2)
        throw std::runtime_error("OpenGL 3.2 API is not available.");
}

//====================================================
// Main Funtion
// Purpose: Set Up Rendering Environment (GLUT & GLEW)
//          & Establish MainLoop
//====================================================
int main (int argc, char **argv) {
    // Seed Random Number Generator
    srand((unsigned int)time(0));
    
    // Create our Window (Initialize GLUT)
    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize (WIDTH*2, HEIGHT*2);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("First Person Shooter Game");
    
    // Set up Callbacks
    glutDisplayFunc (display);
    glutKeyboardFunc (keyboard);
    glutKeyboardUpFunc (keyboardUp);
    
    // Initialize GLEW
    setup();
    
    // Initialize Rendering Environment
    init();
        
    // Start Timer
	glutTimerFunc(FPS, update, 0);
    
    // Run Main Loop
    glutMainLoop();
    
    return 0;
}