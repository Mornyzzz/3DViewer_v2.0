#include "obj.h"

namespace s21 {
class ObjParsingStrategy {
 public:
  virtual void update() = 0;
  virtual void readFile(const char* file_name) = 0;

 protected:
  char line[200];
  obj* object;
  FILE* file;
};

class MinMaxStrategy : public ObjParsingStrategy {
 public:
  void update() override {
    object = obj::getInstance();
    strcpy(line, "");
    x = 0.0, y = 0.0, z = 0.0;
  }
  void readFile(const char* file_name) override {
    update();
    file = std::fopen(file_name, "r");
    while (fgets(line, 200, file)) {
      if (line[0] == 'v' && line[1] == ' ') {
        std::sscanf(line, "v %lf %lf %lf", &x, &y, &z);
        if (x < object->get_minX()) object->set_minX(x);
        if (y < object->get_minY()) object->set_minY(y);
        if (z < object->get_minZ()) object->set_minZ(z);

        if (x > object->get_maxX()) object->set_maxX(x);
        if (y > object->get_maxY()) object->set_maxY(y);
        if (z > object->get_maxZ()) object->set_maxZ(z);
      }
    }
    fclose(file);
  }

 private:
  double x, y, z;
};

class PolygonInsertionStrategy : public ObjParsingStrategy {
 public:
  void update() override {
    object = obj::getInstance();
    polygons = object->get_polygons_matrix();
    (*polygons)(object->get_polygons() - 1, 0);
    strcpy(line, "");
  }
  void readFile(const char* file_name) override {
    update();
    file = std::fopen(file_name, "r");
    for (int i = 0; fgets(line, 200, file);) {
      int polygons_counts = 0;
      if (line[0] == 'f' && line[1] == ' ') {
        char* tmp_line = std::strtok(line, "f ");
        while (tmp_line != nullptr && std::strncmp(tmp_line, "\n", 2) &&
               std::atoi(tmp_line) > 0) {
          polygons->insert(i, polygons_counts, std::atoi(tmp_line));
          tmp_line = std::strtok(nullptr, " ");
          polygons_counts++;
        }
        i++;
      }
    }
    fclose(file);
  }

 private:
  Matrix<int>* polygons;
};

class VerticesInsertionStrategy : public ObjParsingStrategy {
 public:
  void update() override {
    object = obj::getInstance();
    vertices = object->get_vertices_matrix();
    (*vertices)(object->get_vertices() - 1, 2);

    strcpy(line, "");
    x = 0.0, y = 0.0, z = 0.0;
    x_rate = object->get_maxX() - object->get_minX();
    y_rate = object->get_maxY() - object->get_minY();
    z_rate = object->get_maxZ() - object->get_minZ();
    zoom_scale = 3.0 / std::fmax(std::fmax(x_rate, y_rate), z_rate);
    x_center = object->get_minX() + x_rate / 2.0;
    y_center = object->get_minY() + y_rate / 2.0;
    z_center = object->get_minZ() + z_rate / 2.0;
    i = 0;
  }
  void readFile(const char* file_name) override {
    update();
    file = std::fopen(file_name, "r");
    while (fgets(line, 200, file)) {
      if (line[0] == 'v' && line[1] == ' ') {
        std::sscanf(line, "v %lf %lf %lf", &x, &y, &z);
        vertices->insert(i, 0, (x - x_center) * zoom_scale);
        vertices->insert(i, 1, (y - y_center) * zoom_scale);
        vertices->insert(i, 2, (z - z_center) * zoom_scale);
        i++;
      }
    }
    fclose(file);
  }

 private:
  double x, y, z, x_rate, y_rate, z_rate, x_center, y_center, z_center,
      zoom_scale;
  Matrix<double>* vertices;
  int i;
};

class FVerticesCountStrategy : public ObjParsingStrategy {
 public:
  void update() override {
    object = obj::getInstance();
    strcpy(line, "");
    tmp_line = nullptr;
    f_vertices = object->get_f_vertices();
  }
  void readFile(const char* file_name) override {
    update();
    file = fopen(file_name, "r");
    for (int i = 0; fgets(line, 200, file);) {
      if (line[0] == 'f' && line[1] == ' ') {
        f_vertices[i] = 0;
        tmp_line = std::strtok(line, "f ");
        while (tmp_line != nullptr && std::strncmp(tmp_line, "\n", 2) &&
               std::atoi(tmp_line) > 0) {
          tmp_line = std::strtok(nullptr, " ");
          f_vertices[i] += 1;
        }
        i++;
      }
    }
    fclose(file);
  }

 private:
  char* tmp_line;
  int* f_vertices;
};

obj* obj::instance = nullptr;

obj::obj() : vertices_count(0), polygons_count(0) {
  f_vertices = nullptr;
  minX = 0;
  minY = 0;
  minZ = 0;
  maxX = 0;
  maxY = 0;
  maxZ = 0;
}

obj* obj::getInstance() {
  if (instance == nullptr) {
    instance = new obj();
  }
  return instance;
}

void obj::parser(const char* file_name) {
  MinMaxStrategy minMaxStrategy;
  PolygonInsertionStrategy polygonStrategy;
  VerticesInsertionStrategy verticesStrategy;
  FVerticesCountStrategy fVerticesCountStrategy;
  FILE* file = std::fopen(file_name, "r");
  if (!std::strstr(file_name, ".obj"))
    throw std::invalid_argument("FILE EXTENSION ERROR");
  if (!file) throw std::invalid_argument("READ FILE ERROR");
  char line[200];
  vertices_count = 0;
  polygons_count = 0;
  minX = __DBL_MAX__;
  minY = __DBL_MAX__;
  minZ = __DBL_MAX__;
  maxX = -__DBL_MAX__;
  maxY = -__DBL_MAX__;
  maxZ = -__DBL_MAX__;
  while (fgets(line, 200, file)) {
    if (line[0] == 'v' && line[1] == ' ') {
      vertices_count++;
    }
    if (line[0] == 'f' && line[1] == ' ') {
      polygons_count++;
    }
  }
  f_vertices = new int[polygons_count]{};
  fclose(file);

  fVerticesCountStrategy.readFile(file_name);
  minMaxStrategy.readFile(file_name);
  verticesStrategy.readFile(file_name);
  polygonStrategy.readFile(file_name);
}

obj::~obj() {
  instance = nullptr;
  vertices_count = 0;
  polygons_count = 0;
  delete[] f_vertices;
  minX = 0;
  minY = 0;
  minZ = 0;
  maxX = 0;
  maxY = 0;
  maxZ = 0;
}

void obj::affine_transform(double transform_data[3][3]) {
  vertices.scale(vertices_count, transform_data[2][0]);
  vertices.translate(vertices_count, transform_data[0][0], transform_data[0][1],
                     transform_data[0][2]);
  vertices.ox_rotate(vertices_count, transform_data[1][0]);
  vertices.oy_rotate(vertices_count, transform_data[1][1]);
  vertices.oz_rotate(vertices_count, transform_data[1][2]);
}

int obj::normalize_angle(int angle) {
  while (angle < 0) angle += 360 * 16;
  while (angle > 360) angle -= 360 * 16;
  return angle;
}
}  // namespace s21
