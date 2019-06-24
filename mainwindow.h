#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mapa.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    bool kto_pierwszy();
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionSI_vs_SI_triggered();

    void on_actionZako_cz_triggered();

    void on_pushButton_si_clicked();

    void on_pushButton_gracz_clicked();



    void on_actionKomputer_triggered();

    void on_actionGracz_triggered();

private:
    Ui::MainWindow *ui;
    Mapa* z;
};

#endif // MAINWINDOW_H
