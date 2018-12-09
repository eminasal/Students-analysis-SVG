#include<iostream>
#include "svg.hpp"

using namespace std;
using namespace svg;

const int br=100;
double suma[br];


int brojlinija()
{
    int broj = 0;
    ifstream fin("Spisak.txt");
    char znak;
    while (fin.get(znak))
    {
        if (znak == '\n')
            broj++;
    }
    return broj;
}

int maximalni(int niz[], int br)
{
    int maxi=niz[0];
    for(int i=0; i<br; i++)
    {
        if(niz[i]>maxi)
            maxi=niz[i];
    }
    return maxi;
}

int minimalni(int niz[], int br)
{
    int mini=niz[0];
    for(int i=0; i<br; i++)
    {
        if(niz[i]<mini)
            mini=niz[i];
    }
    return mini;
}

double bodovi(int niz1[], int niz2[], int niz3[], int niz4[],int brstud,int k1, int k2, int k3, int k4)
{
    for(int i=0; i<brstud; i++)
        suma[i]=(niz1[i]*k1+niz2[i]*k2+niz3[i]*k3+niz4[i]*k4)/100.0;
}


void zavrsnaocjena(double suma[], int niz[],int bodzavr[], int broj)
{
    for(int i=0; i<broj; i++)
    {
        if(suma[i]<55 || bodzavr[i]<55)
            niz[i]=5;
        else if(suma[i]<64.5 && suma[i]>=54.5)
            niz[i]=6;
        else if(suma[i]<74.5 && suma[i]>=64.5)
            niz[i]=7;
        else if(suma[i]<84.5 && suma[i]>=74.5)
            niz[i]=8;
        else if(suma[i]<94.5 && suma[i]>=84.5)
            niz[i]=9;
        else if(suma[i]<=100 && suma[i]>=94.5)
            niz[i]=10;
        else
            niz[i]=0;
    }
}


double aritmetickasredina(int niz[], int br)
{
    double suma=0;
    for(int i=0; i<br; i++)
    {
        suma=suma+niz[i];
    }
    return suma/br;
}


int sortirajniz(int niz[], int br)
{
    int temp;
    for(int i=0; i<br-1; i++)
    {
        for(int j=i; j<br; j++)
        {
            if(niz[i]>niz[j])
            {
                temp=niz[i];
                niz[i]=niz[j];
                niz[j]=temp;
            }
        }
    }
}


void modus(int niz[],int br)
{
    int maximum=niz[0];
    for(int i=0;i<br;i++)
    {
        if(niz[i]>maximum)
            maximum=niz[i];
    }
    for(int i=0;i<br;i++)
    {
        if(niz[i]==maximum)
            cout<<i+5<<" ";
    }
}



double medijana(int niz[],int duzina)
{
    double paran=(niz[duzina/2]+niz[duzina/2-1])/2.0;
    double neparan=niz[duzina/2];
    if(duzina%2==0)
        return paran;
    return neparan;
}


double varijansa(int niz[], int duzina)
{
    double xpotez=aritmetickasredina(niz, duzina);
    double suma=0;
    for(int i=0; i<duzina; i++)
    {
        suma+=pow((niz[i]-xpotez),2);
    }
    double var=(1.0/(duzina))*suma;
    return var;
}


double standdevijacija(int niz[],int duzina)
{
    return sqrt(varijansa(niz, duzina));
}


double kovarijansa(int niz1[], int niz2[],int duzina)
{
    double xpotez=aritmetickasredina(niz1, duzina);
    double ypotez=aritmetickasredina(niz2, duzina);
    double suma=0;
    for(int i=0; i<duzina; i++)
    {
        suma=suma+(niz1[i]-xpotez)*(niz2[i]-ypotez);
    }
    return suma/(duzina);
}


double korelacija(int niz1[],int niz2[], int duzina)
{
    double kor=kovarijansa(niz1, niz2, duzina)/(standdevijacija(niz1, duzina)*standdevijacija(niz2, duzina));
    return kor;
}


//DISTRIBUCIJA UKUPNIH OCJENA
void distribucija(int niz[],int nizocjena[], int br)
{
    for(int i=0; i<br; i++)
    {
        for(int j=5; j<=10; j++)
        if(niz[i]==j)
            nizocjena[j-5]++;
    }
}


