#ifndef NOTEDISPLAYWIDGET_H
#define NOTEDISPLAYWIDGET_H

#include "displaywidget.h"

#include "src/structures.hpp"

namespace Ui {
class DisplayWidget;
}

class NoteDisplayWidget : public DisplayWidget {
    Q_OBJECT

  public:
    NoteDisplayWidget(QWidget *parent = 0);
    ~NoteDisplayWidget();
    void displayItem(const QString&);

  public slots: //! fonctions héritées de DisplayWidget
    void refresh();
    void del();
    void add();
    void modify();
    void change(int row, int column);
    void changed(int row, int column);

};

#endif // NOTEDISPLAYWIDGET_H
