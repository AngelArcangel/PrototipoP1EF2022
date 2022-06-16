#ifndef CLSPRODUCTOS_H
#define CLSPRODUCTOS_H

#include<conio.h>
#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
#include<cstdlib>

using namespace std;

class ClsProductos
{
    public:
        ClsProductos( int = 0, string = "", string = "", int = 0);
        virtual ~ClsProductos();

        void mestablecerId(int);
        int mobtenerId()const;

        void mestablecerNombreProducto(string);
        string mobtenerNombreProducto()const;

        void mestablecerMarca(string);
        string mobtenerMarca()const;

        void mestablecerExistencia(int);
        int mobtenerExistencia()const;

        mmenuProductos();
        mcrearProductos();

        void nuevoProducto( fstream& );
        void consultarRegistroProducto(fstream&);
        void mostrarLineaPantallaProductos(const ClsProductos &);
        void actualizarRegistroProductos(fstream&);
        void mostrarLineaProductos( ostream&, const ClsProductos & );
        void imprimirRegistroProductos( fstream& );
        void eliminarRegistroProductos( fstream& );
        void buscarProductos( fstream& );

    protected:

    private:
        int iId;
        char cNombre[20];
        char cMarca[20];
        int iExistencia;
};

#endif // CLSPRODUCTOS_H
