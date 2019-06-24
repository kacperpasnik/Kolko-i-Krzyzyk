#include "si.h"

SI::SI()
{
    for (int i = 0; i < 9; i++)
        plansza[i] = 5;
    wsk[0] = 0; wsk[1] = 0;
    for (int i = 0; i < 1000; i++)
        wartosc_mozliwosci[i] = -100;
    for (int i = 0; i < 9; i++)
        plansza_zastepcza[i] = plansza[i];

}

SI::~SI()
{

    delete[] wartosc_mozliwosci;

    delete[] wsk;
}

void SI::Minimaks(int plansza[], short kogo_kolej, int wartosc_mozliwosci[], int plansza_zastepcza[], int wsk[])
{

    for (int i = 0; i<9; i++)
    {
        if (plansza[i] == 5)
        {
            if (kogo_kolej == 0)
            {
                plansza_zastepcza[i] = 0;
                wsk[0]++;
                wartosc_mozliwosci[wsk[0]] = Minimalizacja(plansza_zastepcza, kogo_kolej, wartosc_mozliwosci,wsk);
                plansza_zastepcza[i] = 5;
            }
            else
            {
                plansza_zastepcza[i] = 1;
                wsk[0]++;
                wartosc_mozliwosci[wsk[0]] = Maksymalizacja(plansza_zastepcza, kogo_kolej, wartosc_mozliwosci, wsk);
                plansza_zastepcza[i] = 5;
            }

        }

    }

}

int SI::SprawdzZwyciezce(int plansza[])
{

    for (int i = 0, remis = 0; i<7; i++)
    {
        if ((plansza[i] != 5 && plansza[i + 1] != 5) && plansza[i + 2] != 5)
            remis++;
        if ((i == 0 || i == 6) && (plansza[i] == plansza[i + 1] && plansza[i] == plansza[i + 2]))
        {
            if (plansza[i] == 0)
                return 10;
            else if (plansza[i] == 1)
                return -10;
            else
                continue;
        }
        else if ((i == 0 || i == 2) && (plansza[i] == plansza[i + 3] && plansza[i] == plansza[i + 6]))
        {
            if (plansza[i] == 0)
                return 10;
            else if (plansza[i] == 1)
                return -10;
            else
                continue;
        }
        else if (i != 4 && (plansza[i] == plansza[4]) && (plansza[i] == plansza[8 - i]))
        {
            if (plansza[i] == 0)
                return 10;
            else if (plansza[i] == 1)
                return -10;
            else
                continue;
        }
        else if (remis == 7)
        {
            return 0;
        }
    }
    return -100;
}

int SI::Decyzja(int plansza_x[], int wartosc_mozliwosci[], int wsk[])
{
    int najwyzsza_wartosc = wartosc_mozliwosci[wsk[0]], j[10] = { 0,0,0,0,0,0,0,0,0,0 },a=1, ile_opcji=ile_sciezek(plansza_x);
    for (int i = 0; i < 9; i++)
    {
        if (plansza_x[i] == 5)
        {
            j[a] = i;
            a++;
        }
    }
    a = j[wsk[0]];
    for (ile_opcji; ile_opcji>0; ile_opcji--)
    {
        if (wartosc_mozliwosci[wsk[0] - ile_opcji] > najwyzsza_wartosc)
        {
            najwyzsza_wartosc = wartosc_mozliwosci[wsk[0] - ile_opcji];
            a = j[wsk[0] - ile_opcji];
        }

    }
    if(!kogo_kolej)
        plansza_x[a] = 0;
    else
        plansza_x[a]=1;

    return a;

}

int SI::Minimalizacja(int plansza_zastepcza[], short kogo_kolej, int wartosc_mozliwosci[],int wsk[])
{
    kogo_kolej = true;
    int wartosc_zastepcza = SprawdzZwyciezce(plansza_zastepcza);
    if (wartosc_zastepcza == -10 || wartosc_zastepcza == 0 || wartosc_zastepcza == 10)
        return wartosc_zastepcza;
    else
        Minimaks(plansza_zastepcza, kogo_kolej, wartosc_mozliwosci, plansza_zastepcza,wsk);
    int wartosc = wartosc_mozliwosci[wsk[0]];
    int ile_opcji = ile_sciezek(plansza_zastepcza);
    for (int i = 1; i<ile_opcji; i++)
    {
        if (wartosc_mozliwosci[wsk[0] - i] < wartosc)
            wartosc = wartosc_mozliwosci[wsk[0] - i];
    }
    if (wsk[0]>ile_opcji)
        wsk[0] = wsk[0] - ile_opcji;
    return wartosc;

}

int SI::Maksymalizacja(int plansza_zastepcza[],short kogo_kolej, int wartosc_mozliwosci[],int wsk[])
{
    kogo_kolej = false;
    int wartosc_zastepcza = SprawdzZwyciezce(plansza_zastepcza);
    if (wartosc_zastepcza == -10 || wartosc_zastepcza == 0 || wartosc_zastepcza == 10)
        return wartosc_zastepcza;
    else
        Minimaks(plansza_zastepcza, kogo_kolej, wartosc_mozliwosci, plansza_zastepcza, wsk);
    int wartosc = wartosc_mozliwosci[wsk[0]];
    int ile_opcji = ile_sciezek(plansza_zastepcza);
    for (int i=1;i<ile_opcji;i++)
    {
        if (wartosc_mozliwosci[wsk[0] - i] > wartosc)
            wartosc = wartosc_mozliwosci[wsk[0] - i];
    }
    if (wsk[0]>ile_opcji)
        wsk[0] = wsk[0] - ile_opcji;
    return wartosc;

}

