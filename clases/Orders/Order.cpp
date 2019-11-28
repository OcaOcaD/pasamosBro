#include <string>
using namespace std;
class Order
{
    private:
        string id;
        string price;
        string date;
    public:
        Order();
        //GET
        string get_id(){
            return this->id;
        }
        string get_price(){
            return this->price;
        }
        string get_date(){
            return this->date;
        }
        //SET
        void set_id( string id ){
            this->id = id;
        }
        void set_price( string price ){
            this->price = price;
        }
        void set_normal_date( string datee ){
            this->date = datee;
        }
        void set_date( string datee ){
            // cout << "seting dateeeeeeeeeeeeeeeeeee " << datee <<" that's it."<< endl;
            string aux = "";
            aux += datee[0];
            aux += datee[1];
            aux += '/';
            aux += datee[2];
            aux += datee[3];
            aux += '/';
            aux += datee[4];
            aux += datee [5];
            // cout << "aux: " << aux << endl;
            this->date = aux;
        }
        //
        void cleanO(){
            this->id    = "";
            this->price = "";
            this->date  = "";
        }
        ~Order();
};

Order::Order(){
    this->id    = "";
    this->price = "";
    this->date  = "";
}

Order::~Order(){
}
