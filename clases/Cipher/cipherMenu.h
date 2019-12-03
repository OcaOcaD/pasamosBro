#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>

#define KEY 42069
#define ALPHA "abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define SIZE 62
#define PATH "clases/Cipher/clients_book.txt"

using namespace std;

void options();
void cipherMenu();
vector<vector<string>> obtainClient();
vector<string> obtainRegistry(string jj);
string trans(string jj, bool state);
int findI(char);

void cipher(bool state);

void cipherMenu()
{
    int opc;
    do{
        options();
        cin>>opc;
        
        switch(opc){
            case 1:{
                cipher(true);
                break;
            }
            case 2:{
                cipher(false);
                break;
            }
            case 3:{
                break;
            }
            default:{
                cout << "Bruh moment" << endl;
                break;
            }
        }
    }while(opc != 3);
}
void options(){
    cout << "\t1)Encriptar" << endl
         << "\t2)Desencriptar" << endl
         << "\t3)Salir" << endl << endl
         << "Elija una opcion: ";
}
void cipher(bool state){
    string tmp = "";
    vector<string> result;
    vector<vector<string>> clients = obtainClient();
    for(auto clie:clients){
        for(auto jj:clie){
            tmp += trans(jj, state) + "       ";
        }
        result.push_back(tmp);
        tmp="";
    }
    remove(PATH);
    // cout << "size -> " << result.size() << endl; 
    ofstream file(PATH, ios::app);
    for(auto jj:result){
        // cout << "LINE 2.0  " << jj << endl;
        file << jj << endl;
    }
    file.close();
}
string trans(string jj, bool state){
    int index;
    int juas;
    string result = "";

    for(auto c:jj){
        index = findI(c);
        if(state)
            juas = index+(KEY%SIZE);
        else
            juas = index-(KEY%SIZE);
        result += ALPHA[juas];
    }
    return result;
}
int findI(char c){
    int cont = 0;
    for(auto l:ALPHA){
        if(l == c)
            return cont;
        cont++;
    }
    return -1;
}
vector<vector<string>> obtainClient(){
    string tmp;
    string reg;
    vector<vector<string>> result;
    ifstream file(PATH, ios::in);
    while(getline(file, tmp, '\n')){
        // cout << "LINE ->  " << tmp << endl;
        result.push_back(obtainRegistry(tmp));
    }
    file.close();
    return result;
}
vector<string> obtainRegistry(string jj){
    vector<string> lel;
    string tmp;
    istringstream ss(jj);
    do{
        ss >> tmp;
        if(tmp==" ")
            continue;
        else{
            lel.push_back(tmp);
        }
        tmp="";
    }while(ss);
    return lel;
}