#ifndef CLSCLIENTES_H
#define CLSCLIENTES_H

#include<conio.h>
#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
#include<cstdlib>

using namespace std;
class ClsClientes
{
    public:
        ClsClientes(int = 0, string = "", string = "", int = 0, string = "");
        virtual ~ClsClientes();

        void mestablecerId(int);
        int mobtenerId()const;

        void mestablecerNombreCliente(string);
        string mobtenerNombreCliente()const;

        void mestablecerApellidoCliente(string);
        string mobtenerApellidoCliente()const;

        void mestablecerTelefono(int);
        int mobtenerTelefono()const;

        void mestablecerDireccion(string);
        string mobtenerDireccion()const;

        mmenuCliente();
        mcrearClientes();

        void nuevoCliente( fstream& );
        void consultarRegistroClientes(fstream&);
        void mostrarLineaPantallaClientes(const ClsClientes &);
        void actualizarRegistroClientes(fstream&);
        void mostrarLineaClientes( ostream&, const ClsClientes & );
        void imprimirRegistroClientes( fstream& );
        void eliminarRegistroClientes( fstream& );
        void buscarClientes( fstream& );

    protected:

    private:
        int iId;
        char cNombre[20];
        char cApellido[20];
        int iTelefono;
        char cDireccion[20];
};

#endif // CLSCLIENTES_H
