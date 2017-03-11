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
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_N;
    QAction *action_O;
    QAction *action_C;
    QAction *action_S;
    QAction *action_A;
    QAction *action_X;
    QAction *action_Z;
    QAction *action_X_2;
    QAction *action_C_2;
    QAction *action_V;
    QAction *action_F;
    QAction *action_6;
    QWidget *centralWidget;
    QFormLayout *formLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_3;
    QPushButton *pushButton_2;
    QMenuBar *menuBar;
    QMenu *menu;
    QMenu *menu_E;
    QMenu *menu_H;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(400, 300);
        action_N = new QAction(MainWindow);
        action_N->setObjectName(QStringLiteral("action_N"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/IMG_2318.JPG"), QSize(), QIcon::Normal, QIcon::Off);
        action_N->setIcon(icon);
        action_O = new QAction(MainWindow);
        action_O->setObjectName(QStringLiteral("action_O"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/images/(Preview).png"), QSize(), QIcon::Normal, QIcon::Off);
        action_O->setIcon(icon1);
        action_C = new QAction(MainWindow);
        action_C->setObjectName(QStringLiteral("action_C"));
        action_S = new QAction(MainWindow);
        action_S->setObjectName(QStringLiteral("action_S"));
        action_A = new QAction(MainWindow);
        action_A->setObjectName(QStringLiteral("action_A"));
        action_X = new QAction(MainWindow);
        action_X->setObjectName(QStringLiteral("action_X"));
        action_Z = new QAction(MainWindow);
        action_Z->setObjectName(QStringLiteral("action_Z"));
        action_X_2 = new QAction(MainWindow);
        action_X_2->setObjectName(QStringLiteral("action_X_2"));
        action_C_2 = new QAction(MainWindow);
        action_C_2->setObjectName(QStringLiteral("action_C_2"));
        action_V = new QAction(MainWindow);
        action_V->setObjectName(QStringLiteral("action_V"));
        action_F = new QAction(MainWindow);
        action_F->setObjectName(QStringLiteral("action_F"));
        action_6 = new QAction(MainWindow);
        action_6->setObjectName(QStringLiteral("action_6"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        formLayout = new QFormLayout(centralWidget);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        formLayout->setWidget(0, QFormLayout::LabelRole, pushButton);

        pushButton_3 = new QPushButton(centralWidget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        formLayout->setWidget(1, QFormLayout::LabelRole, pushButton_3);

        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        formLayout->setWidget(2, QFormLayout::LabelRole, pushButton_2);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 17));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        menu_E = new QMenu(menuBar);
        menu_E->setObjectName(QStringLiteral("menu_E"));
        menu_H = new QMenu(menuBar);
        menu_H->setObjectName(QStringLiteral("menu_H"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menu_E->menuAction());
        menuBar->addAction(menu_H->menuAction());
        menu->addAction(action_N);
        menu->addAction(action_O);
        menu->addAction(action_C);
        menu->addSeparator();
        menu->addAction(action_S);
        menu->addAction(action_A);
        menu->addSeparator();
        menu->addAction(action_X);
        menu_E->addAction(action_Z);
        menu_E->addSeparator();
        menu_E->addAction(action_X_2);
        menu_E->addAction(action_C_2);
        menu_E->addAction(action_V);
        menu_E->addSeparator();
        menu_E->addAction(action_F);
        menu_H->addAction(action_6);
        mainToolBar->addAction(action_N);
        mainToolBar->addAction(action_O);
        mainToolBar->addSeparator();
        mainToolBar->addAction(action_C);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        action_N->setText(QApplication::translate("MainWindow", "\346\226\260\345\273\272\357\274\210&N\357\274\211", Q_NULLPTR));
        action_N->setShortcut(QApplication::translate("MainWindow", "Ctrl+N", Q_NULLPTR));
        action_O->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200\357\274\210&O\357\274\211", Q_NULLPTR));
        action_O->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", Q_NULLPTR));
        action_C->setText(QApplication::translate("MainWindow", "\345\205\263\351\227\255\357\274\210&C\357\274\211", Q_NULLPTR));
        action_C->setShortcut(QApplication::translate("MainWindow", "Ctrl+C", Q_NULLPTR));
        action_S->setText(QApplication::translate("MainWindow", "\344\277\235\345\255\230\357\274\210&S\357\274\211", Q_NULLPTR));
        action_S->setShortcut(QApplication::translate("MainWindow", "Ctrl+S", Q_NULLPTR));
        action_A->setText(QApplication::translate("MainWindow", "\345\217\246\345\255\230\344\270\272\357\274\210&A\357\274\211", Q_NULLPTR));
        action_A->setShortcut(QApplication::translate("MainWindow", "Ctrl+A", Q_NULLPTR));
        action_X->setText(QApplication::translate("MainWindow", "\351\200\200\345\207\272\357\274\210&X\357\274\211", Q_NULLPTR));
        action_X->setShortcut(QApplication::translate("MainWindow", "Ctrl+X", Q_NULLPTR));
        action_Z->setText(QApplication::translate("MainWindow", "\346\222\244\351\224\200\357\274\210&Z\357\274\211", Q_NULLPTR));
        action_Z->setShortcut(QApplication::translate("MainWindow", "Ctrl+Z", Q_NULLPTR));
        action_X_2->setText(QApplication::translate("MainWindow", "\345\211\252\345\210\207\357\274\210&X\357\274\211", Q_NULLPTR));
        action_X_2->setShortcut(QApplication::translate("MainWindow", "Ctrl+X", Q_NULLPTR));
        action_C_2->setText(QApplication::translate("MainWindow", "\345\244\215\345\210\266\357\274\210&C\357\274\211", Q_NULLPTR));
        action_C_2->setShortcut(QApplication::translate("MainWindow", "Ctrl+C", Q_NULLPTR));
        action_V->setText(QApplication::translate("MainWindow", "\347\262\230\350\264\264\357\274\210&V\357\274\211", Q_NULLPTR));
        action_V->setShortcut(QApplication::translate("MainWindow", "Ctrl+V", Q_NULLPTR));
        action_F->setText(QApplication::translate("MainWindow", "\346\237\245\346\211\276\357\274\210&F\357\274\211", Q_NULLPTR));
        action_6->setText(QApplication::translate("MainWindow", "\345\205\263\344\272\216", Q_NULLPTR));
        pushButton->setText(QApplication::translate("MainWindow", "PushButton", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("MainWindow", "PushButton", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("MainWindow", "PushButton", Q_NULLPTR));
        menu->setTitle(QApplication::translate("MainWindow", "\346\226\207\344\273\266", Q_NULLPTR));
        menu_E->setTitle(QApplication::translate("MainWindow", "\347\274\226\350\276\221\357\274\210&E\357\274\211", Q_NULLPTR));
        menu_H->setTitle(QApplication::translate("MainWindow", "\345\270\256\345\212\251\357\274\210&H\357\274\211", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
