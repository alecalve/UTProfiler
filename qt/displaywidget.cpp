#include "displaywidget.h"
#include "ui_displaywidget.h"

DisplayWidget::DisplayWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DisplayWidget)
{
    ui->setupUi(this);
    offset = 0;
}

DisplayWidget::~DisplayWidget()
{
    delete ui;
}
