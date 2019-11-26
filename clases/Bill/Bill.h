#include <string>
#include <vector>
#include "Product.h"

class Bill
{
    private:
        int id;
        int idClient;
        float mount;
        std::vector<std::pair<int, Product>> products;
        // date
    public:
        Bill(){};
        //SETTERS
        void set_id(int id);
        void set_idClient(int idClient);
        void set_mount(float mount);
        void set_products(std::vector<std::pair<int, Product>> p);
        void increase_mount(float money);
        void add_product(Product p);
        //GETTERS
        int get_id();
        int get_idClient();
        float get_mount();
        std::vector<std::pair<int, Product>> get_products();
        //FUNCTIONS
        void save();
        int find_product(Product p);
        friend std::vector<Bill> load_bills();
        //OVERLOADS
        friend std::ostream &operator<<(std::ostream &os, Bill& obj);
        friend std::istream &operator>>(std::istream &is, Bill& obj);
};
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
void Bill::add_product(Product p)
{
    int index = find_product(p);
    if(index == -1)
    {
        this->products.push_back(std::make_pair(1,p));   
    }
    else
    {
        this->products[index].first += 1;
    }
    
}
//GETTERS
int Bill::get_id()
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
    for(auto elem : this->products)
    {
        if(elem.second == p)
            return cont;
        cont++;
    }
    return -1;
}
//OVERLOADS
std::ostream &operator<<(std::ostream &os, Bill& obj)
{
    // obj.get_products();
    std::string result = "";

    result += "***********************************" + '\n';
    result += "*id:" + std::to_string(obj.get_id()) + '\n';
    result += "*Id Cliente:" + std::to_string(obj.get_idClient()) + '\n';
    for(auto elem : obj.get_products())
    {
        result += std::to_string(elem.first) + "X  " + elem.second.get_name() + "  c/u  " + std::to_string(elem.second.get_price());
    }
    result += "*Monto:" + std::to_string(obj.get_mount()) + '\n';
    result += "***********************************" + '\n';
    return os << result;
}