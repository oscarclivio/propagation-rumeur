#include <cstdlib>
#include <ctime>
using namespace std;

#include <cmath>

#include<iostream>
using namespace std;

#include<Imagine/Graphics.h>
using namespace Imagine;

//Initialise le générateur aléatoire
void InitRandom()
{
    srand((unsigned int)time(0));
}

//Nombre entier entre a et b
int Random(int a, int b){
    return a+(rand()%(b-a+1));
}

//Nombre arrondi au pourcent entre a et b
double RandomDouble(int a, int b){
    return double(a+(rand()%(b-a+1)))/100.;
}

//Fonction th
double th(double x){
    if (x > 50)
        return 1;
    if (x < -50)
        return -1;
    return (exp(x)-exp(-x))/(exp(x)+exp(-x));
}

//Paramètre du modèle
const double a = 5;

//Fonction x -> th(ax)
double tha(double x){
    return th(a*x);
}


//////////////////////////////////////////////////////////////////////////
// Fonction principale

const int L=70;
const int h=70;
const int c=10; //Echelle


int Xbord = (4*L)/5; //Abscisse frontière verticale
int Ybord = h/2; //Ordonnée frontière horizontale

//Classement de l'individu en sérieux, lambda, pas sérieux (resp. 1.,0.,-1.)
int categorie(int x, int y){
    if (x<Xbord)
        return 0;
    else if (y>=Ybord)
        return -1;
    else
        return 1;
}

//Copie t dans t2
void copie(double* t, double* t2){
    for (int x=0; x<L; x++){
        for (int y=0; y<h; y++){
            t2[x+L*y] = t[x+L*y];
        }
    }
}

//Affiche le tableau en rouge et bleu
void affiche(int* t){
    for (int x=0; x<L; x++){
        for (int y=0; y<h; y++){
            if (t[x+L*y] == 1)
                fillRect(c*x, c*y, c, c, BLUE);
            if (t[x+L*y] == -1)
                fillRect(c*x, c*y, c, c, RED);
            if (t[x+L*y] == 0)
                fillRect(c*x, c*y, c, c, BLACK);
        }
    }
}

//Affiche le tableau avec des intensités de rouge et de bleu
void affichen(double* t){
    for (int x=0; x<L; x++){
        for (int y=0; y<h; y++){
            if (t[x+L*y] >= 0)
                fillRect(c*x, c*y, c, c, Color(0,0,255*t[x+L*y]));
            else
                fillRect(c*x, c*y, c, c, Color(-t[x+L*y]*255,0,0));
        }
    }
    drawLine(Xbord*c,0,Xbord*c,h*c,GREEN);
    drawLine(Xbord*c,Ybord*c,L*c,Ybord*c,GREEN);
    //drawLine((Xbord+Ybord-h)*c,h*c,L*c,(Ybord+Xbord-L)*c,RED);
}

