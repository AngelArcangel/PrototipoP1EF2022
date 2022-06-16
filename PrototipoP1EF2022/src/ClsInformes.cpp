#include "ClsInformes.h"

#include<conio.h>
#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
#include<cstdlib>
#include<ctime>
#include<string.h>

using namespace std;

ClsInformes::ClsInformes()
{
    //ctor
}

ClsInformes::mmenuInformes()
{
    int imenuInformes=0;

    //Menu catalogo
    do
    {
        system("cls");

        cout<<"--------------------------------"<<endl;
        cout<<"|-------SISTEMA INFORMES-------|"<<endl;
        cout<<"--------------------------------"<<endl;
        cout<<"1. "<<endl;
        cout<<"2. IMPRIMIR REGISTRO INFORMES"<<endl;
        cout<<"0. EXIT"<<endl;

        cout<<"-------------------------------"<<endl;
        cout<<"OPCIONES A ESCOGER :     [1/2/3/0]"<<endl;
        cout<<"-------------------------------"<<endl;
        cout<<"INGRESA TU OPCION : ";
        cin>>imenuInformes;
        switch (imenuInformes)
        {
            case 1:
                {

                }
                break;
            case 2:
                {

                }
                break;
            case 3:
                {

                }
                break;
            case 0:
                {

                }
                break;
            default:
                cout<<"Valor ingresado no vádido, intente de nuevo";
                getch();
                break;
        }
    }while(imenuInformes!=0);
}

ClsInformes::~ClsInformes()
{
    //dtor
}
