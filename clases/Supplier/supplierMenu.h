#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include "SimpleLinkedList.h"
#include "Proveedor.h"
using namespace std;
//********************************** Declaration of the functions used
int uSure();	//Simple Yes or no confirmation
int askForVendor( SimpleLinkedList<Proveedor> profile );	//Displays a list of current vendors and asks for one. Returns the id of it
string correct_chain( string str );	//Ensures user is not using the delimitator as part of his fields
string no_blank_space( string str );	//Trim a string
SimpleLinkedList<Proveedor> read_profiles( string path );	//Read the document and returns a lsit with vendor objects
void updateFile( SimpleLinkedList<Proveedor> profile, string path );	//Takes the info of the runtime and overwrites the file.
//********************************** Main suppliers program
void supplierMenu(){
    int menu_opt, acc_opt, del_opt;
	bool bad_parameter;
	string path = "./clases/Supplier/user_register.txt";
	string	u_name, u_a, u_e, u_p;	//name, address, email, phone of a vendor
	SimpleLinkedList<Proveedor> profile = read_profiles( path );
	do{
		cout <<"__________________________________________________________________"<< endl;
		cout << "\t--\t -- CANDY SHOP  -- \t--\t" << endl;
		cout <<"__________________________________________________________________"<< endl;
		cout <<"\tSISTEMA DE PROVEEDORES => Elige una opcion:"<<endl;
	    cout << "\t\t1)NUEVO PROVEEDOR." << endl;
	    cout << "\t\t2)ACCEDER." << endl;
	    cout << "\t\t3)TODOS LOS PROVEEDORES." << endl;
	    cout << "\t\t4)SALIR Y GUARDAR." << endl;
	    cin >> menu_opt;
		switch	( menu_opt ){
			case 1:
			{
				//Registrar nuevo proveedor.
				cout << "\t\tNUEVO PROVEEDOR:" << endl;
				fflush(stdin);
				Proveedor u;
				cout << "\tINTRODUCE LOS DATOS DEL PROVEEDOR" << endl;
				cout << "\tNOMBRE =>" << endl;
				getline(cin, u_name);
				fflush(stdin);
				cout << "\tCORREO ELECTRÓNICO =>" << endl;
				getline(cin, u_e);
				cout << "\t OK. \t"<< u_e <<endl;
				fflush(stdin);
				cout << "\t DIRECCION => " << endl;
				getline(cin, u_a);
				cout << "\t OK. "<< u_e << endl;
				fflush(stdin);
				cout << "\t TELEFONO =>";
				cin >> u_p;
				u.set_name( correct_chain( u_name ) );
				u.set_email( correct_chain( no_blank_space(u_e) ) );
				u.set_address( correct_chain( u_a ) );
				u.set_phone( correct_chain( u_p ) );
				profile.add(u);
				// updateFile( profile, path.c_str() );
				cout << endl << "--- OK. PROVEEDOR REGISTRADO --- " << endl;
				break;
			}
			case 2:
			{
				//Acceder.
				fflush(stdin);
				int whatToDo;
				//SELECCIONDE PROVEEDOR
				cout << "\t\tACCEDER A UN proveedor => Selecciona un PROVEEDOR"<<endl;
				acc_opt = askForVendor(profile);
				do
				{
				cout << "\t\tOK. QUE QUIERES HACER?" << endl;
				cout << "\t\t1)Mostrar" << endl;
				cout << "\t\t2)Modificar" << endl;
				cout << "\t\t3)Eliminar" << endl;
					cin >> whatToDo;
				} while ( whatToDo <1 || whatToDo > 3 );
				switch ( whatToDo ){
					case 1:
						cout << "\t\tMOSTRAR PROVEEDOR:" << endl;
							fflush(stdin);
							cout << endl << "\t INFORMACION DE PROVEEDOR " << endl;
							cout << profile[acc_opt].get_name() << endl;
							cout << profile[acc_opt].get_address() << endl;
							cout << profile[acc_opt].get_email() << endl;
							cout << profile[acc_opt].get_phone() << endl;

							cout << "\t . . . " << endl;
					break;
					case 2:
					{
						fflush(stdin);
						Proveedor u;
						cout << "\t\tMODIFICAR PROVEEDOR" << endl;
						//START MODIFYING
						//NAME
						cout << "\t NUEVO NOMBRE => ";
						getline(cin, u_name);
						fflush(stdin);
						//EMAIL
						cout << endl << "\t NUEVO CORREO =>";
						getline(cin, u_e);
						cout << "\t OK. " << u_e  << endl;
						fflush(stdin);
						//ADDRESS
						cout << "\t NUEVA DIRECCION =>";
						getline(cin, u_a);
						fflush(stdin);
						cout << endl << "\t OK. "<< u_a << endl;
						cout << "\t NUEVO TELÉFONO => ";
						getline(cin, u_p);
						/*******Eliminar proveedor actual e ingresar datos nevos*/
						profile.deleteWhere( acc_opt );
						u.set_name( correct_chain( u_name ) );
						u.set_email( correct_chain( no_blank_space(u_e) ) );
						u.set_address( correct_chain( u_a ) );
						u.set_phone( correct_chain( u_p ) );
						profile.add(u);
						// updateFile( profile, path.c_str() );
						cout << endl << "--- OK. PROVEEDOR MODIFICADO--- " << endl;
					
					break;
					}
					case 3:{
						cout << "\t\t ELIMINAR PROVEEDOR: " << endl;
						fflush(stdin);
						if (uSure() == 1){
							/*A BORRAR :)*/
							profile.deleteWhere( acc_opt );
							cout << endl << "--- OK. PROVEEDOR ELIMINADO--- " << endl;
						}else{
							cout << " ### OK. NADA HECHO  ### "<<endl;
						}
					break;
					}
				//ESTAS FUERON LAS 3 OPCIONES PARA HACER CON EL PROVEEDOR
				}
				break;
			}
			case 3:
			{
				//Mostrar todos
				fflush(stdin); 
                cout << "\t \t PERFILES REGISTRADOS: " << endl;
				cout << "\t ___ NOMBRE ___ \t\t ___ address ___ \t\t ___ EMAIL ___"<< endl;
				for (int i = 0; i < profile.getCont(); i++){
					cout << profile[i].get_name() << "\t\t\t" << profile[i].get_address() << "\t\t" << profile[i].get_email() << "\t\t" << endl;
				}
				break;
			}
			case 4:{
				updateFile( profile, path.c_str() );
				break;
			}
			default: {
				cout << "\t\t # # # INTRODUCE UNA OPCION CORRECTA # # #" << endl;
				break;
			}
		//Estas fueron las 4 opciones del menú principal
		}
	} while ( menu_opt != 4 );
}

