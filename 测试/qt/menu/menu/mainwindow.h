#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void newFile();
    bool needSave();
    bool save();
    bool saveAs();
    bool saveFile(const QString &fileName);

private:
    Ui::MainWindow *ui;
    bool isUntitled;    //是否为无标题的（未保存的）
    QString curFile;    //当前打开文件路径
};

#endif // MAINWINDOW_H
