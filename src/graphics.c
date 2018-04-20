#include "SDL2/SDL.h"
#include "SDL2/SDL_opengl.h"
#include <GL/glu.h>
#include "maze.h"
#define M_SIZE 100

#define true 1
#define false 0
#define bool _Bool

bool renderQuad;
int rot;
int pos[3];

void mazeSeg()
{
  glBegin( GL_QUADS );
    glColor3f(   1.0f,  0.0f,  0.0f);  // Violet
    // Top face
    glVertex3f(  1.0f, 1.0f, -1.0f );  // Top-right of top face
    glVertex3f( -1.0f, 1.0f, -1.0f );  // Top-left of top face
    glVertex3f( -1.0f, 1.0f,  1.0f );  // Bottom-left of top face
    glVertex3f(  1.0f, 1.0f,  1.0f );  // Bottom-right of top face

    // Bottom face
    glVertex3f(  1.0f, -1.0f, -1.0f ); // Top-right of bottom face
    glVertex3f( -1.0f, -1.0f, -1.0f ); // Top-left of bottom face
    glVertex3f( -1.0f, -1.0f,  1.0f ); // Bottom-left of bottom face
    glVertex3f(  1.0f, -1.0f,  1.0f ); // Bottom-right of bottom face

   // Left face
    glVertex3f( -1.0f,  1.0f,  1.0f);  // Top-Right of left face
    glVertex3f( -1.0f,  1.0f, -1.0f);  // Top-Left of left face
    glVertex3f( -1.0f, -1.0f, -1.0f);  // Bottom-Left of left face
    glVertex3f( -1.0f, -1.0f,  1.0f);  // Bottom-Right of left face

    // Right face
    glVertex3f(  1.0f,  1.0f,  1.0f);  // Top-Right of left face
    glVertex3f(  1.0f,  1.0f, -1.0f);  // Top-Left of left face
    glVertex3f(  1.0f, -1.0f, -1.0f);  // Bottom-Left of left face
    glVertex3f(  1.0f, -1.0f,  1.0f);  // Bottom-Right of left face
glEnd();
}

bool initGL()
{
  glEnable( GL_DEPTH_TEST );
  glDepthFunc(GL_LEQUAL);
  glShadeModel(GL_SMOOTH);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
  //glEnable ( GL_LIGHTING );
    // glEnable(GL_LIGHT0);

  //Initialize clear color
  glClearColor( 0.f, 0.f, 0.f, 1.f );
  glClearDepth(1.0f);

  GLfloat aspect = 1 ;

  // Set the viewport to cover the new window
  glViewport(0, 0, 1080, 1080);

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
        1080,                               
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

void handleKeys( SDL_Keycode key, int x, int y, Maze* maze ) 
{ 
  //Toggle quad 
  if( key == SDLK_q ) 
  { 
    renderQuad = !renderQuad; 
  } 
  if( key == SDLK_w )
  {
    if (pos[2] == 0)
      maze_progress(maze, 2);
    if (pos[2] == 1)
      maze_progress(maze, 1);
    if (pos[2] == 2)
      maze_progress(maze, 0);
    if (pos[2] == 3)
      maze_progress(maze, 3);
  }
  if( key == SDLK_s )
  {
    if (pos[2] == 0)
      maze_progress(maze, 0);
    if (pos[2] == 1)
      maze_progress(maze, 3);
    if (pos[2] == 2)
      maze_progress(maze, 2);
    if (pos[2] == 3)
      maze_progress(maze, 1);
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
   GLfloat specular[] = {1, 1, 1, 1.0};
   GLfloat lightpos[] = {pos[0], 0, pos[1], 1};
   
   gluLookAt(	pos[1], 30, pos[0],
			pos[1] + (pos[2] == 1 ? 10 : 0) + (pos[2] == 3 ? -10 : 0), 
      0.0, 
      pos[0] + (pos[2] == 0 ? -10 : 0) + (pos[2] == 2 ? 10 : 0),
			0.0f, 1.0f,  0.0f);

   GLfloat mat_ambient[] = { 0.25, 0.25, 0.25, 1.0 };
GLfloat mat_diffuse[] = { 0.4, 0.4, 0.4, 1.0 };
GLfloat mat_specular[] = { 0.774597, 0.774597, 0.774597, 1.0 };

GLfloat mat_shine = 0.6;
  glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, 1);
  //glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
  glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.1);
  glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.05);

glMaterialfv (GL_FRONT, GL_AMBIENT, mat_ambient);
glMaterialfv (GL_FRONT, GL_DIFFUSE, mat_diffuse);
glMaterialfv (GL_FRONT, GL_SPECULAR, mat_specular);
glMaterialf (GL_FRONT, GL_SHININESS, mat_shine * 128);

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
        glColor3f(   2.0f,  0.5f,  0.0f ); // Orange
        glVertex3f( -2.0f, -2.0f,  2.0f );  // Bottom-left of top face
        glVertex3f(  2.0f, -2.0f,  2.0f );  // Bottom-right of top face
      } 
      if (maze._data[j + i * M_SIZE].wall_east)
      {
        glColor3f(   2.0f,  0.0f,  2.0f);  // Violet
        glVertex3f(  2.0f,  2.0f,  2.0f);  // Top-Right of left face
        glVertex3f(  2.0f,  2.0f, -2.0f);  // Top-Left of left face
        glColor3f(   2.0f,  0.5f,  0.0f ); // Orange
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
        glVertex3f(  2.0f, 2.0f,   -2.0f );  // Top-right of top face
        glVertex3f( -2.0f, 2.0f,   -2.0f );  // Top-left of top face
        glVertex3f( -2.0f, -2.0f,  -2.0f );  // Bottom-left of top face
        glVertex3f(  2.0f, -2.0f,  -2.0f );  // Bottom-right of top face
      }
      glEnd();
      glPopMatrix();
    }

  glTranslatef(pos[1],0,pos[0]);
  mazeSeg();

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
        handleKeys( event.key.keysym.sym , x, y, &maze ); 
      } 
    } 
    //Run frame update 
    //update(window); 
    //Render frame 
    //rot += 10;
    pos[0] = -maze.posy * 4;
    pos[1] = maze.posx * 4;
    render(window, maze); 

    SDL_Delay(100);
  }   
}
