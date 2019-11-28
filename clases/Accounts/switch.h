#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "SimpleIndex.h"
#include "Account.h"
using namespace std;
// A recursive binary search function. It returns 
// location of x in given array arr[l..r] is present, 
// otherwise -1 
int binarySearch(vector<SimpleIndex> simdex, int l, int r, string x, int* ind_pos ) 
{ 
    fflush(stdin);
    cout << "Looking for: " << x << endl;
    if (r >= l) { 
        int mid = l + (r - l) / 2; 
  
        // If the element is present at the middle 
        // itself 
        if (simdex[mid].get_key() == x){
            *ind_pos = mid;
            return simdex[mid].get_nrr(); 
        } 
  
        // If element is smaller than mid, then 
        // it can only be present in left subarray 
        if (simdex[mid].get_key() > x) 
            return binarySearch(simdex, l, mid - 1, x, ind_pos); 
  
        // Else the element can only be present 
        // in right subarray 
        return binarySearch(simdex, mid + 1, r, x, ind_pos); 
    } 
  
    // We reach here when element is not 
    // present in array 
    return -1; 
} 

/******
 * Case 1:
 * Registrar nuevo usuario:
 * 
 * ****/

vector<SimpleIndex> s_opt_1( vector<SimpleIndex> simdex, vector<int>* deleted_list ){;
    string name, lastname, username;
    int age;
    bool correct_info;
    int dir;    //Direction where the account gonna be writed
    Account aux_account;
    SimpleIndex aux_ind;
    do{
        
        correct_info = true;
        cout << "INFO\t1\tIntroduce tu nombre" << endl;fflush(stdin);
        cin >> name;
        cout << "INFO\t1\tIntroduce tu apellido" << endl;fflush(stdin);
        cin >> lastname;
        cout << "INFO\t1\tIntroduce el username" << endl;fflush(stdin);
        cin >> username;
        cout << "INFO\t1\tIntroduce tu edad" << endl;fflush(stdin);
        cin >> age;
        //Build auxiliar account to check for repeated keys
        aux_account.set_name( name );
        aux_account.set_lastname( lastname );
        aux_account.set_username( username );
        aux_account.set_age( age );
        aux_account.buildKey();
        //Go through the index to check similar keys
        for (size_t i = 0; i < simdex.size(); i++){
            if ( simdex[i].check4keys( aux_account.get_key() ) ){
                //Equal key found. need another
                correct_info = false;
            }
        }
        if ( correct_info ){
           //Write Account and index row
            aux_ind.set_key( aux_account.get_username() );
            if ( deleted_list->empty() ){
                //IF the deleted list is empty. Write the new account at the end
                cout << "Escribiendo al final del archivo" << endl;
                aux_ind.set_nrr( simdex.size() );
                aux_account.writeAccount();
            }else{
                //There is free space at the middle pf the file. Write there
                cout << "Escribiendo en el nrr libre: "<< dir <<" del archivo" << endl;
                dir = deleted_list->front();
                aux_ind.set_nrr( dir );
                aux_account.writeAccount( dir );
                deleted_list->erase( deleted_list->begin()+0 );
                rewriteDeleted( *deleted_list );
            }
            aux_ind.writeIndexRow();
            simdex.push_back( aux_ind );
            simdex = abc( simdex );
        }else{
            cout << "Esta clave ya existe" << endl;
        }
        
    } while (correct_info == false);
    return simdex;
}
/* Acceder. (Busqueda binaria):
 * Case 2:
 * ****/
