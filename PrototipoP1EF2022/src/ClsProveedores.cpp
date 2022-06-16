#include "ClsProveedores.h"

#include<conio.h>
#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
#include<cstdlib>
#include<ctime>
#include<string.h>

ClsProveedores::ClsProveedores(int valorId, string txtNombre, string txtDireccion, int valorTelefono)
{
    mestablecerId(valorId);
    mestablecerNombreProveedor(txtNombre);
    mestablecerDireccion(txtDireccion);
    mestablecerTelefono(valorTelefono);
}

int ClsProveedores::mobtenerId() const
{
    return iId;
}

void ClsProveedores::mestablecerId (int ienteroId)
{
    iId = ienteroId;
}

string ClsProveedores::mobtenerNombreProveedor() const
{
    return cNombre;
}

void ClsProveedores::mestablecerNombreProveedor( string scadenaNombreProveedor )
{
   const char *svalorNombreProveedor = scadenaNombreProveedor.data();
   int ilongitud = strlen( svalorNombreProveedor );
   ilongitud = ( ilongitud < 20 ? ilongitud : 19 );
   strncpy( cNombre, svalorNombreProveedor, ilongitud );

   cNombre[ ilongitud ] = '\0';
}

string ClsProveedores::mobtenerDireccion() const
{
    return cDireccion;
}

void ClsProveedores::mestablecerDireccion( string scadenaDireccion )
{
   const char *svalorDireccion = scadenaDireccion.data();
   int ilongitud = strlen( svalorDireccion );
   ilongitud = ( ilongitud < 20 ? ilongitud : 19 );
   strncpy( cDireccion, svalorDireccion, ilongitud );

   cDireccion[ ilongitud ] = '\0';
}

int ClsProveedores::mobtenerTelefono() const
{
    return iTelefono;
}

void ClsProveedores::mestablecerTelefono (int ienteroTelefono)
{
    iTelefono = ienteroTelefono;
}

////////////////////////////////////////////////////////////////////////////////////EMPIEZA CRUD PROVEEDORES
int obtenerCuentaP( const char * const indicador )
{
   int iId;

   // obtener el valor del número de cuenta
   do {
      cout << indicador << " (1 - 100): ";
      cin >> iId;

   } while ( iId < 1 || iId > 100 );

   return iId;

} // fin de la función obtenerCuenta

void ClsProveedores::nuevoProveedor( fstream &insertarEnArchivoProveedor )
{
   // obtener el número de cuenta a crear
   int iId = obtenerCuentaP( "Escriba el nuevo numero de cuenta" );

   // desplazar el apuntador de posición del archivo hasta el registro correcto en el archivo
   insertarEnArchivoProveedor.seekg(
      ( iId - 1 ) * sizeof( ClsProveedores ) );

   // leer el registro del archivo
   ClsProveedores proveedores;
   insertarEnArchivoProveedor.read( reinterpret_cast< char * >( &proveedores ),
      sizeof( ClsProveedores ) );

   // crear el registro, si éste no existe ya
   if ( proveedores.mobtenerId() == 0 ) {

      char cNombre[ 20 ];
      char cDireccion[20];
      int iTelefono;

      // el usuario introduce el apellido, primer nombre y saldo
      cout << "Escriba el nombre: " << endl;
      cin >> setw( 20 ) >> cNombre;
      cout << "Escriba la Direccion: " << endl;
      cin >> setw( 20 ) >> cDireccion;
      cout << "Escriba el Telefono: " << endl;
      cin >> setw( 20 ) >> iTelefono;

      // usar valores para llenar los valores de la cuenta
      proveedores.mestablecerNombreProveedor( cNombre );
      proveedores.mestablecerId( iId );
      proveedores.mestablecerTelefono( iTelefono );
      proveedores.mestablecerDireccion( cDireccion );


      // desplazar el apuntador de posición de archivo hasta el registro correcto en el archivo
      insertarEnArchivoProveedor.seekp( ( iId - 1 ) *
         sizeof( ClsProveedores ) );

      // insertar el registro en el archivo
      insertarEnArchivoProveedor.write(
         reinterpret_cast< const char * >( &proveedores ),
         sizeof( ClsProveedores ) );

   } // fin de instrucción if

   // mostrar error si la cuenta ya existe
   else
      cerr << "La cuenta #" << iId << " ya contiene informacion." << endl;

} // fin de la función nuevoRegistro

