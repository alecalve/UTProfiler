#ifndef ADDSEMESTREDIALOG_H
#define ADDSEMESTREDIALOG_H

#include <QDialog>

namespace Ui {
class AddSemestreDialog;
}

class AddSemestreDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddSemestreDialog(QWidget *parent = 0);
    ~AddSemestreDialog();

public slots:

  //! Déclenché lors d’un click sur "Ajouter UV"
  void uvAdded();

signals:

  //! Signal lancé lorsque Ok est clické
  void choiceMade(int r, bool printemps, bool automne);

private:
    Ui::AddSemestreDialog *ui;
};

#endif // ADDSEMESTREDIALOG_H
