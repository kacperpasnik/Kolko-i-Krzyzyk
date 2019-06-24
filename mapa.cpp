#include "mapa.h"
#include "ui_mapa.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"


Mapa::Mapa(QWidget *parent,bool kto_pierwszy,int graczvsgracz) :
    QDialog(parent),
    ui(new Ui::Mapa)
{
    ui->setupUi(this);

    MainWindow menuglowne;
    switch(graczvsgracz)
    {
         case 0:
        {
            sztuczna.kogo_kolej= kto_pierwszy;
            if(kto_pierwszy==false)
            {
                int pole=0;
                sztuczna.Minimaks(sztuczna.plansza, sztuczna.kogo_kolej, sztuczna.wartosc_mozliwosci, sztuczna.plansza_zastepcza, sztuczna.wsk);
                pole=sztuczna.Decyzja(sztuczna.plansza,sztuczna.wartosc_mozliwosci,sztuczna.wsk);
                Namaluj(pole);
                ui->label_info->setText("Komputer wybrał pole nr: " + QString::number(pole));
                sztuczna.kogo_kolej=true;

            }
            break;
        }
        case 1:
        {
            tryb_gry=1;
            sztuczna.kogo_kolej=false;
            QWidget::setWindowTitle("Aktualny ruch: Kółko");
            break;
        }
        case 2:
        {
            sztuczna.kogo_kolej=false;
            QWidget::setWindowTitle("Komputer vs Komputer");
            cpuvscpu=true;
            break;
        }
    }

}

Mapa::~Mapa()
{
    delete ui;
}


void Mapa::mousePressEvent(QMouseEvent *e)
{
    if(cpuvscpu)
        si_vs_si();
    if(tryb_gry==0)
    {
        sztuczna.zerowanie();
        ui->label_info->setText(" ");
        int kolumna=e->x()/111;
        int wiersz=e->y()/111;
        int pole=kolumna+wiersz*3;
        if(sztuczna.plansza[pole]!=5)
        {
            ui->label_info->setText("Wybrane pole jest już zajęte! Spróbuj ponownie.");

        }
        else
        {
            Namaluj(pole);
            ui->label_info->setText("Wybrano pole nr: " + QString::number(pole));
            sztuczna.plansza[pole]=1;
            sztuczna.plansza_zastepcza[pole]=1;
            sztuczna.kogo_kolej=false;
            //si_vs_si();

            wynik_gry();

            //ruch komputera
            sztuczna.Minimaks(sztuczna.plansza, sztuczna.kogo_kolej, sztuczna.wartosc_mozliwosci, sztuczna.plansza_zastepcza, sztuczna.wsk);
            pole=sztuczna.Decyzja(sztuczna.plansza,sztuczna.wartosc_mozliwosci,sztuczna.wsk);
            Namaluj(pole);
            ui->label_info->setText("Komputer wybrał pole nr: " + QString::number(pole));
            sztuczna.kogo_kolej=true;

            wynik_gry();

        }
    }
    else if(tryb_gry==1)
    {
        sztuczna.zerowanie();
        ui->label_info->setText(" ");

        int kolumna=e->x()/111;
        int wiersz=e->y()/111;
        int pole=kolumna+wiersz*3;
        if(sztuczna.plansza[pole]!=5)
        {
            ui->label_info->setText("Wybrane pole jest już zajęte! Spróbuj ponownie.");

        }
        else
        {
            Namaluj(pole);
            ui->label_info->setText("Wybrano pole nr: " + QString::number(pole));
            sztuczna.plansza[pole]=sztuczna.kogo_kolej;
            sztuczna.plansza_zastepcza[pole]=sztuczna.kogo_kolej;
            sztuczna.kogo_kolej=!sztuczna.kogo_kolej;
        }
        sztuczna.x = sztuczna.SprawdzZwyciezce(sztuczna.plansza);
        if (sztuczna.x == 0)
        {
            ui->label_info->setText("Remis!");
            QMessageBox::information(this,"Koniec gry","Remis!.");
            QCoreApplication::exit();
        }
        else if (sztuczna.x == 10)
        {
            ui->label_info->setText("Wygrywa kółko!");
            QMessageBox::information(this,"Koniec gry","Wygrywa kółko!.");
            QCoreApplication::exit();
        }
        else if (sztuczna.x == -10)
        {
            ui->label_info->setText("Wygrywa krzyżyk!");
            QMessageBox::information(this,"Koniec gry","Wygrywa krzyżyk!.");
            QCoreApplication::exit();
        }
        if(!sztuczna.kogo_kolej)
            QWidget::setWindowTitle("Aktualny ruch: Kółko");
        else
            QWidget::setWindowTitle("Aktualny ruch: Krzyżyk");
    }


}

