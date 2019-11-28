#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "Order.cpp"
using namespace std;
const string WHITESPACE = " \n\r\t\f\v";
//*******************************************Some declarations of functions
string checkOrders( vector<Order> orders );
Order ask4Order(int last_id);
void writeOrder( Order order );
vector<Order> readOrders( int* count );
void deleteOrder( vector<Order>& orders, string id );
void updateFile( vector<Order> orders );
int stringToInt( string num );
string intToString( int num );
//Utilities
string complete( string  sometext );
string ltrim(const string& s);
string rtrim(const string& s);
string trim(const string& s);
string ltrim(const string& s){
	size_t start = s.find_first_not_of(WHITESPACE);
	return (start == string::npos) ? "" : s.substr(start);
}
string rtrim(const string& s){
	size_t end = s.find_last_not_of(WHITESPACE);
	return (end == string::npos) ? "" : s.substr(0, end + 1);
}
string trim(const string& s){
	return rtrim(ltrim(s));
}
//*******************************************Main options in main program
int main(  ) {
    int id;
    int orders_opt;
    bool exit;
    int last = 0;
    string sid;
    vector<Order> orders;
    //Update the orders of the day
    orders = readOrders( &last );
    do{
        //Get the id of the last order registered
        last = orders.size();        //Last order in the vector. Used to get the last id
        if( last != 0 ){
            // sid = orders[last].get_id();    //Last id in string
            id = stringToInt( orders[last-1].get_id() );  //Last id in int
            id = last;
        }else{
            id = 0;
        }
        // cout << "id to write: "<< id << endl;
        exit = false;
        cout <<"__________________________________________________________________"<< endl;
		cout << "\t--\t -- CANDY SHOP  -- \t--\t" << endl;
		cout <<"__________________________________________________________________"<< endl;
		cout <<"\tSISTEMA DE ORDENES => Elige una opcion:"<<endl;
        cout << "\t\t1) Registrar nueva orden" << endl;
        cout << "\t\t2) Eliminar orden" << endl;
        cout << "\t\t3) Mostrar todas" << endl;
        cout << "\t\t4) Volver a menu principal" << endl;
        cin >> orders_opt;
        switch ( orders_opt ) {
            case 1:{
                //Register new order
                Order newOrder;
                newOrder = ask4Order( id );
                cout << "\tOrden registrada: " << newOrder.get_date() << endl;
                orders.push_back( newOrder );
                break;
            }
            case 2:{
                //Delete certain order
                string delete_id;
                delete_id = checkOrders( orders );
                deleteOrder( orders, delete_id );
                break;
            }
            case 3:{
                //Show orders
                cout << "___________________________________________" << endl;
                cout << "\tOrdenes registradas: " << endl;
                for (size_t i = 0; i < orders.size(); i++){
                    cout << "\t " << i << ") id: " << orders[i].get_id() << orders[i].get_price() << " | " << orders[i].get_date() << endl;
                }
                cout << "___________________________________________" << endl;
                break;  
            }
            case 4:{
                //Go to main menu
                exit = true;
            }
            default:{
                cout << "Elige una opcion correcta, por favor :)" << endl;
                break;
            }
        }
    } while ( exit == false );
    return 0;
}
//The definition of the functions

//Ask for an order and returns the id of the selected one
string checkOrders( vector<Order> orders ){
    string id;
    cout << "Cual orden quieres borrar?" << endl;
    for (size_t i = 0; i < orders.size(); i++){
        cout << "\t " << i << ") " << orders[i].get_id() << orders[i].get_price() << " | " << orders[i].get_date() << endl;
    }
    cin >> id;
    return id;
}

Order ask4Order( int last_id ){
    cout << "Creando una orden" << last_id << endl;
    string actual_id;
    string aux_string = "";
    Order aux_order;
    last_id++;  //The next id writing would be one higher
    actual_id = intToString( last_id );
    aux_order.set_id( actual_id );
    cout << "Cantidad total: " << endl;
    fflush(stdin);
    cin >> aux_string;
    aux_order.set_price( aux_string );
    cout << "Fecha de la orden en formato ddmmaa" << endl;
    cin >> aux_string;
    aux_order.set_date( aux_string );
    // cout << aux_order.get_id() << endl;
    // cout << aux_order.get_price() << endl;
    // cout << aux_order.get_date() << endl;  
    writeOrder( aux_order );
    return aux_order;
}

