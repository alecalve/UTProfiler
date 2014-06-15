#ifndef CHOOSEDOSSIERDIALOG_H
#define CHOOSEDOSSIERDIALOG_H

#include <QDialog>

namespace Ui {
class ChooseDossierDialog;
}

class ChooseDossierDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChooseDossierDialog(QWidget *parent = 0);
    ~ChooseDossierDialog();

public slots:
    void callCompleter();

private:
    Ui::ChooseDossierDialog *ui;
};

#endif // CHOOSEDOSSIERDIALOG_H
