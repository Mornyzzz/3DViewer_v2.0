#ifndef CPP4_3D_VIWER_SRC_MODEL_H
#define CPP4_3D_VIWER_SRC_MODEL_H

#include <cmath>
#include <cstring>
#include <iostream>

#include "matrix.h"
namespace s21 {
class obj {
 public:
  ~obj();
  static obj* getInstance();
  void parser(const char* file_name);
  void affine_transform(double transform_data[3][3]);

  int get_vertices() { return vertices_count; }
  double get_vertices(int i, int j) { return vertices(i, j); }
  int get_vertices(int i) { return f_vertices[i]; }
  int get_vertices_rows() { return vertices.getrows(); }
  int get_vertices_cols() { return vertices.getcols(); }
  int get_polygons() { return polygons_count; }
  int get_polygons(int i, int j) { return polygons(i, j); }
  int get_polygons_rows() { return polygons.getrows(); }
  int get_polygons_cols() { return polygons.getcols(); }
  Matrix<int>* get_polygons_matrix() { return &polygons; }
  Matrix<double>* get_vertices_matrix() { return &vertices; }
  int* get_f_vertices() { return f_vertices; }
  double get_minX() { return minX; }
  double get_minY() { return minY; }
  double get_minZ() { return minZ; }
  double get_maxX() { return maxX; }
  double get_maxY() { return maxY; }
  double get_maxZ() { return maxZ; }
  void set_minX(double value) { minX = value; }
  void set_minY(double value) { minY = value; }
  void set_minZ(double value) { minZ = value; }
  void set_maxX(double value) { maxX = value; }
  void set_maxY(double value) { maxY = value; }
  void set_maxZ(double value) { maxZ = value; }

  int normalize_angle(int angle);

 private:
  static obj* instance;
  obj();
  Matrix<double> vertices;
  Matrix<int> polygons;
  int vertices_count;
  int polygons_count;
  int* f_vertices;  // массив длинною vertices_count для записи количиства
  // вершин поверхности
  double minX, minY, minZ;
  double maxX, maxY, maxZ;
};
}  // namespace s21

#endif  // CPP4_3D_VIWER_SRC_MODEL_H