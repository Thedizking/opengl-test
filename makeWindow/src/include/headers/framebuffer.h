#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}
#endif