////////////////////////////////////////////////DESPLIEGE CLIENTES
void ClsProveedores::consultarRegistroProveedores( fstream &leerDeArchivoProveedores )
{

   cout << left << setw( 9 ) << "Id" << setw( 20 )
       << "Nombre" << setw( 20 ) << "Direccion"
       << setw( 20 ) << "Telefono" << endl;

   // colocar el apuntador de posición de archivo al principio del archivo de registros
   leerDeArchivoProveedores.seekg( 0 );

   // leer el primer registro del archivo de registros
   ClsProveedores proveedores;
   leerDeArchivoProveedores.read( reinterpret_cast< char * >( &proveedores ),
      sizeof( ClsProveedores ) );

   // copiar todos los registros del archivo de registros en el archivo de texto
   while ( !leerDeArchivoProveedores.eof() ) {

      // escribir un registro individual en el archivo de texto
      if ( proveedores.mobtenerId() != 0 )
         mostrarLineaPantallaProveedores(proveedores);

      // leer siguiente registro del archivo de registros
      leerDeArchivoProveedores.read( reinterpret_cast< char * >( &proveedores ),
         sizeof( ClsProveedores ) );

   } // fin de instrucción while

} // fin de la función consultarRegistro

void ClsProveedores::mostrarLineaPantallaProveedores( const ClsProveedores &registroProveedores )
{
   cout << left << setw( 10 ) << registroProveedores.mobtenerId()
          << setw( 20 ) << registroProveedores.mobtenerNombreProveedor().data()
          << setw( 20 ) << registroProveedores.mobtenerDireccion().data()
          << setw( 20 ) << registroProveedores.mobtenerTelefono()<< endl;

} // fin de la función mostrarLineaPantalla

///////////////////////////////////////////////////////MODIFICAR
void ClsProveedores::actualizarRegistroProveedores( fstream &actualizarArchivoProveedores )
{
   // obtener el número de cuenta a actualizar
   int numeroCodigo = obtenerCuentaP( "Escriba la cuenta que desea actualizar" );

   // desplazar el apuntador de posición de archivo hasta el registro correcto en el archivo
   actualizarArchivoProveedores.seekg(
      ( numeroCodigo - 1 ) * sizeof( ClsProveedores ) );

   // leer el primer registro del archivo
   ClsProveedores proveedores;
   actualizarArchivoProveedores.read( reinterpret_cast< char * >( &proveedores ),
      sizeof( ClsProveedores ) );

   // actualizar el registro
   if ( proveedores.mobtenerId() != 0 ) {
      mostrarLineaProveedores( cout, proveedores );

      // solicitar al usuario que especifique la transacción
      cout << "\nEscriba el nombre: ";
      char cNombre [ 20 ];
      cin >> cNombre;

      cout << "\nEscriba la Direccion: ";
      char cDireccion [ 20 ];
      cin >> cDireccion;

      cout << "\nEscriba el Telefono: ";
      int iTelefono;
      cin >> iTelefono;

      // actualizar el saldo del registro
      proveedores.mestablecerNombreProveedor( cNombre );
      proveedores.mestablecerDireccion( cDireccion );
      proveedores.mestablecerTelefono( iTelefono );
      mostrarLineaProveedores( cout, proveedores );

      // desplazar el apuntador de posición de archivo hasta el registro correcto en el archivo
      actualizarArchivoProveedores.seekp(
         ( numeroCodigo - 1 ) * sizeof( ClsProveedores ) );

      // escribir el registro actualizado sobre el registro anterior en el archivo
      actualizarArchivoProveedores.write(
         reinterpret_cast< const char * >( &proveedores ),
         sizeof( ClsProveedores ) );

   } // fin de instrucción if

   // mostrar error si la cuenta no existe
   else
      cerr << "La cuenta #" << numeroCodigo << " no tiene informacion." << endl;

} // fin de la función actualizarRegistro

