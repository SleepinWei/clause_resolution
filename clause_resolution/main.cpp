//#include "mainwindow.h"

//#include <QApplication>

// int main(int argc, char *argv[]) {
//   QApplication a(argc, argv);
//   MainWindow w;
//   w.show();
//   return a.exec();
// }

#include <QApplication>
#include <QStyleFactory>
#include <QTextCodec>

#include "mainwindow.h"

int main(int argc, char *argv[]) {
  QTextCodec *codec = QTextCodec::codecForName("UTF-8");
  QTextCodec::setCodecForLocale(codec);

  QApplication a(argc, argv);
  a.setFont(QFont("Arial, Microsoft YaHei", 10));
  a.setStyle(QStyleFactory::create("Fusion"));
  MainWindow w;
  w.show();
  return a.exec();
}
