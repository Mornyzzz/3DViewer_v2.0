#include "controller.h"
namespace s21 {
Controller* Controller::instance = nullptr;

Controller::Controller() { object = obj::getInstance(); }

Controller* Controller::getInstance() {
  if (instance == nullptr) {
    instance = new Controller();
  }
  return instance;
}

void Controller::parser(const char* file_name) { object->parser(file_name); }
int Controller::getVertices() { return object->get_vertices(); }
int Controller::getPolygons() { return object->get_polygons(); }
void Controller::affine_transform(double transform_data[3][3]) {
  object->affine_transform(transform_data);
}
double Controller::get_vertices(int i, int j) {
  return object->get_vertices(i, j);
}
int Controller::get_vertices(int i) { return object->get_vertices(i); }

int Controller::get_polygons(int i, int j) {
  return object->get_polygons(i, j);
}

int Controller::normalize_angle(int angle) {
  return object->normalize_angle(angle);
}
}  // namespace s21