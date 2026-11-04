#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <vector>
#include <cmath>

#include "render/render.h"
#include "functions/functions.h"

constexpr int screenWidth = 1080;
constexpr int screenHeight = 1080;

int main(){
//---------------------------------------------------------------------------------------------------------------------------------
// INIT
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
  glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "Lorenz", nullptr, nullptr);

  glfwMakeContextCurrent(window);
  glfwSwapInterval(0);

  glewExperimental = GL_TRUE;
  GLenum err = glewInit();
  if (err != GLEW_OK){std::cerr << "Failed to init Glew\n"; return -1;}
  glGetError();

//---------------------------------------------------------------------------------------------------------------------------------- 
//MAIN
Renderer r = Renderer(window, screenWidth, screenHeight);

  while (!glfwWindowShouldClose(window)){
    double now = glfwGetTime();
    
    glClearColor(0.0705f, 0.2196f, 0.2196f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    std::vector<float> p = functions::lorenzAttractor(20000, 0.005, 10.0, 28.0, 8.0/3.0, {0.0f, 1.0f, 1.05f});

    r.drawPoints(p, 3);
  
    glfwSwapBuffers(window);
    glfwPollEvents();
}

glfwDestroyWindow(window);
glfwTerminate();
return 0;
}
