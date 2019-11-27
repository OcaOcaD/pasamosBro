#ifndef PRODUCT_H_INCLUDED
#define PRODUCT_H_INCLUDED

#include <string>
#include <sstream>
#include <iostream>

using namespace std;

class Product
{
    public:
        Product();
        ~Product();
        //GETS
		string  get_sup_id();
		string  get_prod_id();
		string  get_stock();
		string  get_name();
		string  get_desc();
		string  get_cost();
		string  get_price();
        //SETS
		void set_sup_id( string sup_id );
		void set_prod_id( string prod_id );
		void set_stock( string stock );
		void set_name( string name );
		void set_desc( string desc );
		void set_cost( string cost );
		void set_price( string price );
		//METHODS
		void buildProductId();
		void buildPrice();

    protected:

    private:
		string sup_id;
		string prod_id;
        string name;
        string desc;
		string stock;
		string cost;
        string price;
};
Product::Product(){
	this->sup_id  = "";
	this->prod_id = "";
	this->name    = "";
	this->desc    = "";
	this->stock   = "";
	this->cost    = "";
	this->price   = "";
}
//*******************************************Dctor
Product::~Product()
{
   //dtor
}
//GETS
string Product::get_sup_id(){
	return this->sup_id;
}
string Product::get_prod_id(){
	return this->prod_id;
}
string Product::get_stock(){
	return this->stock;
}
string Product::get_name(){
	return this->name;
}
string Product::get_desc(){
	return this->desc;
}
string Product::get_cost(){
	return this->cost;
}
string Product::get_price(){
	return this->price;
}
//SETS
void Product::set_sup_id( string sup_id ){
	this->sup_id = sup_id;
}
void Product::set_prod_id( string prod_id ){
	this->prod_id = prod_id;
}
void Product::set_stock( string stock ){
	this->stock = stock;
}
void Product::set_name( string name ){
	this->name = name;
}
void Product::set_desc( string desc ){
	this->desc = desc;
}
void Product::set_cost( string cost ){
	this->cost = cost;
}
void Product::set_price( string price ){
	this->price = price;
}
//METHODS
void Product::buildProductId(){
	string id = "";
	int random;
	for (size_t i = 0; i < 2; i++){
		if( this->name[i] != ' ' )
			id += this->name[i];
	}
	for (size_t i = 0; i < 2; i++){
		if( this->desc[i] != ' ' )
			id += this->desc[i];
	}
	if( this->sup_id[0] != ' ' )
		id += this->sup_id[0];
	this->prod_id = id;
}
void Product::buildPrice(){
	// object from the class stringstream
    stringstream i( this->cost );
    // The object has the cost
    int x = 0;
    i >> x;
    // Now the variable x holds the value equivalent, but integer like 11110000
	float price;
	price = 1.30 * x;
	/*NOW RETURN THE MULTIPLIED VALUE TO STRING*/
	stringstream ss;  
	ss << price;  
	string s;  
	ss >> s;  
	this->price = s;
};
#endif // PRODUCT_H_INCLUDED
