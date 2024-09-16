#include "glFacade.h"

namespace s21 {
glFacade* glFacade::instance = nullptr;

glFacade* glFacade::getInstance() {
  if (instance == nullptr) {
    instance = new glFacade();
  }
  return instance;
}

void glFacade::set_color(QString color) {
  if (color == "Red")
    glColor3d(1, 0, 0);
  else if (color == "Green")
    glColor3d(0, 1, 0);
  else if (color == "Blue")
    glColor3d(0, 0, 1);
  else if (color == "Pink")
    glColor3d(1, 0, 1);
  else
    glColor3d(1, 1, 1);
}

void glFacade::set_background_color(QString background_color) {
  if (background_color == "Red")
    glClearColor(1, 0.0, 0.0, 0.0);
  else if (background_color == "Green")
    glClearColor(0, 1, 0.0, 0.0);
  else if (background_color == "Blue")
    glClearColor(0, 0.0, 1, 0.0);
  else
    glClearColor(0, 0.0, 0.0, 0.0);
}

void glFacade::projection_type(QString projection_type) {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (projection_type == "Central")
    glFrustum(-2, +2, -2, +2, 5.0, 15.0);
  else
    glOrtho(-2, +2, -2, +2, 1.0, 15.0);
}

void glFacade::set_position(int xRot, int yRot, int zRot) {
  glMatrixMode(GL_MODELVIEW);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  glTranslatef(0.0, 0.0, -7.0);
  glRotatef(xRot / 16.0, 1.0, 0.0, 0.0);
  glRotatef(yRot / 16.0, 0.0, 1.0, 0.0);
  glRotatef(zRot / 16.0, 0.0, 0.0, 1.0);
}

void glFacade::draw_axis() {
  glBegin(GL_LINE_LOOP);
  glVertex3d(2, 0, 0);
  glVertex3d(-2, 0, 0);
  glEnd();
  glBegin(GL_LINE_LOOP);
  glVertex3d(0, 2, 0);
  glVertex3d(0, -2, 0);
  glEnd();
  glBegin(GL_LINE_LOOP);
  glVertex3d(0, 0, 2);
  glVertex3d(0, 0, -2);
  glEnd();
}

void glFacade::draw_vertices() {
  Controller* controller = Controller::getInstance();
  for (int i = 0; i < controller->getPolygons(); i++) {
    for (int j = 0; j < controller->get_vertices(i); j++) {
      glBegin(GL_POINTS);
      glVertex3d(
          controller->get_vertices(controller->get_polygons(i, j) - 1, 0),
          controller->get_vertices(controller->get_polygons(i, j) - 1, 1),
          controller->get_vertices(controller->get_polygons(i, j) - 1, 2));
    }
    glEnd();
  }
}

void glFacade::draw_lines() {
  Controller* controller = Controller::getInstance();
  for (int i = 0; i < controller->getPolygons(); i++) {
    glBegin(GL_LINE_LOOP);
    for (int j = 0; j < controller->get_vertices(i); j++) {
      glVertex3d(
          controller->get_vertices(controller->get_polygons(i, j) - 1, 0),
          controller->get_vertices(controller->get_polygons(i, j) - 1, 1),
          controller->get_vertices(controller->get_polygons(i, j) - 1, 2));
    }
    glEnd();
  }
}

void glFacade::blending_mode(bool k) {
  if (k) {
    glEnable(GL_BLEND);
  } else {
    glDisable(GL_BLEND);
  }
}

void glFacade::point_draw_mode(QString vertex_display) {
  if (vertex_display == "Square")
    glDisable(GL_POINT_SMOOTH);
  else {
    glEnable(GL_POINT_SMOOTH);
  }
}

void glFacade::point_size(int vertex_size) {
  glEnable(GL_PROGRAM_POINT_SIZE);
  glPointSize(vertex_size);
}

void glFacade::line_draw_mode(QString line_type) {
  if (line_type == "Dashed") {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x00FF);
  } else {
    glDisable(GL_LINE_STIPPLE);
  }
}

void glFacade::line_size(int line_width) { glLineWidth(line_width); }
}  // namespace s21