void writeOrder( Order order ){
    ofstream outFile;
    string path = "orders.txt";
	outFile.open( path.c_str(), std::ios::app);
    vector<string> cadena;
    string id    = order.get_id();
    string price = order.get_price();
    string date  = order.get_date();
    string id_full    = "";
    string price_full = "";
    string date_full  = "";
    id_full   = complete( trim( id ) );
    price_full= complete( trim( price ) );
    date_full = complete( trim( date ) );
    cadena.push_back( id_full );
    cadena.push_back( price_full );
    cadena.push_back( date_full );
    for (size_t i = 0; i < 3; i++){
        outFile << cadena[i];
    }
    outFile.close();
}

vector<Order> readOrders( int *count ){
    vector<Order> orders;
    string path = "orders.txt";
    ifstream inFile;
    inFile.open(path.c_str());
    char data;
    int type = 0;		//Caracterísitica del jugador que se está leyendo
    string aux_string;
    Order o;
    int cont;
    if ( !inFile.fail() ){
        //cout <<"Archivo encontrado"<< endl;
        cont = 0;
        while (inFile >> std::noskipws >> data){
            if( cont == 49 ){
                //Save the field in the corresponding attribute of the Order
                switch ( type ){
                    case 0: //id
                        trim( aux_string );
                        // cout << "\t Readed id: " << aux_string << endl;
                        o.set_id( aux_string );
                        cont = 0;
                        break;
                    case 1: //price
                        trim( aux_string );
                        // cout << "\t Readed price: " << aux_string << endl;
                        o.set_price( aux_string );
                        cont = 0;
                        break;
                    case 2: //date
                        trim( aux_string );
                        // cout << "\t Readed date: " << aux_string << endl;
                        o.set_normal_date( aux_string );
                        cont = 0;
                        // o.set_date( aux_string );
                        break;
                }
                //Clean and redo with next field
                // cout << "Cleaning after type: " << type << endl;
                aux_string = "";
                type++;
                //Order completed. Read next
                if ( type == 3 ){
                    // cout << "Pushed" << endl;
                    orders.push_back( o );   //Pushing the order just readed
                    o.cleanO();
                    type = 0;
                    cont = 0;
                }
            }else{
                aux_string += data;
                // cout << "Building: " << aux_string << endl;
                cont++;
            }
        }//ENDUP READING FILE
    }
    *count = orders.size();
    return orders;
}
//Rewrite the file without the unwanted order
void deleteOrder( vector<Order>& orders, string id ){
    // cout << "id to delete should be: " << id << endl;
    int int_id = 0;
    string file_path = "orders.txt";
    int_id = stringToInt( id );
    // cout << "Borrando: " << int_id << endl;
    orders.erase( orders.begin() + int_id );
    ofstream t;
    t.open(file_path.c_str(), ios::out);
    for (size_t i = 0; i < orders.size(); i++){
        // cout << "ok." << i << endl;
        t << complete( trim( orders[i].get_id() ) );
        // cout << "ok(..)" << i << endl;
        t << complete( trim( orders[i].get_price() ) );
        // cout << "ok[...]" << i << endl;
        t << complete( trim( orders[i].get_date() ) );
    }
    t.close();
    cout << "Ok, eliminado" << endl;
}

//Takes the info of the runtime and overwrites the file.
void updateFile( vector<Order> orders ){
	ofstream outFile;
    string path = "orders.txt";
	outFile.open( path.c_str(), std::ios::app);
	for ( int i = 0; i < sizeof(orders); i++ ){
		writeOrder( orders[i] );
	}
}
//Takes a number in string tyupe and returns it in int type
int stringToInt( string num ){
    stringstream ss;
    int nums;
    ss << num;
    ss >> nums;
    return nums;
}
//Takes a number in int tyupe and returns it in string type
string intToString( int num ){
    stringstream ss;
    string nums;
    ss << num;
    ss >> nums;
    return nums;
}
string complete( string  sometext ){
    //Completes the field to 50 lenght
    string completed = "";
    completed += sometext;
    for( int i = completed.size(); i < 50; i++ ){
        completed += " " ;
        // cout << "Aquí no llego jaja" << i <<endl;
    }
    // cout << "lleguéeeeeeee......"<< completed <<"......" << endl;
    return completed;
}