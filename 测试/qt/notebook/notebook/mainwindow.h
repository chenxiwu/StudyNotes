#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class QLineEdit;
class QDialog;
class QLabel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void newFile();
    bool maybeSave();
    bool save();
    bool saveAs();
    bool saveFile(const QString &fileName);

private slots:
    void on_action_N_triggered();

    void on_action_S_triggered();

    void on_action_A_triggered();

    void showFindText();

    void on_action_F_triggered();

private:
    Ui::MainWindow *ui;
    bool isUntitled;    //是否为无标题的（未保存的）
    QString curFile;    //当前打开文件路径

    QLineEdit *findLineEdit;
    QDialog *findDlg;
    QLabel *statusLabel;
};


#endif // MAINWINDOW_H
