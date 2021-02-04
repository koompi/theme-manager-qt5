#include "mainwindow.h"

#include <QLabel>
#include <QPushButton>
#include <QProcess>
#include <QVBoxLayout>
#include <QWidget>
#include <QDebug>
#include <QDialog>
#include <QGridLayout>
#include <QImageReader>
#include <QToolButton>
#include <QIcon>
#include <QApplication>
#include <QWidget>
#include <QScrollArea>
#include <QDir>

QWidget* wrap(QLayout* l) {
    auto widget = new QWidget();
    widget->setLayout(l);
    return widget;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QString savedata = QDir::homePath().append("/.config/Theme Manager/thememanager.ini");
    QLocale lsystem = QLocale::system();
    QSettings settings(savedata, QSettings::IniFormat);
    settings.beginGroup("mainwindow");
    if (settings.value("combo").toInt() == 0){
        if (lsystem.languageToString(lsystem.language()) != "Khmer"){
            setenglishlang();
        }
        if (lsystem.languageToString(lsystem.language()) == "Khmer"){
            setkhmerlang();
        }
    }
    if (settings.value("combo").toInt() == 1){
        setkhmerlang();
    }
    if (settings.value("combo").toInt() == 2){
        setenglishlang();
    }
    if (settings.value("combo").toInt() != 0 && settings.value("combo").toInt() != 1 && settings.value("combo").toInt() != 2){

        if (lsystem.languageToString(lsystem.language()) != "Khmer"){
            setenglishlang();
        }
        if (lsystem.languageToString(lsystem.language()) == "Khmer"){
            setkhmerlang();
        }
    }
}
void MainWindow::fullmainwindow(){
    //All Widget And Mainwindow
    QWidget *widgetscroll = new QWidget;
    QMainWindow *Mainwindowscoll = new QMainWindow;
    QScrollArea *scroll = new QScrollArea;
    QWidget *LastWidget = new QWidget;

    // All layout variables
    QHBoxLayout * langtoollayout = new QHBoxLayout;
    QGridLayout * ThumbnailLayout = new QGridLayout;
    QVBoxLayout * Mainlayout = new QVBoxLayout;
    QHBoxLayout * FooterLayout = new QHBoxLayout;
    QVBoxLayout *layoutscroll = new QVBoxLayout(widgetscroll);
    QVBoxLayout * MainLastLayout = new QVBoxLayout(LastWidget);

    // Header
    QLabel * AppTitle = new QLabel;
    AppTitle->setText(tr("Choose a theme you like and click apply."));
    AppTitle->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Expanding);
    AppTitle->setMinimumHeight(35);
    AppTitle->setMaximumHeight(35);

    // Footer
    QPushButton * Default = new QPushButton;
    QPushButton * Apply = new QPushButton;
    QPushButton * Cancel = new QPushButton;

    //Combobox
    combo = new QComboBox(this);
    combo->addItem(tr("System Language"));
    combo->addItem(tr("Khmer"));
    combo->addItem(tr("English"));
    combo->setFocusPolicy(Qt::ClickFocus);

    loadlanguage(); //load language and combobox

    if(selected == 0) {
        Apply->setDisabled(true);
    }
    ConfirmButton(Default, tr("Restore Default"), tr("preferences-desktop-default-applications"));
    ConfirmButton(Apply, tr("Apply"), tr("dialog-ok-apply"));
    ConfirmButton(Cancel, tr("Cancel"), tr("dialog-cancel"));

    // All thumbnail
    QToolButton* KoompiDark = new QToolButton;
    QToolButton* KoompiLight = new QToolButton;
    QToolButton* KoompiMosxDark = new QToolButton;
    QToolButton* KoompiMosxLight = new QToolButton;
    QToolButton* KoompiWinxDark = new QToolButton;
    QToolButton* KoompiWinxLight = new QToolButton;

    FooterLayout->addWidget(Default);
    FooterLayout->addStretch();
    FooterLayout->addWidget(Apply);
    FooterLayout->addWidget(Cancel);

    langtoollayout->addWidget(AppTitle);
    langtoollayout->addStretch();
    langtoollayout->addWidget(combo);

    Thumbnail(KoompiDark, tr("KOOMPI Dark"), "://resources/images/koompi-dark.png");
    Thumbnail(KoompiLight, tr("KOOMPI Light"), "://resources/images/koompi-light.png");
    Thumbnail(KoompiMosxDark, tr("KOOMPI MOSX Dark"), "://resources/images/mosx-dark.png");
    Thumbnail(KoompiMosxLight, tr("KOOMPI MOSX Light"), "://resources/images/mosx-light.png");
    Thumbnail(KoompiWinxDark, tr("KOOMPI WinX Dark"), "://resources/images/winx-dark.png");
    Thumbnail(KoompiWinxLight, tr("KOOMPI WinX Light"), "://resources/images/winx-light.png");

    ThumbnailLayout->setSpacing(20);
    ThumbnailLayout->addWidget(KoompiDark, 1, 1, 1, 1, Qt::AlignCenter);
    ThumbnailLayout->addWidget(KoompiLight, 1, 2, 1, 1, Qt::AlignCenter);
    ThumbnailLayout->addWidget(KoompiMosxDark, 2, 1, 1, 1, Qt::AlignCenter);
    ThumbnailLayout->addWidget(KoompiMosxLight, 2, 2, 1, 1, Qt::AlignCenter);
    ThumbnailLayout->addWidget(KoompiWinxDark, 3, 1, 1, 1, Qt::AlignCenter);
    ThumbnailLayout->addWidget(KoompiWinxLight, 3, 2, 1, 1, Qt::AlignCenter);

    Mainlayout->addLayout(ThumbnailLayout);
    

    // Mainwindow And Widget Scoll

    // +WidgetScroll
    scroll->setWidget(widgetscroll);
    scroll->setWidgetResizable(true);
    scroll->setFocusPolicy(Qt::NoFocus);
    layoutscroll->addLayout(Mainlayout);

    //+MainwindowScroll
    Mainwindowscoll->setGeometry(0,0,880,525);
    Mainwindowscoll->setCentralWidget(scroll);

    //Last Widget
    LastWidget->setGeometry(0,0,900,655);

    MainLastLayout->addLayout(langtoollayout);
    MainLastLayout->addWidget(Mainwindowscoll);
    MainLastLayout->addLayout(FooterLayout);

    LastWidget->show();

    connect(combo,&QComboBox::textActivated,this, [=](){
        qDebug()<<combo->currentData()<<combo->currentText()<<combo->currentIndex();

        if (combo->currentIndex() == 0){
            restartApp();    //restart app
        }
        if (combo->currentIndex() == 1){
            restartApp();
        }
        if (combo->currentIndex() == 2){
            restartApp();
        }

        savelanguage();
    });

    connect(Default, &QPushButton::clicked, this, [=](){
        qDebug() << "KoompiLight clicked";
        QProcess* restore_theme = new QProcess;
        restore_theme->execute("/usr/bin/bash /usr/share/org.koompi.theme.manager/kmp-dark.sh");
    });

    connect(Cancel, &QPushButton::clicked, this, [=](){
        QApplication::quit();
    });

    connect(Apply, &QPushButton::clicked, this, [=](){
        QProcess* update_theme = new QProcess;
        qDebug() << selected;
        switch(selected) {
        case 1:
            update_theme->execute("/usr/bin/bash /usr/share/org.koompi.theme.manager/kmp-dark.sh");
            break;
        case 2:
            update_theme->execute("/usr/bin/bash /usr/share/org.koompi.theme.manager/kmp-light.sh");
            break;
        case 3:
            update_theme->execute("/usr/bin/bash /usr/share/org.koompi.theme.manager/mosx-dark.sh");
            break;
        case 4:
            update_theme->execute("/usr/bin/bash /usr/share/org.koompi.theme.manager/mosx-light.sh");
            break;
        case 5:
            update_theme->execute("/usr/bin/bash /usr/share/org.koompi.theme.manager/winx-dark.sh");
            break;
        case 6:
            update_theme->execute("/usr/bin/bash /usr/share/org.koompi.theme.manager/winx-light.sh");
            break;
        }
    });

    connect(KoompiDark, &QToolButton::clicked, this, [=](){
        selected = 1;
        Apply->setDisabled(false);
    });

    connect(KoompiLight, &QToolButton::clicked, this, [=](){
        selected = 2;
        Apply->setDisabled(false);
    });

    connect(KoompiMosxDark, &QToolButton::clicked, this, [=](){
        selected = 3;
        Apply->setDisabled(false);
    });

    connect(KoompiMosxLight, &QToolButton::clicked, this, [=](){
        selected = 4;
        Apply->setDisabled(false);
    });

    connect(KoompiWinxDark, &QToolButton::clicked, this, [=](){
        selected = 5;
        Apply->setDisabled(false);
    });

    connect(KoompiWinxLight, &QToolButton::clicked, this, [=](){
        selected = 6;
        Apply->setDisabled(false);
    });

    LastWidget->setWindowIcon(QIcon::fromTheme(tr("preferences-desktop-theme-global")));
    LastWidget->setWindowTitle(tr("Theme Manager"));
    //this->setCentralWidget(wrap(MainLastLayout));

}

