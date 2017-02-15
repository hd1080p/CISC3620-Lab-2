// Local Headers
#include "glitter.hpp"

// System Headers
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Standard Headers
#include <cstdio>
#include <cstdlib>

const GLchar* vertexShaderSource =
"#version 330 core\n"

"layout (location = 0) in vec3 position;"
"layout (location = 1) in vec3 color;"

"out vec3 vertexColor;"

"void main() {"
"gl_Position = vec4(position.x, position.y, position.z, 1.0);"
"vertexColor = color;"
"}\0"
;

const GLchar* fragmentShaderSource =
"#version 330 core\n"

"in vec3 vertexColor;"

"out vec4 color;\n"

"void main() {"
"color = vec4(vertexColor, 1.0f);"
"}\0";

GLfloat vertices[] = {
  /*Drawing a House
  //First Triangle
  //x     y     z     r     g     b    */
   0.5f, -0.5f, 0.0f, 0.2f, 0.5f, 0.8f,
  -0.5f, -0.5f, 0.0f, 0.2f, 0.5f, 0.8f,
  -0.5f,  0.5f, 0.0f, 0.2f, 0.5f, 0.8f,

  //Second Triangle
   0.5f, -0.5f, 0.0f, 0.5f, 0.2f, 0.3f,
   0.5f,  0.5f, 0.0f, 0.5f, 0.2f, 0.3f,
  -0.5f,  0.5f, 0.0f, 0.5f, 0.2f, 0.3f,
  
  //Third Triangle
   -0.5f, 0.5f, 0.0f, 0.7f, 0.8f, 0.4f,
    0.5f, 0.5f, 0.0f, 0.7f, 0.8f, 0.4f,
    0.0f, 1.0f, 0.0f, 0.7f, 0.8f, 0.4f
};


int main(int argc, char * argv[]) {
  
  // Load GLFW and Create a Window
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
  auto mWindow = glfwCreateWindow(600, 800, "OpenGL", nullptr, nullptr);
  
  // Check for Valid Context
  if (mWindow == nullptr) {
    fprintf(stderr, "Failed to Create OpenGL Context");
    return EXIT_FAILURE;
  }
  
  // Create Context and Load OpenGL Functions
  glfwMakeContextCurrent(mWindow);
  gladLoadGL();
  fprintf(stderr, "OpenGL %s\n", glGetString(GL_VERSION));
  
  // vertex array object stores vertex attribute information
  // stores subsequent calls to glVertexAttribPointer, glEnableVertexAttribArray, vbos associated
  // with vertex attributes
  GLuint VAO;
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);
  
  // vertex buffer object stores large number of vertices on GPU
  GLuint VBO; glGenBuffers(1, &VBO);    // generate buffer object and save its id
  glBindBuffer(GL_ARRAY_BUFFER, VBO);   // this is going to be your GL_ARRAY_BUFFER
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);  // copy vertex data into buffer
  
  // this is the first (0th) vertex attribute, has 3 components, is of type GL_FLOAT, should
  // not be normalized, each one is 3 floats apart, start at beginning of buffer (offset is 0)
  // this vertex attribute takes its data from the VBO currently bound to GL_ARRAY_BUFFER
  glVertexAttribPointer(0, 3,  GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
  glEnableVertexAttribArray(0);

  //Color attribute
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3* sizeof(GLfloat)));
  glEnableVertexAttribArray(1);
  
  // unbind GL_ARRAY_BUFFER and vertex array -- state has been applied
  // unbind OpenGL objects when finished configuring them so don't mess them up
  glBindBuffer(GL_ARRAY_BUFFER, 0); 
  glBindVertexArray(0);
  
  
  // shaders must be dynamically compiled at runtime
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);
  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);
  
  // Link shaders
  GLuint shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);
  
  // Clean up: shader objects no longer needed after they are linked
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
  
  // Rendering Loop
  while (glfwWindowShouldClose(mWindow) == false) {
    if (glfwGetKey(mWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
      glfwSetWindowShouldClose(mWindow, true);
    
    // Background Fill Color
    glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Draw our first triangle
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);     // bind the VAO we configured before
    glDrawArrays(GL_TRIANGLES, 0, 12);   // draw the objects
    glBindVertexArray(0);     // unbind the VAO

    
    glfwSwapBuffers(mWindow);   // flip buffers and draw
    glfwPollEvents();           // check if any events are triggered, call corresponding callbacks
  }
  
  // Properly de-allocate all resources once they've outlived their purpose
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glfwTerminate();
  
  return EXIT_SUCCESS;
}
