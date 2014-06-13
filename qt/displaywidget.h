#ifndef DISPLAYWIDGET_H
#define DISPLAYWIDGET_H

#include <QWidget>

namespace Ui {
class DisplayWidget;
}

class DisplayWidget : public QWidget
{
    Q_OBJECT

public:
    DisplayWidget(QWidget *parent = 0);
    ~DisplayWidget();
    virtual void displayItem(const QString&)=0;

public slots:
    virtual void refresh()=0;
    virtual void add()=0;
    virtual void del()=0;
    virtual void modify()=0;
    virtual void change(int row, int column)=0;
    virtual void changed(int row, int column)=0;
    void filter(QString) { refresh(); }


protected:
    Ui::DisplayWidget *ui;

    unsigned int offset;
};

#endif // DISPLAYWIDGET_H
