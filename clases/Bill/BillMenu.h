#include "Bill.h"
#include "Productos.h"
#include <string>
#include <algorithm>

using namespace std;

void menu();
void print_inventory(vector<Productos>& inventory);
void print_bills(vector<Bill>& bills);
Bill still_buying(vector<Productos>& inventory, vector<Bill>& bills, int& quantity);
Productos pick_product(vector<Productos>& inventory, int& quantity);
Productos search_product(vector<Productos>& inventory, string&, int&);
void init_inventory(vector<Productos>& inventory);
void init_registry(vector<Bill>& bills);
void erase_bill(vector<Bill>& bills);
void search_bill(vector<Bill>& bills, int id);
void modify_bill(vector<Bill>& bills, int id, vector<Productos>& inventory, int& quantity);
void reset_idBill(vector<Bill>& bills);

int bill_menu()
{
    int client_opt;
    int quantity;
    string name;
    vector<Bill> bills;
    vector<Productos> inventory;
    
    init_inventory(inventory);
    init_registry(bills);

    do
    {
        menu();
        cin >> client_opt;
        switch(client_opt)
        {
            case 1:{
                Bill b = still_buying(inventory, bills, quantity);
                bills.push_back(b);
                reload_bills(bills);
                break;
            }
            case 2:{
                print_bills(bills);
                break;
            }
            case 3:{
                int id;
                cout << "Ingrese el id de la factura a buscar -> ";
                cin.sync();
                cin >> id;
                search_bill(bills, id);
                break;
            }
            case 4:{
                int id;
                print_bills(bills);
                cout << "Ingrese el id de la factura a modificar -> ";
                cin.sync();
                cin >> id;
                modify_bill(bills, id, inventory, quantity);
                break;
            }
            case 5:{
                erase_bill(bills);
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
Bill still_buying(vector<Productos>& inventory, vector<Bill>& bills, int& quantity)
{        
    string opc;        
    Bill bill = Bill(bills.size()+1, 69);
    do
    {
        print_inventory(inventory);
        auto p = pick_product(inventory, quantity);
        if(p.get_quantity() == -1)
            cout << "No existe el producto";
        else
        {
            bill.add_product(p, quantity);
            
        }
        cout << endl << "Quiere agregar otro? y/n ";
        cin.sync();
        getline(cin, opc);
    }while(opc == "y");

    return bill;
}
Productos pick_product(vector<Productos>& inventory, int& quantity)
{
    string name;
    cout << "Ingrese el nombre del producto: ";
    cin.sync();
    getline(cin, name);
    cout << "Cantidad a comprar: ";
    cin >> quantity;
    return search_product(inventory, name, quantity);
}
Productos search_product(vector<Productos>& inventory, string& name, int& quantity)
{
    Productos p = Productos();
    int cont = 0;
    for(auto elem : inventory)
    {
        if(elem == name)
        {
            if(elem.get_quantity() >= quantity)
            {
                elem.set_quantity(elem.get_quantity()-quantity);
                replace(inventory.begin(), inventory.end(), inventory[cont],elem);
                reload_product(inventory);
                return elem;
            }
        }
        cont++;
    }
    return p;
}
void print_inventory(vector<Productos>& inventory)
{
    cout << "\t************ Productos ************" << endl;
    for(auto elem : inventory)
        cout << elem << endl;
    cout << "\t***********************************" << endl;
}
void print_bills(vector<Bill>& bills)
{
    cout << "\t************ Facturas ************" << endl;
    for(auto elem : bills)
    {
        elem.print_bill();
        cout << endl;
    } 
    cout << "\t***********************************" << endl;
}
void init_registry(vector<Bill>& b)
{
    b = load_bills();
}
void init_inventory(vector<Productos>& p)
{
    p = load_products();
}
void erase_bill(vector<Bill>& bills)
{
    int index;
    print_bills(bills);
    cout << "Ingrese el id de la factura -> ";
    cin.sync();
    cin>>index;
    if(index >= 0 && index <= bills.size())
    {
        bills.erase(bills.begin()+index-1);
        reset_idBill(bills);
        reload_bills(bills);
    }
    else
        cout << "No existe ese id" << endl;
}
void modify_bill(vector<Bill>& bills, int id, vector<Productos>& inventory, int& quantity)
{
    if(id >= 0 && id <= bills.size())
    {
        Bill b = still_buying(inventory, bills, quantity);
        bills.erase(bills.begin()+id-1);
        bills.insert(bills.begin()+id, b);
        reset_idBill(bills);
        reload_bills(bills);
    }
    else
        cout << "No existe ese id" << endl;
}
void search_bill(vector<Bill>& bills, int id)
{
    if(id >= 0 && id <= bills.size())
        bills[id-1].print_bill();
    else
        cout << "No existe ese id" << endl;
}
void reset_idBill(vector<Bill>& bills)
{
    for(int cont = 0; cont < bills.size(); cont++)
        bills[cont].set_id(cont+1);
}
