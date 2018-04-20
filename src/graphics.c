#include "SDL2/SDL.h"
#include "SDL2/SDL_opengl.h"
#include <GL/glu.h>
#include "maze.h"
#define M_SIZE 10

#define true 1
#define false 0
#define bool _Bool

bool renderQuad;
int rot;
int pos[3];

void mazeSeg()
{
  glBegin( GL_QUADS );
    // Top face
    glColor3f(   0.0f, 2.0f,  0.0f );  // Green
    glVertex3f(  2.0f, 2.0f, -2.0f );  // Top-right of top face
    glVertex3f( -2.0f, 2.0f, -2.0f );  // Top-left of top face
    glVertex3f( -2.0f, 2.0f,  2.0f );  // Bottom-left of top face
    glVertex3f(  2.0f, 2.0f,  2.0f );  // Bottom-right of top face

    // Bottom face
    glColor3f(   2.0f,  0.5f,  0.0f ); // Orange
    glVertex3f(  2.0f, -2.0f, -2.0f ); // Top-right of bottom face
    glVertex3f( -2.0f, -2.0f, -2.0f ); // Top-left of bottom face
    glVertex3f( -2.0f, -2.0f,  2.0f ); // Bottom-left of bottom face
    glVertex3f(  2.0f, -2.0f,  2.0f ); // Bottom-right of bottom face

   // Left face
    glColor3f(   0.0f,  0.0f,  2.0f);  // Blue
    glVertex3f( -2.0f,  2.0f,  2.0f);  // Top-Right of left face
    glVertex3f( -2.0f,  2.0f, -2.0f);  // Top-Left of left face
    glVertex3f( -2.0f, -2.0f, -2.0f);  // Bottom-Left of left face
    glVertex3f( -2.0f, -2.0f,  2.0f);  // Bottom-Right of left face

    // Right face
    glColor3f(   2.0f,  0.0f,  2.0f);  // Violet
    glVertex3f(  2.0f,  2.0f,  2.0f);  // Top-Right of left face
    glVertex3f(  2.0f,  2.0f, -2.0f);  // Top-Left of left face
    glVertex3f(  2.0f, -2.0f, -2.0f);  // Bottom-Left of left face
    glVertex3f(  2.0f, -2.0f,  2.0f);  // Bottom-Right of left face
glEnd();
}

bool initGL()
{
  glEnable( GL_DEPTH_TEST );
  glDepthFunc(GL_LEQUAL);
  glShadeModel(GL_SMOOTH);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
  glFrustum(0,0,0,0,0,10);

  //Initialize clear color
  glClearColor( 0.f, 0.f, 0.f, 1.f );
  glClearDepth(1.0f);

  GLfloat aspect = 1920 / 1080;

  // Set the viewport to cover the new window
  glViewport(0, 0, 1920, 1080);

  // Set the aspect ratio of the clipping volume to match the viewport
  glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
  glLoadIdentity();             // Reset
  // Enable perspective projection with fovy, aspect, zNear and zFar
  gluPerspective(45.0f, aspect, 0.1f, 400.0f);

  //Check for error
  GLenum error = glGetError();
  if( error != GL_NO_ERROR )
  {
    printf( "Error initializing OpenGL! \n");
    return false;
  }

  return true;
}


bool init(SDL_Window** window)
{
    //Initialize SDL
    if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
    {
        return false;    
    }
    *window = SDL_CreateWindow(
        "Cubes",                  
        SDL_WINDOWPOS_UNDEFINED,           
        SDL_WINDOWPOS_UNDEFINED,           
        1920,                               
        1080,                               
        SDL_WINDOW_OPENGL
    );
    SDL_GL_CreateContext(*window);
    
    //Initialize OpenGL
    if( initGL() == false )
    {
        return false;    
    }
    
    return true;    
}

void handleKeys( SDL_Keycode key, int x, int y ) 
{ 
  //Toggle quad 
  if( key == SDLK_q ) 
  { 
    renderQuad = !renderQuad; 
  } 
  if( key == SDLK_w )
  {
    if (pos[2] == 0)
      pos[0] -= 4;
    if (pos[2] == 1)
      pos[1] += 4;
    if (pos[2] == 2)
      pos[0] += 4;
    if (pos[2] == 3)
      pos[1] -= 4;

  }
  if( key == SDLK_s )
  {
     if (pos[2] == 0)
      pos[0] += 4;
    if (pos[2] == 1)
      pos[1] -= 4;
    if (pos[2] == 2)
      pos[0] -= 4;
    if (pos[2] == 3)
      pos[1] += 4;
  }
  if( key == SDLK_a )
  {
    pos[2] = (pos[2] + 3)%4;
  }
  if( key == SDLK_d )
  {
    pos[2] = (pos[2] + 1)%4;
  }
}

