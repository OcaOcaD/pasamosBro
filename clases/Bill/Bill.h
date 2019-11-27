#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include "Product.h"


void split_s(std::string& line, char c);

class Bill
{
    private:
        int id;
        int idClient;
        float mount = 0.0;
        std::vector<std::pair<int, Product>> products;
    public:
        Bill(){};
        ~Bill();
        Bill(const std::string &line);
        Bill(int id, int idClient);
        //SETTERS
        void set_id(int id);
        void set_idClient(int idClient);
        void set_mount(float mount);
        void set_products(std::vector<std::pair<int, Product>> p);
        void increase_mount(float money);
        void add_product(Product p, int quantity);
        //GETTERS
        int get_id() const;
        int get_idClient();
        float get_mount();
        std::vector<std::pair<int, Product>> get_products();
        //FUNCTIONS
        void save();
        friend std::vector<Bill> load_bills();
        int find_product(Product p);
        bool is_file_empty();
        void print_bill();
        friend void reload_bills(std::vector<Bill>& b);
        //OVERLOADS
        friend std::ostream &operator<<(std::ostream &os, Bill& obj);
        friend std::istream &operator>>(std::istream &is, Bill& obj);
        friend bool operator==(Bill &obj, int &id);

};
Bill::Bill(int id, int idClient)
{
    this->id = id;
    this->idClient = idClient;
    this->mount = 0.0;
}
Bill::Bill(const std::string &line)
{
    std::string aux;
    std::stringstream stream(line);

    getline(stream, aux, ':');
    getline(stream, aux, '@');
    set_id(std::stoi(aux));
    getline(stream, aux, ':');
    getline(stream, aux, '@');
    set_idClient(std::stoi(aux));
    this->mount = 0.0;
}
Bill::~Bill()
{
    this->id = 0;
    this->idClient = 0;
    this->mount = 0.0;
    this->products.clear();
}
std::vector<Bill> load_bills()
{
    Product p;
    Bill b;
    size_t pos;
    std::vector<Bill> bills{};
    std::string aux, lines, tmp;
    std::ifstream file("./clases/Bill/bill.txt", std::ios::app);

    while(!file.eof())
    {
        while(true)
        {
            if(b.get_mount() == 0)
            {
                for(int cont=0; cont<2; cont++)
                {
                    getline(file, aux);
                    tmp += aux + "@";
                }
                b = Bill(tmp);
            }
            while(aux!="%")
            {
                getline(file, aux);
                lines += aux + "@";
                pos = (lines.begin(), lines.end(), '@');
                if(pos >= 4)
                    break; 
            }
            for(int cont = 0; cont < 4; cont++)
            {
                getline(file, aux);
                lines += aux + "@";
                pos = lines.find("price:");
                if(pos != -1)
                {
                    getline(file, aux);
                    tmp += aux;
                    p = Product(lines);
                    if(tmp != "\0")
                    {
                        pos = tmp.find("earned:");
                        tmp = tmp.substr(pos+7);
                        split_s(tmp, '@');
                        b.add_product(p, std::stoi(tmp));
                    }       
                    break;
                }
            }
            
            if(b.get_mount() == 0)
            {
                getline(file, aux);
                tmp += aux + "@";
            }
            do
            {
                getline(file, aux);
            }while(aux!="%");
            getline(file, aux); // este mero
            pos = aux.find("Monto");
            if(pos == -1 || pos > 3000)
            {
                lines = "\0";
                tmp = "\0";
                lines += aux + "@";
            }
            else
            {
                getline(file, aux); 
                lines = "\0";
                tmp = "\0";
                break;
            }
        }
        bills.push_back(b);
        b.~Bill();
    }
    return bills;
}
void split_s(std::string& line, char c)
{
    std::string result = "";
    for(auto e : line)
    {
        if(e != c)
            result += e;
        else
            break;
    }
    line = result;
    // return result;
}
//SETTERS
void Bill::set_id(int id)
{
    this->id = id;
}
void Bill::set_idClient(int idClient)
{
    this->idClient = idClient;
}
void Bill::set_mount(float mount)
{
    this->mount = mount;
}
void Bill::set_products(std::vector<std::pair<int, Product>> p)
{
    this->products = p;
}
void Bill::increase_mount(float money)
{
    this->mount += money;
}
void Bill::add_product(Product p, int quantity)
{
    int index = find_product(p);
    if(index == -1)
    {
        this->products.push_back(std::make_pair(quantity,p));
    }
    else
    {
        this->products[index].first += quantity;
    }
    increase_mount(p.get_price()*quantity);   
}
//GETTERS
int Bill::get_id() const
{
    return this->id;
}
int Bill::get_idClient()
{
    return this->idClient;
}
float Bill::get_mount()
{
    return this->mount;
}
std::vector<std::pair<int, Product>> Bill::get_products()
{
    return this->products;
}
//FUNCTIONS
int Bill::find_product(Product p)
{
    int cont = 0;
    for(auto elem : get_products())
    {
        if(elem.second == p)
        {
            std::cout << "<- " << elem.second.get_name() << " -> " << p.get_name() << std::endl;
            return cont;
        }
        cont++;
    }
    return -1;
}
void reload_bills(std::vector<Bill>& b)
{
    std::remove("./clases/Bill/bill.txt");
    for(auto elem : b)
        elem.save();
}
void Bill::save()
{
    std::ofstream file("./clases/Bill/bill.txt", std::ios::app);
    if (!file.is_open())
        std::cout << "No se pudo abrir el archivo" << std::endl;
    else
    {
        if(!is_file_empty())
            file << std::endl;
        file << *this;
    }
}
bool Bill::is_file_empty()
{
    std::ifstream file("./clases/Bill/bill.txt", std::ios::app);
    file.seekg(0,std::ios::end);
    size_t size = file.tellg();
    file.close();
    if(size == 0)
        return true;
    return false;
}
void Bill::print_bill()
{
    std::string result = "";
    // std::cout << "size: " << get_products().size();
    result += "***********************************" + '\n';
    result += "\nid:" + std::to_string(get_id()) + '\n';
    result += "Id Cliente:" + std::to_string(get_idClient()) + '\n';
    for(auto elem : get_products())
    {
        result += std::to_string(elem.first) + "x  " + elem.second.get_name() + "  c/u  " + std::to_string(elem.second.get_price());
        result += "\n";
    }
    result += "\nMonto:" + std::to_string(get_mount()) + "\n";
    result += "***********************************" + '\n';
    std::cout << result << std::endl;
}
//OVERLOADS
std::ostream &operator<<(std::ostream &os, Bill& obj)
{
    // obj.get_products();
    std::string result = "";

    result += "id:" + std::to_string(obj.get_id()) + '\n';
    result += "Id Cliente:" + std::to_string(obj.get_idClient()) + '\n';
    result += "%\n";
    for(auto elem : obj.get_products())
    {
        result += "name:" + elem.second.get_name() + '\n' +
                  "description:" + elem.second.get_description() + '\n' +
                  "quantity:" + std::to_string(elem.second.get_quantity()) + '\n' +
                  "price:" + std::to_string(elem.second.get_price()) + '\n';

        result += "earned:" + std::to_string(elem.first) + '\n' + "%\n";
    }
    result += "Monto:" + std::to_string(obj.get_mount()) + '\n';

    return os << result;
}
bool operator==(Bill &obj, int &id)
{
    if(obj.get_id() == id)
        return true;
    return false;
}
// std::istream &operator>>(std::istream &is, Bill& obj)
// {
//     std::vector<Product> p = load_products();
//     std::cout << "\t************ Productos ************" << std::endl;
//     for(auto elem : p)
//         std::cout << elem << std::endl;
//     std::cout << "\t***********************************" << std::endl;
// }