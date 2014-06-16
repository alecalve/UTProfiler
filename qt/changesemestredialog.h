#ifndef CHANGESEMESTREDIALOG_H
#define CHANGESEMESTREDIALOG_H

#include <QDialog>

#include "qt/uvdisplaywidget.h"

namespace Ui {
class ChangeSemestreDialog;
}

//! Dialogue permettant de choisir les périodes d'ouvertures d'une UV
class ChangeSemestreDialog : public QDialog
{
    Q_OBJECT

  public:
    explicit ChangeSemestreDialog(QWidget *parent = 0, QString u="");
    ~ChangeSemestreDialog();

    //! Slot qui lorsque Ok est clické, déclenche le changement de valeur du semestre
  public slots:
    void closing();

    //! Attribut : UV dont on souhaite changer les jours d'ouverture, et la fenetre pop up de changement de semestre
  private:
    Ui::ChangeSemestreDialog *ui;
    QString uv;
};

#endif // CHANGESEMESTREDIALOG_H
