//ES EXACTAMENTE EL PROYECTO, COPIA DE RESPALDO 
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
using namespace std;

string productos[25];
float precio[25];
int existencias[25];
string zona[25];
string password = "pswrd";
int totalProductos= 0;

// PROTOTIPOS DE FUNCIONES
void leerproductos();
void cargar();
void guardaproducto();
int menuppal();
bool validarpswrd();
void modovendedor();
int edicionproductos();
void modocomprador();
void mostrarproductos();
void mostrarproductoszona(string zonaSeleccionada);
void factura();
void linea(int fila);

//MATRIZ
char decoracion[2][40]={
{'=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','='},
{'*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*'}
};

//ARREGLO 
string mensajes[5]={
"Cargando productos...",
"Preparando sistema...",
"Verificando archivos...",
"Conectando usuarios...",
"Todo listo..."
};

//FUNCIONES 
void linea(int fila)
{
    for(int i=0;i<40;i++)
    {
        cout<<decoracion[fila][i];
    }
    cout<<endl;
}

void leerproductos()
{
    ifstream archivo("productos.txt");

    if(!archivo.is_open())
    {
        cout << "No se pudo abrir el archivo." << endl;
        return;
    }


    totalProductos = 0;

    string linea;

    while(getline(archivo,linea))
    {
        size_t pos1 = linea.find('|');
        size_t pos2 = linea.find('|', pos1 + 1);
        size_t pos3 = linea.find('|', pos2 + 1);


        if(pos1 != string::npos &&
           pos2 != string::npos &&
           pos3 != string::npos)
        {

            productos[totalProductos] = linea.substr(0,pos1);


            precio[totalProductos] = stof(
                linea.substr(pos1+1,pos2-pos1-1)
            );


            existencias[totalProductos] = stoi(
                linea.substr(pos2+1,pos3-pos2-1)
            );


            zona[totalProductos] = linea.substr(pos3+1);


            totalProductos++;
        }
    }


    archivo.close();


    cout << "Productos cargados correctamente." << endl;
    cout << "Total productos: " << totalProductos << endl;
}

void mostrarproductos()
{
    cout << "\n========== PRODUCTOS ==========\n\n";

    for(int i = 0; i < totalProductos; i++)
    {
        cout << i + 1 << ". "
             << productos[i]
             << "   $" << precio[i]
             << "   Existencias: " << existencias[i]
             << "   " << zona[i]
             << endl;
    }
}

void mostrarproductoszona(string zonaSeleccionada)
{
    cout << "\n========== PRODUCTOS DISPONIBLES ==========\n\n";

    bool encontrado = false;

    for(int i = 0; i < totalProductos; i++)
    {
        if(zona[i] == zonaSeleccionada)
        {
            cout << i + 1 << ". "
                 << productos[i]
                 << "   $" << precio[i]
                 << "   Existencias: " << existencias[i]
                 << endl;

            encontrado = true;
        }
    }

    if(!encontrado)
    {
        cout << "No hay productos disponibles en esta zona." << endl;
    }
}

void cargar()
{
    system("cls");

    linea(0);

    cout<<"\n";
    cout<<"          UNIVERSIDAD STORE\n";
    cout<<"     Sistema de Gestion de Tienda\n\n";

    linea(1);

    cout<<"\n";

    for(int i=0;i<5;i++)
    {
        cout<<mensajes[i]<<endl;

        for(int j=0;j<20;j++)
        {
            cout<<(char)219;
            Sleep(40);
        }

        cout<<" 100%"<<endl<<endl;
    }

    Sleep(600);
}

void guardaproducto()
{

    ofstream archivo("productos.txt");

    if (archivo.is_open())
    {
        for (int i = 0; i < totalProductos; i++)
        {
          archivo << productos[i] << "|"
        << precio[i] << "|"
        << existencias[i] << "|"
        << zona[i] << endl;
        }
        archivo.close();
        cout << "Productos guardados correctamente." << endl;
    }
    else
    {
        cout << "No se pudo abrir el archivo para guardar." << endl;
    }
}

