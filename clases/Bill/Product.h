#ifndef PRODUCT_H_INCLUDED
#define PRODUCT_H_INCLUDED

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

class Product
{
    private: 
        std::string name;
        std::string description;
        int quantity;
        float price;
    public:
        Product();
        Product(const std::string& line);
        Product(std::string name, std::string description, int quantity, float price);
        //SETTERS
        void set_name(std::string name);
        void set_description(std::string set_description);
        void set_quantity(int quantity);
        void set_price(float price);
        //GETTERS
        std::string get_name() const;
        std::string get_description() const;
        float get_price() const;
        int get_quantity() const;
        //FUNCTIONS
        void save();
        bool is_file_empty();
        friend void reload_product(std::vector<Product>& p);
        friend std::vector<Product> load_products();
        //OVERLOADS
        friend std::ostream &operator<<(std::ostream &os, Product& obj);
        friend std::istream &operator>>(std::istream &is, Product& obj);
        friend bool operator==(const Product &obj, const Product &obj1);
        friend bool operator==(Product &obj, std::string &name);
};

Product::Product()
{
    this->quantity = -1;
}
Product::Product(const std::string &line)
{
    std::string aux;
    std::stringstream stream(line);

    getline(stream, aux, ':');
    getline(stream, aux, '@');
    set_name(aux);
    getline(stream, aux, ':');
    getline(stream, aux, '@');
    set_description(aux);
    getline(stream, aux, ':');
    getline(stream, aux, '@');
    set_quantity(std::stoi(aux));
    getline(stream, aux, ':');
    getline(stream, aux, '@');
    set_price(std::stof(aux));
    getline(stream, aux, '\n');
}
Product::Product(std::string name, std::string description, int quantity, float price)
{
    set_name(name);
    set_description(description);
    set_quantity(quantity);
    set_price(price);
}
void Product::set_name(std::string name)
{
    this->name = name;
}
void Product::set_description(std::string description)
{
    this->description = description;
}
void Product::set_quantity(int quantity)
{
    this->quantity = quantity;
}
void Product::set_price(float price)
{
    this->price = price;
}
std::string Product::get_name() const
{
    return this->name;
}
std::string Product::get_description() const
{
    return this->description;
}
float Product::get_price() const
{
    return this->price;
}
int Product::get_quantity() const
{
    return this->quantity;
}
void reload_product(std::vector<Product>& p)
{
    std::remove("./clases/Bill/product.txt");
    for(auto elem : p)
        elem.save();
}
void Product::save()
{
    std::ofstream file("./clases/Bill/product.txt", std::ios::app);
    if (!file.is_open())
        std::cout << "No se pudo abrir el archivo" << std::endl;
    else
    {
        if(!is_file_empty())
            file << std::endl;
        file << *this;
    }
    file.close();
}
std::vector<Product> load_products()
{
    std::string aux, lines;
    std::vector<Product> products{};
    std::ifstream file("./clases/Bill/product.txt", std::ios::app);

    while(!file.eof())
    {
        for(int cont = 0; cont < 5; cont++)
        {
            getline(file, aux);
            lines += aux + "@";
        }
        Product p = Product(lines);
        products.push_back(p);
        lines = "\0";
    }
    file.close();
    return products;
}
bool Product::is_file_empty()
{
    std::ifstream file("./clases/Bill/product.txt", std::ios::app);
    file.seekg(0,std::ios::end);
    size_t size = file.tellg();
    file.close();
    if(size == 0)
        return true;
    return false;
}
std::ostream &operator<<(std::ostream &os, Product& obj)
{
    return os << "name:" << obj.get_name() << std::endl
              << "description:" << obj.get_description() << std::endl
              << "quantity:" << obj.get_quantity() << std::endl
              << "price:" << obj.get_price() << std::endl;
}
std::istream &operator>>(std::istream &is, Product& obj)
{
    std::string name, description;
    int quantity;
    float price;

    std::cout << "Ingrese el nombre del dulce: ";
    std::cin.ignore();
    getline(is, name);
    std::cout << "Ingrese la descripcion del dulce: ";
    std::cin.clear();
    getline(is, description);
    std::cout << "Ingrese la cantidad en inventariado: ";
    is >> quantity;
    std::cout << "Ingrese el precio del dulce: ";
    is >> price;

    obj = Product(name, description, quantity, price);

    return is;
}
bool operator==(const Product &obj, const Product &obj1)
{
    if(obj.get_name() == obj1.get_name())
         return true;
    return false;
}
bool operator==(Product &obj, std::string &name)
{
    if(obj.get_name() == name)
        return true;
    else
        return false;
}
#endif // PRODUCT_H_INCLUDED