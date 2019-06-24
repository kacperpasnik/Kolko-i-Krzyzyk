#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mapa.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionSI_vs_SI_triggered()
{
    hide();
    z= new Mapa(this,false,2);
    z->exec();
}

void MainWindow::on_actionZako_cz_triggered()
{
    QCoreApplication::exit();
}

void MainWindow::on_pushButton_si_clicked()
{
    hide();
    z= new Mapa(this,kto_pierwszy(),0);
    z->exec();
}

void MainWindow::on_pushButton_gracz_clicked()
{
    hide();
    z= new Mapa(this,kto_pierwszy(),1);
    z->exec();
}



void MainWindow::on_actionKomputer_triggered()
{
    if(ui->actionKomputer->isChecked()==true)
    {
        //ui->actionKomputer->setChecked(false);
        ui->actionGracz->setChecked(false);
    }
    else if(ui->actionKomputer->isChecked()==false)
    {
        ui->actionKomputer->setChecked(true);
    }

}

void MainWindow::on_actionGracz_triggered()
{
    if(ui->actionGracz->isChecked()==true)
    {
        //ui->actionGracz->setChecked(false);
        ui->actionKomputer->setChecked(false);
    }
    else if(ui->actionGracz->isChecked()==false)
    {
        ui->actionGracz->setChecked(true);
    }

}

bool MainWindow::kto_pierwszy()
{
    if(ui->actionGracz->isChecked()==true)
        return true;
    else if(ui->actionKomputer->isChecked()==true)
        return false;
}
