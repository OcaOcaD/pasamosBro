#ifndef EMPLEADO_H_INCLUDED
#define EMPLEADO_H_INCLUDED

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
const string WHITESPACEE = " \n\r\t\f\v";

//Utilities
string ltrimEmp(const string& s);
string rtrimEmp(const string& s);
string trimEmp(const string& s);
string ltrimEmp(const string& s){
	size_t start = s.find_first_not_of(WHITESPACEE);
	return (start == string::npos) ? "" : s.substr(start);
}
string rtrimEmp(const string& s){
	size_t end = s.find_last_not_of(WHITESPACEE);
	return (end == string::npos) ? "" : s.substr(0, end + 1);
}
string trimEmp(const string& s){
	return rtrimEmp(ltrimEmp(s));
}



class Empleado
{
   private:
     string name;
     string pass;
     string profile;
   public:
      Empleado(){};
      Empleado(vector<string>&);
      Empleado(string name, string pass, string profile);
      string get_name();
      string get_pass();
      string get_profile();
      void set_name( string name );
      void set_pass( string pass );
      void set_profile( string profile );  
      void show();
      void fill();
      friend istream &operator>>(istream& is, Empleado& obj);
      friend ostream &operator<<(ostream& os, Empleado& obj);
};
Empleado::Empleado(vector<string>& jj)
{
   set_name( trimEmp(jj[0]) );
   set_pass( trimEmp(jj[1]) );
   set_profile( trimEmp(jj[2]) );
   fill();
}
Empleado::Empleado(string name, string pass, string profile)
{
   set_name(name);
   set_pass(pass);
   set_profile(profile);
   fill();
}
//***********************dEFINITIONS OF METHODS SOMETHING CAKE
string Empleado::get_name(){
   return this-> name;
}
string Empleado::get_pass(){
   return this-> pass;
}
string Empleado::get_profile(){
   return this-> profile;
}
void Empleado::set_name( string name ){
   this->name = name;
}
void Empleado::set_pass( string pass ){
   this->pass = pass;
}
void Empleado::set_profile( string profile ){
   this->profile = profile;
} 
void Empleado::fill()
{
   for( int i =this->name.size(); i < 20; i++ ){
		this->name.append(" ");
	} 
   for( int i =this->pass.size(); i < 20; i++ ){
		this->pass.append(" ");
	} 
   for( int i =this->profile.size(); i < 20; i++ ){
		this->profile.append(" ");
	} 
} 
void Empleado::show()
{
   cout      << endl << "Nombre : " << this->get_name()
             << endl << "Contrasenia: " << this->get_pass()
             << endl << "Perfil: " << this->get_profile() << endl
             << endl;
}
ostream &operator<<(ostream &os, Empleado& obj){

   return os << obj.get_name() << obj.get_pass() << obj.get_profile();
}
istream &operator>>(istream &is, Empleado& obj){
   string aux = "";
   cout << "\tNombre: " << endl;
   cin.sync();
   getline(is, aux);
   obj.set_name(aux);
   cout << "\tContrasenia: " << endl;
   cin.sync();
   getline(is, aux);
   obj.set_pass(aux);
   cout << "\tPerfil: " << endl;
   cin.sync();
   getline(is, aux);
   obj.set_profile(aux);

   return is;
}

#endif // EMPLEADO_H_INCLUDED


// vector<int> transform(string key)
// vector<string> badabum( vector<int>dmwr )
// int aSerbianFilm(vector<string> nombres)