#include "gl_framework.hpp"
#include "cg.h"
// #include "03_colorcube_rotate.hpp"
extern GLfloat xrot,yrot,zrot;

namespace csX75
{
  //! Initialize GL State
  void initGL(void)
  {
    //Set framebuffer clear color
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
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
    else if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
      yrot -= 1.0;
    else if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
      yrot += 1.0;
    else if (key == GLFW_KEY_UP && action == GLFW_PRESS)
      xrot += 1.0;
    else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
      xrot += 1.0;
    else if (key == GLFW_KEY_PAGE_UP && action == GLFW_PRESS)
      zrot += 1.0;
    else if (key == GLFW_KEY_PAGE_DOWN && action == GLFW_PRESS)
      zrot += 1.0;
    else if(key == GLFW_KEY_L && action == GLFW_PRESS)
      cg::loadObject();
  }
      //!GLFW mouse click callback
  // void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
  // {
  //   if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && mods == GLFW_MOD_SHIFT)
  //       // Delete point
  //     int a=0;
  //   else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
  //     glfwGetCursorPos(window, &xpos, &ypos);
  //     std::cout<<"Position: "<<xpos<<" "<<ypos<<std::endl;
      
  //       // popup_menu(); Insert point
  //         if(count<4){          
  //           zpos=0.5;
  //         }else if(count >4 && count<8){
  //           zpos=-0.5;
  //           // glDrawArrays(GL_TRIANGLES, 0 ,4);
  //         }else{
  //           count=0;
  //           zpos=0.5;
  //         }
  //         positions[count]={ xpos, ypos, zpos, 1};
  //         // std::cout<<"Position: "<<positions[count][0]<<std::endl;
  //         csX75::setPoint(positions);
  //         count++;
  //         // if(count==8){            
  //         //   glDrawArrays(GL_TRIANGLES, 0, 8);
  //         // }
  //         // else{            
  //           // glDrawArrays(GL_POINTS, 0, count);
  //         // }

  //     }
  // }
};  
  


