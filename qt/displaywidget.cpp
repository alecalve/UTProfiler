#include "displaywidget.h"
#include "ui_displaywidget.h"

//! ouverture d'un pop up
DisplayWidget::DisplayWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DisplayWidget)
{
    ui->setupUi(this);
    offset = 0;
}

//! fermeture du pop up
DisplayWidget::~DisplayWidget()
{
    delete ui;
}
