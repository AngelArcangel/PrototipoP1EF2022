#include "ClsCatalogos.h"
#include "ClsClientes.h"
#include "ClsProveedores.h"
#include "ClsProductos.h"
#include "ClsVenta.h"

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
        cout<<"1. VENTA"<<endl;
        cout<<"2. CLIENTES"<<endl;
        cout<<"3. PROVEEDORES"<<endl;
        cout<<"4. PRODUCTOS"<<endl;
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
                    ClsVenta venta;
                    venta.mmenuVenta();
                }
                break;
            case 2:
                {
                    ClsClientes clientes;
                    clientes.mmenuCliente();
                }
                break;
            case 3:
                {
                    ClsProveedores proveedores;
                    proveedores.mmenuProveedores();
                }
                break;
            case 4:
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
                cout<<"Valor ingresado no vádido, intente de nuevo";
                getch();
                break;
        }
    }while(imenuCatalogo!=0);
}

ClsCatalogos::~ClsCatalogos()
{
    //dtor
}
