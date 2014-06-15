#ifndef EXIGENCESDIALOG_H
#define EXIGENCESDIALOG_H

#include <QDialog>

namespace Ui {
class ExigencesDialog;
}

class ExigencesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ExigencesDialog(QWidget *parent = 0);
    ~ExigencesDialog();

public slots:
    void resolve();

private:
    Ui::ExigencesDialog *ui;
};

#endif // EXIGENCESDIALOG_H