//BROJ MUSKARACA
int brojM(string pol[], int broj)
{
    int brojM=0;
    for(int i=0; i<broj; i++)
    {
        if(pol[i]== "M" || pol[i]=="m" || pol[i]=="mu�ki" || pol[i]=="Mu�ki" || pol[i]=="muski" || pol[i]=="Muski")
            brojM++;
    }
    return brojM;
}


void distribucijapol(int niz[], int nizM[], int nizZ[],string pol[], int broj)
{
    for(int i=0; i<broj; i++)
    {
        for(int j=5; j<=10; j++)
        {
            if(niz[i]==j)
            {
                if(pol[i]== "M" || pol[i]=="m" || pol[i]=="mu�ki" || pol[i]=="Mu�ki" || pol[i]=="muski" || pol[i]=="Muski")
                    nizM[j-5]++;
                else //if(pol[i]== "Z" || pol[i]=="�" || pol[i]== "z" || pol[i]=="�"|| pol[i]=="�enski" || pol[i]=="�enski" || pol[i]=="zenski" || pol[i]=="zenski")
                    nizZ[j-5]++;
            }
        }
    }
}


void distribucijasmjer(int niz[], string smjer[], int TKN[],int PM[], int MI[], int O[], int MN[],int broj)
{
    for(int i=0; i<broj; i++)
    {
        for(int j=0; j<=5; j++)
        {
            if(niz[i]==j+5) //ocjena
            {
                if(smjer[i]== "TKN")
                    TKN[j]++;
                else if(smjer[i]== "PM")
                    PM[j]++;
                else if(smjer[i]== "MI")
                    MI[j]++;
                else if(smjer[i]== "O")
                    O[j]++;
                else if(smjer[i]== "MN")
                    MN[j]++;
            }
        }
    }
}




void ukupna(int niz[])
{
    Dimensions dimensions(600, 600);
    Document doc("ukupneocjene.svg", Layout(dimensions, Layout::BottomLeft));
    // Okvir slike

    Polygon border(Stroke(2, Color::Transparent));
    border<<Point(0, 0)<< Point(dimensions.width,0)<<Point(dimensions.width, dimensions.height)<<Point(0, dimensions.height);
    doc << border;

    doc << (LineChart(Dimensions(20, 20))
            <<(Polyline(Stroke(2, Color::White))
            << Point(0, 0)<<Point(20,0)<<Point(40,0)<< Point(60, 0)<<Point(80,0)<<Point(100,0)<<Point(120,0))
            <<(Polyline(Stroke(2, Color::White))
            << Point(0,0)<<Point(0,20)<<Point(0,40)<<Point(0,60)<<Point(0,80)<<Point(0,100)));

    doc<< Text(Point(58,135),"UKUPNE OCJENE", Color::Black, Font(3.5, "Verdana"));
    doc<< Text(Point(65,5),"OCJENE", Color::Black, Font(3.5, "Verdana"));
    doc<< Text(Point(7,15),"BROJ", Color::Black, Font(3, "Verdana"));
    doc<< Text(Point(2,12),"STUDENATA", Color::Black, Font(3, "Verdana"));

     //ISPISUJE OCJENE NA GRAFU
    string ocjenegraf="5 6 7 8 9 10";
    for(int i=0; i<=10; i+=2)
        doc<< Text(Point(30+i*10, 10), ocjenegraf.substr(i,2), Color::Black, Font(3 ,"Verdana"));
    string a="0 5 10152025";
    for(int i=0; i<6; i++)
        doc<< Text(Point(10,20+i*20),a.substr(i*2,2), Color::Black, Font(3, "Verdana"));
    for(int i=0; i<6; i++)
        doc<< Line(Point(30+i*20,20),Point(30+i*20,20+niz[i]*4),Stroke(3, Color::Pink));


    doc.save();
}