vector<SimpleIndex> s_opt_2( vector<SimpleIndex> simdex, vector<int>* deleted_list ){
    ifstream inFile;
    string path = "./clases/Accounts/accounts.txt";
    string acc_string;  //account register with delimitators
    string username;    
    Account acc_acc;    //Accesed account
    //Menu variables
        int position;       //Position in the simdex where the username is found
        int access_opt;
        bool exit_access;
        int index_position;
    //Ask for the register name
    cout << "Introduce tu username" <<endl;
    cin >> username;
    //Binary search for the username on the index
    position = binarySearch( simdex, 0, simdex.size()-1, username, &index_position );
    if( position != -1 ){
        //Username found in the index at position position
        cout << "Lo encontre en el index. Accounts pos: "<< position << endl;
        //Knowing the nrr we can position on the correct place of the file
        acc_acc.accessAccount( position );
        //Check if the account is active or not
        if ( acc_acc.get_state() == 1 ){
            //Active account and data in memory. Show menu
            do{
                exit_access = false;
                cout << "\t1)Mostrar" << endl;
                cout << "\t2)Modificar" << endl;
                cout << "\t3)Eliminar" << endl;
                cout << "\t4)Salir" << endl;
                cin >> access_opt;
                switch ( access_opt ){
                case 1:{
                    //Show account info
                    cout << "\tUsername:\t" << acc_acc.get_username() << endl;
                    cout << "\tNombre:\t" << acc_acc.get_name() << " " << acc_acc.get_lastname() << endl;
                    cout << "\tEdad:\t" << acc_acc.get_age() << endl;
                    cout << "\t____________________" << endl;
                    break;
                }
                case 2:{
                    //Modify info
                    bool exit_modify;
                    int modify_opt;
                    string aux_string;
                    int aux_int;
                    SimpleIndex newIndexRow;
                    do{
                        exit_modify = false;
                        cout << "\t\t1)Modificar nombre" << endl;
                        cout << "\t\t2)Modificar apellido" << endl;
                        cout << "\t\t3)Modificar username" << endl;
                        cout << "\t\t4)Modificar edad" << endl;
                        cout << "\t\t5)Regresar a menú de cuenta" << endl;
                        cin >> modify_opt;
                        switch ( modify_opt ){
                            case 1:{
                                int account_pos;
                                int toDelete;
                                //Modify name
                                fflush(stdin);
                                cout << "\t\tIntroduce el nuevo nombre "<< endl;
                                cin >>aux_string;
                                acc_acc.set_name( aux_string );
                                //Rebuild the key. As the info has changed
                                acc_acc.buildKey();
                                //Replace the account in the file. Now with the modified info
                                acc_acc.replaceAccount( position );
                                //Pop the index at position. As it has changed.
                                account_pos = simdex[position].get_nrr();
                                cout << "Voy a borrar la posicion " << index_position << "del index" <<endl;
                                cout << "Esta contiene la cuenta con el username: " << simdex[index_position].get_key()<<endl;
                                system("pause");
                                simdex.erase(simdex.begin() + index_position);
                                //Set the new index row with the modified data of the accesed account
                                newIndexRow.set_nrr( account_pos );
                                newIndexRow.set_key( acc_acc.get_username() );
                                //Index vector and accounts file corrected. Now push new account in the index
                                simdex.push_back( newIndexRow );
                                simdex = abc( simdex );     //Reorder alphabetically
                                rewriteAllIndex( simdex );
                                cout << "Ok. Modificacion hecha " << endl;
                                break;
                            }
                            case 2:{
                                //Modify lastname
                                cout << "\t\tIntroduce el nuevo apellido "<< endl;
                                cin >>aux_string;
                                acc_acc.set_lastname( aux_string );
                                acc_acc.buildKey();
                                acc_acc.replaceAccount( position );
                                //Pop the index at position. As it has changed.
                                simdex.erase(simdex.begin() + position);
                                //Set the new index row with the modified data of the accesed account
                                newIndexRow.set_nrr( simdex.size() );
                                newIndexRow.set_key( acc_acc.get_username() );
                                //Index vector and accounts file corrected. Now push new account in the index
                                simdex.push_back( newIndexRow );
                                simdex = abc( simdex );     //Reorder alphabetically
                                rewriteAllIndex( simdex );
                                cout << "Ok. Modificacion hecha " << endl;
                                break;
                            }
                            case 3:{
                                //Modify username
                                cout << "\t\tIntroduce el nuevo username "<< endl;
                                cin >>aux_string;
                                acc_acc.set_username( aux_string );
                                acc_acc.buildKey();
                                acc_acc.replaceAccount( position );
                                //Pop the index at position. As it has changed.
                                simdex.erase(simdex.begin() + position);
                                //Set the new index row with the modified data of the accesed account
                                newIndexRow.set_nrr( simdex.size() );
                                newIndexRow.set_key( acc_acc.get_username() );
                                //Index vector and accounts file corrected. Now push new account in the index
                                simdex.push_back( newIndexRow );
                                simdex = abc( simdex );     //Reorder alphabetically
                                rewriteAllIndex( simdex );
                                exit_access = true;
                                cout << "Ok. Modificacion hecha " << endl;
                                break;
                            }
                            case 4:{
                                //Modify age
                                cout << "\t\tIntroduce tu nueva edad "<< endl;
                                cin >>aux_int;
                                acc_acc.set_age( aux_int );
                                acc_acc.buildKey();
                                acc_acc.replaceAccount( position );
                                //Pop the index at position. As it has changed.
                                simdex.erase(simdex.begin() + position);
                                //Set the new index row with the modified data of the accesed account
                                newIndexRow.set_nrr( simdex.size() );
                                newIndexRow.set_key( acc_acc.get_username() );
                                //Index vector and accounts file corrected. Now push new account in the index
                                simdex.push_back( newIndexRow );
                                simdex = abc( simdex );     //Reorder alphabetically
                                rewriteAllIndex( simdex );
                                cout << "Ok. Modificacion hecha " << endl;
                                break;
                            }
                            case 5:{
                                exit_modify = true;
                                break;
                            }
                            
                            default:{
                                cout << "Introduce una opción correcta" << endl;
                                break;
                            }
                        }
                    } while ( exit_modify == false );
                    
                    break;
                }
                case 3:{
                    //Delete account
                    fflush(stdin);
                    bool exit_delete;
                    int exit_opt;
                    SimpleIndex newIndexRow;
                    do{
                        exit_delete = false;
                        cout << "\t\t1)Bloquear temporalmente" << endl;
                        cout << "\t\t2)Eliminar permanentemente" << endl;
                        cout << "\t\t3)Regresar a menú de cuenta" << endl;

                        cin >> exit_opt;
                        switch ( exit_opt )
                        {
                            case 1:{
                                //Block temporary
                                int account_pos;
                                acc_acc.set_state( 0 );
                                account_pos = simdex[position].get_nrr();
                                cout << "Voy a bloquear la posicion " << position << "de las cuentas" <<endl;
                                system("pause");
                                acc_acc.replaceAccount( position );
                                //Pop the index at position. As it has changed.
                                simdex.erase(simdex.begin() + index_position);
                                //Set the new index row with the modified data of the accesed account
                                newIndexRow.set_nrr( account_pos );
                                newIndexRow.set_key( acc_acc.get_username() );
                                //Index vector and accounts file corrected. Now push new account in the index
                                simdex.push_back( newIndexRow );
                                simdex = abc( simdex );     //Reorder alphabetically
                                rewriteAllIndex( simdex );
                                cout << "Ok. Cuenta bloqueada " << endl;
                                exit_delete = true;
                                exit_access = true;
                                break;
                            }
                            case 2:{
                                //Delete permanently
                                int toDelete;
                                //Pop the index at position. As it has changed.
                                system("pause");
                                for (size_t i = 0; i < simdex.size(); i++)
                                {
                                    if ( simdex[i].get_nrr() == position ){
                                        toDelete = i;
                                    }
                                }
                                cout << "Voy a borrar el número" << toDelete<< endl;
                                simdex.erase(simdex.begin() + toDelete);
                                rewriteAllIndex( simdex );
                                //Delete from accounts.txt
                                acc_acc.deleteAccount( position );
                                //Now add the nrr of the deleted account to the deleted list  and the deleted File
                                if( toDelete != simdex.size() ){
                                    deleted_list->push_back( position );
                                    addDeleted( position );
                                }
                                cout << "Ok, Cuenta elimida permanentemente" << endl;
                                exit_delete = true;
                                exit_access = true;
                                break;
                            }
                            case 3:{
                                exit_delete = true;
                                break;
                            }
                            default:{
                                cout << "\t\tIntroduce una opción correcta..." << endl;
                                break;
                            }
                        }
                    } while ( exit_delete == false );
                    
                    break;
                }
                case 4:{
                    exit_access = true;
                    break;
                }
                default:
                    break;
                }
            } while ( exit_access == false );
        }else{
            cout << "Parece que está cuenta ha sido bloqueada" << endl;
            cout << "Intenta recuperrla o accesa a otra diferente" << endl;
            system("pause");
        }
    }else{
        //Not found
        cout << "Nombre de usuario no encontrado" << endl;
        system("pause");
    }
    return simdex;
}
/******
 * Case 3:
 * Recuperar cuenta:
 * 
 * ****/
