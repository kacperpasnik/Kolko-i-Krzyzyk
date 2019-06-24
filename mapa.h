#ifndef MAPA_H
#define MAPA_H

#include <QDialog>
#include <QPainter>
#include <QPixmap>
#include <QMouseEvent>
#include "si.h"
#include <qmessagebox.h>
#include <QApplication>
#include <QThread>


namespace Ui {
class Mapa;
}

class Mapa : public QDialog
{
    Q_OBJECT

public:
    explicit Mapa(QWidget *parent = nullptr, bool kto_pierwszy=false,int graczvsgracz=0);
    ~Mapa();

private:
    Ui::Mapa *ui;
    QPainter *painter;
    void mousePressEvent(QMouseEvent *e);
    QPixmap pix;
    QString kolko=":/ikony/img/O.png";
    QString krzyzyk=":/ikony/img/X.png";
    SI sztuczna;
    void Namaluj(int);
    int tryb_gry=0;
    void si_vs_si();
    bool cpuvscpu=false;
    void wynik_gry();

};

#endif // MAPA_H
