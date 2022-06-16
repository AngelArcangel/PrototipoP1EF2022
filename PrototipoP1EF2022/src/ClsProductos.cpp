#include "ClsProductos.h"

#include<conio.h>
#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
#include<cstdlib>
#include<ctime>
#include<string.h>

ClsProductos::ClsProductos(int valorId, string txtNombre, string txtMarca, int valorExistencia)
{
    mestablecerId(valorId);
    mestablecerNombreProducto(txtNombre);
    mestablecerMarca(txtMarca);
    mestablecerExistencia(valorExistencia);
}

int ClsProductos::mobtenerId() const
{
    return iId;
}

void ClsProductos::mestablecerId (int ienteroId)
{
    iId = ienteroId;
}

string ClsProductos::mobtenerNombreProducto() const
{
    return cNombre;
}

void ClsProductos::mestablecerNombreProducto( string scadenaNombreProducto )
{
   const char *svalorNombreProducto = scadenaNombreProducto.data();
   int ilongitud = strlen( svalorNombreProducto );
   ilongitud = ( ilongitud < 20 ? ilongitud : 19 );
   strncpy( cNombre, svalorNombreProducto, ilongitud );

   cNombre[ ilongitud ] = '\0';
}

string ClsProductos::mobtenerMarca() const
{
    return cMarca;
}

void ClsProductos::mestablecerMarca( string scadenaMarca )
{
   const char *svalorMarca = scadenaMarca.data();
   int ilongitud = strlen( svalorMarca );
   ilongitud = ( ilongitud < 20 ? ilongitud : 19 );
   strncpy( cMarca, svalorMarca, ilongitud );

   cMarca[ ilongitud ] = '\0';
}

int ClsProductos::mobtenerExistencia() const
{
    return iExistencia;
}

void ClsProductos::mestablecerExistencia (int ienteroExistencia)
{
    iExistencia = ienteroExistencia;
}

/////////////////////////////////////////////////////////////////////////////////EMPIEZA CRUD PRODUCTOS
int obtenerCuentaPr( const char * const indicador )
{
   int iId;

   // obtener el valor del número de cuenta
   do {
      cout << indicador << " (1 - 100): ";
      cin >> iId;

   } while ( iId < 1 || iId > 100 );

   return iId;

} // fin de la función obtenerCuenta

void ClsProductos::nuevoProducto( fstream &insertarEnArchivoProducto )
{
   // obtener el número de cuenta a crear
   int iId = obtenerCuentaPr( "Escriba el nuevo numero de cuenta" );

   // desplazar el apuntador de posición del archivo hasta el registro correcto en el archivo
   insertarEnArchivoProducto.seekg(
      ( iId - 1 ) * sizeof( ClsProductos ) );

   // leer el registro del archivo
   ClsProductos productos;
   insertarEnArchivoProducto.read( reinterpret_cast< char * >( &productos ),
      sizeof( ClsProductos ) );

   // crear el registro, si éste no existe ya
   if ( productos.mobtenerId() == 0 ) {

      char cNombre[ 20 ];
      char cMarca[20];
      int iExistencia;

      // el usuario introduce el apellido, primer nombre y saldo
      cout << "Escriba el nombre: " << endl;
      cin >> setw( 20 ) >> cNombre;
      cout << "Escriba la Marca: " << endl;
      cin >> setw( 20 ) >> cMarca;
      cout << "Escriba la Existencia: " << endl;
      cin >> setw( 20 ) >> iExistencia;

      // usar valores para llenar los valores de la cuenta
      productos.mestablecerNombreProducto( cNombre );
      productos.mestablecerId( iId );
      productos.mestablecerMarca( cMarca );
      productos.mestablecerExistencia( iExistencia );

      // desplazar el apuntador de posición de archivo hasta el registro correcto en el archivo
      insertarEnArchivoProducto.seekp( ( iId - 1 ) *
         sizeof( ClsProductos ) );

      // insertar el registro en el archivo
      insertarEnArchivoProducto.write(
         reinterpret_cast< const char * >( &productos ),
         sizeof( ClsProductos ) );

   } // fin de instrucción if

   // mostrar error si la cuenta ya existe
   else
      cerr << "La cuenta #" << iId << " ya contiene informacion." << endl;

} // fin de la función nuevoRegistro

