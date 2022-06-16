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
//////////////////////////////////////////////////////////////////////////////////////////////FUNCIONES CRUD
int obtenerCuenta( const char * const indicador )
{
   int iId;

   // obtener el valor del número de cuenta
   do {
      cout << indicador << " (1 - 100): ";
      cin >> iId;

   } while ( iId < 1 || iId > 100 );

   return iId;

} // fin de la función obtenerCuenta

void ClsClientes::nuevoCliente( fstream &insertarEnArchivoCliente )
{
   // obtener el número de cuenta a crear
   int iId = obtenerCuenta( "Escriba el nuevo numero de cuenta" );

   // desplazar el apuntador de posición del archivo hasta el registro correcto en el archivo
   insertarEnArchivoCliente.seekg(
      ( iId - 1 ) * sizeof( ClsClientes ) );

   // leer el registro del archivo
   ClsClientes clientes;
   insertarEnArchivoCliente.read( reinterpret_cast< char * >( &clientes ),
      sizeof( ClsClientes ) );

   // crear el registro, si éste no existe ya
   if ( clientes.mobtenerId() == 0 ) {

      char cNombre[ 20 ];
      char cApellido[20];
      int iTelefono;
      char cDireccion[20];

      // el usuario introduce el apellido, primer nombre y saldo
      cout << "Escriba el nombre: " << endl;
      cin >> setw( 20 ) >> cNombre;
      cout << "Escriba el Apellido: " << endl;
      cin >> setw( 20 ) >> cApellido;
      cout << "Escriba el Telefono: " << endl;
      cin >> setw( 20 ) >> iTelefono;
      cout << "Escriba la Direccion: " << endl;
      cin >> setw( 20 ) >> cDireccion;

      // usar valores para llenar los valores de la cuenta
      clientes.mestablecerNombreCliente( cNombre );
      clientes.mestablecerId( iId );
      clientes.mestablecerApellidoCliente( cApellido );
      clientes.mestablecerTelefono( iTelefono );
      clientes.mestablecerDireccion( cDireccion );


      // desplazar el apuntador de posición de archivo hasta el registro correcto en el archivo
      insertarEnArchivoCliente.seekp( ( iId - 1 ) *
         sizeof( ClsClientes ) );

      // insertar el registro en el archivo
      insertarEnArchivoCliente.write(
         reinterpret_cast< const char * >( &clientes ),
         sizeof( ClsClientes ) );

   } // fin de instrucción if

   // mostrar error si la cuenta ya existe
   else
      cerr << "La cuenta #" << iId << " ya contiene informacion." << endl;

} // fin de la función nuevoRegistro

////////////////////////////////////////////////DESPLIEGE CLIENTES
void ClsClientes::consultarRegistroClientes( fstream &leerDeArchivoClientes )
{

   cout << left << setw( 9 ) << "Id" << setw( 20 )
       << "Nombre" << setw( 20 ) << "Apellido"
       << setw( 20 ) << "Telefono" << setw( 20 ) << "Direccion" << endl;

   // colocar el apuntador de posición de archivo al principio del archivo de registros
   leerDeArchivoClientes.seekg( 0 );

   // leer el primer registro del archivo de registros
   ClsClientes clientes;
   leerDeArchivoClientes.read( reinterpret_cast< char * >( &clientes ),
      sizeof( ClsClientes ) );

   // copiar todos los registros del archivo de registros en el archivo de texto
   while ( !leerDeArchivoClientes.eof() ) {

      // escribir un registro individual en el archivo de texto
      if ( clientes.mobtenerId() != 0 )
         mostrarLineaPantallaClientes(clientes);

      // leer siguiente registro del archivo de registros
      leerDeArchivoClientes.read( reinterpret_cast< char * >( &clientes ),
         sizeof( ClsClientes ) );

   } // fin de instrucción while

} // fin de la función consultarRegistro

void ClsClientes::mostrarLineaPantallaClientes( const ClsClientes &registroClientes )
{
   cout << left << setw( 10 ) << registroClientes.mobtenerId()
          << setw( 20 ) << registroClientes.mobtenerNombreCliente().data()
          << setw( 20 ) << registroClientes.mobtenerApellidoCliente().data()
          << setw( 20 ) << registroClientes.mobtenerTelefono()
          << setw( 20 ) << registroClientes.mobtenerDireccion().data()<< endl;

} // fin de la función mostrarLineaPantalla

