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
  w.setWindowTitle("Clause Resolution");
  w.show();
  return a.exec();
}