void Mapa::si_vs_si()
{
    int pole=0;
    for(int i=0; i<9;i++)
    {

        sztuczna.zerowanie();
        ui->label_info->setText(" ");
        if(sztuczna.kogo_kolej)
        {
            sztuczna.Minimaks(sztuczna.plansza, sztuczna.kogo_kolej, sztuczna.wartosc_mozliwosci, sztuczna.plansza_zastepcza, sztuczna.wsk,sztuczna.kogo_kolej);
            pole=sztuczna.Decyzja(sztuczna.plansza,sztuczna.wartosc_mozliwosci,sztuczna.wsk);
        }
        else
        {
            sztuczna.Minimaks(sztuczna.plansza, sztuczna.kogo_kolej, sztuczna.wartosc_mozliwosci, sztuczna.plansza_zastepcza, sztuczna.wsk);
            pole=sztuczna.Decyzja(sztuczna.plansza,sztuczna.wartosc_mozliwosci,sztuczna.wsk);
        }
        Namaluj(pole);
        qApp->processEvents();
        QThread::msleep(1000);
        ui->label_info->setText("Komputer wybrał pole nr: " + QString::number(pole));
        sztuczna.kogo_kolej=!sztuczna.kogo_kolej;

        sztuczna.x = sztuczna.SprawdzZwyciezce(sztuczna.plansza);
        if (sztuczna.x == 0)
        {
            ui->label_info->setText("Remis!");
            QMessageBox::information(this,"Koniec gry","Remis!.");
            QCoreApplication::exit();
        }
        else if (sztuczna.x == 10)
        {
            ui->label_info->setText("Wygrywa komputer!");
            QMessageBox::information(this,"Koniec gry","Wygrywa Kółko!.");
            QCoreApplication::exit();
        }
        else if (sztuczna.x == -10)
        {
            ui->label_info->setText("Wygrywa gracz!");
            QMessageBox::information(this,"Koniec gry","Wygrywa Krzyżyk!.");
            QCoreApplication::exit();
        }

    }
}

void Mapa::Namaluj(int pole)
{
    if(sztuczna.kogo_kolej)
        pix=krzyzyk;
    else
        pix=kolko;

    switch (pole)
    {
        case 0: ui->label_0->setPixmap(pix.scaled(100,100,Qt::KeepAspectRatio)); break;
        case 1: ui->label_1->setPixmap(pix.scaled(100,100,Qt::KeepAspectRatio)); break;
        case 2: ui->label_2->setPixmap(pix.scaled(100,100,Qt::KeepAspectRatio)); break;
        case 3: ui->label_3->setPixmap(pix.scaled(100,100,Qt::KeepAspectRatio)); break;
        case 4: ui->label_4->setPixmap(pix.scaled(100,100,Qt::KeepAspectRatio)); break;
        case 5: ui->label_5->setPixmap(pix.scaled(100,100,Qt::KeepAspectRatio)); break;
        case 6: ui->label_6->setPixmap(pix.scaled(100,100,Qt::KeepAspectRatio)); break;
        case 7: ui->label_7->setPixmap(pix.scaled(100,100,Qt::KeepAspectRatio)); break;
        case 8: ui->label_8->setPixmap(pix.scaled(100,100,Qt::KeepAspectRatio)); break;

    }

}

void Mapa::wynik_gry()
{
    sztuczna.x = sztuczna.SprawdzZwyciezce(sztuczna.plansza);
    if (sztuczna.x == 0)
    {
        ui->label_info->setText("Remis!");
        QMessageBox::information(this,"Koniec gry","Remis!.");
        QCoreApplication::exit();
    }
    else if (sztuczna.x == 10)
    {
        ui->label_info->setText("Wygrywa komputer!");
        QMessageBox::information(this,"Koniec gry","Wygrywa komputer!.");
        QCoreApplication::exit();
    }
    else if (sztuczna.x == -10)
    {
        ui->label_info->setText("Wygrywa gracz!");
        QMessageBox::information(this,"Koniec gry","Wygrywa gracz!.");
        QCoreApplication::exit();
    }
}
