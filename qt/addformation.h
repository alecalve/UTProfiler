#ifndef ADDFORMATION_H
#define ADDFORMATION_H 1

#include <QDialog>

namespace Ui {
class AddFormation;
}

class AddFormation : public QDialog
{
    Q_OBJECT

public:
    explicit AddFormation(QWidget *parent = 0);
    ~AddFormation();

public slots :
    void createFormation();
    void uvAdded();
    void creditsAdded();

private:
    Ui::AddFormation *ui;
};

#endif // ADDFORMATION_H