void ukupnapopolovima(int nizM[], int nizZ[])
{
    Dimensions dimensions(600, 600);
    Document doc("ukupneocjenepolovi.svg", Layout(dimensions, Layout::BottomLeft));
    // Okvir slike
    Polygon border(Stroke(2, Color::Transparent));
    border<<Point(0, 0)<< Point(dimensions.width,0)<<Point(dimensions.width, dimensions.height)<<Point(0, dimensions.height);
    doc << border;

    doc << (LineChart(Dimensions(20, 20))
            <<(Polyline(Stroke(2, Color::White))
            << Point(0, 0)<<Point(20,0)<<Point(40,0)<< Point(60, 0)<<Point(80,0)<<Point(100,0)<<Point(120,0))
            <<(Polyline(Stroke(2, Color::White))
            << Point(0,0)<<Point(0,20)<<Point(0,40)<<Point(0,60)<<Point(0,80)));

    doc<< Text(Point(30,130),"UKUPNA RASPODJELA OCJENA PO POLOVIMA", Color::Black, Font(3.5, "Verdana"));
    doc<< Text(Point(10,10),"OCJENE", Color::Black, Font(3, "Verdana"));
    doc<< Text(Point(5,115),"BR. STUDENATA", Color::Black, Font(3, "Verdana"));

     //ISPISUJE OCJENE NA GRAFU
    string ocjenegraf="5 6 7 8 9 10";
    for(int i=0; i<=10; i+=2)
        doc<< Text(Point(30+i*10, 10), ocjenegraf.substr(i,2), Color::Black, Font(3 ,"Verdana"));
    string a="0 5 101520";
    for(int i=0; i<5; i++)
        doc<< Text(Point(10,20+i*20),a.substr(i*2,2), Color::Black, Font(3, "Verdana"));
    string polovi="ZM";
     for(int i=0; i<2; i++)
        doc<< Text(Point(130, 80+i*5),polovi.substr(i,1), Color::Black, Font(3, "Verdana"));

    for(int i=0; i<6; i++)
    {
        doc<< Line(Point(28+i*20,20),Point(28+i*20,20+nizM[i]*4),Stroke(3, Color::Cadetblue));
        doc<< Line(Point(31+i*20,20),Point(31+i*20,20+nizZ[i]*4),Stroke(3, Color::Maroon));
    }

    doc<< Line(Point(125, 85),Point(125, 88),Stroke(3, Color::Cadetblue));
    doc<< Line(Point(125, 80),Point(125, 83),Stroke(3, Color::Maroon));


    doc.save();
}

void ukupnoposmjerovima(int nizTKN[], int nizPM[], int nizMI[], int nizO[],int  nizMN[])
{
    Dimensions dimensions(600, 600);
    Document doc("ukupneocjenesmjerovi.svg", Layout(dimensions, Layout::BottomLeft));
    // Okvir slike
    Polygon border(Stroke(2, Color::Transparent));
    border<<Point(0, 0)<< Point(dimensions.width,0)<<Point(dimensions.width, dimensions.height)<<Point(0, dimensions.height);
    doc << border;

    doc << (LineChart(Dimensions(20, 20))
            <<(Polyline(Stroke(2, Color::White))
            << Point(0, 0)<<Point(20,0)<<Point(40,0)<< Point(60, 0)<<Point(80,0)<<Point(100,0)<<Point(120,0))
            <<(Polyline(Stroke(2, Color::White))
            << Point(0,0)<<Point(0,20)<<Point(0,40)<<Point(0,60)<<Point(0,80)));

    doc<< Text(Point(30,130),"UKUPNA RASPODJELA OCJENA PO SMJEROVIMA", Color::Black, Font(3.5, "Verdana"));
    doc<< Text(Point(10,10),"OCJENE", Color::Black, Font(3, "Verdana"));
    doc<< Text(Point(5,115),"BR. STUDENATA", Color::Black, Font(3, "Verdana"));

     //ISPISUJE OCJENE NA GRAFU
    string ocjenegraf="5 6 7 8 9 10";
    for(int i=0; i<=10; i+=2)
        doc<< Text(Point(30+i*10, 10), ocjenegraf.substr(i,2), Color::Black, Font(3 ,"Verdana"));
    string a="0 5 101520";
    for(int i=0; i<5; i++)
        doc<< Text(Point(10,20+i*20),a.substr(i*2,2), Color::Black, Font(3, "Verdana"));
    string smjerovi="TKN PM MI O  MN ";
     for(int i=0; i<5; i++)
        doc<< Text(Point(130, 80+i*5),smjerovi.substr(i*3,3), Color::Black, Font(3, "Verdana"));

    for(int i=0; i<6; i++)
    {
        doc<< Line(Point(25+i*20,20),Point(25+i*20,20+nizTKN[i]*4),Stroke(3, Color::Violetred));
        doc<< Line(Point(28+i*20,20),Point(28+i*20,20+nizPM[i]*4),Stroke(3, Color::Green));
        doc<< Line(Point(31+i*20,20),Point(31+i*20,20+nizMI[i]*4),Stroke(3, Color::Cadetblue));
        doc<< Line(Point(34+i*20,20),Point(34+i*20,20+nizO[i]*4),Stroke(3, Color::Yellow));
        doc<< Line(Point(37+i*20,20),Point(37+i*20,20+nizMN[i]*4),Stroke(3, Color::Silver));
    }

    doc<< Line(Point(125, 80),Point(125, 83),Stroke(3, Color::Violetred));
    doc<< Line(Point(125, 85),Point(125, 88),Stroke(3, Color::Green));
    doc<< Line(Point(125, 90),Point(125, 93),Stroke(3, Color::Cadetblue));
    doc<< Line(Point(125, 95),Point(125, 98),Stroke(3, Color::Yellow));
    doc<< Line(Point(125, 100),Point(125, 103),Stroke(3, Color::Silver));


    doc.save();
}

