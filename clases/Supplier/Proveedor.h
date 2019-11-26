#ifndef USUARIO_H
#define USUARIO_H
#include <string>
#include <sstream>
using namespace std;

class Proveedor
{
    public:
        Proveedor();
        //GETS
    	string get_name();
        string get_email();
        string get_address();
        string get_phone();
        //SETS
        void set_name( string name );
		void set_email( string email );
		void set_address( string address );
		void set_phone( string phone );
		//METHODS

		bool validate_address( string address );
		bool validate_email( string email );

        ~Proveedor();

    protected:

    private:
        string name;
        string email;
        string address;
        string phone;

};

Proveedor::Proveedor(){
    this->name = "";
	this->email = "";
	this->address = "";
	this->phone = "";
}
//********************************************GETS
string Proveedor::get_name(){
	return this->name;
}

string Proveedor::get_email(){
    return this->email;
}

string Proveedor::get_address(){
	return this->address;
}

string Proveedor::get_phone(){
	return this->phone;
}
//********************************************SETS
void Proveedor::set_name(string name){
	this->name = name;
}

void Proveedor::set_email(string email){
	this->email = email;
}

void Proveedor::set_address(string address){
	this->address = address;
}

void Proveedor::set_phone(string phone){
	this->phone = phone;
}
//*******************************************Methods
bool Proveedor::validate_address( string address ){			//Returns false if the user alredy exists
	bool state;
	state = ( this->address == address ) ? false : true;
	return state;
}
bool Proveedor::validate_email( string email ){				//Returns false if the email alredy exists
	bool state;
	state = ( this->email == email ) ? false : true;
	return state;
}
//*******************************************Dctor
Proveedor::~Proveedor()
{
   //dtor
}


#endif // USUARIO_H
