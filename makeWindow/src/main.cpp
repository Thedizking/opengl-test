#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "headers/framebuffer.h"
#include "headers/processInput.h"

// Vertex Shader code
const char* vertexShaderSource = "#version 330 core\n"
            "layout (location = 0) in vec3 aPos;\n"
            "void main() {\n"
            "gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
            "}\0";


// Fragment Shader code
const char* fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "void main() {\n"
                                   "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                   "}\0";




int main (int argc, char *argv[]) {

  // Initialize GLFW and pick version
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


  unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);

  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);


  unsigned int framentShader = glCreateShader(GL_FRAGMENT_SHADER);

  glShaderSource(framentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(framentShader);

  int  success;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if(!success)
  {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
  }


  unsigned int shaderProgram = glCreateProgram();


  glAttachShader(vertexShader, shaderProgram);
  glAttachShader(framentShader, shaderProgram);
  glLinkProgram(shaderProgram);

  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

  if(!success) {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    std::cerr << "Failure to link shaders!";
  }

  glUseProgram(shaderProgram);

  glDeleteShader(vertexShader);
  glDeleteShader(framentShader);



  // Create Window
  GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);

  if (window == NULL) {
    std::cerr << "Failed to create window" << "\n";
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  // Initialize GLAD
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cerr << "Failed to initialize GLAD" << "\n";
    return -2;
  }

  glViewport(0, 0, 800, 600); // Lower left X, Lower left Y, Width, Height 
  
  // Render Loop
  while (!glfwWindowShouldClose(window)) {
    
    //Process Input before rendering
    processInput(window);

    // Render Here
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // Set State.
    glClear(GL_COLOR_BUFFER_BIT); // Use set state

    // Check and call events
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
