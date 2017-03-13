#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProgressBar>
#include <QLabel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void updateLocalIP();
    bool isIP_SegmentEqual(QString ip1, QString subnetMask1, QString ip2, QString subnetMask2);
    bool checkInput();

private slots:
    void on_pushButton_Open_clicked();
    void on_pushButton_Update_clicked();

    void tabWidgetCurrentChanged(int index);


private:
    Ui::MainWindow *ui;
    QProgressBar *progressBar;
    QLabel *statusLabel;
    int curPage;
};

#endif // MAINWINDOW_H
