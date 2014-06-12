#include "addformation.h"
#include "ui_addformation.h"

addformation::addformation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::addformation)
{
    ui->setupUi(this);
}

addformation::~addformation()
{
    delete ui;
}
