#ifndef CPP4_3DVIEWER_V2_0_11_CONTROLLER_H
#define CPP4_3DVIEWER_V2_0_11_CONTROLLER_H

#include "../model/obj.h"

namespace s21 {
class Controller {
 private:
  static Controller *instance;
  Controller();
  obj *object;

 public:
  void parser(const char *file_name);
  static Controller *getInstance();
  int getVertices();
  int getPolygons();
  void affine_transform(double transform_data[3][3]);
  double get_vertices(int i, int j);
  int get_vertices(int i);
  int get_polygons(int i, int j);
  int normalize_angle(int angle);
};

Controller *getController();
}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_11_CONTROLLER_H
