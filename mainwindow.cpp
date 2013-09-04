#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
  ui->setupUi(this);
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::on_start_button_clicked()
{

}

void MainWindow::on_generate_button_clicked()
{
  mpz_class q, p, N, e, d;
  genrsa(mpz_class(ui->selection_comboBox->currentText().toInt()), q, p, N, e, d);
  ui->q_textedit->setText(QString::fromStdString(q.get_str()));
  ui->p_textedit->setText(QString::fromStdString(p.get_str()));
  ui->n_textedit->setText(QString::fromStdString(N.get_str()));
  ui->e_textedit->setText(QString::fromStdString(e.get_str()));
  ui->d_textedit->setText(QString::fromStdString(d.get_str()));
}