void ClsProveedores::mostrarLineaProveedores( ostream &salidaProveedores, const ClsProveedores &registroProveedores )
{
   salidaProveedores << left << setw( 9 ) << registroProveedores.mobtenerId()
          << setw( 20 ) << registroProveedores.mobtenerNombreProveedor().data()
          << setw( 20 ) << registroProveedores.mobtenerDireccion().data()
          << setw( 20 ) << registroProveedores.mobtenerTelefono()<< endl;

} // fin de la función mostrarLinea

////////////////////////////////////////////////////////IMPRIMIR REGISTRO
void ClsProveedores::imprimirRegistroProveedores( fstream &leerDeArchivoProveedores )
{
   // crear archivo de texto
   ofstream archivoImprimirSalidaProveedores( "ImprimirRegistroProveedores.txt", ios::out );

   // salir del programa si ofstream no puede crear el archivo
   if ( !archivoImprimirSalidaProveedores ) {
      cerr << "No se pudo crear el archivo." << endl;
      exit( 1 );

   } // fin de instrucción if
   else{
    cout<<"Se creo el archivo Departamentos"<<endl;
   }

   archivoImprimirSalidaProveedores << left << setw( 9 ) << "Id" << setw( 20 )
       << "Nombre: " << setw( 20 ) << "Direccion:" << setw( 20 ) << "Telefono:" << endl;

   // colocar el apuntador de posición de archivo al principio del archivo de registros
   leerDeArchivoProveedores.seekg( 0 );

   // leer el primer registro del archivo de registros
   ClsProveedores proveedores;
   leerDeArchivoProveedores.read( reinterpret_cast< char * >( &proveedores ),
      sizeof( ClsProveedores ) );

   // copiar todos los registros del archivo de registros en el archivo de texto
   while ( !leerDeArchivoProveedores.eof() ) {

      // escribir un registro individual en el archivo de texto
      if ( proveedores.mobtenerId() != 0 )
         mostrarLineaProveedores( archivoImprimirSalidaProveedores, proveedores );

      // leer siguiente registro del archivo de registros
      leerDeArchivoProveedores.read( reinterpret_cast< char * >( &proveedores ),
         sizeof( ClsProveedores ) );

   } // fin de instrucción while

} // fin de la función imprimirRegistro

