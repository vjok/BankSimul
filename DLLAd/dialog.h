#ifndef DIALOG_H
#define DIALOG_H
#include <QDialog>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QDebug>
#include <QDesktopWidget>


namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    void showAd10();
private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
