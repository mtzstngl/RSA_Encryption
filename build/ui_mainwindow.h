/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    QGroupBox *generation_groupBox;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *selection_horizontalLayout;
    QLabel *selection_label;
    QComboBox *selection_comboBox;
    QPushButton *generate_button;
    QVBoxLayout *q_verticalLayout;
    QLabel *q_label;
    QTextEdit *q_textedit;
    QVBoxLayout *p_verticalLayout;
    QLabel *p_label;
    QTextEdit *p_textedit;
    QVBoxLayout *n_verticalLayout;
    QLabel *n_label;
    QTextEdit *n_textedit;
    QVBoxLayout *e_verticalLayout;
    QLabel *e_label;
    QTextEdit *e_textedit;
    QVBoxLayout *d_verticalLayout;
    QLabel *d_label;
    QTextEdit *d_textedit;
    QGroupBox *encDec_groupBox;
    QGridLayout *gridLayout_3;
    QVBoxLayout *encDecBox_verticalLayout;
    QHBoxLayout *method_horizontalLayout;
    QLabel *method_label;
    QComboBox *method_comboBox;
    QHBoxLayout *selectEnc_horizontalLayout;
    QComboBox *selectEnc_comboBox;
    QPushButton *start_button;
    QVBoxLayout *input_verticalLayout;
    QLabel *input_label;
    QTextEdit *input_textedit;
    QVBoxLayout *output_verticalLayout;
    QLabel *output_label;
    QTextEdit *output_textedit;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(879, 737);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        generation_groupBox = new QGroupBox(centralWidget);
        generation_groupBox->setObjectName(QStringLiteral("generation_groupBox"));
        gridLayout = new QGridLayout(generation_groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        selection_horizontalLayout = new QHBoxLayout();
        selection_horizontalLayout->setSpacing(6);
        selection_horizontalLayout->setObjectName(QStringLiteral("selection_horizontalLayout"));
        selection_label = new QLabel(generation_groupBox);
        selection_label->setObjectName(QStringLiteral("selection_label"));

        selection_horizontalLayout->addWidget(selection_label);

        selection_comboBox = new QComboBox(generation_groupBox);
        selection_comboBox->setObjectName(QStringLiteral("selection_comboBox"));

        selection_horizontalLayout->addWidget(selection_comboBox);


        verticalLayout_3->addLayout(selection_horizontalLayout);

        generate_button = new QPushButton(generation_groupBox);
        generate_button->setObjectName(QStringLiteral("generate_button"));

        verticalLayout_3->addWidget(generate_button);

        q_verticalLayout = new QVBoxLayout();
        q_verticalLayout->setSpacing(6);
        q_verticalLayout->setObjectName(QStringLiteral("q_verticalLayout"));
        q_label = new QLabel(generation_groupBox);
        q_label->setObjectName(QStringLiteral("q_label"));

        q_verticalLayout->addWidget(q_label);

        q_textedit = new QTextEdit(generation_groupBox);
        q_textedit->setObjectName(QStringLiteral("q_textedit"));

        q_verticalLayout->addWidget(q_textedit);


        verticalLayout_3->addLayout(q_verticalLayout);

        p_verticalLayout = new QVBoxLayout();
        p_verticalLayout->setSpacing(6);
        p_verticalLayout->setObjectName(QStringLiteral("p_verticalLayout"));
        p_label = new QLabel(generation_groupBox);
        p_label->setObjectName(QStringLiteral("p_label"));

        p_verticalLayout->addWidget(p_label);

        p_textedit = new QTextEdit(generation_groupBox);
        p_textedit->setObjectName(QStringLiteral("p_textedit"));

        p_verticalLayout->addWidget(p_textedit);


        verticalLayout_3->addLayout(p_verticalLayout);

        n_verticalLayout = new QVBoxLayout();
        n_verticalLayout->setSpacing(6);
        n_verticalLayout->setObjectName(QStringLiteral("n_verticalLayout"));
        n_label = new QLabel(generation_groupBox);
        n_label->setObjectName(QStringLiteral("n_label"));

        n_verticalLayout->addWidget(n_label);

        n_textedit = new QTextEdit(generation_groupBox);
        n_textedit->setObjectName(QStringLiteral("n_textedit"));

        n_verticalLayout->addWidget(n_textedit);


        verticalLayout_3->addLayout(n_verticalLayout);

        e_verticalLayout = new QVBoxLayout();
        e_verticalLayout->setSpacing(6);
        e_verticalLayout->setObjectName(QStringLiteral("e_verticalLayout"));
        e_label = new QLabel(generation_groupBox);
        e_label->setObjectName(QStringLiteral("e_label"));

        e_verticalLayout->addWidget(e_label);

        e_textedit = new QTextEdit(generation_groupBox);
        e_textedit->setObjectName(QStringLiteral("e_textedit"));

        e_verticalLayout->addWidget(e_textedit);


        verticalLayout_3->addLayout(e_verticalLayout);

        d_verticalLayout = new QVBoxLayout();
        d_verticalLayout->setSpacing(6);
        d_verticalLayout->setObjectName(QStringLiteral("d_verticalLayout"));
        d_label = new QLabel(generation_groupBox);
        d_label->setObjectName(QStringLiteral("d_label"));

        d_verticalLayout->addWidget(d_label);

        d_textedit = new QTextEdit(generation_groupBox);
        d_textedit->setObjectName(QStringLiteral("d_textedit"));

        d_verticalLayout->addWidget(d_textedit);


        verticalLayout_3->addLayout(d_verticalLayout);


        gridLayout->addLayout(verticalLayout_3, 0, 0, 1, 1);


        gridLayout_2->addWidget(generation_groupBox, 0, 0, 1, 1);

        encDec_groupBox = new QGroupBox(centralWidget);
        encDec_groupBox->setObjectName(QStringLiteral("encDec_groupBox"));
        gridLayout_3 = new QGridLayout(encDec_groupBox);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        encDecBox_verticalLayout = new QVBoxLayout();
        encDecBox_verticalLayout->setSpacing(6);
        encDecBox_verticalLayout->setObjectName(QStringLiteral("encDecBox_verticalLayout"));
        method_horizontalLayout = new QHBoxLayout();
        method_horizontalLayout->setSpacing(6);
        method_horizontalLayout->setObjectName(QStringLiteral("method_horizontalLayout"));
        method_label = new QLabel(encDec_groupBox);
        method_label->setObjectName(QStringLiteral("method_label"));

        method_horizontalLayout->addWidget(method_label);

        method_comboBox = new QComboBox(encDec_groupBox);
        method_comboBox->setObjectName(QStringLiteral("method_comboBox"));

        method_horizontalLayout->addWidget(method_comboBox);


        encDecBox_verticalLayout->addLayout(method_horizontalLayout);

        selectEnc_horizontalLayout = new QHBoxLayout();
        selectEnc_horizontalLayout->setSpacing(6);
        selectEnc_horizontalLayout->setObjectName(QStringLiteral("selectEnc_horizontalLayout"));
        selectEnc_comboBox = new QComboBox(encDec_groupBox);
        selectEnc_comboBox->setObjectName(QStringLiteral("selectEnc_comboBox"));

        selectEnc_horizontalLayout->addWidget(selectEnc_comboBox);

        start_button = new QPushButton(encDec_groupBox);
        start_button->setObjectName(QStringLiteral("start_button"));

        selectEnc_horizontalLayout->addWidget(start_button);


        encDecBox_verticalLayout->addLayout(selectEnc_horizontalLayout);

        input_verticalLayout = new QVBoxLayout();
        input_verticalLayout->setSpacing(6);
        input_verticalLayout->setObjectName(QStringLiteral("input_verticalLayout"));
        input_label = new QLabel(encDec_groupBox);
        input_label->setObjectName(QStringLiteral("input_label"));

        input_verticalLayout->addWidget(input_label);

        input_textedit = new QTextEdit(encDec_groupBox);
        input_textedit->setObjectName(QStringLiteral("input_textedit"));

        input_verticalLayout->addWidget(input_textedit);


        encDecBox_verticalLayout->addLayout(input_verticalLayout);

        output_verticalLayout = new QVBoxLayout();
        output_verticalLayout->setSpacing(6);
        output_verticalLayout->setObjectName(QStringLiteral("output_verticalLayout"));
        output_label = new QLabel(encDec_groupBox);
        output_label->setObjectName(QStringLiteral("output_label"));

        output_verticalLayout->addWidget(output_label);

        output_textedit = new QTextEdit(encDec_groupBox);
        output_textedit->setObjectName(QStringLiteral("output_textedit"));

        output_verticalLayout->addWidget(output_textedit);


        encDecBox_verticalLayout->addLayout(output_verticalLayout);


        gridLayout_3->addLayout(encDecBox_verticalLayout, 0, 0, 1, 1);


        gridLayout_2->addWidget(encDec_groupBox, 0, 1, 1, 1);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        generation_groupBox->setTitle(QApplication::translate("MainWindow", "Generation - Input", 0));
        selection_label->setText(QApplication::translate("MainWindow", "Select strength", 0));
        selection_comboBox->clear();
        selection_comboBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "128", 0)
         << QApplication::translate("MainWindow", "256", 0)
         << QApplication::translate("MainWindow", "512", 0)
         << QApplication::translate("MainWindow", "1024", 0)
         << QApplication::translate("MainWindow", "2048", 0)
         << QApplication::translate("MainWindow", "4096", 0)
        );
        generate_button->setText(QApplication::translate("MainWindow", "Generate", 0));
        q_label->setText(QApplication::translate("MainWindow", "q:", 0));
        p_label->setText(QApplication::translate("MainWindow", "p:", 0));
        n_label->setText(QApplication::translate("MainWindow", "N:", 0));
        e_label->setText(QApplication::translate("MainWindow", "e:", 0));
        d_label->setText(QApplication::translate("MainWindow", "d:", 0));
        encDec_groupBox->setTitle(QApplication::translate("MainWindow", "Encryption - Decryption", 0));
        method_label->setText(QApplication::translate("MainWindow", "Choose encryption method", 0));
        method_comboBox->clear();
        method_comboBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "RSA", 0)
         << QApplication::translate("MainWindow", "RSAES-OAEP", 0)
         << QApplication::translate("MainWindow", "RSAES-PKCS1-V1_5", 0)
        );
        selectEnc_comboBox->clear();
        selectEnc_comboBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Encrypt", 0)
         << QApplication::translate("MainWindow", "Decrypt", 0)
        );
        start_button->setText(QApplication::translate("MainWindow", "Start", 0));
        input_label->setText(QApplication::translate("MainWindow", "Plain Text", 0));
        output_label->setText(QApplication::translate("MainWindow", "Encrypted", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
