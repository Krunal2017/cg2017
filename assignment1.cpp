/*
  CSX75: Tutorial 2

  A program which opens a window and draws the "color cube."

  Modified from An Introduction to OpenGL Programming, 
  Ed Angel and Dave Shreiner, SIGGRAPH 2013

  Written by Parag Chaudhuri, 2015
*/

#include "assignment1.hpp"
// #include <GL/glew.h>
// #include <GLFW/glfw3.h>
// #include <iostream>
GLuint shaderProgram;
GLuint vbo, vao;
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
//-----------------------------------------------------------------

void initBuffersGL(void)
{

  std::string vertex_shader_file("vshader.glsl");
  std::string fragment_shader_file("fshader.glsl");

  std::vector<GLuint> shaderList;
  shaderList.push_back(cg::LoadShaderGL(GL_VERTEX_SHADER, vertex_shader_file));
  shaderList.push_back(cg::LoadShaderGL(GL_FRAGMENT_SHADER, fragment_shader_file));

  shaderProgram = cg::CreateProgramGL(shaderList);
  glUseProgram( shaderProgram );

}
// GLfloat pointVertex[] = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
// GLfloat pointVertex2[] = { SCREEN_WIDTH * 0.75, SCREEN_HEIGHT / 2 };
void renderGL(void)
{ //GLfloat pointvertex[] = { 256 , 256 }; 
  glClear(GL_COLOR_BUFFER_BIT);
  // glEnableClientState(GL_VERTEX_ARRAY);
  // glPointSize(50);
  // glVertexPointer( 2 , GL_FLOAT , 0 ,pointVertex);
  // glDrawArrays(GL_POINTS, 0, 1);
  // glDisableClientState(GL_VERTEX_ARRAY);

  
}

int main(int argc, char** argv)
{
  //! The pointer to the GLFW window
  GLFWwindow* window;

  //! Setting up the GLFW Error callback
  glfwSetErrorCallback(cg::error_callback);

  //! Initialize GLFW
  if (!glfwInit())
    return -1;

  //We want OpenGL 3.3
  // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); 
  // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  //This is for MacOSX - can be omitted otherwise
  // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); 
  //We don't want the old OpenGL 
  // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 

  //! Create a windowed mode window and its OpenGL context
  window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Assignment 1", NULL, NULL);
  if (!window)
    {
      glfwTerminate();
      return -1;
    }
  
  //! Make the window's context current 
  glfwMakeContextCurrent(window);

  //Initialize GLEW
  //Turn this on to get Shader based OpenGL
  glewExperimental = GL_TRUE;
  GLenum err = glewInit();
  if (GLEW_OK != err)
    {
      //Problem: glewInit failed, something is seriously wrong.
      std::cerr<<"GLEW Init Failed : %s"<<std::endl;
    }

  //Print and see what context got enabled
  std::cout<<"Vendor: "<<glGetString (GL_VENDOR)<<std::endl;
  std::cout<<"Renderer: "<<glGetString (GL_RENDERER)<<std::endl;
  std::cout<<"Version: "<<glGetString (GL_VERSION)<<std::endl;
  std::cout<<"GLSL Version: "<<glGetString (GL_SHADING_LANGUAGE_VERSION)<<std::endl;

  //Keyboard Callback
  glfwSetKeyCallback(window, cg::key_callback);
  //Cursor Position Callback
  // glfwSetCursorPosCallback(window, cursor_pos_callback);
  //Mouse Callback
  glfwSetMouseButtonCallback(window, cg::mouse_button_callback);
  //Framebuffer resize callback
  glfwSetFramebufferSizeCallback(window, cg::framebuffer_size_callback);

  // Ensure we can capture the escape key being pressed below
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

  //Initialize GL state
  cg::initGL();
  initBuffersGL();


  // glClearColor ( 0.0 , 0.1 , 0.1 , 1.0f );
          // glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
          // glViewport ( 0.0f , 0.0f , SCREEN_WIDTH , SCREEN_HEIGHT );
          // glMatrixMode( GL_PROJECTION );
          // glLoadIdentity( );
          // glOrtho( 0 , SCREEN_WIDTH , 0 , SCREEN_HEIGHT , 0 , 1 );
          // glMatrixMode(GL_MODELVIEW);
          // glLoadIdentity( );

  // Loop until the user closes the window
  while (glfwWindowShouldClose(window) == 0)
    {
      glClear( GL_COLOR_BUFFER_BIT ); 
      // Render here
      renderGL();

      // Swap front and back buffers
      glfwSwapBuffers(window);
      
      // Poll for and process events
      glfwPollEvents();
    }
  
  glfwTerminate();
  return 0;
}

//-------------------------------------------------------------------------


