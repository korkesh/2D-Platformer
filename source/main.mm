#include "sharedHeaders.h"
#include "player.h"
#include "level.h"

#pragma mark Globals

Player player;
Level level;
SoundEngine soundEngine;

float prevXpos = 0, prevYpos = 1.5, prevZpos = 15;
float lastx = WIDTH/2, lasty = HEIGHT/2;

float xpos = 0.0f, ypos = 0.0, zpos = 0.0;


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
    
    // Adjust Camera
    camera();

    // Render Scene
    level.renderLevel();
    
    // Render Player
    player.renderPlayer();

    glutSwapBuffers(); //swap the buffers
}

//====================================================
// Update
// Purpose: Update According to FPS
// Input: 0
//====================================================
void update (int t) {
    
    player.updatePosition(level.getLevelWidth(), level.getLevelHeight(), level.getObjectList());
    player.updatePlayerAnimation(FPS / 1000.0f);
    
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
    if (key =='w')
    {
        if (!player.getIsJumping()) {
            player.setIsJumping(true);
            player.setVelY(12.0f);
            soundEngine.playSound(soundEngine.getSound()[soundEngine.getSoundMap().find("/Users/Korkesh/2D-Platformer/resources/jump.wav")->second]);
        }
    }
    
    if (key =='s')
    {
        //player.setState(DOWN);
    }
    
    if (key =='d')
    {
        player.setState(RIGHT);
    }
    
    if (key =='a')
    {
        player.setState(LEFT);
    }
    
    if (key == KEY_SPACE)
    {
        if (!player.getIsJumping()) {
            player.setIsJumping(true);
            player.setVelY(12.0f);
            soundEngine.playSound(soundEngine.getSound()[soundEngine.getSoundMap().find("/Users/Korkesh/2D-Platformer/resources/jump.wav")->second]);
        }
    }
    
    if (key == KEY_ESC)
    {
        exit(0);
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
    
    if (key =='s' && player.getState() == DOWN)
    {
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
    level = Level(0, 0, WIDTH * 3, HEIGHT - 150.0f);
    level.setLevelSprite(WIDTH, HEIGHT - 150.0f);
    player = Player();
    player.initializeSprite();
    player.setPosition(player.getPosition().posX, level.getLevelHeight());
    soundEngine = SoundEngine();
    soundEngine.sound(0, 0, 0, "/Users/Korkesh/2D-Platformer/resources/SuperMarioBros.wav", true);
    soundEngine.sound(0, 0, 0, "/Users/Korkesh/2D-Platformer/resources/jump.wav", false);
    textures();
//    SetupWorld(); // TODO: Used to load levels
    
    glClearColor(0.2, 0.2, 0.6, 1.0); /* Mario Blue */
 	glViewport(0, 0, WIDTH, HEIGHT);
    
 	glMatrixMode(GL_PROJECTION);
 	glLoadIdentity();
    glOrtho(0, WIDTH, HEIGHT, 0, 0, 1);
    
    soundEngine.playSound(soundEngine.getSound()[soundEngine.getSoundMap().find("/Users/Korkesh/2D-Platformer/resources/SuperMarioBros.wav")->second]);

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
    glutInitWindowSize (WIDTH, HEIGHT);
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