///////////////////////////////////////////////////////MODIFICAR
void ClsClientes::actualizarRegistroClientes( fstream &actualizarArchivoClientes )
{
   // obtener el número de cuenta a actualizar
   int numeroCodigo = obtenerCuenta( "Escriba la cuenta que desea actualizar" );

   // desplazar el apuntador de posición de archivo hasta el registro correcto en el archivo
   actualizarArchivoClientes.seekg(
      ( numeroCodigo - 1 ) * sizeof( ClsClientes ) );

   // leer el primer registro del archivo
   ClsClientes clientes;
   actualizarArchivoClientes.read( reinterpret_cast< char * >( &clientes ),
      sizeof( ClsClientes ) );

   // actualizar el registro
   if ( clientes.mobtenerId() != 0 ) {
      mostrarLineaClientes( cout, clientes );

      // solicitar al usuario que especifique la transacción
      cout << "\nEscriba el nombre: ";
      char cNombre [ 20 ];
      cin >> cNombre;

      cout << "\nEscriba el Apellido: ";
      char cApellido [ 20 ];
      cin >> cApellido;

      cout << "\nEscriba el Telefono: ";
      int iTelefono;
      cin >> iTelefono;

      cout << "\nEscriba la Direccion: ";
      char cDireccion [ 20 ];
      cin >> cDireccion;

      // actualizar el saldo del registro
      clientes.mestablecerNombreCliente( cNombre );
      clientes.mestablecerApellidoCliente( cApellido );
      clientes.mestablecerTelefono( iTelefono );
      clientes.mestablecerDireccion( cDireccion );
      mostrarLineaClientes( cout, clientes );

      // desplazar el apuntador de posición de archivo hasta el registro correcto en el archivo
      actualizarArchivoClientes.seekp(
         ( numeroCodigo - 1 ) * sizeof( ClsClientes ) );

      // escribir el registro actualizado sobre el registro anterior en el archivo
      actualizarArchivoClientes.write(
         reinterpret_cast< const char * >( &clientes ),
         sizeof( ClsClientes ) );

   } // fin de instrucción if

   // mostrar error si la cuenta no existe
   else
      cerr << "La cuenta #" << numeroCodigo << " no tiene informacion." << endl;

} // fin de la función actualizarRegistro

void ClsClientes::mostrarLineaClientes( ostream &salidaClientes, const ClsClientes &registroClientes )
{
   salidaClientes << left << setw( 9 ) << registroClientes.mobtenerId()
          << setw( 20 ) << registroClientes.mobtenerNombreCliente().data()
          << setw( 20 ) << registroClientes.mobtenerApellidoCliente().data()
          << setw( 20 ) << registroClientes.mobtenerTelefono()
          << setw( 20 ) << registroClientes.mobtenerDireccion().data()<< endl;

} // fin de la función mostrarLinea

////////////////////////////////////////////////////////IMPRIMIR REGISTRO
void ClsClientes::imprimirRegistroClientes( fstream &leerDeArchivoClientes )
{
   // crear archivo de texto
   ofstream archivoImprimirSalidaClientes( "ImprimirRegistroClientes.txt", ios::out );

   // salir del programa si ofstream no puede crear el archivo
   if ( !archivoImprimirSalidaClientes ) {
      cerr << "No se pudo crear el archivo." << endl;
      exit( 1 );

   } // fin de instrucción if
   else{
    cout<<"Se creo el archivo Departamentos"<<endl;
   }

   archivoImprimirSalidaClientes << left << setw( 9 ) << "Id" << setw( 20 )
       << "Nombre: " << setw( 20 ) << "Apellido:" << setw( 20 ) << "Telefono:" << setw( 20 ) << "Direccion:" << endl;

   // colocar el apuntador de posición de archivo al principio del archivo de registros
   leerDeArchivoClientes.seekg( 0 );

   // leer el primer registro del archivo de registros
   ClsClientes clientes;
   leerDeArchivoClientes.read( reinterpret_cast< char * >( &clientes ),
      sizeof( ClsClientes ) );

   // copiar todos los registros del archivo de registros en el archivo de texto
   while ( !leerDeArchivoClientes.eof() ) {

      // escribir un registro individual en el archivo de texto
      if ( clientes.mobtenerId() != 0 )
         mostrarLineaClientes( archivoImprimirSalidaClientes, clientes );

      // leer siguiente registro del archivo de registros
      leerDeArchivoClientes.read( reinterpret_cast< char * >( &clientes ),
         sizeof( ClsClientes ) );

   } // fin de instrucción while

} // fin de la función imprimirRegistro