int menuppal()
{
    int opcion;

    system("cls");

    linea(0);

    cout << "\n";
    cout << "             UNIVERSIDAD STORE\n";
    cout << "        Sistema de Venta Universitario\n\n";

    linea(1);

    cout << "\n";
    cout << "          +-----------------------+\n";
    cout << "          |      MENU PRINCIPAL   |\n";
    cout << "          +-----------------------+\n\n";

    cout << "            [1] DUENO\n";
    cout << "            [2] CLIENTE\n";
    cout << "            [3] SALIR\n\n";

    linea(0);

    cout << "\nSeleccione una opcion: ";
    cin >> opcion;

    return opcion;
}

bool validarpswrd()
{
    string contrasena;

    cout << "Ingrese la contraseña: " << endl;
    cin >> contrasena;

    if (contrasena == password)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void modovendedor()
{
    int productoEditar;
    int opcionEditar;
    char continuar;

    do
    {
        mostrarproductos();

        cout << "\nIngrese el numero del producto que desea modificar: ";
        cin >> productoEditar;

    productoEditar--;

        
        if(productoEditar < 0 || productoEditar >= totalProductos)
        {
            cout << "\nProducto invalido.\n";
        }
        else
        {
            cout << "===== PRODUCTO SELECCIONADO ====="<<endl;
            cout << "Nombre: " << productos[productoEditar] <<endl;
            cout << "Precio: $" << precio[productoEditar] <<endl;
            cout << "Existencias: " << existencias[productoEditar] <<endl;
            cout << "Zona: " << zona[productoEditar] <<endl;

        opcionEditar = edicionproductos();

        switch(opcionEditar)
        {
            case 1:
                cout << "Nuevo nombre: ";
                cin >> productos[productoEditar];
                break;
            case 2:
                cout << "Nuevo precio: ";
                cin >> precio[productoEditar];
                break;
            case 3:
                cout << "Nueva cantidad: ";
                cin >> existencias[productoEditar];
                break;
            case 4:
                cout << "Nueva zona: ";
                cin >> zona[productoEditar];
                break;
            default:
                cout << "Opcion invalida.\n";
        }
            guardaproducto();

            cout << "\nProducto actualizado correctamente.\n";

            cout << "\n===== NUEVOS DATOS =====\n";
            cout << "Nombre: " << productos[productoEditar] << endl;
            cout << "Precio: $" << precio[productoEditar] << endl;
            cout << "Existencias: " << existencias[productoEditar] << endl;
            cout << "Zona: " << zona[productoEditar] << endl;
        }

        cout << "\nDesea modificar otro producto? (S/N): ";
        cin >> continuar;

    } while(continuar == 'S' || continuar == 's');
}

int edicionproductos()
{
    int editar;

    cout << "¿Que quiere modificar?" << endl;
    cout << "1.nombre" << endl;
    cout << "2.precio" << endl;
    cout << "3.cantidad" << endl;
    cout << "4.zona" << endl;
    cin >> editar;

    return editar;
}

void modocomprador()
{
    int opcionZona;
    int opcionProducto;
    int cantidad;
    int seguir;
    int salir = 0;
    int productoValido;
    int zonaCorrecta;

    do
    {
        productoValido = 0;
        zonaCorrecta = 0;

        cout << endl;
        cout << "===== MODO COMPRADOR =====" << endl;
        cout << "1. Zona1" << endl;
        cout << "2. Zona2" << endl;
        cout << "3. Zona3" << endl;
        cout << "4. Zona4" << endl;
        cout << "Seleccione una zona: ";
        cin >> opcionZona;

        cout << endl;


        cout << endl;

    string zonaSeleccionada;

        switch(opcionZona)
        {
            case 1:
                zonaSeleccionada = "Zona1";
                break;
        
            case 2:
                zonaSeleccionada = "Zona2";
                break;
        
            case 3:
                zonaSeleccionada = "Zona3";
                break;
        
            case 4:
                zonaSeleccionada = "Zona4";
                break;
        
            default:
                cout << "Zona invalida." << endl;
                continue;
        }

    mostrarproductoszona(zonaSeleccionada);

        cout << "Seleccione el numero del producto: ";
        cin >> opcionProducto;

        opcionProducto--;

        if (opcionProducto < 0 || opcionProducto >= totalProductos)
        {
            cout << "Producto invalido." << endl;
        }
        else
        {
            productoValido = 1;

            switch (opcionZona)
            {
                case 1:
                    if (zona[opcionProducto] == "Zona1")
                    {
                        zonaCorrecta = 1;
                    }
                    else
                    {
                        cout << "Ese producto no pertenece a la Zona1." << endl;
                    }
                    break;

                case 2:
                    if (zona[opcionProducto] == "Zona2")
                    {
                        zonaCorrecta = 1;
                    }
                    else
                    {
                        cout << "Ese producto no pertenece a la Zona2." << endl;
                    }
                    break;

                case 3:
                    if (zona[opcionProducto] == "Zona3")
                    {
                        zonaCorrecta = 1;
                    }
                    else
                    {
                        cout << "Ese producto no pertenece a la Zona3." << endl;
                    }
                    break;

                case 4:
                    if (zona[opcionProducto] == "Zona4")
                    {
                        zonaCorrecta = 1;
                    }
                    else
                    {
                        cout << "Ese producto no pertenece a la Zona4." << endl;
                    }
                    break;

                default:
                    cout << "Zona invalida." << endl;
                    break;
            }

            if (productoValido == 1 && zonaCorrecta == 1)
            {
                cout << "Ingrese cantidad: ";
                cin >> cantidad;

                if (cantidad <= 0)
                {
                    cout << "Cantidad invalida." << endl;
                }
                else if (cantidad > existencias[opcionProducto])
                {
                    cout << "No hay suficientes existencias." << endl;
                }
                else
                {
                    existencias[opcionProducto] = existencias[opcionProducto] - cantidad;

                    cout << "Compra realizada correctamente." << endl;
                    cout << "Existencias restantes: " << existencias[opcionProducto] << endl;
                }
            }
        }

        do
        {
            cout << endl;
            cout << "¿Desea comprar otro producto?" << endl;
            cout << "1. No" << endl;
            cout << "2. Si" << endl;
            cout << "Seleccione una opcion: ";
            cin >> seguir;

            switch (seguir)
            {
                case 1:
                    salir = 1;
                    break;

                case 2:
                    salir = 0;
                    break;

                default:
                    cout << "Opcion invalida." << endl;
                    break;
            }

        } while (seguir != 1 && seguir != 2);

    } while (salir == 0);

    guardaproducto();
}

void factura()
{
    string compraProducto[25];
    float compraPrecio[25];
    int compraCantidad[25];
    float compraSubtotal[25];
    int totalCompra = 0;

    float total = 0;
    cout << "\n=====================================\n";
    cout << "         TICKET DE LA COMPRA\n";
    cout << "=====================================\n";
    cout << "Producto\tPrecio\tCant.\tSubtotal\n";
    for (int i = 0; i < totalCompra; i++)
    {
        cout << compraProducto[i] << "\t$"
             << compraPrecio[i] << "\t"
             << compraCantidad[i] << "\t$"
             << compraSubtotal[i] << endl;
        total += compraSubtotal[i];
    }
    cout << "-------------------------------------\n";
    cout << "TOTAL A PAGAR: $" << total << endl;
    cout << "=====================================\n";
}

int main()
{
    int opcion;

    leerproductos();
    cargar();

   do
    {
    opcion = menuppal();

        switch (opcion)
        {
        case 1:
            if (validarpswrd())
            {
                modovendedor();
            } else {
                cout << "contraseña incorrecta" <<endl;
            }
            break;
    
        case 2:
            modocomprador();
        break;        
            
        case 3:
            cout << "gracias por usar el sistema..." <<endl;
        break;
    
        default:
        cout <<"opcion invalida..." <<endl;
            break;
        } 
  } while(opcion != 3);
    

    return 0;


}
