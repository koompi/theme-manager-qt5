#ifndef CUSTOMLABEL_H
#define CUSTOMLABEL_H

#include <QWidget>
#include <QLabel>
class customLabel : public QLabel
{
    Q_OBJECT
public:
    explicit customLabel(QWidget *parent = nullptr);

signals:

};

#endif // CUSTOMLABEL_H
