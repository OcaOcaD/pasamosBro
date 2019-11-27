#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
// #include "SimpleLinkedList.h"
#include "Product.h"
using namespace std;
const string WHITESPACE = " \n\r\t\f\v";
//********************************** Function prototypes
// int uSure();														//Simple Yes or no confirmation
string addSize( string something );									//Concat SIZE of the given string to the string
int askForProduct( SimpleLinkedList<Product> &profile );				//Displays a list of current vendors and asks for one. Returns the id of it
SimpleLinkedList<Product> readP( string path );						//Read the document and returns a lsit with vendor objects
void updateFile( SimpleLinkedList<Product> &profile, string path );	//Takes the info of the runtime and overwrites the file.
//Utilities
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
int stringToInt( string num );
//********************************** Main clients program
void productsMenu(){
    int menu_opt_products, acc_opt, del_opt;
	bool bad_parameter;
	string path = "./clases/Products/user_register.txt";
	string	aux_string;
	SimpleLinkedList<Product> product;
	product = readP( path );
	do{
		cout <<"__________________________________________________________________"<< endl;
		cout << "\t--\t -- CANDY SHOP  -- \t--\t" << endl;
		cout <<"__________________________________________________________________"<< endl;
		cout <<"\tSISTEMA DE PRODUCTOS => Elige una opcion:"<<endl;
	    cout << "\t\t1)NUEVO PRODUCTO."  << endl;
	    cout << "\t\t2)VER PRODUCTO."    << endl;
	    cout << "\t\t3)VER INVENTARIO."  << endl;
	    cout << "\t\t4)SALIR Y GUARDAR." << endl;
	    cin >> menu_opt_products;
		switch	( menu_opt_products ){
			case 1:
			{
				//Registrar nuevo Product.
				cout << "\t\tNUEVO PRODUCTO:" << endl;
				fflush(stdin);
				Product p;
				cout << "\tINTRODUCE LOS DATOS DEL PRODUCTO" << endl;
				cout << "\tNOMBRE => ";
				getline(cin, aux_string);
				p.set_name( aux_string );
				cout << "\t DESCRIPCIÓN => ";
				getline(cin, aux_string);
				p.set_desc( aux_string );
				cout << endl;
				cout << "\t COSTO => ";
				getline(cin, aux_string);
				cout << endl;
				p.set_cost( aux_string );
				p.buildPrice();
				cout << "\t EN EXISTENCIA => ";
				getline(cin, aux_string);
				p.set_stock( aux_string );
				cout << "\t PROVEEDOR => ";
				getline(cin, aux_string);
				p.set_sup_id( aux_string );
				p.buildProductId();
				//Now add the new product to the list
				product.add(p);
				cout << endl << "--- OK. PRODUCTO " << p.get_prod_id() << " REGISTRADO --- " << endl;
				break;
			}
			case 2:
			{
				//Acceder.
				fflush(stdin);
				int whatToDo;
				//SELECCIONDE Product
				cout << "\t\tACCEDER A UN PRODUCTO => Selecciona un PRODUCTO"<<endl;
				acc_opt = askForProduct(product);
				do{
					cout << "\t\tOK. QUE QUIERES HACER?" << endl;
					cout << "\t\t1)Mostrar" << endl;
					cout << "\t\t2)Modificar" << endl;
					cout << "\t\t3)Eliminar" << endl;
					cin >> whatToDo;
				} while ( whatToDo < 1 || whatToDo > 3 );
				switch ( whatToDo ){
					case 1:
						cout << "\t\tMOSTRAR PRODUCTO:" << endl;
							fflush(stdin);
							cout << endl << "\t INFORMACION DE PRODUCTO " << endl;
							cout << "sup_id:  " << product[acc_opt].get_sup_id()  << endl;
							cout << "prod_id: " << product[acc_opt].get_prod_id() << endl;
							cout << "name:    " << product[acc_opt].get_name()    << endl;
							cout << "desc:    " << product[acc_opt].get_desc()    << endl;
							cout << "stock:   " << product[acc_opt].get_stock()   << endl;
							cout << "cost:    " << product[acc_opt].get_cost()    << endl;
							cout << "price:   " << product[acc_opt].get_price()   << endl;

							cout << "\t . . . " << endl;
					break;
					case 2:
					{
						fflush(stdin);
						Product np;
						cout << "\t\tMODIFICAR PRODUCTO" << endl;
						//START MODIFYING
						cout << "\tNOMBRE =>" << endl;
						getline(cin, aux_string);
						np.set_name( aux_string );
						cout << "\t DESCRIPCIÓN =>";
						getline(cin, aux_string);
						np.set_desc( aux_string );
						cout << endl;
						cout << "\t COSTO =>";
						getline(cin, aux_string);
						cout << endl;
						np.set_cost( aux_string );
						np.buildPrice();
						cout << "\t EN EXISTENCIA =>";
						getline(cin, aux_string);
						np.set_stock( aux_string );
						cout << "\t PROVEEDOR =>";
						getline(cin, aux_string);
						np.set_sup_id( aux_string );
						np.buildProductId();
						/*******Eliminar producto actual e ingresar datos nevos*/
						product.deleteWhere( acc_opt );
						product.add( np );
						cout << endl << "--- OK. PRODUCTO MODIFICADO--- " << endl;
					break;
					}
					case 3:{
						cout << "\t\t ELIMINAR PRODUCTO: " << endl;
						fflush(stdin);
						if (uSure() == 1){
							/*A BORRAR :)*/
							product.deleteWhere( acc_opt );
							cout << endl << "--- OK. PRODUCTO ELIMINADO--- " << endl;
						}else{
							cout << " ### OK. NADA HECHO  ### "<<endl;
						}
					break;
					}
				//ESTAS FUERON LAS 3 OPCIONES PARA HACER CON EL Product
				}
				break;
			}
			case 3:
			{
				//Mostrar todos
				fflush(stdin); 
                cout << "\t \t PRODUCTOS REGISTRADOS: " << endl;
				for (int i = 0; i < product.getCont(); i++){
					cout << "\t ___ PRODUCT ID    : " << product[i].get_prod_id() << endl;
					cout << "\t ___ PROVEEDOR ID  : " << product[i].get_sup_id()  << endl;
					cout << "\t ___ NOMBRE        : " << product[i].get_name()    << endl;
					cout << "\t ___ DESCRIPCION   : " << product[i].get_desc()    << endl;
					cout << "\t ___ EN INVENTARIO : " << product[i].get_stock()   << endl;
					cout << "\t ___ COSTO         : " << product[i].get_cost()    << endl;
					cout << "\t ___ PRECIO        : " << product[i].get_price()   << endl;
					cout << "_____________________________________________________________" << endl;
				}
				break;
			}
			case 4:{
				updateFile( product, path.c_str() );
				break;
			}
			default: {
				cout << "\t\t # # # INTRODUCE UNA OPCION CORRECTA # # #" << endl;
				break;
			}
		//Estas fueron las 4 opciones del menú principal
		}
	} while ( menu_opt_products != 4 );
}