////////////////////////////////////////////////////////////ELIMINAR
void ClsClientes::eliminarRegistroClientes( fstream &eliminarDeArchivoClientes )
{
   // obtener número de cuenta a eliminar
   int numeroCodigo= obtenerCuenta( "Escriba la cuenta a eliminar" );

   // desplazar el apuntador de posición de archivo hasta el registro correcto en el archivo
   eliminarDeArchivoClientes.seekg(
      ( numeroCodigo - 1 ) * sizeof( ClsClientes ) );

   // leer el registro del archivo
   ClsClientes clientes;
   eliminarDeArchivoClientes.read( reinterpret_cast< char * >( &clientes ),
      sizeof( ClsClientes ) );

   // eliminar el registro, si es que existe en el archivo
   if ( clientes.mobtenerId() != 0 ) {
      ClsClientes clienteEnBlancoClientes;

      // desplazar el apuntador de posición de archivo hasta el registro correcto en el archivo
      eliminarDeArchivoClientes.seekp( ( numeroCodigo - 1 ) *
         sizeof( ClsClientes ) );

      // reemplazar el registro existente con un registro en blanco
      eliminarDeArchivoClientes.write(
         reinterpret_cast< const char * >( &clienteEnBlancoClientes ),
         sizeof( ClsClientes ) );

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
void ClsClientes::buscarClientes( fstream &leerDeArchivoClientes)
{

   // obtener el número de cuenta a buscar
   int numeroCodigo = obtenerCuenta( "Escriba la cuenta que desea buscar" );

   // desplazar el apuntador de posición de archivo hasta el registro correcto en el archivo
   leerDeArchivoClientes.seekg(
      ( numeroCodigo - 1 ) * sizeof( ClsClientes ) );

   // leer el primer registro del archivo
   ClsClientes clientes;
   leerDeArchivoClientes.read( reinterpret_cast< char * >( &clientes ),
      sizeof( ClsClientes ) );
    //cout<<empleado.mobtenerClave();

   // actualizar el registro
   if ( clientes.mobtenerId() != 0 ) {
      mostrarLineaClientes( cout, clientes );
   }

   // mostrar error si la cuenta no existe
   else
   {
       cerr << "La cuenta #" << numeroCodigo << " no tiene informacion." << endl;
   }
   getch();

} // fin de la función consultarRegistro
//////////////////////////////////////////////////////////////////////////////////////////////TERMINA FUNCIONS CRUD
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
        cout<<"|----SISTEMA CRUD CLIENTES----|"<<endl;
        cout<<"-------------------------------"<<endl;
        cout<<"1. Ingreso Clientes"<<endl;
        cout<<"2. Despliegue Clientes"<<endl;
        cout<<"3. Modifica Clientes"<<endl;
        cout<<"4. Imprimir Regisro de Clientes"<<endl;
        cout<<"5. Borra Clientes"<<endl;
        cout<<"6. Buscar Clientes"<<endl;
        cout<<"0. Volver"<<endl;
        cout<<"-------------------------------"<<endl;
        cout<<"Opcion a escoger:[1/2/3/4/5/6/0]"<<endl;
        cout<<"------------------------------"<<endl;
        cout<<"Ingresa tu Opcion: ";
        cin>>iseleccionMenuClientes;
        switch(iseleccionMenuClientes)
        {
        case 1:
            {
                system("cls");
                nuevoCliente(archivoClientes);
                getch();
            }
            break;
        case 2:
            {
                system("cls");
                consultarRegistroClientes(archivoClientes);
                getch();
            }
            break;
        case 3:
            {
                system("cls");
                actualizarRegistroClientes(archivoClientes);
                getch();
            }
            break;
        case 4:
            {
                system("cls");
                imprimirRegistroClientes(archivoClientes);
                getch();
            }
            break;
        case 5:
            {
                system("cls");
                eliminarRegistroClientes(archivoClientes);
                getch();
            }
            break;
        case 6:
            {
                system("cls");
                buscarClientes(archivoClientes);
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
    }while(iseleccionMenuClientes!=0);
}

ClsClientes::~ClsClientes()
{
    //dtor
}
