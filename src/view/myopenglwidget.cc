#include "myopenglwidget.h"
//#include "mainwindow.h"

#include <QOpenGLWidget>
#include <QSettings>
#include <QtWidgets>

MyOpenGLWidget::MyOpenGLWidget(QWidget *parent) : QOpenGLWidget{parent} {
  controller = s21::Controller::getInstance();
  gl_facade = s21::glFacade::getInstance();
  axis_check = 0;
  set = new QSettings("launch_settings.init", QSettings::IniFormat);
}

void MyOpenGLWidget::on_SelectFileButton_clicked() {
  QString f_name;
  QString filename =
      QFileDialog::getOpenFileName(this, "Choose File", NULL, "OBJ (*.obj)");
  if (!filename.isNull()) {
    QByteArray ba = filename.toLocal8Bit();
    const char *filename_c = ba.data();
    controller->parser(filename_c);
    f_name = filename.split('/').last();
    emit send_info(controller->getVertices(), controller->getPolygons(),
                   f_name);
    update();
  }
}

void MyOpenGLWidget::on_checkAxes_clicked() {
  if (axis_check != 0)
    axis_check += 1;
  else
    axis_check -= 1;
  update();
}

void MyOpenGLWidget::on_applySettingsButton_clicked(
    QMap<QString, QString> map) {
  projection_type = map["projection"];
  line_type = map["line_type"];
  line_color = map["line_color"];
  line_width = map["line_width"].toInt();
  vertex_color = map["vertex_color"];
  vertex_size = map["vertex_size"].toInt();
  vertex_display = map["vertex_display"];
  background_color = map["background_color"];
  set->setValue("projection", map["projection"]);
  set->setValue("lineType", map["line_type"]);
  set->setValue("lineColor", map["line_color"]);
  set->setValue("lineWidth", map["line_width"]);
  set->setValue("vertexColor", map["vertex_color"]);
  set->setValue("vertexSize", map["vertex_size"]);
  set->setValue("vertexDisplay", map["vertex_display"]);
  set->setValue("backgroundColor", map["background_color"]);
  update();
}

void MyOpenGLWidget::mousePressEvent(QMouseEvent *event) {
  lastPos = event->pos();
}

void MyOpenGLWidget::mouseMoveEvent(QMouseEvent *event) {
  int dx = event->position().x() - lastPos.x();
  int dy = event->position().y() - lastPos.y();

  if (event->buttons() & Qt::LeftButton) {
    xRot = controller->normalize_angle(xRot + 8 * dy);
    yRot = controller->normalize_angle(yRot + 8 * dx);
  } else if (event->buttons() & Qt::RightButton) {
    xRot = controller->normalize_angle(xRot + 8 * dy);
    zRot = controller->normalize_angle(zRot + 8 * dx);
  }
  lastPos = event->pos();
  update();
}

void MyOpenGLWidget::on_transformButton_clicked2(double transform_data[3][3]) {
  controller->affine_transform(transform_data);
  update();
}

void MyOpenGLWidget::initializeGL() {}

void MyOpenGLWidget::paintGL() {
  background_color = set->value("backgroundColor").toString();
  projection_type = set->value("projection").toString();
  vertex_display = set->value("vertexDisplay").toString();

  gl_facade->set_background_color(background_color);
  gl_facade->projection_type(projection_type);
  gl_facade->set_position(xRot, yRot, zRot);

  drawLines();
  if (vertex_display != "None") drawPoints();
  if (axis_check != 0) drawAxis();
}

void MyOpenGLWidget::drawLines() {
  line_color = set->value("lineColor").toString();
  line_type = set->value("lineType").toString();
  line_width = set->value("lineWidth").toInt();

  gl_facade->set_color(line_color);
  gl_facade->line_draw_mode(line_type);
  gl_facade->line_size(line_width);
  gl_facade->draw_lines();
}

void MyOpenGLWidget::drawPoints() {
  vertex_color = set->value("vertexColor").toString();
  vertex_size = set->value("vertexSize").toInt();

  gl_facade->set_color(vertex_color);
  gl_facade->blending_mode(true);
  gl_facade->point_draw_mode(vertex_display);
  gl_facade->point_size(vertex_size);
  gl_facade->draw_vertices();
}

void MyOpenGLWidget::drawAxis() {
  QString color = "Pink";
  gl_facade->set_color(color);
  gl_facade->draw_axis();
}
