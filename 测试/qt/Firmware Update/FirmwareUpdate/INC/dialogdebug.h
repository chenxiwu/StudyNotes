#ifndef DIALOGDEBUG_H
#define DIALOGDEBUG_H

#include <QDialog>

namespace Ui {
class DialogDebug;
}

class DialogDebug : public QDialog
{
    Q_OBJECT

public:
    explicit DialogDebug(QWidget *parent = 0);
    ~DialogDebug();

private slots:
    void autoScroll();

    void on_pushButton_Clear_clicked();

private:
    Ui::DialogDebug *ui;    
};

#endif // DIALOGDEBUG_H
