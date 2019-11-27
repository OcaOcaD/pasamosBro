#include <vector>
#include <iostream>
#include "clases/Supplier/supplierMenu.h"
#include "clases/Products/productsMenu.h"



#include "clases/Client/clientMenu.h"
using namespace std;

int main(int argc, char const *argv[])
{
    bool main_exit = false;
    int opt;
    do{
        cout << "\t1)Proveedores\t Delimitadores de campos " << endl;
        cout << "\t2)Productos\t Campos de dimension " << endl;
        cout << "\t3)... " << endl;
        cout << "\t4)Empleados FALTA AGREGAR\t Indices simples " << endl;
        cout << "\t5)Clientes\t Indices invertidos " << endl;
        cout << "\t6)Hash FALTA AGREGAR" << endl;
        cout << "\t7)... " << endl;
        cout << "\t9)Exit program" << endl;
        cin >> opt;
        switch( opt ){
            case 1:{
                //Providers / Suppliers  || Campos por delimitadores
                supplierMenu();
                break;
            }
            case 2:{
                //Products || Dimention fields
                productsMenu();
            }
        /*
            ...other cases...
        */
            case 5:{
                //Clients || inverted indexes
                clientsMenu();
                break;
            }
            /*
                ...other cases...
            */
            case 9:{
                return 0;
                break;
            }
        }
    } while ( opt != 9 );
    
    return 0;
}
