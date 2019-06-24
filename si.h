#ifndef SI_H
#define SI_H


class SI
{
public:
    SI();
    ~SI();
    //int * plansza = new int[9];
    int * wsk = new int[2];
    int * wartosc_mozliwosci = new int[1000];
    //int * plansza_zastepcza = new int[9];
    int plansza[9];
    int plansza_zastepcza[9];
    int x = 0;
    bool kogo_kolej=false;
    int Decyzja(int plansza_x[], int wartosc_mozliwosci[], int wsk[]);
    int Minimalizacja(int plansza_zastepcza[], short kogo_kolej, int wartosc_mozliwosci[],int wsk[]);
    int Maksymalizacja(int plansza_zastepcza[],short kogo_kolej, int wartosc_mozliwosci[],int wsk[]);
    int SprawdzZwyciezce(int plansza[]);
    void Minimaks(int plansza[], short kogo_kolej, int wartosc_mozliwosci[], int plansza_zastepcza[], int wsk[]);
    int ile_sciezek(int x_plansza[]);
    void zerowanie();
    int Minimalizacja(int plansza_zastepcza[], short kogo_kolej, int wartosc_mozliwosci[],int wsk[],int sivssi);
    int Maksymalizacja(int plansza_zastepcza[],short kogo_kolej, int wartosc_mozliwosci[],int wsk[],int sivssi);
    void Minimaks(int plansza[], short kogo_kolej, int wartosc_mozliwosci[], int plansza_zastepcza[], int wsk[],int sivssi);
    int SprawdzZwyciezce(int plansza[],int sivssi);
};

#endif // SI_H
