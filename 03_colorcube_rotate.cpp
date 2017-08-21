/*
  CSX75 Tutorial 3

  A program which opens a window and draws the "color cube."

  Use the arrow keys and PgUp,PgDn,
  keys to make the cube move.

  Modified from An Introduction to OpenGL Programming, 
  Ed Angel and Dave Shreiner, SIGGRAPH 2013

  Written by Parag Chaudhuri, 2015
*/


#include "03_colorcube_rotate.hpp"

GLuint shaderProgram;
GLuint vbo, vao;

glm::mat4 rotation_matrix;
glm::mat4 ortho_matrix;
glm::mat4 modelview_matrix;
GLuint uModelViewMatrix;

//-----------------------------------------------------------------

//6 faces, 2 triangles/face, 3 vertices/triangle
const int num_vertices = 64;

//Eight vertices in homogenous coordinates
glm::vec4 positions[16] = {
  glm::vec4(-0.45, -0.8, 0.045, 1.0),
  glm::vec4(-0.45, 0.8, 0.045, 1.0),
  glm::vec4(0.45, 0.8, 0.045, 1.0),
  glm::vec4(0.45, -0.8, 0.045, 1.0),
  glm::vec4(-0.45, -0.8, -0.045, 1.0),
  glm::vec4(-0.45, 0.8, -0.045, 1.0),
  glm::vec4(0.45, 0.8, -0.045, 1.0),
  glm::vec4(0.45, -0.8, -0.045, 1.0),

  glm::vec4(-0.40, -0.69, 0.046, 1.0),
  glm::vec4(-0.40, 0.75, 0.046, 1.0),
  glm::vec4(0.40, 0.75, 0.046, 1.0),
  glm::vec4(0.40, -0.69, 0.046, 1.0),

  glm::vec4(-0.14, -0.78, 0.046, 1.0),
  glm::vec4(-0.14, -0.70, 0.046, 1.0),
  glm::vec4(0.14, -0.70, 0.046, 1.0),
  glm::vec4(0.14, -0.78, 0.046, 1.0)
};

//RGBA colors
glm::vec4 colors[16] = {
  glm::vec4(0.15, 0.15, 0.15, 1.0),
  glm::vec4(0.15, 0.15, 0.15, 1.0),
  glm::vec4(0.15, 0.15, 0.15, 1.0),
  glm::vec4(0.15, 0.15, 0.15, 1.0),
  
  // glm::vec4(1.0, 1.0, 1.0, 1.0),
  // glm::vec4(0.4, 0.3, 0.6, 1.0),
  // glm::vec4(1.0, 1.0, 1.0, 1.0),
  // glm::vec4(0.4, 0.3, 0.6, 1.0),
  glm::vec4(0.15, 0.15, 0.15, 1.0),
  glm::vec4(0.15, 0.15, 0.15, 1.0),
  glm::vec4(0.15, 0.15, 0.15, 1.0),
  glm::vec4(0.15, 0.15, 0.15, 1.0),

  glm::vec4(1.0, 1.0, 1.0, 1.0),
  glm::vec4(0.4, 0.3, 0.6, 1.0),
  glm::vec4(1.0, 1.0, 1.0, 1.0),
  glm::vec4(0.4, 0.3, 0.6, 1.0),

  glm::vec4(0.35, 0.35, 0.35, 1.0),
  glm::vec4(0.35, 0.35, 0.35, 1.0),
  glm::vec4(0.35, 0.35, 0.35, 1.0),
  glm::vec4(0.35, 0.35, 0.35, 1.0)
};
int tri_idx=0;
glm::vec4 v_positions[num_vertices];
glm::vec4 v_colors[num_vertices];

// quad generates two triangles for each face and assigns colors to the vertices
void quad(int a, int b, int c, int d)
{
  v_colors[tri_idx] = colors[a]; v_positions[tri_idx] = positions[a]; tri_idx++;
  v_colors[tri_idx] = colors[b]; v_positions[tri_idx] = positions[b]; tri_idx++;
  v_colors[tri_idx] = colors[c]; v_positions[tri_idx] = positions[c]; tri_idx++;
  v_colors[tri_idx] = colors[a]; v_positions[tri_idx] = positions[a]; tri_idx++;
  v_colors[tri_idx] = colors[c]; v_positions[tri_idx] = positions[c]; tri_idx++;
  v_colors[tri_idx] = colors[d]; v_positions[tri_idx] = positions[d]; tri_idx++;
 }

void setPoint(glm::vec4 position)
{
  // v_colors[tri_idx] = colors[a]; v_positions[tri_idx] = positions[a]; tri_idx++;
  v_colors[tri_idx] = colors[1]; v_positions[tri_idx] = position; tri_idx++;
}

