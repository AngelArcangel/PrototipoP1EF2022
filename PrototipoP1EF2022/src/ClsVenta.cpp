#include "ClsVenta.h"

#include<conio.h>
#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
#include<cstdlib>
#include<ctime>
#include<string.h>

ClsVenta::ClsVenta(int valorId, string txtCliente, string txtProducto, int valorCantidad, int valorPrecio)
{
    mestablecerId(valorId);
    mestablecerNombreCliente(txtCliente);
    mestablecerProducto(txtProducto);
    mestablecerCantidad(valorCantidad);
    mestablecerPrecio(valorPrecio);
}

int ClsVenta::mobtenerId() const
{
    return iId;
}

void ClsVenta::mestablecerId (int ienteroId)
{
    iId = ienteroId;
}

string ClsVenta::mobtenerNombreCliente() const
{
    return cCliente;
}

void ClsVenta::mestablecerNombreCliente( string scadenaNombreCliente )
{
   const char *svalorNombreClienteV = scadenaNombreCliente.data();
   int ilongitud = strlen( svalorNombreClienteV );
   ilongitud = ( ilongitud < 20 ? ilongitud : 19 );
   strncpy( cCliente, svalorNombreClienteV, ilongitud );

   cCliente[ ilongitud ] = '\0';
}
string ClsVenta::mobtenerProducto() const
{
    return cProducto;
}

void ClsVenta::mestablecerProducto( string scadenaProducto )
{
   const char *svalorProducto = scadenaProducto.data();
   int ilongitud = strlen( svalorProducto );
   ilongitud = ( ilongitud < 20 ? ilongitud : 19 );
   strncpy( cProducto, svalorProducto, ilongitud );

   cProducto[ ilongitud ] = '\0';
}

int ClsVenta::mobtenerCantidad() const
{
    return iCantidad;
}

void ClsVenta::mestablecerCantidad (int ienteroCantidad)
{
    iCantidad = ienteroCantidad;
}

int ClsVenta::mobtenerPrecio() const
{
    return iPrecio;
}

void ClsVenta::mestablecerPrecio (int ienteroPrecio)
{
    iPrecio = ienteroPrecio;
}

/////////////////////////////////////////////////////////////////////FUNCIONES DE VENTA
int obtenerCuentaV( const char * const indicador )
{
   int iId;

   // obtener el valor del número de cuenta
   do {
      cout << indicador << " (1 - 100): ";
      cin >> iId;

   } while ( iId < 1 || iId > 100 );

   return iId;

} // fin de la función obtenerCuenta

void ClsVenta::nuevoVenta( fstream &insertarEnArchivoVenta )
{
   // obtener el número de cuenta a crear
   int iId = obtenerCuentaV( "Escriba el nuevo numero de cuenta" );

   // desplazar el apuntador de posición del archivo hasta el registro correcto en el archivo
   insertarEnArchivoVenta.seekg(
      ( iId - 1 ) * sizeof( ClsVenta ) );

   // leer el registro del archivo
   ClsVenta venta;
   insertarEnArchivoVenta.read( reinterpret_cast< char * >( &venta ),
      sizeof( ClsVenta ) );

   // crear el registro, si éste no existe ya
   if ( venta.mobtenerId() == 0 ) {

      char cCliente[ 20 ];
      char cProducto[20];
      int iCantidad;
      int iPrecio;

      // el usuario introduce el apellido, primer nombre y saldo
      cout << "Escriba el nombre: " << endl;
      cin >> setw( 20 ) >> cCliente;
      cout << "Escriba el Producto: " << endl;
      cin >> setw( 20 ) >> cProducto;
      cout << "Escriba el Cantidad: " << endl;
      cin >> setw( 20 ) >> iCantidad;
      cout << "Escriba el Precio: " << endl;
      cin >> setw( 20 ) >> iPrecio;

      // usar valores para llenar los valores de la cuenta
      venta.mestablecerNombreCliente( cCliente );
      venta.mestablecerId( iId );
      venta.mestablecerProducto( cProducto );
      venta.mestablecerCantidad( iCantidad );
      venta.mestablecerPrecio( iPrecio );


      // desplazar el apuntador de posición de archivo hasta el registro correcto en el archivo
      insertarEnArchivoVenta.seekp( ( iId - 1 ) *
         sizeof( ClsVenta ) );

      // insertar el registro en el archivo
      insertarEnArchivoVenta.write(
         reinterpret_cast< const char * >( &venta ),
         sizeof( ClsVenta ) );

   } // fin de instrucción if

   // mostrar error si la cuenta ya existe
   else
      cerr << "La cuenta #" << iId << " ya contiene informacion." << endl;

} // fin de la función nuevoRegistro

