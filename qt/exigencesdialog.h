#ifndef EXIGENCESDIALOG_H
#define EXIGENCESDIALOG_H

#include <QDialog>

#include "src/dossier.hpp"

namespace Ui {
class ExigencesDialog;
}

class ExigencesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ExigencesDialog(QWidget *parent = 0);
    ~ExigencesDialog();
    inline void setDossier(Dossier *d) { dossier = d; }

public slots:
    void resolve();
    void wishAdded();
    void rejectAdded();

private:
    Ui::ExigencesDialog *ui;
    Dossier *dossier;
};

#endif // EXIGENCESDIALOG_H
