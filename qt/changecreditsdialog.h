#ifndef CHANGECREDITSDIALOG_H
#define CHANGECREDITSDIALOG_H

#include <QDialog>

namespace Ui {
class ChangeCreditsDialog;
}

class ChangeCreditsDialog : public QDialog {
    Q_OBJECT

public:
    explicit ChangeCreditsDialog(QWidget *parent = 0, QString u="");
    ~ChangeCreditsDialog();

public slots:
    void ajouter();
    void closing();

private:
    Ui::ChangeCreditsDialog *ui;
    QString uv;
};

#endif // CHANGECREDITSDIALOG_H
