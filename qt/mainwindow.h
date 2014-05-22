#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "src/uvmanager.hpp"

namespace Ui { class MainWindow; }

//! Fenêtre principale de l'application
class MainWindow : public QMainWindow {
  Q_OBJECT

  public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

  public slots:
    void afficheUvs();
    void saveUvs();

  private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
