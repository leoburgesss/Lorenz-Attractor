#include "render/render.h"

#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp> 
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <vector>

void Renderer::setVertices(const std::vector<float>& points, int components){
  components_ = components;
  vertexCount_ = static_cast<int>(points.size()) / components;

  glBindVertexArray(vao_);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_);

  glBufferData(
      GL_ARRAY_BUFFER,
      points.size() * sizeof(float),
      points.data(),
      GL_STATIC_DRAW
      );

  glVertexAttribPointer(
      0,
      components,
      GL_FLOAT,
      GL_FALSE,
      components * sizeof(float),
      (void*)0
      );
  glEnableVertexAttribArray(0);
}

static GLuint compileShader(GLenum type, const std::string& src){
  GLuint s = glCreateShader(type);
  const char* c = src.c_str();
  glShaderSource(s, 1, &c, nullptr);
  glCompileShader(s);

  GLint ok = 0; 
  glGetShaderiv(s, GL_COMPILE_STATUS, &ok);
  if (!ok) {
    char log[1024];
    glGetShaderInfoLog(s, sizeof(log), nullptr, log);
    std::cerr << "Shader compile failed:\n" << log << "\n";
    }
  return s;
}

void Renderer::createProgram(const std::string& vertPath, const std::string& fragPath){
  auto readFile = [](const std::string& path){
    std::ifstream f(path);
    std::stringstream ss;
    ss << f.rdbuf();
    return ss.str();
  };

  GLuint vs = compileShader(GL_VERTEX_SHADER, readFile(vertPath));
  GLuint fs = compileShader(GL_FRAGMENT_SHADER, readFile(fragPath));

  program_ = glCreateProgram();
  glAttachShader(program_, vs);
  glAttachShader(program_, fs);
  glLinkProgram(program_);

  glDeleteShader(vs); 
  glDeleteShader(fs);
}

glm::mat4 Renderer::computeMVP(){
  int fw, fh;
  glfwGetFramebufferSize(window_, &fw, &fh);
  float aspect = static_cast<float>(fw) / static_cast<float>(fh);
  glm::mat4 proj = glm::perspective(glm::radians(50.0f), aspect, 0.1f, 100.0f);
  
  float t = glfwGetTime();

  glm::mat4 view = glm::lookAt(
      glm::vec3(60.0f*std::sin(t/8), 70.0f, 60.0f*std::cos(t/8)),
      glm::vec3(0.0f,30.0f,0.0f),
      glm::vec3(0.0f,1.0f,0.0f)
      );

  glm::mat4 model = glm::rotate(glm::mat4(1.0f),
                              glm::radians(-90.0f),
                              glm::vec3(1, 0, 0));

  glm::mat4 mvp = proj * view * model; 
  return mvp;
}

void Renderer::drawPoints(std::vector<float> p, int components){
  for(float point: p){points_.push_back(point);}
  
  setVertices(p, components);
  glUseProgram(program_);
  setMVP(computeMVP());
  glBindVertexArray(vao_);
  glDrawArrays(GL_LINE_LOOP, 0, vertexCount_);
  flushPoints();
}


void Renderer::setMVP(const glm::mat4& mvp) {
    glUseProgram(program_);
    glUniformMatrix4fv(mvpLoc_, 1, GL_FALSE, glm::value_ptr(mvp));
}

void Renderer::flushPoints(){
  points_ = {};
}

Renderer::Renderer(GLFWwindow* window, int w, int h): window_(window), width_(w), height_(h) {
    glGenVertexArrays(1, &vao_);
    glGenBuffers(1, &vbo_);
    createProgram("shaders/point.vert", "shaders/point.frag");
    mvpLoc_ = glGetUniformLocation(program_, "uMVP");
}
