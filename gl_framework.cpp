#include "gl_framework.hpp"

namespace cg
{
  //! Initialize GL State
  void initGL(void)
  {
    //Set framebuffer clear color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    //Set depth buffer furthest depth
    glClearDepth(1.0);
    //Set depth test to less-than
    glDepthFunc(GL_LESS);
    //Enable depth testing
    glEnable(GL_DEPTH_TEST);
  }
  
  //!GLFW Error Callback
  void error_callback(int error, const char* description)
  {
    std::cerr<<description<<std::endl;
  }
  
  //!GLFW framebuffer resize callback
  void framebuffer_size_callback(GLFWwindow* window, int width, int height)
  {
    //!Resize the viewport to fit the window size - draw to entire window
    glViewport(0, 0, width, height);
  }
  
  //!GLFW keyboard callback
  void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
  {
    //!Close the window if the ESC key was pressed
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
      glfwSetWindowShouldClose(window, GL_TRUE);

  }

  //!GLFW mouse click callback
  void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
  {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && mods == GLFW_MOD_SHIFT)
        // Delete point
      int a=0;
    else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
        // popup_menu(); Insert point
          double xpos, ypos;
          glfwGetCursorPos(window, &xpos, &ypos);
          std::cout<<"Position: "<<xpos<<" "<<ypos<<std::endl;
          glClearColor ( 0.0 , 0.1 , 0.1 , 1.0f );
          glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
          glViewport ( 0 , 0 , 1024 , 768 );
          glMatrixMode(GL_PROJECTION);
          glLoadIdentity();
          glOrtho( 0 , 1024 , 768 , 0 , 100 , -100 );
          glMatrixMode(GL_MODELVIEW);
          glLoadIdentity();

          glPointSize(10);
          // glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
          glBegin(GL_POINTS);
          glColor4f(0.7,0.5,0,1);
          glVertex3f(xpos,ypos,0);
          glEnd();
          // glfwSwapBuffers(window);
      }
  }

};  
  


