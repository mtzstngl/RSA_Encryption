#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include "rsa.h"
#include "rsaes-oaep.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private slots:
  void on_start_button_clicked();
  void on_generate_button_clicked();
  void on_selectEnc_comboBox_currentTextChanged(const QString &text);

private:
  Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
