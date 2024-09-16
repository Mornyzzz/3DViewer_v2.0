#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>

#include "qgifimage.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 signals:
  void signal_data(double transform_data[3][3]);
  void signal_settings(QMap<QString, QString> map);

 protected:
  void keyPressEvent(QKeyEvent *event);

 private slots:
  void on_transformButton_clicked();
  void on_applySettings_clicked();
  void on_saveImage_clicked();
  void on_recordScreencast_clicked();
  void saveGifFrame();

 public slots:
  void receiveInfo(int vertices_count, int polygons_count, QString f_name);

 private:
  Ui::MainWindow *ui;
  QSettings *set;
  QGifImage *gif;
  QImage *frame;
  QTimer *timer;
  QString gifSavePath;
  int time;
};

#endif  // MAINWINDOW_H