void s_opt_3( vector<SimpleIndex> simdex ){
    string username;
    int position;
    Account rec_acc;
    SimpleIndex newIndexRow;
    int index_position;
    cout << "Cual es el username de la cuenta a recuperar?" << endl;
    cin >> username;
    //Check if exists
    //Binary search for the username on the index
    position = binarySearch( simdex, 0, simdex.size()-1, username, &index_position );
    if( position != -1 ){
        //Username found in the index at position position
        cout << "Lo encontré!" <<endl;
        //Knowing the nrr we can position on the correct place of the file
        rec_acc.accessAccount( position );
        //Change account status to 1(active) and rewrite
        rec_acc.set_state( 1 );
        rec_acc.replaceAccount( position );
        cout << "Ok. Cuenta desbloqueada " << endl;
    }else{
        //Not found
        cout << "Nombre de usuario no encontrado" << endl;
        system("pause");
    }
}
/******
 * Case 4:
 * Administración:
 * 
 * ****/
void s_opt_4( vector<SimpleIndex> simdex ){ 
    cout << "\t--- INDICE DE CUENTAS ---" << endl;
    cout << "\t-- NRR -- \t->\t -- LLAVE --" << endl;
    for (size_t i = 0; i < simdex.size(); i++){
        cout << "\t\t" << simdex[i].getText() << endl;
    }  

}