#ifndef ADDNOTEDIALOG_H
#define ADDNOTEDIALOG_H

#include <QDialog>

//! Classe pop up ajout note
namespace Ui {
class AddNoteDialog;
}

//! Dialog de création de NoteUV
class AddNoteDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddNoteDialog(QWidget *parent = 0);
    ~AddNoteDialog();

public slots:
    //! fonction permettant la création d'une nouvelle note
    void createNote();

private:
    //! attribut de la fenetre de dialogue d'ajout de note
    Ui::AddNoteDialog *ui;
};

#endif // ADDNOTEDIALOG_H
