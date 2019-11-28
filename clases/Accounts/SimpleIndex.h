#include <string>
#include <sstream>
#include <fstream>
using namespace std;
class SimpleIndex
{
    private:
        string key;
        int nrr;
        int register_size;
    public:
        SimpleIndex();
        int get_nrr();
        int get_register_size();
        string get_key();
        void set_key( string key );
        void set_nrr( int nrr );
        void set_register_size( int register_size );
        ~SimpleIndex();
        //MTHODS
        bool operator<( SimpleIndex comparing );
        bool operator>( SimpleIndex comparing );
        string getText();
        bool check4keys( string key );
        void writeIndexRow();
};
SimpleIndex::SimpleIndex(){
    key         = "--NO KEY--";
    nrr           = -1;
    register_size = -1;
}
SimpleIndex::~SimpleIndex()
{
}
bool SimpleIndex::operator<( SimpleIndex comparing ){
    if( this->key < comparing.get_key() )
        return true;
    else
        return false;
}
bool SimpleIndex::operator>( SimpleIndex comparing ){
    if( this->key > comparing.get_key() )
        return true;
    else
        return false;
}
    //GETS
    string SimpleIndex::get_key(){
        return this->key;
    }
    int SimpleIndex::get_nrr(){
        return this->nrr;
    }
    int SimpleIndex::get_register_size(){
        return this->register_size;
    }
    //SETS
    void SimpleIndex::set_key( string key ){
        this->key = key;
    }
    void SimpleIndex::set_nrr( int nrr ){
        this->nrr = nrr;
    }
    void SimpleIndex::set_register_size( int register_size ){
        this->register_size = register_size;
    }
//METHDS
string SimpleIndex::getText(){
    stringstream ss;
    ss << this->key << " -> " << this->nrr << endl;
    return ss.str();
}
bool SimpleIndex::check4keys( string key ){
    if ( this->key == key ){
        return true;
    }else{
        return false;
    } 
}
void SimpleIndex::writeIndexRow(){
    string path = "./clases/Accounts/index.txt";
    ofstream outFile;
    stringstream ss;
    outFile.open( path.c_str(), ios::out | ios::app );
    ss << this->nrr << "|" << this->key << endl;
    outFile << ss.str();
}
