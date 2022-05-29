#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QStandardItemModel>
#include <QString>
#include <sstream>

#include "clause.h"
#include "implication.h"
#include "literal.h"
#include "predicate.h"
#include "unify.h"
#include "util.h"

inline void stdString2QString(const std::string &str, QString &qs) {
  qs = QString::fromLocal8Bit(QByteArray::fromRawData(str.c_str(), str.size()));
}

inline void QString2stdString(const QString &qs, std::string &str) {
  str = qs.toLocal8Bit().constData();
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  std::vector<QStandardItemModel *> models;

private slots:
  void on_actionAbout_the_Program_triggered();

  void on_actionAbout_Qt_triggered();

  void on_actionRun_triggered();

  void on_actionClear_triggered();

  void on_pushButtonRun_clicked();

  void on_pushButtonClear_clicked();

private:
  Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
