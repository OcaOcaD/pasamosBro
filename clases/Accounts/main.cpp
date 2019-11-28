#include <iostream>
#include <string>
#include <vector>
#include "switch.h"
using namespace std;
int main(int argc, char const *argv[])
{
    vector<SimpleIndex> simdex;
    vector<int> deleted_list;
    int menu_opt;
    bool exit_menu = false;     //Flag to exit menu
    cout << "Indices simples" << endl;      
    do
    {
        //Look for saved accoutns and index
        simdex = loadIndex();
        deleted_list = loadDeleted();
        if ( !deleted_list.empty() ){
            sort( deleted_list.begin(), deleted_list.end() );
        }
        if ( !simdex.empty() ){
            simdex = abc( simdex );
        }
        //Now continue running the program
        cout << " 1) Registrar nuevo usuario " << endl;  
        cout << " 2) Acceder. (Busqueda binaria) " << endl;  
        cout << " 3) Recuperar cuenta " << endl;  
        cout << " 4) Administración " << endl;
        cout << " 5) Salir " << endl;
        cin >> menu_opt;
        switch ( menu_opt ){
            case 1:{
                //Register new account
                simdex = s_opt_1( simdex, &deleted_list );
                break;
            }
            case 2:{
                //Access account
                simdex = s_opt_2( simdex, &deleted_list );
                break;
            }
            case 3:{
                //Recover account
                s_opt_3( simdex );
                break;
            }
            case 4:{
                s_opt_4( simdex );
                break;
            }
            case 5:{
                exit_menu = true;
                break;
            }
            default:{
                cout << "introduce una opción valida" << endl;
                break;
            }
        }
    } while ( exit_menu == false );
    return 0;
}