int SI::ile_sciezek(int x_plansza[])
{
    int x = 0;
    for (int i = 0; i < 9; i++)
    {
        if (x_plansza[i] == 5)
            x++;
    }
    return x;
}

void SI::zerowanie()
{
    wsk[0] = 0; wsk[1] = 0;
    for (int i = 0; i < 1000; i++)
        wartosc_mozliwosci[i] = -100;
    for (int i = 0; i < 9; i++)
        plansza_zastepcza[i] = plansza[i];
}

int SI::Minimalizacja(int plansza_zastepcza[], short kogo_kolej, int wartosc_mozliwosci[],int wsk[],int sivssi)
{
    /*if(sivssi==0)
        kogo_kolej = true;
    else
        kogo_kolej=false;*/
    kogo_kolej=0;
    int wartosc_zastepcza = SprawdzZwyciezce(plansza_zastepcza,sivssi);
    if (wartosc_zastepcza == -10 || wartosc_zastepcza == 0 || wartosc_zastepcza == 10)
        return wartosc_zastepcza;
    else
        Minimaks(plansza_zastepcza, kogo_kolej, wartosc_mozliwosci, plansza_zastepcza,wsk,sivssi);
    int wartosc = wartosc_mozliwosci[wsk[0]];
    int ile_opcji = ile_sciezek(plansza_zastepcza);
    for (int i = 1; i<ile_opcji; i++)
    {
        if (wartosc_mozliwosci[wsk[0] - i] < wartosc)
            wartosc = wartosc_mozliwosci[wsk[0] - i];
    }
    if (wsk[0]>ile_opcji)
        wsk[0] = wsk[0] - ile_opcji;
    return wartosc;

}

int SI::Maksymalizacja(int plansza_zastepcza[],short kogo_kolej, int wartosc_mozliwosci[],int wsk[],int sivssi)
{
    /*if(sivssi==0)
        kogo_kolej = false;
    else
        kogo_kolej=true;*/
    kogo_kolej=1;
    int wartosc_zastepcza = SprawdzZwyciezce(plansza_zastepcza,sivssi);
    if (wartosc_zastepcza == -10 || wartosc_zastepcza == 0 || wartosc_zastepcza == 10)
        return wartosc_zastepcza;
    else
        Minimaks(plansza_zastepcza, kogo_kolej, wartosc_mozliwosci, plansza_zastepcza, wsk,sivssi);
    int wartosc = wartosc_mozliwosci[wsk[0]];
    int ile_opcji = ile_sciezek(plansza_zastepcza);
    for (int i=1;i<ile_opcji;i++)
    {
        if (wartosc_mozliwosci[wsk[0] - i] > wartosc)
            wartosc = wartosc_mozliwosci[wsk[0] - i];
    }
    if (wsk[0]>ile_opcji)
        wsk[0] = wsk[0] - ile_opcji;
    return wartosc;

}
void SI::Minimaks(int plansza[], short kogo_kolej, int wartosc_mozliwosci[], int plansza_zastepcza[], int wsk[],int sivssi)
{

    for (int i = 0; i<9; i++)
    {
        if (plansza[i] == 5)
        {
            if (kogo_kolej == 0)
            {
                plansza_zastepcza[i] = 0;
                wsk[0]++;
                wartosc_mozliwosci[wsk[0]] = Maksymalizacja(plansza_zastepcza, kogo_kolej, wartosc_mozliwosci,wsk,sivssi);
                plansza_zastepcza[i] = 5;
            }
            else
            {
                plansza_zastepcza[i] = 1;
                wsk[0]++;
                wartosc_mozliwosci[wsk[0]] = Minimalizacja(plansza_zastepcza, kogo_kolej, wartosc_mozliwosci, wsk,sivssi);
                plansza_zastepcza[i] = 5;
            }

        }

    }

}

int SI::SprawdzZwyciezce(int plansza[],int sivssi)
{

    for (int i = 0, remis = 0; i<7; i++)
    {
        if ((plansza[i] != 5 && plansza[i + 1] != 5) && plansza[i + 2] != 5)
            remis++;
        if ((i == 0 || i == 6) && (plansza[i] == plansza[i + 1] && plansza[i] == plansza[i + 2]))
        {
            if (plansza[i] == 0)
                return -10;
            else if (plansza[i] == 1)
                return 10;
            else
                continue;
        }
        else if ((i == 0 || i == 2) && (plansza[i] == plansza[i + 3] && plansza[i] == plansza[i + 6]))
        {
            if (plansza[i] == 0)
                return -10;
            else if (plansza[i] == 1)
                return 10;
            else
                continue;
        }
        else if (i != 4 && (plansza[i] == plansza[4]) && (plansza[i] == plansza[8 - i]))
        {
            if (plansza[i] == 0)
                return -10;
            else if (plansza[i] == 1)
                return 10;
            else
                continue;
        }
        else if (remis == 7)
        {
            return 0;
        }
    }
    return -100;
}