////////////////////////////////////////////////DESPLIEGE CLIENTES
void ClsProductos::consultarRegistroProducto( fstream &leerDeArchivoProductos )
{

   cout << left << setw( 9 ) << "Id" << setw( 20 )
       << "Nombre" << setw( 20 ) << "Marca"
       << setw( 20 ) << "Existencia" << endl;

   // colocar el apuntador de posición de archivo al principio del archivo de registros
   leerDeArchivoProductos.seekg( 0 );

   // leer el primer registro del archivo de registros
   ClsProductos productos;
   leerDeArchivoProductos.read( reinterpret_cast< char * >( &productos ),
      sizeof( ClsProductos ) );

   // copiar todos los registros del archivo de registros en el archivo de texto
   while ( !leerDeArchivoProductos.eof() ) {

      // escribir un registro individual en el archivo de texto
      if ( productos.mobtenerId() != 0 )
         mostrarLineaPantallaProductos(productos);

      // leer siguiente registro del archivo de registros
      leerDeArchivoProductos.read( reinterpret_cast< char * >( &productos ),
         sizeof( ClsProductos ) );

   } // fin de instrucción while

} // fin de la función consultarRegistro

void ClsProductos::mostrarLineaPantallaProductos( const ClsProductos &registroProductos )
{
   cout << left << setw( 10 ) << registroProductos.mobtenerId()
          << setw( 20 ) << registroProductos.mobtenerNombreProducto().data()
          << setw( 20 ) << registroProductos.mobtenerMarca().data()
          << setw( 20 ) << registroProductos.mobtenerExistencia()<< endl;

} // fin de la función mostrarLineaPantalla

///////////////////////////////////////////////////////MODIFICAR
void ClsProductos::actualizarRegistroProductos( fstream &actualizarArchivoProductos )
{
   // obtener el número de cuenta a actualizar
   int numeroCodigo = obtenerCuentaPr( "Escriba la cuenta que desea actualizar" );

   // desplazar el apuntador de posición de archivo hasta el registro correcto en el archivo
   actualizarArchivoProductos.seekg(
      ( numeroCodigo - 1 ) * sizeof( ClsProductos ) );

   // leer el primer registro del archivo
   ClsProductos productos;
   actualizarArchivoProductos.read( reinterpret_cast< char * >( &productos ),
      sizeof( ClsProductos ) );

   // actualizar el registro
   if ( productos.mobtenerId() != 0 ) {
      mostrarLineaProductos( cout, productos );

      // solicitar al usuario que especifique la transacción
      cout << "\nEscriba el nombre: ";
      char cNombre [ 20 ];
      cin >> cNombre;

      cout << "\nEscriba la Marca: ";
      char cMarca [ 20 ];
      cin >> cMarca;

      cout << "\nEscriba la Existencia: ";
      int iExistencia;
      cin >> iExistencia;

      // actualizar el saldo del registro
      productos.mestablecerNombreProducto( cNombre );
      productos.mestablecerMarca( cMarca );
      productos.mestablecerExistencia( iExistencia );
      mostrarLineaProductos( cout, productos );

      // desplazar el apuntador de posición de archivo hasta el registro correcto en el archivo
      actualizarArchivoProductos.seekp(
         ( numeroCodigo - 1 ) * sizeof( ClsProductos ) );

      // escribir el registro actualizado sobre el registro anterior en el archivo
      actualizarArchivoProductos.write(
         reinterpret_cast< const char * >( &productos ),
         sizeof( ClsProductos ) );

   } // fin de instrucción if

   // mostrar error si la cuenta no existe
   else
      cerr << "La cuenta #" << numeroCodigo << " no tiene informacion." << endl;

} // fin de la función actualizarRegistro

