#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "src/uvmanager.hpp"
#include "src/abstractio.hpp"

namespace Ui { class MainWindow; }

//! Fenêtre principale de l'application
class MainWindow : public QMainWindow {
  Q_OBJECT

  public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

  public slots:
    //! Slot qui permet de charger des données externes
    void loadFile();

    //! Slot qui permet de sauvegarder les données
    void saveFile();

  private:
    Ui::MainWindow *ui;

    //! Stratégie de sauvegarde des données
    AbstractIo *ioPolicy;
};

#endif // MAINWINDOW_H
