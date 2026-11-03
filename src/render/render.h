#pragma once 
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>

class Renderer{
public:
  Renderer(GLFWwindow* window, int w, int h);
    void setVertices(const std::vector<float>& points, int components);
    void drawPoints(std::vector<float> p, int components);
    void flushPoints();
    void setMVP(const glm::mat4& mvp);
    glm::mat4 computeMVP();
  
private:
  std::vector<float> points_;
  GLFWwindow* window_;
  GLuint vao_, vbo_;
  GLuint program_;
  GLint mvpLoc_;
  int components_, vertexCount_;
  int width_, height_;

  void createProgram(const std::string& vertPath, const std::string& fragPath);
};