void ClsProductos::mostrarLineaProductos( ostream &salidaProductos, const ClsProductos &registroProductos )
{
   salidaProductos << left << setw( 9 ) << registroProductos.mobtenerId()
          << setw( 20 ) << registroProductos.mobtenerNombreProducto().data()
          << setw( 20 ) << registroProductos.mobtenerMarca().data()
          << setw( 20 ) << registroProductos.mobtenerExistencia()<< endl;

} // fin de la función mostrarLinea

////////////////////////////////////////////////////////IMPRIMIR REGISTRO
void ClsProductos::imprimirRegistroProductos( fstream &leerDeArchivoProductos )
{
   // crear archivo de texto
   ofstream archivoImprimirSalidaProductos( "ImprimirRegistroProductos.txt", ios::out );

   // salir del programa si ofstream no puede crear el archivo
   if ( !archivoImprimirSalidaProductos ) {
      cerr << "No se pudo crear el archivo." << endl;
      exit( 1 );

   } // fin de instrucción if
   else{
    cout<<"Se creo el archivo Departamentos"<<endl;
   }

   archivoImprimirSalidaProductos << left << setw( 9 ) << "Id" << setw( 20 )
       << "Nombre: " << setw( 20 ) << "Marca:" << setw( 20 ) << "Existencia:" << endl;

   // colocar el apuntador de posición de archivo al principio del archivo de registros
   leerDeArchivoProductos.seekg( 0 );

   // leer el primer registro del archivo de registros
   ClsProductos productos;
   leerDeArchivoProductos.read( reinterpret_cast< char * >( &productos ),
      sizeof( ClsProductos ) );

   // copiar todos los registros del archivo de registros en el archivo de texto
   while ( !leerDeArchivoProductos.eof() ) {

      // escribir un registro individual en el archivo de texto
      if ( productos.mobtenerId() != 0 )
         mostrarLineaProductos( archivoImprimirSalidaProductos, productos );

      // leer siguiente registro del archivo de registros
      leerDeArchivoProductos.read( reinterpret_cast< char * >( &productos ),
         sizeof( ClsProductos ) );

   } // fin de instrucción while

} // fin de la función imprimirRegistro

////////////////////////////////////////////////////////////ELIMINAR
void ClsProductos::eliminarRegistroProductos( fstream &eliminarDeArchivoProductos )
{
   // obtener número de cuenta a eliminar
   int numeroCodigo= obtenerCuentaPr( "Escriba la cuenta a eliminar" );

   // desplazar el apuntador de posición de archivo hasta el registro correcto en el archivo
   eliminarDeArchivoProductos.seekg(
      ( numeroCodigo - 1 ) * sizeof( ClsProductos ) );

   // leer el registro del archivo
   ClsProductos productos;
   eliminarDeArchivoProductos.read( reinterpret_cast< char * >( &productos ),
      sizeof( ClsProductos ) );

   // eliminar el registro, si es que existe en el archivo
   if ( productos.mobtenerId() != 0 ) {
      ClsProductos enBlancoProductos;

      // desplazar el apuntador de posición de archivo hasta el registro correcto en el archivo
      eliminarDeArchivoProductos.seekp( ( numeroCodigo - 1 ) *
         sizeof( ClsProductos ) );

      // reemplazar el registro existente con un registro en blanco
      eliminarDeArchivoProductos.write(
         reinterpret_cast< const char * >( &enBlancoProductos ),
         sizeof( ClsProductos ) );

      cout << "Empleado clave #" << numeroCodigo << " eliminado correctamente.\n";

   } // fin de instrucción if

   // mostrar error si el registro no existe
   else
   {
       cerr << "Empleado clave #" << numeroCodigo << " esta vacia.\n";
   }
   getch();

} // fin de eliminarRegistro

