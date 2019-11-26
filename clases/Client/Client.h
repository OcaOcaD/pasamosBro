#include <string>
#include <vector>
using namespace std;
class Client
{
    private:
        string phone;
        string name;
        string lastname;
        string address;
    public:
        Client();
        Client( string phone);
        //GETS
        string get_phone();
        string get_name();
        string get_lastname();
        string get_address();
        //SETS
        void set_phone( string phone );
        void set_name( string name );
        void set_lastname( string lastname );
        void set_address( string address );
        //Normal methods
        bool askForData(  );  //Asks the user for data and builds up a client. returns false if the id alredy exists(phone)
        void show();
        string saveString();        //Returns the string that will be saved in the document
};
//-------------------------------------DEFINITIONS-----------------------------------------
Client::Client(){
    this->phone    = "";
    this->name     = "";
    this->lastname = "";
    this->address  = "";
}
Client::Client( string phone ){
    this->phone    = phone;
    this->name     = "";
    this->lastname = "";
    this->address  = "";
}
//**********************************GETS
string Client::get_phone(){
    return this->phone;
}
string Client::get_name(){
    return this->name;
}
string Client::get_lastname(){
    return this->lastname;
}
string Client::get_address(){
    return this->address;
}
//**********************************SETS
void Client::set_phone( string phone ){
    this->phone = phone;
}
void Client::set_name( string name ){
    this->name = name;
}
void Client::set_lastname( string lastname ){
    this->lastname = lastname;
}
void Client::set_address( string address ){
    this->address = address;
}

//**********************************METHODS
bool Client::askForData(  ){
    string aux_string;
    cout << "\t - Ingresa tu télefono (id)" << endl;
    cin >> aux_string;  //phone
    // //Check if the id exists
    // for (size_t i = 0; i < client_book.size(); i++){
    //     if( client_book[i].get_phone() == aux_string )
    //         return false;
    // }
    this->set_phone( aux_string );
    cout << "\t - Ingresa tu NOMBRE sin apellidos " << endl;
    cin >> aux_string;  //name
    this->set_name( aux_string );
    cout << "\t - Ingresa tus apellidos " << endl;
    cin >> aux_string;  //lastname
    this->set_lastname( aux_string );
    cout << "\t - Ingresa tu dirección " << endl;
    cin >> aux_string;  //address
    this->set_address( aux_string );
    return true;
}
void Client::show(){
    cout << "Cliente: " << this->phone << endl;
    cout << "\t" << this->name << " " << this->lastname << " --- " << this->address << endl;
    cout << "_______________________________________________" << endl;
}
/*  Returns the string that is gonna be written in the file. The form is the next 
    10(phone)25(name)25(lastname)25(address)    */
string Client::saveString(){
    string client_string = ""; 
    string aux_string = "";
    int size;
    //Complete the registers to a pecific lenght
    aux_string = this->phone;
    size = 10;
    for( size_t i = aux_string.size(); i < size; i++ ){
        aux_string += " ";
    }
    client_string += aux_string;    //Add attribute
    aux_string = "";                //Clear
    aux_string = this->name;        //Next attribbute
    size = 25;
    for( size_t i = aux_string.size(); i < size; i++ ){
        aux_string += " ";
    }
    client_string += aux_string;    //add Attribute
    aux_string = "";                //cleaC
    aux_string = this->lastname;        //Next attribbute
    size = 25;
    for( size_t i = aux_string.size(); i < size; i++ ){
        aux_string += " ";
    }
    client_string += aux_string;    //Add attribute
    aux_string = "";                //Clear
    aux_string = this->address;     //Next attribbute
    size = 25;
    for( size_t i = aux_string.size(); i < size; i++ ){
        aux_string += " ";
    }
    client_string += aux_string;    //add attribute
    aux_string = "";                //clear
    return client_string;
}