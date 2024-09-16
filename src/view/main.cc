#include <QApplication>

#include "mainwindow.h"

// #pragma comment( lib, "OpenGL32.lib" )

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
#ifdef __linux__
  setlocale(LC_NUMERIC, "C");
#endif
  MainWindow w;
  w.show();
  return a.exec();
}
