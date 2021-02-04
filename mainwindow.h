#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QToolButton>
#include <QPushButton>
#include <QComboBox>
#include <QSettings>
#include <QLocale>
#include <QTranslator>
#include <QProcess>

class MainWindow : public QMainWindow
{
    Q_OBJECT
  signals:
    void currentClick();
private:
    void savelanguage();
    void loadlanguage();
    void fullmainwindow();
    void setkhmerlang();
    void setenglishlang();
    void restartApp();


public:
    MainWindow(QWidget *parent = nullptr);
    QToolButton* Thumbnail(
            QToolButton* Button,
            const QString &Name,
            const QString &ImagePath);
    QPushButton* ConfirmButton(QPushButton* Button,
                               const QString &Name,
                               const QString &IconName);


    QComboBox *combo = new QComboBox(this);
    QMainWindow *khmermain = new QMainWindow(this);
     QMainWindow *englishmain = new QMainWindow(this);
      QTranslator *translator = new QTranslator;
    int selected = 0;
    ~MainWindow();
};
#endif // MAINWINDOW_H