void scatterplot(int bodparc[], int bodzavr[],int brstud)
{
    Dimensions dimensions(600, 600);
    Document doc("Scatterplot.svg", Layout(dimensions, Layout::BottomLeft));
   Polygon border(Stroke(2, Color::Transparent));
    border<<Point(0, 0)<< Point(dimensions.width,0)<<Point(dimensions.width, dimensions.height)<<Point(0, dimensions.height);
    doc << border;

    doc << (LineChart(Dimensions(20, 20))
            <<(Polyline(Stroke(2, Color::White))
            << Point(0, 0)<<Point(10,0)<<Point(20,0)<<Point(30,0)<<Point(40,0)<<Point(50,0)
            << Point(60,0)<<Point(70,0)<<Point(80,0)<<Point(90,0)<<Point(100,0))
            <<(Polyline(Stroke(2, Color::White))
            << Point(0,0)<<Point(0,10)<<Point(0,20)<<Point(0,30)<<Point(0,40)<<Point(0,50)
            <<Point(0,60)<<Point(0,70)<<Point(0,80)<<Point(0,90)<<Point(0,100)));


    LineChart chart(20.0);
    Polyline polyline_a(Stroke(2, Color::Transparent));
    for(int i=0; i<brstud; i++)
        polyline_a << Point(0, 0) <<Point(bodparc[i], bodzavr[i]);
    chart <<polyline_a;
    doc << chart;


    doc<< Line(Point(20+minimalni(bodparc,brstud),20+minimalni(bodzavr, brstud)),Point(20+maximalni(bodparc,brstud),20+maximalni(bodzavr, brstud)),
               Stroke(0.8, Color::Cadetblue));

    doc<< Text(Point(55,140),"Scatter plot", Color::Black, Font(4.5, "Verdana"));
    doc<< Text(Point(50,3),"Bod parcijalnog ispita", Color::Black, Font(3, "Verdana"));
    doc<< Text(Point(3,132),"Bod zavrsnog ispita", Color::Black, Font(3, "Verdana"));
    //string zavr="BOD ZAVRSNOG ISPITA";
    //string zavr="Bod zavrsnog ispita"
    //for(int i=0; i<19; i++)
       // doc<< Text(Point(2,100-i*3),zavr.substr(i,1), Color::Black, Font(3, "Verdana"));

    string a=" 10 20 30 40 50 60 70 80 90100";
    for(int i=0; i<11; i++)
    {
        doc<< Text(Point(30+10*i,10),a.substr(i*3,3), Color::Black, Font(3, "Verdana"));
        doc<< Text(Point(10,30+i*10),a.substr(i*3,3), Color::Black, Font(3, "Verdana"));
    }
    doc.save();
}

void otvaranje()
{
    char odgovor;
    cout<<endl<<"Na sljedeca pitanja odgovorite sa D(za DA) ili N(za NE)."<<endl;
    cout<<"Da li zelite pogledati dijagram ukupnih ocjena?  ";
    cin>>odgovor;
    if(odgovor=='D' || odgovor=='d')
        system("start ukupneocjene.svg");
    cout<<endl<<"Da li zelite pogledati dijagram ukupnih ocjena rasporedjenih po spolovima?  ";
    cin>>odgovor;
    if(odgovor=='D' || odgovor=='d')
        system("start ukupneocjenepolovi.svg");
    cout<<endl<<"Da li zelite pogledati dijagram ukupnih ocjena rasporedjenih po smjerovima?  ";
    cin>>odgovor;
    if(odgovor=='D' || odgovor=='d')
        system("start ukupneocjenesmjerovi.svg");
    cout<<endl<<"Da li zelite pogledati scatter plot ocjena?  ";
    cin>>odgovor;
    if(odgovor=='D' || odgovor=='d')
        system("start scatterplot.svg");
    cout<<endl<<"Hvala na paznji!"<<endl;
}


