#include "ClsClientes.h"

#include<conio.h>
#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
#include<cstdlib>
#include<ctime>
#include<string.h>

ClsClientes::ClsClientes(int valorId, string txtNombre, string txtApellido, int valorTel, string txtDirec)
{
    //ctor
    mestablecerId(valorId);
    mestablecerNombreCliente(txtNombre);
    mestablecerApellidoCliente(txtApellido);
    mestablecerTelefono(valorTel);
    mestablecerDireccion(txtDirec);
}

int ClsClientes::mobtenerId() const
{
    return iId;
}

void ClsClientes::mestablecerId (int ienteroId)
{
    iId = ienteroId;
}

string ClsClientes::mobtenerNombreCliente() const
{
    return cNombre;
}

void ClsClientes::mestablecerNombreCliente( string scadenaNombreCliente )
{
   const char *svalorNombreCliente = scadenaNombreCliente.data();
   int ilongitud = strlen( svalorNombreCliente );
   ilongitud = ( ilongitud < 20 ? ilongitud : 19 );
   strncpy( cNombre, svalorNombreCliente, ilongitud );

   cNombre[ ilongitud ] = '\0';
}

string ClsClientes::mobtenerApellidoCliente() const
{
    return cApellido;
}

void ClsClientes::mestablecerApellidoCliente( string scadenaApellidoCliente )
{
   const char *svalorApellidoCliente = scadenaApellidoCliente.data();
   int ilongitud = strlen( svalorApellidoCliente );
   ilongitud = ( ilongitud < 20 ? ilongitud : 19 );
   strncpy( cApellido, svalorApellidoCliente, ilongitud );

   cApellido[ ilongitud ] = '\0';
}

int ClsClientes::mobtenerTelefono() const
{
    return iTelefono;
}

void ClsClientes::mestablecerTelefono (int ienteroTelefono)
{
    iTelefono = ienteroTelefono;
}

string ClsClientes::mobtenerDireccion() const
{
    return cDireccion;
}

void ClsClientes::mestablecerDireccion( string scadenaDireccion )
{
   const char *svalorDireccion = scadenaDireccion.data();
   int ilongitud = strlen( svalorDireccion );
   ilongitud = ( ilongitud < 20 ? ilongitud : 19 );
   strncpy( cDireccion, svalorDireccion, ilongitud );

   cDireccion[ ilongitud ] = '\0';
}


ClsClientes::mcrearClientes()
{
    ofstream archivoClientes("RegistrosClientes.dat", ios::out | ios::binary);
    if(!archivoClientes)
    {
        cerr<<"No se habrio el archivo"<<endl;
        exit(1);
    }
    ClsClientes ClientesEnBlanco;
    for(int i=0; i<100; i++)
    {
        archivoClientes.write(reinterpret_cast<const char * > (&ClientesEnBlanco), sizeof(ClsClientes));
    }
}

ClsClientes::mmenuCliente()
{
    int iseleccionMenuClientes;
    do
    {
        system("cls");
        // abrir el archivo en modo de lectura y escritura
        fstream archivoClientes("RegistrosClientes.dat", ios::in | ios::out | ios::binary);
        // salir del programa si fstream no puede abrir el archivo
        if ( !archivoClientes )
            {
                cerr << "No se pudo abrir el archivo." << endl;
                mcrearClientes();
                cout <<  "Archivo creado satisfactoriamente, pruebe de nuevo";
                exit ( 1 );

            }
        cout<<"-------------------------------"<<endl;
        cout<<"|SISTEMA GESTION DEPARTAMENTOS|"<<endl;
        cout<<"-------------------------------"<<endl;
        cout<<"1. Ingreso Departamento"<<endl;
        cout<<"2. Despliegue Departamentos"<<endl;
        cout<<"3. Modifica Departamento"<<endl;
        cout<<"4. Imprimir Regisro de Departamentos"<<endl;
        cout<<"5. Borra Departamento"<<endl;
        cout<<"6. Buscar Departamento"<<endl;
        cout<<"0. Volver al menu superior"<<endl;
        cout<<"-------------------------------"<<endl;
        cout<<"Opcion a escoger:[1/2/3/4/5/6/0]"<<endl;
        cout<<"------------------------------"<<endl;
        cout<<"Ingresa tu Opcion: ";
        cin>>iseleccionMenuClientes;
        switch(iseleccionMenuClientes)
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
        case 4:
            {
            }
            break;
        case 5:
            {
            }
            break;
        case 6:
            {
            }
            break;
        case 0:
            {
            }
            break;
        default:
            cout<<"Opción invalida, intenta de nuevo";
            getch();
            break;
        }
    }while(iseleccionMenuClientes!=0);
}

ClsClientes::~ClsClientes()
{
    //dtor
}
