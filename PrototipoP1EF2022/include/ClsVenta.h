#ifndef CLSVENTA_H
#define CLSVENTA_H

#include<conio.h>
#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
#include<cstdlib>

using namespace std;

class ClsVenta
{
    public:
        ClsVenta(int = 0, string = "", string = "", int = 0, int = 0);
        virtual ~ClsVenta();

        void mestablecerId(int);
        int mobtenerId()const;

        void mestablecerNombreCliente(string);
        string mobtenerNombreCliente()const;

        void mestablecerProducto(string);
        string mobtenerProducto()const;

        void mestablecerCantidad(int);
        int mobtenerCantidad()const;

        void mestablecerPrecio(int);
        int mobtenerPrecio()const;

        mcrearVenta();
        mmenuVenta();

         void nuevoVenta( fstream& );
         void consultarRegistroVenta(fstream&);
         void mostrarLineaPantallaVenta(const ClsVenta &);
        void mostrarLineaVenta( ostream&, const ClsVenta & );
         void buscarVenta( fstream& );

    protected:

    private:
        int iId;
        char cCliente[20];
        char cProducto[20];
        int iCantidad;
        int iPrecio;
};

#endif // CLSVENTA_H
