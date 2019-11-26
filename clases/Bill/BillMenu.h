// #include "Bill.h"
#include "Product.h"
#include <string>

using namespace std;

void menu();
void print_inventory(vector<Product>& inventory);
void init_inventory(vector<Product>& inventory);

int bill_menu()
{
    int client_opt;
    vector<Product> inventory;
    init_inventory(inventory);
    do
    {
        menu();
        cin >> client_opt;
        switch(client_opt)
        {
            case 1:{
                print_inventory(inventory);
                break;
            }
            case 2:{
                break;
            }
            case 3:{
                break;
            }
            case 4:{
                break;
            }
            case 5:{
                break;
            }
            case 6:{
                break;
            }
            default:{
                return 0;
                break;
            }
        }
    }while(client_opt != 6);
    return 0;
}

void menu()
{
    cout << "\t************ Facturar ************" << endl
         << "\t1)Agregar" << endl
         << "\t2)Imprimir" << endl
         << "\t3)Buscar" << endl
         << "\t4)Modificar" << endl
         << "\t5)Eliminar" << endl
         << "\t6)Salir" << endl << endl
         << "Elija una opcion:  ";
}
void print_inventory(vector<Product>& inventory)
{
    cout << "\t************ Productos ************" << endl;
    for(auto elem : inventory)
        cout << elem << endl;
    cout << "\t***********************************" << endl;
}
void init_inventory(vector<Product>& p)
{
    p = load_products();
}