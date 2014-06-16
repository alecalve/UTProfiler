#ifndef FORMATIONDISPLAYWIDGET_H
#define FORMATIONDISPLAYWIDGET_H

#include "displaywidget.h"

#include "src/structures.hpp"

namespace Ui {
class DisplayWidget;
}

class FormationDisplayWidget : public DisplayWidget {
    Q_OBJECT

  public:
    FormationDisplayWidget(QWidget *parent = 0);
    ~FormationDisplayWidget();
    void displayItem(const QString&);

    //! Meme fonction que la classe DisplayWidget dont elle hérite
  public slots:
    void refresh();
    void del();
    void add();
    void modify();
    void change(int row, int column);
    void changed(int row, int column);

};

#endif // FORMATIONDISPLAYWIDGET_H
