#ifndef ADDCATEGORIEDIALOG_H
#define ADDCATEGORIEDIALOG_H

#include <QDialog>

namespace Ui {
class AddCategorieDialog;
}

class AddCategorieDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddCategorieDialog(QWidget *parent = 0);
    ~AddCategorieDialog();

public slots:
    void createCategorie();

private:
    Ui::AddCategorieDialog *ui;
};

#endif // ADDCATEGORIEDIALOG_H
