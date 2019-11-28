#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "empleado.h"

#define K 101
#define folk 20000

using namespace std;

void saveIntoFile(Empleado& emp);
vector<int> transform(string);
vector<string> badabum(vector<int>dmwr);
int transformadaDeFourier(int);
int aSerbianFilm(vector<string> nombres);
int something(string xxxsom);
Empleado recoverEmployee(int hash, bool& found);

void empleadoMenu()
{
	int empleado_opt;
	bool exit_employee_hash = false;
	do{
		cout << "1 Agregar empleado" << endl;
		cout << "2 Mostrar empleado" << endl;
		cout << "3 Salir" << endl;
		cout << "Seleccione una opcion:";
		cin >> empleado_opt;
		cin.ignore();
		switch(empleado_opt){
			case 1:{
				//Agregar empleado
				Empleado new_employee;
				cin >> new_employee;
				new_employee.show();
				new_employee.fill();
				saveIntoFile(new_employee);
				break;
			}
			case 2:{
				//Show employee 
				Empleado aux_emp;
				string perfil;
				int hash;
				bool found = false;
				cout << "\tCual es el perfil de tu empleado" << endl;
				cin >> perfil;
				hash = aSerbianFilm(badabum(transform(perfil)));
				Empleado emp = recoverEmployee( hash, found);
				if( found  ){
					emp.show();
				}else{
					cout << "Ese perfil no existe." << endl;
				}
				break;
			}
			case 3:{
				exit_employee_hash = true;
			}
			default:{
				cout << "Opcion inexistente"<< endl;
				break;
			}
		}
	}while( exit_employee_hash == false );
}
void saveIntoFile(Empleado& emp){
	int hash;
	hash = aSerbianFilm(badabum(transform(trim(emp.get_profile()))));

	ofstream file("./clases/Empleado/empleado.txt", ios::in|ios::out);
	file.seekp(hash*60);
	file << emp;
	file.close();
}
vector<int> transform(string key){
	int value;
	int cont=0;
	vector<int> numbers;
	string filled = key;

	//Espacios
	for( int i =filled.size(); i < 12; i++ ){
		filled.append(" ");
	} 

	for(auto c : filled){
		value = (int)filled[cont];
		numbers.push_back(value);
		cont++;
	}
	return numbers;
}
vector<string> badabum( vector<int>dmwr ){
	
	int cont=0;
	string tmp = "";
	vector<string> pairs;

	do{
		for( int i = 0; i < 2; i++ ){
			tmp += to_string(dmwr[cont]);
			cont++;
		}
		pairs.push_back(tmp);
		tmp="\0";
	}while(cont < 12);
	return pairs;
}
int aSerbianFilm(vector<string> nombres)
{
	int x;
	int sum = 0;
    stringstream ss;

	sum = something(nombres[0]);

	for(int cont = 1; cont < nombres.size(); cont++){
		x = something(nombres[cont]);
		sum += x;
		sum = transformadaDeFourier(sum);
	}
    return sum % K;
}
int transformadaDeFourier(int x)
{
	return x % 20000;
}
int something(string xxxsom)
{
	int x;
    stringstream ss;

	ss << xxxsom;
	ss >> x;
	return x;
}
Empleado recoverEmployee( int hash,  bool& found){
	ifstream inFile;
    string path = "./clases/Empleado/empleado.txt";
    int row_count = 0;
	int row_size = 20 + 20 + 20;
	int position = row_size * hash;
	int cont = 0;
	int type = 0;
	char data;
	string aux_string;
	vector<string> jj;
    inFile.open( path.c_str(), ios::app );
    if ( !inFile.fail() ){
		inFile.seekg( position );
        while( inFile >> noskipws >> data && type < 3 ){
			if( cont == 20 ){
				jj.push_back(aux_string);
				aux_string = "";
				cont = 0;
				type++;
			}
			aux_string += data;
			cont++;
		}
		found = true;
		Empleado emp = Empleado(jj);
		return emp;
	}
	found = false;
}










