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
  string output;

  if(ui->selectEnc_comboBox->currentText() == "Encrypt"){ //encrypt
    switch(ui->method_comboBox->currentIndex()){
      case 0: //RSA
        output = rsa_enc(ui->input_textedit->toPlainText().toStdString(),
                         ui->e_textedit->toPlainText().toStdString(),
                         ui->n_textedit->toPlainText().toStdString());
        ui->output_textedit->setText(QString::fromStdString(output));
        break;
      case 1: //RSA (completely)
        output = rsa_enc_completely(ui->input_textedit->toPlainText().toStdString(),
                         ui->e_textedit->toPlainText().toStdString(),
                         ui->n_textedit->toPlainText().toStdString());
        ui->output_textedit->setText(QString::fromStdString(output));
        break;
      case 2: //RSAES-OAEP
        //TODO: implement me
        break;
      case 3: //RSAES-PKCS1-V1_5
        //TODO: implement me
        break;
      default:
        ui->input_textedit->setText("You shouldn't be able to select this!!");
        break;
    }
  }else{ //decrypt
    switch(ui->method_comboBox->currentIndex()){
      case 0: //RSA
        output = rsa_dec(ui->input_textedit->toPlainText().toStdString(),
                         ui->d_textedit->toPlainText().toStdString(),
                         ui->n_textedit->toPlainText().toStdString());
        ui->output_textedit->setText(QString::fromStdString(output));
        break;
      case 1: //RSA (completely)
        output = rsa_dec_completely(ui->input_textedit->toPlainText().toStdString(),
                         ui->d_textedit->toPlainText().toStdString(),
                         ui->n_textedit->toPlainText().toStdString());
        ui->output_textedit->setText(QString::fromStdString(output));
        break;
      case 2: //RSAES-OAEP
        //TODO: implement me
        break;
      case 3: //RSAES-PKCS1-V1_5
        //TODO: implement me
        break;
      default:
        ui->input_textedit->setText("You shouldn't be able to select this!!");
        break;
    }
  }
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

void MainWindow::on_selectEnc_comboBox_currentTextChanged(const QString &text)
{
  if(text == "Encrypt"){
    ui->input_label->setText(QString("Plain Text"));
    ui->output_label->setText(QString("Encrypted"));
  }else if(text == "Decrypt"){
    ui->input_label->setText(QString("Encrypted"));
    ui->output_label->setText(QString("Plain Text"));
  }
}
