#ifndef CHANGESEMESTREDIALOG_H
#define CHANGESEMESTREDIALOG_H

#include <QDialog>

#include "qt/uvdisplaywidget.h"

namespace Ui {
class ChangeSemestreDialog;
}

class ChangeSemestreDialog : public QDialog
{
    Q_OBJECT

  public:
    explicit ChangeSemestreDialog(QWidget *parent = 0, bool p=false, bool a=false, int r=-1);
    ~ChangeSemestreDialog();

  public slots:
    void closing();

  signals:
    void choiceMade(int r, bool printemps, bool automne);

  private:
    Ui::ChangeSemestreDialog *ui;
    int row;
};

#endif // CHANGESEMESTREDIALOG_H
