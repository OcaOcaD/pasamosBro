#include <string>
#include <iostream>
#include <fstream>
#include "functions.h"

using namespace std;
class Account
{
private:
    int age;
    int state;
    string key;
    string name;
    string lastname;
    string username;

public:
    Account();
    ~Account();
    //MTHDS
    void buildKey();
    void writeAccount();
    void writeAccount( int nrr );
    void accessAccount( int nrr );
    void distributeAccount( string acc_string );
    void replaceAccount( int nrr );
    void deleteAccount( int nrr );
        //GETS
        int get_age();
        string get_key();
        string get_name();
        string get_lastname();
        string get_username();
        int get_state();
        //SETS
        void set_age( int age );
        void set_key( string key );
        void set_name( string name );
        void set_lastname( string lastname );
        void set_username( string username );
        void set_key( int key );
        void set_state( int state );

};

Account::Account()
{
    key      = "NO-KEY";
    age      = 0;
    name     = "--NO NAME YET--";
    lastname = "--NO LASTNAME--";
    username = "--NO USERNAME--";
    state    = 1; 
}
Account::~Account()
{
}
//MTHDS
    void Account::buildKey(){
        //Creates a key based on the attribs
        string x = intToStringAccounts( age );
        this->key = "";
        this->key += lastname[0];
        this->key += username[0];
        this->key += name[0];
        this->key += x;
    }
    void Account::writeAccount(){
        string path = "./clases/Accounts/accounts.txt";
        ofstream outFile;
        stringstream ss;
        outFile.open( path.c_str(), ios::out | ios::app );
        ss << this->key << "|" << this->name << "|" << this->lastname << "|" << this->username << "|" << this->age << "|" << this->state << endl;
        outFile << ss.str();
        outFile.close();
    }
    void Account::writeAccount( int nrr ){
        ifstream inFile;
        string path = "./clases/Accounts/accounts.txt";
        string acc_string;
        stringstream ss;
        vector<string> replacingFile;
        int cont = 0;
        inFile.open( path.c_str(), ios::app );
        if ( !inFile.fail() ){
            while( getline(inFile, acc_string) ){
                //When the free nrr is reached. Place the new account. if not. keep the same info
                if ( cont == nrr ){
                    //Write the new account here
                    ss << this->key << "|" << this->name << "|" << this->lastname << "|" << this->username << "|" << this->age << "|" << this->state;
                    ss >> acc_string;
                    replacingFile.push_back( acc_string );
                }else{
                    //Mantein the accounts the same.
                    replacingFile.push_back( acc_string );
                }
                cont++;
            }
            inFile.close();
            rewriteAccounts( replacingFile );
        }
    }
    void Account::distributeAccount( string acc_string ){
        cout << "exploding: " << acc_string << endl;
        vector<string> account_part;
        account_part = explode( acc_string, '|' );
        this->key      = account_part[0];
        this->name     = account_part[1];
        this->lastname = account_part[2];
        this->username = account_part[3];
        this->age      = stringToInt( account_part[4]);
        this->state    = stringToInt( account_part[5]);
    }
    void Account::accessAccount( int nrr ){
        ifstream inFile;
        string path = "./clases/Accounts/accounts.txt";
        string acc_string;
        int cont = 0;
        inFile.open( path.c_str(), ios::app );
        if ( !inFile.fail() ){
            while( getline(inFile, acc_string) ){
                if ( cont ==nrr ){
                    inFile.close();
                    this->distributeAccount( acc_string );
                }
                cont++;
            }
        }
    }
    void Account::replaceAccount( int nrr ){
        ifstream inFile;
        string path = "./clases/Accounts/accounts.txt";
        string acc_string;
        vector<string> replacingFile;
        stringstream ss;
        int cont = 0;
        inFile.open( path.c_str(), ios::app );
        if ( !inFile.fail() ){
            while( getline(inFile, acc_string) ){
                if ( cont == nrr ){
                    //If the replacing account. Rewrite it
                    ss << this->key << "|" << this->name << "|" << this->lastname << "|" << this->username << "|" << this->age << "|" << this->state;
                    ss >> acc_string;
                    replacingFile.push_back( acc_string );
                }else{
                    //If not the replacing account. Copy it the same
                    replacingFile.push_back( acc_string );
                }
                cont++;
            }
            //Now delete the past accoutns and replace it with the correct modified information
            inFile.close();
            rewriteAccounts( replacingFile );
            //Accounts corrected. Now correct the index ( do it from the switch )  rewriteIndex( nrr );
        }
        
    }
    void Account::deleteAccount( int nrr ){
        ifstream inFile;
        string path = "./clases/Accounts/accounts.txt";
        string acc_string;
        vector<string> replacingFile;
        stringstream ss;
        int cont = 0;
        inFile.open( path.c_str(), ios::app );
        if ( !inFile.fail() ){
            while( getline(inFile, acc_string) ){
                if ( cont == nrr ){
                    //Print a blank row so hte program doesn't trip
                    acc_string = " ";
                    replacingFile.push_back( acc_string );
                }else{
                    //If not the replacing account. Copy it the same
                    replacingFile.push_back( acc_string );
                }
                cont++;
            }
            //Now delete the past accoutns and replace it with the correct modified information
            inFile.close();
            rewriteAccounts( replacingFile );
            //Accounts corrected. Now correct the index ( do it from the switch )  rewriteIndex( nrr );
        }
    }
        //GETS
        int Account::get_age(){
            return this->age;
        }
        string Account::get_key(){
            return this->key;
        }
        string Account::get_name(){
            return this->name;
        }
        string Account::get_lastname(){
            return this->lastname;
        }
        string Account::get_username(){
            return this->username;
        }
        int Account::get_state(){
            return this->state;
        }
        //SETS
        void Account::set_key( string key ){
            this->key = key;
        }
        void Account::set_age( int age ){
            this->age = age;
        }
        void Account::set_name( string name ){
            this->name = name;
        }
        void Account::set_lastname( string lastname ){
            this->lastname = lastname;
        }
        void Account::set_username( string username ){
            this->username = username;
        }
        void Account::set_key( int key ){
            this->key = key;
        }
        void Account::set_state( int state ){
            this->state = state;
        }