//********************************** Function definitions

//Read the document and returns a list with vendor objects
SimpleLinkedList<Product> readP( string path ){
	SimpleLinkedList<Product> inv;
	ifstream inFile;
	inFile.open(path.c_str());
	char data;
	int type;		//Caracterísitica del jugador que se está leyendo
	string aux_sup_id  = "";
	string aux_prod_id = "";
	string aux_stock   = "";
	string aux_name    = "";
	string aux_desc    = "";
	string aux_cost    = "";
	string aux_price   = "";
	bool reading_size;
    Product p;
	string fsize;
	int fsizeInt;
	int fsizeCount;
	int position;
    bool done = false;
	if ( !inFile.fail() ){
		//cout <<"Archivo encontrado"<< endl;
		reading_size = true;
		fsizeCount = 0;
		type = 0;
		while (inFile >> std::noskipws >> data){
			if( reading_size == true && fsizeCount < 4 ){
				// cout << "CONTANDO-" << fsizeCount << "-fsize: " << fsize <<endl;
				fsize += data;
				fsizeCount++;
				if( fsizeCount > 3 ){
					//Finished reading the size of the field
					//- Limpíar fsize de espacios
					trim( fsize );
					// cout << "TRIMED SIZE: "<<fsize<<endl;
					//- Convertir a entero
					fsizeInt = stringToInt( fsize );
					if( fsizeInt == 0 ){
                        // cout << "Reading empty field" << endl;
                        // done = true;
                        break;
                    }
					// cout << "Tamano: " << type << "=> " << fsizeInt << endl;
					//- Comenzar a revisar campo según el tamaño de la cadena|
					fsize = "";
					fsizeCount = 0;
					reading_size = false;
				}
			}else{
				//Save product field
				switch ( type ){
					//prod_id
					case 0:{
						aux_prod_id += data;
						// cout << "Progress: " << aux_prod_id << endl;
					break;
					} 
					//sup_id;
					case 1:{
						aux_sup_id += data;
						// cout << "Progress: " << aux_sup_id << endl;
					break;
					} 
					//name;
					case 2:{
						aux_name += data;
						// cout << "Progress: " << aux_name << endl;
					break;
					} 
					//desc;
					case 3:{
						aux_desc += data;
						// cout << "Progress: " << aux_desc << endl;
					break;
					} 
					//stock;
					case 4:{
						aux_stock += data;
						// cout << "Progress: " << aux_stock << endl;
					break;
					} 
					//cost;
					case 5:{
						aux_cost += data;
						// cout << "Progress: " << aux_cost << endl;
					break;
					} 
					//price;
					case 6:{
						aux_price += data;
						// cout << "Progress: " << aux_price << endl;
					break;
					}
					default:{
						// position = inFile.tellg();
						// cout << "Pos"
						// inFile.seekg(position-1, ios::beg);
						// cout << "algo más????type = "<< type <<endl;
						
					break;
					} 
				}
				cout << "TYPE=> "<<type <<endl;
				cout << " fsizeInf:  " << fsizeInt << "-->";
				fsizeInt--;
				cout << fsizeInt <<endl;
				if( fsizeInt == 0 ){
					type++;
					if( type > 6 ){
						cout << "NEW PRODUCT_____________________" << endl;
						p.set_sup_id( aux_sup_id );
						p.set_prod_id( aux_prod_id );
						p.set_stock( aux_stock );
						p.set_name( aux_name );
						p.set_desc( aux_desc );
						p.set_cost( aux_cost );
						p.set_price( aux_price );
						inv.add(p);
						type = 0;	//Guardar nombre de nuevo
						aux_sup_id  = "";
						aux_prod_id = "";
						aux_name    = "";
						aux_desc    = "";
						aux_stock   = "";
						aux_cost    = "";
						aux_price   = "";
						reading_size = true;
					}else{
						cout << "Cambiando al tipo " << type <<" mientras fsi es "<<fsizeInt<< endl;
						reading_size = true;
					}
				} 
			}
		}
		// cout << "NEW PRODUCT_________out____________" << endl;
		// p.set_sup_id( aux_sup_id );
		// p.set_prod_id( aux_prod_id );
		// p.set_stock( aux_stock );
		// p.set_name( aux_name );
		// p.set_desc( aux_desc );
		// p.set_cost( aux_cost );
		// p.set_price( aux_price );
		// inv.add(p);
		inFile.close();
        return inv;
	}else{
        cout <<" ####ERROR OPENING THE FILE####"<<endl;
        return inv;
	}
}
//Simple Y or N confirmation
// int uSure(){
// 	int ans;
// 	do{
// 		cout << "\t Seguro de borrar el Product?" << endl;
// 		cout << "\t1)Si, deseo borrar el Product" << endl;
// 		cout << "\t2)No, cancelar" << endl;
// 		cin >> ans;
// 		ans = getch();
// 		switch( ans ){
// 			case 1: {
// 				return 1;
// 				break;
// 			}
// 			case 2: {
// 				return 0;
// 				break;
// 			}
// 			default:{
// 				cout << "Si o no?" << endl;
// 			}
// 		}	
// 	} while (ans != 1 || ans != 2);
// }

