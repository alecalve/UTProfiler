#ifndef ADDFORMATION_H
#define ADDFORMATION_H

#include <QWidget>

namespace Ui {
class addformation;
}

class addformation : public QWidget
{
    Q_OBJECT

public:
    explicit addformation(QWidget *parent = 0);
    ~addformation();

private:
    Ui::addformation *ui;
};

#endif // ADDFORMATION_H