int main(){

    double* e = new double[L*h]; //"opinion continue"
    double* e2 = new double[L*h]; //"sauvegarde mémoire"

    int* opinion = new int[L*h];

    openWindow(c*L, c*h);

/*
 //PREMIER CAS: DEUX CAMPS FACE A FACE

//Initialisation de e


    double* influence = new double[L*h];

    for (int x=0; x<L; x++){
        //Ici, cas bateau où deux camps opposés aux deux bords horizontaux du tableau mais possibilité de faire moins trivial
        e[x] = 1.;
        e[x+L*(h-1)] = -1.;
        opinion[x] = 1;
        opinion[x+L*(h-1)] = -1;
        for (int y=1; y<h-1; y++){
            e[x+L*y] = 0.;
            opinion[x+L*y] = 0;
        }
    }

    //Initialisation des influences
    for (int x=0; x<L; x++){
        for (int y=0; y<h; y++){
            influence[x+L*y] = 0.5;
        }
    }

    InitRandom();

    //Propagation avec tout le temps des interactions
    for (int t=0; t<10000; t++){
        copie(e, e2); //Pb: interactions en meme temps ?
        for (int x=0; x<L; x++){
            for (int y=0; y<h; y++){ //4 voisins
                double S = 0;
                S += e2[x+L*y]; //équivaut à sa propre influence égale à 1
                if (x < L-1)
                    S += influence[x+1+L*y]*e2[x+1+L*y];
                if (x > 0)
                    S += influence[x-1+L*y]*e2[x-1+L*y];
                if (y < h-1)
                    S += influence[x+L*(y+1)]*e2[x+L*(y+1)];
                if (y > 0)
                    S += influence[x+L*(y-1)]*e2[x+L*(y-1)];
                e[x+L*y] = tha(S);
                if (e[x+L*y]>0.5)
                    opinion[x+L*y] = 1;
                else if (e[x+L*y]<-0.5)
                    opinion[x+L*y] = -1;
                else
                    opinion[x+L*y] = 0;
            }
        }
            affichen(e);
            milliSleep(50);
            click();
    }
    //FIN DU PREMIER CAS
    */


        //SECOND CAS: RUMEUR QUI PART D'UN POINT ET TROIS CATEGORIES

        InitRandom();

        double* influence = new double[L*L*h*h];


        //Initialisation de e
        for (int x=0; x<L; x++)
            for (int y=0; y<h; y++){
                e[x+L*y] = 0.;
                opinion[x+L*y] = 0;
            }
        //Différents points de départs, choisir deux lignes consécutives e = ..., opinion = ...
        //e[Xbord-5+L*(Ybord+1)] = 1.;
        //opinion[Xbord-5+L*(Ybord+1)] = 1;
        e[Xbord-5+L*(Ybord/2)] = 1.;
        opinion[Xbord/4+L*(Ybord/2)] = 1;
        //e[(3*Xbord)/4+L*((Ybord))] = 1.;
        //opinion[(3*Xbord)/4+L*((Ybord))] = 1;
        //e[Xbord-1+L*((3*Ybord)/2)] = 1.;
        //opinion[Xbord-1+L*((3*Ybord)/2)] = 1;
        //e[Xbord+L*((1*Ybord)/2)] = 1.;
        //opinion[Xbord+L*((1*Ybord)/2)] = 1;
        //e[L-1+L*((Ybord)/2+10)] = 1.;
        //opinion[L-1+L*((Ybord)/2+10)] = 1;
        //e[L-1] = 1.;
        //opinion[L-1] = 1;
        //e[L*(Ybord-1)] = 1.;
        //opinion[L*(Ybord-1)] = 1;
        //e[Xbord/2+L*((3*Ybord)/4)] = 1.;
        //opinion[Xbord/2+L*((3*Ybord)/4)] = 1;
        //e[L*h-1] = 1.;
        //opinion[L*h-1] = 1;

        //Initialisation de l'influence...
        for (int x=0; x<L; x++)
            for (int y=0; y<h; y++)
                    for (int x2=0; x2<L; x2++)
                        for (int y2=0; y2<h; y2++){
                            if (categorie(x,y)==categorie(x2,y2)) //Meme catégorie
                                if (categorie(x,y) == 0)
                                    influence[x+L*y+L*h*(x2+L*y2)] = RandomDouble(0,100);
                                else
                                    influence[x+L*y+L*h*(x2+L*y2)] = RandomDouble(0,100);
                            else if (categorie(x,y)==0 && categorie(x2,y2) == 1) //Lambda / Serieux
                                influence[x+L*y+L*h*(x2+L*y2)] = RandomDouble(50,100);
                            else if (categorie(x,y)==0 && categorie(x2,y2) == -1) //Lambda / Non-Serieux
                                influence[x+L*y+L*h*(x2+L*y2)] = RandomDouble(-50,50);
                            else if (categorie(x,y)==1 && categorie(x2,y2) == 0) //Serieux / Lambda
                                influence[x+L*y+L*h*(x2+L*y2)] = RandomDouble(-50,50);
                            else if (categorie(x,y)==1 && categorie(x2,y2) == -1) //Serieux / Non-Serieux
                                influence[x+L*y+L*h*(x2+L*y2)] = RandomDouble(-100,-50);
                            else if (categorie(x,y)==-1 && categorie(x2,y2) == 0) //Non-Serieux / Lambda
                                influence[x+L*y+L*h*(x2+L*y2)] = RandomDouble(0,50);
                            else if (categorie(x,y)==-1 && categorie(x2,y2) == 1) //Non-Serieux / Serieux
                                influence[x+L*y+L*h*(x2+L*y2)] = RandomDouble(-50,50);
                        }


        affichen(e);
        milliSleep(50);
        click();

        //Propagation avec tout le temps des interactions
        for (int t=0; t<10000; t++){
            copie(e, e2);
            for (int x=0; x<L; x++)
                for (int y=0; y<h; y++){
                    double S=0;
                    if (x>0){
                        S += influence[x+L*y+L*h*(x-1+L*y)]*e2[x-1+L*y];
                        if (y>0)
                            S += influence[x+L*y+L*h*(x-1+L*(y-1))]*e2[x-1+L*(y-1)];
                        if (y<L-1)
                            S += influence[x+L*y+L*h*(x-1+L*(y+1))]*e2[x-1+L*(y+1)];
                    }
                    if (x<L-1){
                        S += influence[x+L*y+L*h*(x+1+L*y)]*e2[x+1+L*y];
                        if (y>0)
                            S += influence[x+L*y+L*h*(x+1+L*(y-1))]*e2[x+1+L*(y-1)];
                        if (y<L-1)
                            S += influence[x+L*y+L*h*(x+1+L*(y+1))]*e2[x+1+L*(y+1)];
                    }
                    if (y>0)
                        S += influence[x+L*y+L*h*(x+L*(y-1))]*e2[x+L*(y-1)];
                    if (y<L-1)
                        S += influence[x+L*y+L*h*(x+L*(y+1))]*e2[x+L*(y+1)];
                    e[x+L*y] = tha(S);
                    if (e[x+L*y]>0.5)
                        opinion[x+L*y] = 1;
                    else if (e[x+L*y]<-0.5)
                        opinion[x+L*y] = -1;
                    else
                        opinion[x+L*y] = 0;
                }
            if (t%10){
                affichen(e);
                milliSleep(50);}
        }

    //FIN DU SECOND CAS

    delete[] e;
    delete[] e2;
    delete[] opinion;
    delete[] influence;
    endGraphics();
    return 0;
}