QToolButton *MainWindow::Thumbnail(QToolButton *Button, const QString &Name, const QString &ImagePath)
{
    Button->setText(Name);
    Button->setIcon(QIcon(ImagePath));
    Button->setIconSize(QSize(400,220));
    Button->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    Button->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    Button->setMaximumSize(390,275);
    Button->setFocusPolicy(Qt::ClickFocus);
    return Button;
}

QPushButton *MainWindow::ConfirmButton(QPushButton *Button, const QString &Name, const QString &IconName)
{
    Button->setText(Name);
    Button->setIcon(QIcon::fromTheme(IconName));
    Button->setIconSize(QSize(26,26));
    Button->setMinimumHeight(35);
    Button->setMaximumHeight(35);
    return Button;
}

void MainWindow::loadlanguage(){
    QString savedata = QDir::homePath().append("/.config/Theme Manager/thememanager.ini");
    QSettings settings(savedata, QSettings::IniFormat);
    settings.beginGroup("mainwindow");
    combo->setCurrentIndex(settings.value("combo").toInt());
    settings.endGroup();
}
void MainWindow::savelanguage(){
    QString savedata = QDir::homePath().append("/.config/Theme Manager/thememanager.ini");
    QSettings settings(savedata, QSettings::IniFormat);
    settings.beginGroup("mainwindow");
    settings.setValue("combo", combo->currentIndex());
    settings.endGroup();
}
void MainWindow::setenglishlang(){
    QTranslator t;
    t.load(":/i18n/km_KH.qm");
    qApp->removeTranslator(&t);
    fullmainwindow();
    englishmain->close();
    khmermain->close();
}
void MainWindow::setkhmerlang(){
    QTranslator t;
    t.load(":/i18n/km_KH.qm");
    qApp->installTranslator(&t);
    fullmainwindow();
    englishmain->close();
    khmermain->close();
}
void MainWindow::restartApp()
{
    qApp->quit();
    QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
    qApp->quit();
}
MainWindow::~MainWindow()
{
}


