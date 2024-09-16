#ifndef CPP4_GLFACADE_H
#define CPP4_GLFACADE_H

#include <QOpenGLWidget>
#include <QSettings>

#include "../../controller/controller.h"

namespace s21 {
class glFacade {
 public:
  static glFacade* getInstance();
  void set_color(QString color);
  void set_background_color(QString background_color);
  void projection_type(QString projection_type);
  void set_position(int xRot, int yRot, int zRot);
  void draw_axis();
  void draw_vertices();
  void draw_lines();
  void blending_mode(bool k);
  void point_draw_mode(QString vertex_display);
  void point_size(int vertex_size);
  void line_draw_mode(QString line_type);
  void line_size(int line_width);

 private:
  static glFacade* instance;
  glFacade(){};
};
}  // namespace s21

#endif  // CPP4_GLFACADE_H