////////////////////////////////////////////////////////////////BUSCAR
void ClsProductos::buscarProductos( fstream &leerDeArchivoProductos)
{

   // obtener el número de cuenta a buscar
   int numeroCodigo = obtenerCuentaPr( "Escriba la cuenta que desea buscar" );

   // desplazar el apuntador de posición de archivo hasta el registro correcto en el archivo
   leerDeArchivoProductos.seekg(
      ( numeroCodigo - 1 ) * sizeof( ClsProductos ) );

   // leer el primer registro del archivo
   ClsProductos productos;
   leerDeArchivoProductos.read( reinterpret_cast< char * >( &productos ),
      sizeof( ClsProductos ) );
    //cout<<empleado.mobtenerClave();

   // actualizar el registro
   if ( productos.mobtenerId() != 0 ) {
      mostrarLineaProductos( cout, productos );
   }

   // mostrar error si la cuenta no existe
   else
   {
       cerr << "La cuenta #" << numeroCodigo << " no tiene informacion." << endl;
   }
   getch();

} // fin de la función consultarRegistro
/////////////////////////////////////////////////////////////////////////////////TERMINA CRUD DE PRODUCTOS

ClsProductos::mcrearProductos()
{
    ofstream archivoProductos("RegistrosProductos.dat", ios::out | ios::binary);
    if(!archivoProductos)
    {
        cerr<<"No se habrio el archivo"<<endl;
        exit(1);
    }
    ClsProductos productosEnBlanco;
    for(int i=0; i<100; i++)
    {
        archivoProductos.write(reinterpret_cast<const char * > (&productosEnBlanco), sizeof(ClsProductos));
    }
}

ClsProductos::mmenuProductos()
{
    int iseleccionMenuProductos;
    do
    {
        system("cls");
        // abrir el archivo en modo de lectura y escritura
        fstream archivoProductos("RegistrosProductos.dat", ios::in | ios::out | ios::binary);
        // salir del programa si fstream no puede abrir el archivo
        if ( !archivoProductos )
            {
                cerr << "No se pudo abrir el archivo." << endl;
                mcrearProductos();
                cout <<  "Archivo creado satisfactoriamente, pruebe de nuevo";
                exit ( 1 );

            }
        cout<<"--------------------------------"<<endl;
        cout<<"|----SISTEMA CRUD PRODUCTOS----|"<<endl;
        cout<<"--------------------------------"<<endl;
        cout<<"1. Ingreso Productos"<<endl;
        cout<<"2. Despliegue Productos"<<endl;
        cout<<"3. Modifica Productos"<<endl;
        cout<<"4. Imprimir Regisro de Productos"<<endl;
        cout<<"5. Borra Productos"<<endl;
        cout<<"6. Buscar Productos"<<endl;
        cout<<"0. Volver"<<endl;
        cout<<"-------------------------------"<<endl;
        cout<<"Opcion a escoger:[1/2/3/4/5/6/0]"<<endl;
        cout<<"------------------------------"<<endl;
        cout<<"Ingresa tu Opcion: ";
        cin>>iseleccionMenuProductos;
        switch(iseleccionMenuProductos)
        {
        case 1:
            {
                system("cls");
                nuevoProducto(archivoProductos);
                getch();
            }
            break;
        case 2:
            {
                system("cls");
                consultarRegistroProducto(archivoProductos);
                getch();
            }
            break;
        case 3:
            {
                system("cls");
                actualizarRegistroProductos(archivoProductos);
                getch();
            }
            break;
        case 4:
            {
                system("cls");
                imprimirRegistroProductos(archivoProductos);
                getch();
            }
            break;
        case 5:
            {
                system("cls");
                eliminarRegistroProductos(archivoProductos);
                getch();
            }
            break;
        case 6:
            {
                system("cls");
                buscarProductos(archivoProductos);
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
    }while(iseleccionMenuProductos!=0);
}
ClsProductos::~ClsProductos()
{
    //dtor
}
