#ifndef CLSPROVEEDORES_H
#define CLSPROVEEDORES_H

#include<conio.h>
#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
#include<cstdlib>

using namespace std;

class ClsProveedores
{
    public:
        ClsProveedores(int =0, string ="", string ="", int =0);
        virtual ~ClsProveedores();

        void mestablecerId(int);
        int mobtenerId()const;

        void mestablecerNombreProveedor(string);
        string mobtenerNombreProveedor()const;

        void mestablecerDireccion(string);
        string mobtenerDireccion()const;

        void mestablecerTelefono(int);
        int mobtenerTelefono()const;

        mmenuProveedores();
        mcrearProveedores();

        void nuevoProveedor( fstream& );
        void consultarRegistroProveedores(fstream&);
        void mostrarLineaPantallaProveedores(const ClsProveedores &);
        void actualizarRegistroProveedores(fstream&);
        void mostrarLineaProveedores( ostream&, const ClsProveedores & );
        void imprimirRegistroProveedores( fstream& );
        void eliminarRegistroProveedores( fstream& );
        void buscarProveedores( fstream& );

    protected:

    private:
        int iId;
        char cNombre[20];
        char cDireccion[20];
        int iTelefono;
};

#endif // CLSPROVEEDORES_H