////////////////////////////////////////////////////////////ELIMINAR
void ClsProveedores::eliminarRegistroProveedores( fstream &eliminarDeArchivoProveedores )
{
   // obtener número de cuenta a eliminar
   int numeroCodigo= obtenerCuentaP( "Escriba la cuenta a eliminar" );

   // desplazar el apuntador de posición de archivo hasta el registro correcto en el archivo
   eliminarDeArchivoProveedores.seekg(
      ( numeroCodigo - 1 ) * sizeof( ClsProveedores ) );

   // leer el registro del archivo
   ClsProveedores proveedores;
   eliminarDeArchivoProveedores.read( reinterpret_cast< char * >( &proveedores ),
      sizeof( ClsProveedores ) );

   // eliminar el registro, si es que existe en el archivo
   if ( proveedores.mobtenerId() != 0 ) {
      ClsProveedores EnBlancoProveedores;

      // desplazar el apuntador de posición de archivo hasta el registro correcto en el archivo
      eliminarDeArchivoProveedores.seekp( ( numeroCodigo - 1 ) *
         sizeof( ClsProveedores ) );

      // reemplazar el registro existente con un registro en blanco
      eliminarDeArchivoProveedores.write(
         reinterpret_cast< const char * >( &EnBlancoProveedores ),
         sizeof( ClsProveedores ) );

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
void ClsProveedores::buscarProveedores( fstream &leerDeArchivoProveedores)
{

   // obtener el número de cuenta a buscar
   int numeroCodigo = obtenerCuentaP( "Escriba la cuenta que desea buscar" );

   // desplazar el apuntador de posición de archivo hasta el registro correcto en el archivo
   leerDeArchivoProveedores.seekg(
      ( numeroCodigo - 1 ) * sizeof( ClsProveedores ) );

   // leer el primer registro del archivo
   ClsProveedores proveedores;
   leerDeArchivoProveedores.read( reinterpret_cast< char * >( &proveedores ),
      sizeof( ClsProveedores ) );
    //cout<<empleado.mobtenerClave();

   // actualizar el registro
   if ( proveedores.mobtenerId() != 0 ) {
      mostrarLineaProveedores( cout, proveedores );
   }

   // mostrar error si la cuenta no existe
   else
   {
       cerr << "La cuenta #" << numeroCodigo << " no tiene informacion." << endl;
   }
   getch();

} // fin de la función consultarRegistro
////////////////////////////////////////////////////////////////////////////////////TERMINA CRUD DE PROVEEDORES

ClsProveedores::mcrearProveedores()
{
    ofstream archivoProveedores("RegistrosProveedores.dat", ios::out | ios::binary);
    if(!archivoProveedores)
    {
        cerr<<"No se habrio el archivo"<<endl;
        exit(1);
    }
    ClsProveedores ProveedoresEnBlanco;
    for(int i=0; i<100; i++)
    {
        archivoProveedores.write(reinterpret_cast<const char * > (&ProveedoresEnBlanco), sizeof(ClsProveedores));
    }
}

ClsProveedores::mmenuProveedores()
{
    int iseleccionMenuProveedores;
    do
    {
        system("cls");
        // abrir el archivo en modo de lectura y escritura
        fstream archivoProveedores("RegistrosProveedores.dat", ios::in | ios::out | ios::binary);
        // salir del programa si fstream no puede abrir el archivo
        if ( !archivoProveedores )
            {
                cerr << "No se pudo abrir el archivo." << endl;
                mcrearProveedores();
                cout <<  "Archivo creado satisfactoriamente, pruebe de nuevo";
                exit ( 1 );

            }
        cout<<"--------------------------------"<<endl;
        cout<<"|---SISTEMA CRUD PROVEEDORES---|"<<endl;
        cout<<"--------------------------------"<<endl;
        cout<<"1. Ingreso Proveedores"<<endl;
        cout<<"2. Despliegue Proveedores"<<endl;
        cout<<"3. Modifica Proveedores"<<endl;
        cout<<"4. Imprimir Regisro de Proveedores"<<endl;
        cout<<"5. Borra Proveedores"<<endl;
        cout<<"6. Buscar Proveedores"<<endl;
        cout<<"0. Volver"<<endl;
        cout<<"-------------------------------"<<endl;
        cout<<"Opcion a escoger:[1/2/3/4/5/6/0]"<<endl;
        cout<<"------------------------------"<<endl;
        cout<<"Ingresa tu Opcion: ";
        cin>>iseleccionMenuProveedores;
        switch(iseleccionMenuProveedores)
        {
        case 1:
            {
                system("cls");
                nuevoProveedor(archivoProveedores);
                getch();
            }
            break;
        case 2:
            {
                system("cls");
                consultarRegistroProveedores(archivoProveedores);
                getch();
            }
            break;
        case 3:
            {
                system("cls");
                actualizarRegistroProveedores(archivoProveedores);
                getch();
            }
            break;
        case 4:
            {
                system("cls");
                imprimirRegistroProveedores(archivoProveedores);
                getch();
            }
            break;
        case 5:
            {
                system("cls");
                eliminarRegistroProveedores(archivoProveedores);
                getch();
            }
            break;
        case 6:
            {
                system("cls");
                buscarProveedores(archivoProveedores);
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
    }while(iseleccionMenuProveedores!=0);
}

ClsProveedores::~ClsProveedores()
{
    //dtor
}
