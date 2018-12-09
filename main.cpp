#include <iostream>
#include<cmath>
#include<fstream>
#include<cstdlib>
#include<iomanip>
#include "funkcije.hpp"
#include "svg.hpp"

using namespace std;


int main()
{
    int brstud=brojlinija();
    int proj=0,lab=0, parc=0, zavr=0,brocjena=6;
    string ime[brstud], prezime[brstud], pol[brstud], smjer[brstud];
    int bodproj[brstud], bodlab[brstud], bodparc[brstud],bodzavr[brstud];
    int zavrsneocjene[brstud], sortzavrsneocjene[brstud];
    int ocjeneM[brocjena]={0,0,0,0,0,0},ocjeneZ[brocjena]={0,0,0,0,0,0},distribuiran[brocjena]={0,0,0,0,0,0};
    int ocjeneTKN[brocjena]={0,0,0,0,0,0},ocjenePM[brocjena]={0,0,0,0,0,0},ocjeneMI[brocjena]={0,0,0,0,0,0},ocjeneO[brocjena]={0,0,0,0,0,0},ocjeneMN[brocjena]={0,0,0,0,0,0};

    ifstream fin;
    fin.open("Spisak.txt", ios::app);
    if(fin.fail())
        exit(1);
    fin>>proj>>lab>>parc>>zavr;
    for(int i=0; i<brstud; i++)
        fin>>ime[i]>>prezime[i]>>pol[i]>>smjer[i]>>bodproj[i]>>bodlab[i]>>bodparc[i]>>bodzavr[i];
    fin.close();
    int brM=brojM(pol, brstud);
    int brZ=brstud-brM;
    cout<<endl<<"Broj studenata je na ovom kursu je: "<<brstud<<" -"<<setw(3)<<brM<<" muskog  i "<<setw(3)<<brZ<<" zenskog spola."<<endl<<endl;
    cin.get();
    /*
    cout<<"Suma bodova i zavrsna ocjena po studentu je:"<<endl;
    for(int i=0; i<brstud; i++)
        cout<<i+1<<". "<<suma[i]<<" i ocjena je: "<<zavrsneocjene[i]<<endl;
        */

    bodovi(bodproj, bodlab, bodparc, bodzavr, brstud,proj, lab, parc, zavr);
    zavrsnaocjena(suma, zavrsneocjene, bodzavr, brstud);
    for(int i=0; i<brstud; i++)
        sortzavrsneocjene[i]=zavrsneocjene[i];
    sortirajniz(sortzavrsneocjene, brstud);
    distribucija(zavrsneocjene,distribuiran, brstud);
    distribucijapol(zavrsneocjene,ocjeneM,ocjeneZ,pol,brstud);
    distribucijasmjer(zavrsneocjene,smjer,ocjeneTKN,ocjenePM,ocjeneMI, ocjeneO, ocjeneMN, brstud);
    ukupna(distribuiran),ukupnapopolovima(ocjeneM, ocjeneZ),ukupnoposmjerovima(ocjeneTKN,ocjenePM, ocjeneMN, ocjeneMI, ocjeneO);
    scatterplot(bodparc,bodzavr, brstud);


    cout<<"OCJENE"<<setw(5)<<"SUM"<<setw(15)<<"MALE  FEMALE"<<setw(15)<<"  TKN PM MI  O MN"<<endl;
    for(int i=0; i<brocjena; i++)
    {
        cout<<setw(4)<<i+5<<setw(6)<< distribuiran[i]<<setw(7)<< ocjeneM[i]<<setw(7)<<ocjeneZ[i];
        cout<<setw(7)<<ocjeneTKN[i]<<setw(3)<<ocjenePM[i]<<setw(3)<<ocjeneO[i]<<setw(3)<<ocjeneMI[i]<<setw(3)<<ocjeneMN[i]<<endl;
    }
    cin.get();
    cout<<"Aritmeticka sredina ocjena "<<setw(28)<<aritmetickasredina(zavrsneocjene, brstud)<<endl;
    cout<<"Modus zavrsnih ocjena "<<setw(33);
    modus(distribuiran, brocjena);
    cout<<endl<<"Medijana zavrsnih ocjena "<<setw(30)<<medijana(sortzavrsneocjene, brstud)<<endl;
    cout<<"Varijansa zavrsnih ocjena "<<setw(29)<<varijansa(zavrsneocjene, brstud)<<endl;
    cout<<"Standardna devijacija ocjena "<<setw(26)<<standdevijacija(zavrsneocjene, brstud)<<endl;
    cout<<"Kovarijansa bod zavrsnog i parcijalnog ispita "<<setw(9)<<kovarijansa(bodzavr,bodparc, brstud)<<endl;
    cout<<"Korelacija bod zavrsnog i parcijalnog ispita "<<setw(10)<<korelacija(bodzavr,bodparc, brstud);
    cout<<"unesite rijec"<<endl;
    cin.get();
    otvaranje();

    return 0;
}