//********************************** Definition of the functions used
//Functions definitions
//Read the document and returns a lsit with vendor objects
SimpleLinkedList<Proveedor> read_profiles( string path ){
	SimpleLinkedList<Proveedor> profile;
	ifstream inFile;
	inFile.open(path.c_str());
	char data;
	int type = 0;		//Caracterísitica del jugador que se está leyendo
	string aux_name, aux_email, aux_user, aux_phone;
    Proveedor u;
	if ( !inFile.fail() ){
		//cout <<"Archivo encontrado"<< endl;
		while (inFile >> std::noskipws >> data){
		    //cout << "Data: " << data<< " ascii "<<(int)data << "; type: " << type << endl;
		    if ( data == 124 || data == '|' ){	// |
    			//cout << "CAMBIO DE TIPO" << endl;
    			type++;
    		}
    		//Save character
    		switch ( type ){
    			case 0: //Nombre
					if ( data != '|' && data != 10  ){
						aux_name += data;
					}
					break;
				case 1: //address
					if ( data != '|' && data != 10  ){
						aux_user += data;
					}
					break;
				case 2: //mail
					if ( data != '|' && data != 10  ){
						aux_email += data;
					}
					break;
				case 3: //phone
					if ( data != '|' && data != 10  ){
						aux_phone += data;
					}
					break;
    		}
    		//Save profile
    		if ( data == '\r' || data == 10 ){	// Carriege Line
                u.set_name(aux_name);
                u.set_email(aux_email);
                u.set_address(aux_user);
                u.set_phone(aux_phone);
				profile.add(u);
    			type = 0;	//Guardar nombre de nuevo
    			aux_name  = "";
				aux_email = "";
				aux_user  = "";
				aux_phone  = "";
    		}
		}
        return profile;
	}else{
        cout <<" ####ERROR OPENING THE FILE####"<<endl;
        return profile;
	}
}
//Simple Y or N confirmation
int uSure(){
	int ans;
	do{
		cout << "\t Seguro de borrar el proveedor?" << endl;
		cout << "\t1)Si, deseo borrar el proveedor" << endl;
		cout << "\t2)No, cancelar" << endl;
		cin.sync();
		cin >> ans;
		switch( ans ){
			case 1: {
				return 1;
				break;
			}
			case 2: {
				return 0;
				break;
			}
			default:{
				cout << "Si o no?" << endl;
			}
		}	
	} while (ans != 1 || ans != 2);
}
//Ensures user is not using the delimitator as part of his fields
string correct_chain( string str ){
	for( string::size_type i = 0; i < str.size(); i++ ) {
	    if ( str[i] == '|' || str[i] == 10 ){
	    	str[i] = '/';
	    }
	}
	return str;
}
//Trim a string
string no_blank_space( string str ){
	string nice_str;
	for( string::size_type i = 0; i < str.size(); i++ ) {
	    if ( str[i] == ' ' || str[i] == 32 ){
	    }else{
	    	nice_str += str[i];
	    }
	}
	return nice_str;
}
//Displays a list of current vendors and asks for one. Returns the id of it
int askForVendor( SimpleLinkedList<Proveedor> profile ){
	int opc;
	for ( int i = 0; i < profile.getCont(); i++){
			cout << i << ")" << profile[i].get_address() << endl;
	}
	fflush(stdin);
	cout << "Selecciona el proveedor a modificar" << endl;
	do
	{
		cin >> opc;
	} while ( opc > profile.getCont()-1 || opc < 0 );
	return opc;
}
//Takes the info of the runtime and overwrites the file.
void updateFile( SimpleLinkedList<Proveedor> profile, string path ){
	ofstream outFile;
	outFile.open( path );
	for ( int i = 0; i < profile.getCont(); i++ ){
		outFile << profile[i].get_name() << '|' << profile[i].get_address() << '|' << profile[i].get_email() << '|' << profile[i].get_phone() << endl;
	}
}