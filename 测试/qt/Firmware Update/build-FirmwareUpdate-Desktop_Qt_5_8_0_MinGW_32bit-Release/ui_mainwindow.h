/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_O;
    QAction *action;
    QAction *action_D;
    QAction *action_A;
    QWidget *centralWidget;
    QLabel *label;
    QPushButton *pushButton_Open;
    QLabel *label_2;
    QComboBox *comboBox_LocalIP;
    QTabWidget *tabWidget;
    QWidget *tab;
    QLineEdit *lineEdit_AutoControllerIP;
    QLineEdit *lineEdit_AutoControllerPort;
    QLabel *label_5;
    QLabel *label_6;
    QWidget *tab_2;
    QLineEdit *lineEdit_ManualControllerPort;
    QLineEdit *lineEdit_ManualControllerIP;
    QLabel *label_3;
    QLabel *label_4;
    QPushButton *pushButton_Update;
    QLineEdit *lineEdit_Firmware;
    QMenuBar *menuBar;
    QMenu *menu_F;
    QMenu *menu_H;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(450, 320);
        action_O = new QAction(MainWindow);
        action_O->setObjectName(QStringLiteral("action_O"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/Res/Open.ico"), QSize(), QIcon::Normal, QIcon::Off);
        action_O->setIcon(icon);
        action = new QAction(MainWindow);
        action->setObjectName(QStringLiteral("action"));
        action_D = new QAction(MainWindow);
        action_D->setObjectName(QStringLiteral("action_D"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/Res/112.ico"), QSize(), QIcon::Normal, QIcon::Off);
        action_D->setIcon(icon1);
        action_A = new QAction(MainWindow);
        action_A->setObjectName(QStringLiteral("action_A"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/Res/About.ico"), QSize(), QIcon::Normal, QIcon::Off);
        action_A->setIcon(icon2);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(30, 20, 81, 21));
        pushButton_Open = new QPushButton(centralWidget);
        pushButton_Open->setObjectName(QStringLiteral("pushButton_Open"));
        pushButton_Open->setGeometry(QRect(350, 20, 71, 23));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(30, 50, 81, 21));
        comboBox_LocalIP = new QComboBox(centralWidget);
        comboBox_LocalIP->setObjectName(QStringLiteral("comboBox_LocalIP"));
        comboBox_LocalIP->setGeometry(QRect(120, 50, 201, 21));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(30, 90, 391, 111));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        lineEdit_AutoControllerIP = new QLineEdit(tab);
        lineEdit_AutoControllerIP->setObjectName(QStringLiteral("lineEdit_AutoControllerIP"));
        lineEdit_AutoControllerIP->setGeometry(QRect(110, 20, 181, 20));
        lineEdit_AutoControllerPort = new QLineEdit(tab);
        lineEdit_AutoControllerPort->setObjectName(QStringLiteral("lineEdit_AutoControllerPort"));
        lineEdit_AutoControllerPort->setGeometry(QRect(110, 50, 181, 20));
        label_5 = new QLabel(tab);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(10, 20, 101, 21));
        label_6 = new QLabel(tab);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(10, 50, 101, 21));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        lineEdit_ManualControllerPort = new QLineEdit(tab_2);
        lineEdit_ManualControllerPort->setObjectName(QStringLiteral("lineEdit_ManualControllerPort"));
        lineEdit_ManualControllerPort->setGeometry(QRect(110, 50, 181, 20));
        lineEdit_ManualControllerIP = new QLineEdit(tab_2);
        lineEdit_ManualControllerIP->setObjectName(QStringLiteral("lineEdit_ManualControllerIP"));
        lineEdit_ManualControllerIP->setGeometry(QRect(110, 20, 181, 20));
        label_3 = new QLabel(tab_2);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 20, 101, 21));
        label_4 = new QLabel(tab_2);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(10, 50, 101, 21));
        tabWidget->addTab(tab_2, QString());
        pushButton_Update = new QPushButton(centralWidget);
        pushButton_Update->setObjectName(QStringLiteral("pushButton_Update"));
        pushButton_Update->setGeometry(QRect(140, 210, 131, 31));
        lineEdit_Firmware = new QLineEdit(centralWidget);
        lineEdit_Firmware->setObjectName(QStringLiteral("lineEdit_Firmware"));
        lineEdit_Firmware->setGeometry(QRect(120, 20, 201, 20));
        MainWindow->setCentralWidget(centralWidget);
        label->raise();
        pushButton_Open->raise();
        label_2->raise();
        comboBox_LocalIP->raise();
        tabWidget->raise();
        pushButton_Update->raise();
        lineEdit_Firmware->raise();
        label_5->raise();
        label_6->raise();
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 450, 17));
        menu_F = new QMenu(menuBar);
        menu_F->setObjectName(QStringLiteral("menu_F"));
        menu_H = new QMenu(menuBar);
        menu_H->setObjectName(QStringLiteral("menu_H"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menu_F->menuAction());
        menuBar->addAction(menu_H->menuAction());
        menu_F->addAction(action_O);
        menu_F->addAction(action);
        menu_H->addAction(action_D);
        menu_H->addAction(action_A);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindows", Q_NULLPTR));
        action_O->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200(&O)", Q_NULLPTR));
        action->setText(QApplication::translate("MainWindow", "\351\200\200\345\207\272", Q_NULLPTR));
        action_D->setText(QApplication::translate("MainWindow", "\345\215\207\347\272\247\350\257\264\346\230\216(&D)", Q_NULLPTR));
        action_A->setText(QApplication::translate("MainWindow", "\345\205\263\344\272\216(&A)", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "\345\215\207\347\272\247\345\233\272\344\273\266\357\274\232", Q_NULLPTR));
        pushButton_Open->setText(QApplication::translate("MainWindow", "\346\211\223 \345\274\200", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "\346\234\254\345\234\260IP\357\274\232", Q_NULLPTR));
        comboBox_LocalIP->setCurrentText(QString());
#ifndef QT_NO_TOOLTIP
        lineEdit_AutoControllerIP->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        label_5->setText(QApplication::translate("MainWindow", "\346\216\247\345\210\266\345\231\250IP\357\274\232", Q_NULLPTR));
        label_6->setText(QApplication::translate("MainWindow", "\346\216\247\345\210\266\345\231\250\347\253\257\345\217\243\357\274\232", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "\350\207\252\345\212\250\345\215\207\347\272\247", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        lineEdit_ManualControllerIP->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        label_3->setText(QApplication::translate("MainWindow", "\346\216\247\345\210\266\345\231\250IP\357\274\232", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWindow", "\346\216\247\345\210\266\345\231\250\347\253\257\345\217\243\357\274\232", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "\346\211\213\345\212\250\345\215\207\347\272\247", Q_NULLPTR));
        pushButton_Update->setText(QApplication::translate("MainWindow", "\345\215\207  \347\272\247", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        lineEdit_Firmware->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        menu_F->setTitle(QApplication::translate("MainWindow", "\346\226\207\344\273\266(&F)", Q_NULLPTR));
        menu_H->setTitle(QApplication::translate("MainWindow", "\345\270\256\345\212\251(&H)", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
