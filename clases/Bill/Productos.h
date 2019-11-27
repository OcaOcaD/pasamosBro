#ifndef PRODUCTOS_H_INCLUDED
#define PRODUCTOS_H_INCLUDED

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

class Productos
{
    private: 
        std::string name;
        std::string description;
        int quantity;
        float price;
    public:
        Productos();
        Productos(const std::string& line);
        Productos(std::string name, std::string description, int quantity, float price);
        //SETTERS
        void set_name(std::string name);
        void set_description(std::string set_description);
        void set_quantity(int quantity);
        void set_price(float price);
        //GETTERS
        float get_price() const;
        int get_quantity() const;
        std::string get_name() const;
        std::string get_description() const;
        //FUNCTIONS
        void save();
        bool is_file_empty();
        friend std::vector<Productos> load_products();
        friend void reload_product(std::vector<Productos>& p);
        //OVERLOADS
        friend bool operator==(Productos &obj, std::string &name);
        friend std::ostream &operator<<(std::ostream &os, Productos& obj);
        friend std::istream &operator>>(std::istream &is, Productos& obj);
        friend bool operator==(const Productos &obj, const Productos &obj1);
};

Productos::Productos()
{
    this->quantity = -1;
}
Productos::Productos(const std::string &line)
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
Productos::Productos(std::string name, std::string description, int quantity, float price)
{
    set_name(name);
    set_description(description);
    set_quantity(quantity);
    set_price(price);
}
void Productos::set_name(std::string name)
{
    this->name = name;
}
void Productos::set_description(std::string description)
{
    this->description = description;
}
void Productos::set_quantity(int quantity)
{
    this->quantity = quantity;
}
void Productos::set_price(float price)
{
    this->price = price;
}
std::string Productos::get_name() const
{
    return this->name;
}
std::string Productos::get_description() const
{
    return this->description;
}
float Productos::get_price() const
{
    return this->price;
}
int Productos::get_quantity() const
{
    return this->quantity;
}
void reload_product(std::vector<Productos>& p)
{
    std::remove("./clases/Bill/product.txt");
    for(auto elem : p)
        elem.save();
}
void Productos::save()
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
std::vector<Productos> load_products()
{
    std::cout << " " << std::endl;
    std::string aux, lines;
    std::vector<Productos> products{};
    std::ifstream file("./clases/Bill/product.txt", std::ios::app);

    while(!file.eof())
    {
        for(int cont = 0; cont < 5; cont++)
        {
            getline(file, aux);
            lines += aux + "@";
        }
        Productos p = Productos(lines);
        products.push_back(p);
        lines = "\0";
    }
    file.close();
    return products;
}
bool Productos::is_file_empty()
{
    std::ifstream file("./clases/Bill/product.txt", std::ios::app);
    file.seekg(0,std::ios::end);
    size_t size = file.tellg();
    file.close();
    if(size == 0)
        return true;
    return false;
}
std::ostream &operator<<(std::ostream &os, Productos& obj)
{
    return os << "name:" << obj.get_name() << std::endl
              << "description:" << obj.get_description() << std::endl
              << "quantity:" << obj.get_quantity() << std::endl
              << "price:" << obj.get_price() << std::endl;
}
std::istream &operator>>(std::istream &is, Productos& obj)
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

    obj = Productos(name, description, quantity, price);

    return is;
}
bool operator==(const Productos &obj, const Productos &obj1)
{
    if(obj.get_name() == obj1.get_name())
         return true;
    return false;
}
bool operator==(Productos &obj, std::string &name)
{
    if(obj.get_name() == name)
        return true;
    else
        return false;
}
#endif // PRODUCTOS_H_INCLUDED