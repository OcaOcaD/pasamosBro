#include <vector>
#include <iostream>
#include <fstream>
#include "clases/Bill/BillMenu.h"
#include "clases/Client/clientMenu.h"
#include "clases/Cipher/cipherMenu.h"
#include "clases/Orders/ordersMenu.h"
#include "clases/Accounts/AccountsMenu.h"
#include "clases/Supplier/supplierMenu.h"
#include "clases/Products/productsMenu.h"
#include "clases/Empleado/empleadoMenu.h"

using namespace std;

int main(int argc, char const *argv[])
{
    bool main_exit = false;
    int opt;
    do{
        cout << "\t1)Proveedores\t Delimitadores de campos " << endl;
        cout << "\t2)Productos\t Campos de dimension " << endl;
        cout << "\t3)Ordenes \t Longitud fija" << endl;
        cout << "\t4)Empleados \t Indices simples " << endl;
        cout << "\t5)Clientes\t Indices invertidos " << endl;
        cout << "\t6)Hash" << endl;
        cout << "\t7)Serializacion " << endl;
        cout << "\t10)Serializacion " << endl;
        cout << "\t11)Exit program" << endl;
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
            case 3:{
                ordersMenu();
                break;
            }
            case 4:{
                accountsMenu();
                break;
            }
            case 5:{
                //Clients || inverted indexes
                clientsMenu();
                break;
            }
            case 6:{
                empleadoMenu();
                break;
            }
            case 7:{
                bill_menu();
                break;
            }
            case 10:{
                cipherMenu();
                break;
            }
            case 11:{
                return 0;
                break;
            }
            default:{
                std::cout << "xd" << std::endl;
            }
        }
    }while( opt != 11 );
    return 0;
}
