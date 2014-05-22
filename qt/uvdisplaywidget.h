#ifndef UVDISPLAYWIDGET_H
#define UVDISPLAYWIDGET_H

#include <QWidget>
#include <QTextStream>
#include <QTableWidgetItem>

#include "src/uv.hpp"

namespace Ui {
class UvDisplayWidget;
}

class UvDisplayWidget : public QWidget {
    Q_OBJECT

  public:
    explicit UvDisplayWidget(QWidget *parent = 0);
    ~UvDisplayWidget();
    void choiceSemestre(int row, bool printemps, bool automne);

  public slots:
    void refresh();
    void change(int row, int column);
    void changed(int row, int column);

  private:
    Ui::UvDisplayWidget *ui;
};

#endif // UVDISPLAYWIDGET_H
