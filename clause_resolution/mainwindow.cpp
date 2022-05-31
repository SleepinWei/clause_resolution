#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_actionAbout_the_Program_triggered() {
  QMessageBox::about(
      this, "About the Program",
      "Resolution principle is the basic theory of general logic reasoning "
      "algorithm, that is, agents can judge whether a conclusion is true or "
      "not by a series of given clause sets and combining two clauses. This "
      "principle can be used in computer efficiently, and it is a better "
      "reasoning technology that can be realized in computer. It makes great "
      "progress in automatic theorem proving.\n\nIn this program, the problem "
      "of solving the case is first transformed into clauses and the known "
      "facts, processes and objectives are determined. Then, the antecedents "
      "and consequent of each implication (process) are separated and deduced "
      "through forward links to obtain the results to be proved.\n\nYou can "
      "enter the Knowledge Base and Query to be resolved in the program, and "
      "then click Run to see the resolution process and results of the output. "
      "Click Clear to clear the input and output.\n\nEnjoy!");
}

void MainWindow::on_actionAbout_Qt_triggered() {
  QMessageBox::aboutQt(this, "About Qt");
}

void MainWindow::on_actionRun_triggered() { on_pushButtonRun_clicked(); }

void MainWindow::on_actionClear_triggered() { on_pushButtonClear_clicked(); }

void MainWindow::on_pushButtonRun_clicked() {
  ui->lineEdit->clear();
  ui->lineEdit->setReadOnly(true);
  for (const auto m : models) {
    m->clear();
  }
  std::vector<QStandardItemModel *>().swap(models); // clear the vector

  KB base;

  std::string str;

  QString2stdString(ui->plainTextEdit->toPlainText(), str);
  std::stringstream ss(str);

  while (!ss.eof()) {
    std::string s;
    ss >> s;
    base.addFromString(s);
  }

  QString2stdString(ui->lineEdit_2->text(), str);
  Literal l;
  int index(0);
  l.fromString(str, index);

  auto r = base.entails(l);

  {
    auto vec = base.getImplications();
    auto model = new QStandardItemModel;
    model->setColumnCount(1);
    model->setRowCount(vec.size());
    model->setHeaderData(0, Qt::Horizontal, "Implications");
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setModel(model);
    ui->tableView->horizontalHeader()->setVisible(false);

    for (size_t i = 0; i < vec.size(); i++) {
      QString s;
      stdString2QString(vec[i], s);
      model->setItem(i, new QStandardItem(s));
      model->setHeaderData(i, Qt::Vertical, i);
    }

    ui->tableView->resizeColumnsToContents();
    models.push_back(model);
  }

  {
    auto vec = base.getFacts();
    auto model = new QStandardItemModel;
    model->setColumnCount(1);
    model->setRowCount(vec.size());
    model->setHeaderData(0, Qt::Horizontal, "Facts");
    ui->tableView_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView_2->setModel(model);
    ui->tableView_2->horizontalHeader()->setVisible(false);

    for (size_t i = 0; i < vec.size(); i++) {
      QString s;
      stdString2QString(vec[i], s);
      model->setItem(i, new QStandardItem(s));
      model->setHeaderData(i, Qt::Vertical, i);
    }

    ui->tableView_2->resizeColumnsToContents();
    models.push_back(model);
  }

  {
    auto vec = base.getProcess();
    auto model = new QStandardItemModel;
    model->setColumnCount(1);
    model->setRowCount(vec.size());
    model->setHeaderData(0, Qt::Horizontal, "Process");
    ui->tableView_3->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView_3->setModel(model);
    ui->tableView_3->horizontalHeader()->setVisible(false);

    for (size_t i = 0; i < vec.size(); i++) {
      QString s;
      stdString2QString(vec[i], s);
      model->setItem(i, new QStandardItem(s));
      model->setHeaderData(i, Qt::Vertical, i);
    }

    ui->tableView_3->resizeColumnsToContents();
    models.push_back(model);
  }

  ui->lineEdit->setReadOnly(true);
  ui->lineEdit->clear();
  ui->lineEdit->insert(r ? "True" : "False");
}

void MainWindow::on_pushButtonClear_clicked() {
  ui->plainTextEdit->clear();
  ui->lineEdit_2->clear();
  ui->lineEdit->clear();
  for (const auto m : models) {
    m->clear();
  }
  std::vector<QStandardItemModel *>().swap(models); // clear the vector
}