////////////////////////////////////////////////DESPLIEGE CLIENTES
void ClsVenta::consultarRegistroVenta( fstream &leerDeArchivoVenta )
{

   cout << left << setw( 9 ) << "Id" << setw( 20 )
       << "Cliente" << setw( 20 ) << "Producto"
       << setw( 20 ) << "Cantidad" << setw( 20 ) << "Precio" << endl;

   // colocar el apuntador de posición de archivo al principio del archivo de registros
   leerDeArchivoVenta.seekg( 0 );

   // leer el primer registro del archivo de registros
   ClsVenta venta;
   leerDeArchivoVenta.read( reinterpret_cast< char * >( &venta ),
      sizeof( ClsVenta ) );

   // copiar todos los registros del archivo de registros en el archivo de texto
   while ( !leerDeArchivoVenta.eof() ) {

      // escribir un registro individual en el archivo de texto
      if ( venta.mobtenerId() != 0 )
         mostrarLineaPantallaVenta(venta);

      // leer siguiente registro del archivo de registros
      leerDeArchivoVenta.read( reinterpret_cast< char * >( &venta ),
         sizeof( ClsVenta ) );

   } // fin de instrucción while

} // fin de la función consultarRegistro

void ClsVenta::mostrarLineaPantallaVenta( const ClsVenta &registroVenta )
{
   cout << left << setw( 10 ) << registroVenta.mobtenerId()
          << setw( 20 ) << registroVenta.mobtenerNombreCliente().data()
          << setw( 20 ) << registroVenta.mobtenerProducto().data()
          << setw( 20 ) << registroVenta.mobtenerCantidad()
          << setw( 20 ) << registroVenta.mobtenerPrecio()<< endl;

} // fin de la función mostrarLineaPantalla

////////////////////////////////////////////////////////////////BUSCAR
void ClsVenta::mostrarLineaVenta( ostream &salidaVenta, const ClsVenta &registroVenta )
{
   salidaVenta << left << setw( 9 ) << registroVenta.mobtenerId()
          << setw( 20 ) << registroVenta.mobtenerNombreCliente().data()
          << setw( 20 ) << registroVenta.mobtenerProducto().data()
          << setw( 20 ) << registroVenta.mobtenerCantidad()
          << setw( 20 ) << registroVenta.mobtenerPrecio()<< endl;

} // fin de la función mostrarLinea

void ClsVenta::buscarVenta( fstream &leerDeArchivoVenta)
{

   // obtener el número de cuenta a buscar
   int numeroCodigo = obtenerCuentaV( "Escriba la cuenta que desea buscar" );

   // desplazar el apuntador de posición de archivo hasta el registro correcto en el archivo
   leerDeArchivoVenta.seekg(
      ( numeroCodigo - 1 ) * sizeof( ClsVenta ) );

   // leer el primer registro del archivo
   ClsVenta venta;
   leerDeArchivoVenta.read( reinterpret_cast< char * >( &venta ),
      sizeof( ClsVenta ) );
    //cout<<empleado.mobtenerClave();

   // actualizar el registro
   if ( venta.mobtenerId() != 0 ) {
      mostrarLineaVenta( cout, venta );
   }

   // mostrar error si la cuenta no existe
   else
   {
       cerr << "La cuenta #" << numeroCodigo << " no tiene informacion." << endl;
   }
   getch();

} // fin de la función consultarRegistro
/////////////////////////////////////////////////////////////////////TERMINA FUNCIONES DE VENTA
ClsVenta::mcrearVenta()
{
    ofstream archivoVenta("RegistrosVenta.dat", ios::out | ios::binary);
    if(!archivoVenta)
    {
        cerr<<"No se habrio el archivo"<<endl;
        exit(1);
    }
    ClsVenta VentaEnBlanco;
    for(int i=0; i<100; i++)
    {
        archivoVenta.write(reinterpret_cast<const char * > (&VentaEnBlanco), sizeof(ClsVenta));
    }
}

ClsVenta::mmenuVenta()
{
    int iseleccionMenuVenta;
    do
    {
        system("cls");
        // abrir el archivo en modo de lectura y escritura
        fstream archivoVenta("RegistrosVenta.dat", ios::in | ios::out | ios::binary);
        // salir del programa si fstream no puede abrir el archivo
        if ( !archivoVenta )
            {
                cerr << "No se pudo abrir el archivo." << endl;
                mcrearVenta();
                cout <<  "Archivo creado satisfactoriamente, pruebe de nuevo";
                exit ( 1 );

            }
        cout<<"------------------------"<<endl;
        cout<<"|----ISTEMA VENTA----|"<<endl;
        cout<<"-----------------------"<<endl;
        cout<<"1. Ingreso Venta"<<endl;
        cout<<"2. Despliegue Venta"<<endl;
        cout<<"3. Buscar Clientes"<<endl;
        cout<<"0. Volver"<<endl;
        cout<<"-------------------------------"<<endl;
        cout<<"Opcion a escoger:[1/2/3/4/5/6/0]"<<endl;
        cout<<"------------------------------"<<endl;
        cout<<"Ingresa tu Opcion: ";
        cin>>iseleccionMenuVenta;
        switch(iseleccionMenuVenta)
        {
        case 1:
            {
                system("cls");
                nuevoVenta(archivoVenta);
                getch();
            }
            break;
        case 2:
            {
                system("cls");
                consultarRegistroVenta(archivoVenta);
                getch();
            }
            break;
        case 3:
            {
                system("cls");
                buscarVenta(archivoVenta);
                getch();
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
    }while(iseleccionMenuVenta!=0);
}

ClsVenta::~ClsVenta()
{
    //dtor
}