//Displays a list of current vendors and asks for one. Returns the id of it
int askForProduct( SimpleLinkedList<Product> &profile ){
	int opc;
	for ( int i = 0; i < profile.getCont(); i++){
			cout << i << ")" << profile[i].get_name() << endl;
	}
	fflush(stdin);
	cout << "Selecciona el Product a modificar" << endl;
	do{
		cin >> opc;
	} while ( opc > profile.getCont()-1 || opc < 0 );
	return opc;
}
//Takes the info of the runtime and overwrites the file.
void updateFile( SimpleLinkedList<Product> &inv, string path ){
	cout << "PORQUE NO GUARDO NADAAAAA"<<endl;
	ofstream outFile;
	string XXsup_id ;
	string XXprod_id ;
	string XXstock ;
	string XXname ;
	string XXdesc ;
	string XXcost ;
	string XXprice ;
	outFile.open( path.c_str() );
	for ( int i = 0; i < inv.getCont(); i++ ){
		XXsup_id  = addSize( inv[i].get_sup_id() );
		outFile << XXsup_id;
		XXprod_id = addSize( inv[i].get_prod_id() );
		outFile << XXprod_id;
		XXstock   = addSize( inv[i].get_stock() );
		outFile << XXstock;
		XXname    = addSize( inv[i].get_name() );
		outFile << XXname;
		XXdesc    = addSize( inv[i].get_desc() );
		outFile << XXdesc;
		XXcost    = addSize( inv[i].get_cost() );
		outFile << XXcost;
		XXprice   = addSize( inv[i].get_price() );
		outFile << XXprice;
	}
	outFile.close();
}
//RETUNS A XXXXString where XXXX is the size of the field
string addSize( string something ){
	//int size of the string
    int somsize = something.size();
	//Pass the size to string
	stringstream ss;  
	ss << somsize;  
	string s;
	ss >> s; 
	//Complete the size of the string
	for (int i = s.size(); i < 4; i++)	{
		s += ' ';
	}
	//concat s and something
	string xxxxsomething = "";
	xxxxsomething += s;				//xxxx
	xxxxsomething += something;		//xxxxsomething
	return xxxxsomething;
}
//Utilities

int stringToInt( string num ){
	stringstream ss(num);
	int n;
	ss >> n;
	return n;
}