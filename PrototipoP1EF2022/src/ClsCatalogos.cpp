#include "ClsCatalogos.h"
#include "ClsClientes.h"
#include "ClsProveedores.h"
#include "ClsProductos.h"

using namespace std;

ClsCatalogos::ClsCatalogos()
{
    //ctor
}

ClsCatalogos::mmenuCatalogos()
{
    int imenuCatalogo=0;

    //Menu catalogo
    do
    {
        system("cls");

        cout<<"---------------------------------"<<endl;
        cout<<"|-------SISTEMA CATALOGOS-------|"<<endl;
        cout<<"---------------------------------"<<endl;
        cout<<"1. CLIENTES"<<endl;
        cout<<"2. PROVEEDORES"<<endl;
        cout<<"3. PRODUCTOS"<<endl;
        cout<<"0. EXIT"<<endl;

        cout<<"-------------------------------"<<endl;
        cout<<"OPCIONES A ESCOGER :     [1/2/3/0]"<<endl;
        cout<<"-------------------------------"<<endl;
        cout<<"INGRESA TU OPCION : ";
        cin>>imenuCatalogo;
        switch (imenuCatalogo)
        {
            case 1:
                {
                    ClsClientes clientes;
                    clientes.mmenuCliente();
                }
                break;
            case 2:
                {
                    ClsProveedores proveedores;
                    proveedores.mmenuProveedores();
                }
                break;
            case 3:
                {
                    ClsProductos productos;
                    productos.mmenuProductos();
                }
                break;
            case 0:
                {

                }
                break;
            default:
                cout<<"Valor ingresado no v�dido, intente de nuevo";
                getch();
                break;
        }
    }while(imenuCatalogo!=0);
}

ClsCatalogos::~ClsCatalogos()
{
    //dtor
}
