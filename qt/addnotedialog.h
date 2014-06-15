#ifndef ADDNOTEDIALOG_H
#define ADDNOTEDIALOG_H

#include <QDialog>

//! Classe pop up ajout note
namespace Ui {
class AddNoteDialog;
}

class AddNoteDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddNoteDialog(QWidget *parent = 0);
    ~AddNoteDialog();

public slots:
    void createNote();

private:
    Ui::AddNoteDialog *ui;
};

#endif // ADDNOTEDIALOG_H