// generate 12 triangles: 36 vertices and 36 colors
void colorcube(void)
{
    // quad( 9, 8, 11, 10);
    quad( 1, 0, 3, 2 );
    quad( 2, 3, 7, 6 );
    quad( 3, 0, 4, 7 );
    quad( 6, 5, 1, 2 );
    quad( 4, 5, 6, 7 );
    quad( 5, 4, 0, 1 );

    quad( 9, 8, 11, 10);

    quad( 13, 12, 15, 14);
}
// glm::vec4 positions[8];
  int count=0;
  double xpos1, ypos1, zpos1;
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
  {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && mods == GLFW_MOD_SHIFT)
        // Delete point
      int a=0;
    else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
      glfwGetCursorPos(window, &xpos1, &ypos1);
      std::cout<<"Position: "<<xpos1<<" "<<ypos1<<std::endl;
      
        // popup_menu(); Insert point
          if(count<4){          
            zpos1=0.5;
          }else if(count >4 && count<8){
            zpos1=-0.5;
            // glDrawArrays(GL_TRIANGLES, 0 ,4);
          }else{
            count=0;
            zpos1=0.5;
          }
          setPoint(glm::vec4(xpos1/1000,ypos1/1000,zpos1,1));
          glDrawArrays(GL_POINTS, 0, num_vertices);
          // positions[count]={ xpos, ypos, zpos, 1};
          // std::cout<<"Position: "<<positions[count][0]<<std::endl;
          // csX75::setPoint(positions);
          count++;
          // if(count==8){            
          //   glDrawArrays(GL_TRIANGLES, 0, 8);
          // }
          // else{            
            // glDrawArrays(GL_POINTS, 0, count);
          // }

      }
  }

//-----------------------------------------------------------------

void initBuffersGL(void)
{
  colorcube();

  //Ask GL for a Vertex Attribute Object (vao)
  glGenVertexArrays (1, &vao);
  //Set it as the current array to be used by binding it
  glBindVertexArray (vao);

  //Ask GL for a Vertex Buffer Object (vbo)
  glGenBuffers (1, &vbo);
  //Set it as the current buffer to be used by binding it
  glBindBuffer (GL_ARRAY_BUFFER, vbo);
  //Copy the points into the current buffer
  glBufferData (GL_ARRAY_BUFFER, sizeof (v_positions) + sizeof(v_colors), NULL, GL_STATIC_DRAW);
  glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(v_positions), v_positions );
  glBufferSubData( GL_ARRAY_BUFFER, sizeof(v_positions), sizeof(v_colors), v_colors );

  // Load shaders and use the resulting shader program
  std::string vertex_shader_file("03_vshader.glsl");
  std::string fragment_shader_file("03_fshader.glsl");

  std::vector<GLuint> shaderList;
  shaderList.push_back(csX75::LoadShaderGL(GL_VERTEX_SHADER, vertex_shader_file));
  shaderList.push_back(csX75::LoadShaderGL(GL_FRAGMENT_SHADER, fragment_shader_file));

  shaderProgram = csX75::CreateProgramGL(shaderList);
  glUseProgram( shaderProgram );

  // set up vertex arrays
  GLuint vPosition = glGetAttribLocation( shaderProgram, "vPosition" );
  glEnableVertexAttribArray( vPosition );
  glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
  
  GLuint vColor = glGetAttribLocation( shaderProgram, "vColor" ); 
  glEnableVertexAttribArray( vColor );
  glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(v_positions)) );

  uModelViewMatrix = glGetUniformLocation( shaderProgram, "uModelViewMatrix");
}

void renderGL(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  rotation_matrix = glm::rotate(glm::mat4(1.0f), xrot, glm::vec3(1.0f,0.0f,0.0f));
  rotation_matrix = glm::rotate(rotation_matrix, yrot, glm::vec3(0.0f,1.0f,0.0f));
  rotation_matrix = glm::rotate(rotation_matrix, zrot, glm::vec3(0.0f,0.0f,1.0f));
  ortho_matrix = glm::ortho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);

  modelview_matrix = ortho_matrix * rotation_matrix;

  glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));
  // Draw 
  glDrawArrays(GL_TRIANGLES, 0, num_vertices);
  
}

int main(int argc, char** argv)
{
  //! The pointer to the GLFW window
  GLFWwindow* window;

  //! Setting up the GLFW Error callback
  glfwSetErrorCallback(csX75::error_callback);

  //! Initialize GLFW
  if (!glfwInit())
    return -1;

  //We want OpenGL 4.0
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); 
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  //This is for MacOSX - can be omitted otherwise
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); 
  //We don't want the old OpenGL 
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 

  //! Create a windowed mode window and its OpenGL context
  window = glfwCreateWindow(512, 512, "CS475/CS675 Tutorial 3: Rotating  Colorcube", NULL, NULL);
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
  glfwSetKeyCallback(window, csX75::key_callback);
  //Framebuffer resize callback
  glfwSetFramebufferSizeCallback(window, csX75::framebuffer_size_callback);
  glfwSetMouseButtonCallback(window, mouse_button_callback);

  // Ensure we can capture the escape key being pressed below
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

  //Initialize GL state
  csX75::initGL();
  initBuffersGL();

  // Loop until the user closes the window
  while (glfwWindowShouldClose(window) == 0)
    {
       
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