void render(SDL_Window* w, Maze maze)
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
   glMatrixMode(GL_MODELVIEW); 
   
   glLoadIdentity();
   
   gluLookAt(	pos[1], 0.0f, pos[0],
			pos[1] + (pos[2] == 1 ? 1 : 0) + (pos[2] == 3 ? -1 : 0), 
      0.0, 
      pos[0] + (pos[2] == 0 ? -1 : 0) + (pos[2] == 2 ? 1 : 0),
			0.0f, 1.0f,  0.0f);
/*
  //Render quad
  for (int i = 0; i < 10; ++i){
    glPushMatrix();
    glTranslatef( 0, 0, -i * 4 );                     // Translate back 6 units
    mazeSeg();
    glPopMatrix();
  }

  */

  

  for (int i = 0; i < M_SIZE; ++i)
    for (int j = 0; j < M_SIZE; ++j)
    {
      glPushMatrix();
      glTranslatef(j * 4, 0, -i * 4);
      glBegin( GL_QUADS );
      if (maze._data[j + i * M_SIZE].wall_north)
      {
        glColor3f(   0.0f, 2.0f,   0.0f );  // Green
        glVertex3f(  2.0f, 2.0f,   2.0f );  // Top-right of top face
        glVertex3f( -2.0f, 2.0f,   2.0f );  // Top-left of top face
        glVertex3f( -2.0f, -2.0f,  2.0f );  // Bottom-left of top face
        glVertex3f(  2.0f, -2.0f,  2.0f );  // Bottom-right of top face
      } 
      if (maze._data[j + i * M_SIZE].wall_east)
      {
        glColor3f(   2.0f,  0.0f,  2.0f);  // Violet
        glVertex3f(  2.0f,  2.0f,  2.0f);  // Top-Right of left face
        glVertex3f(  2.0f,  2.0f, -2.0f);  // Top-Left of left face
        glVertex3f(  2.0f, -2.0f, -2.0f);  // Bottom-Left of left face
        glVertex3f(  2.0f, -2.0f,  2.0f);  // Bottom-Right of left face
      }
      if (maze._data[j + i * M_SIZE].wall_west)
      {
        // Left face
        glColor3f(   0.0f,  0.0f,  2.0f);  // Blue
        glVertex3f( -2.0f,  2.0f,  2.0f);  // Top-Right of left face
        glVertex3f( -2.0f,  2.0f, -2.0f);  // Top-Left of left face
        glVertex3f( -2.0f, -2.0f, -2.0f);  // Bottom-Left of left face
        glVertex3f( -2.0f, -2.0f,  2.0f);  // Bottom-Right of left face
      }
      if (maze._data[j + i * M_SIZE].wall_south)
      {
        glColor3f(   0.0f, 2.0f,   0.0f );  // Green
        glVertex3f(  2.0f, 2.0f,   2.0f );  // Top-right of top face
        glVertex3f( -2.0f, 2.0f,   2.0f );  // Top-left of top face
        glVertex3f( -2.0f, -2.0f,  2.0f );  // Bottom-left of top face
        glVertex3f(  2.0f, -2.0f,  2.0f );  // Bottom-right of top face
      }
      glEnd();
      glPopMatrix();
    }


 //Update screen
  SDL_GL_SwapWindow(w);
}

int main()
{
  SDL_Window* window;
  init(&window);
  bool quit;
  SDL_Event event;
  pos[0] = 0;
  pos[1] = 0;
  pos[2] = 0;

  Maze maze;

  maze_generate(&maze, M_SIZE, M_SIZE);

  while(!quit)
  {
    //While there are events to handle 
    while( SDL_PollEvent( &event ) ) 
    { 
      if( event.type == SDL_QUIT ) 
        quit = true; 
      else if( event.type == SDL_KEYDOWN ) 
      { 
        //Handle keypress with current mouse position 
        int x = 0, y = 0;
        SDL_GetMouseState( &x, &y ); 
        handleKeys( event.key.keysym.sym , x, y ); 
      } 
    } 
    //Run frame update 
    //update(window); 
    //Render frame 
    //rot += 10;
    render(window, maze); 

    SDL_Delay(100);
  }   
}
