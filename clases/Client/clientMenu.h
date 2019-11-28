#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "Client.h"

using namespace std;

//********************************** Some data types used int he lists
struct Word{
    //Secondary index. Has words and its position in the indexes file.
    string word;
    int position_in_index;
};
struct Index_row{
    //Index with nrr and and its aparition in the clients file.
    int nrr;
    int next;
};
//********************************** Declaration of the functions used
void initializeClients( vector<Word>& vocabulary, vector<Index_row>& index );
void saveClient( Client c, vector<Word>& vocabulary, vector<Index_row>& indexd );    //Do the pushes in all the lists correctly
vector<Client> recoverClient( string search_string, vector<Word>& vocabulary, vector<Index_row>& index );
void initializeClients( vector<Word>& vocabulary, vector<Index_row>& index );  
// Do the pushes in all the lists correctly 
// vector<Client>& clients_book
void saveClient( Client c, vector<Word>& vocabulary, vector<Index_row>& index ); 
Client getClientInfo( int nrr );
void deleteClient( int nrr, Client oldClient, vector<Index_row>& index, vector<Word>& vocabulary );
void modifyClient( int nrr, Client oldClient, Client newClient, vector<Index_row>& index, vector<Word>& vocabulary );
void replaceVocabularyFile( vector<Word> vocabulary );
int inVocabulary( vector<Word>& vocabulary, string searchedWord );
void replaceIndexFile( vector<Index_row> index );
//Utility
int stringToInt( string data );
int getTotalClients();  //returns the nrr based on the number of registers in the file

//********************************** Main clients program
void clientsMenu(){
    bool exit_client_menu = false;
    int client_opt;
    //Initialize lists with info in the files
    //Secondary index
    vector<Word> vocabulary;            //secondary index. Has words and its position in the indexes file.
    //Main index
    vector<Index_row> index;            //Index with nrr and and its aparition in the clients file.
    initializeClients( vocabulary, index );   //load clients from files
    do{
        cout << "Opciones sobre clientes..." << endl;
        cout << "\t 1) Registrar cliente" << endl;
        cout << "\t 2) Buscar y mostrar cliente" << endl;
        cout << "\t 3) Modificar cliente" << endl;
        cout << "\t 4) Eliminar cliente" << endl;
        cout << "\t 5) Mostrar listas" << endl;
        cout << "\t 6) Guardar y salir al menu principal" << endl;
        cin >> client_opt;
        switch (client_opt){
            case 1:{
                //Register new client. Create one and build it
                Client new_client;
                if ( new_client.askForData( ) ){
                    saveClient( new_client, vocabulary, index );
                    cout << "_____________________________________________" << endl; 
                }
                
                break;
            }//*************************** End of case register
            case 2:{
                //Search for a client
                int search_client_opt;
                string search_string = "";
                vector<Client> results;
                do{
                    cout << "Buscar cliente por..." << endl;
                    cout << "\t  1)Telefono" << endl;
                    cout << "\t  2)Nombre" << endl;
                    cout << "\t  3)Apellido" << endl;
                    cout << "\t  4)Volver a menu de clientes" << endl;
                    cin >> search_client_opt;
                    switch (search_client_opt){
                        case 1:{
                            cout << "Ingresa el telefono del cliente" << endl;
                            cin >> search_string;
                            results = recoverClient( search_string, vocabulary, index );
                            for( int i = 0; i < results.size(); i++ ){
                                // results[i].show();
                            }
                            break;
                        }
                        case 2:{
                            cout << "Ingresa el nombre del cliente" << endl;
                            cin >> search_string;
                            results = recoverClient( search_string, vocabulary, index  );
                            for( int i = 0; i < results.size(); i++ ){
                                // results[i].show();
                            }
                            break;
                        }
                        case 3:{
                            cout << "Ingresa el apellido del cliente" << endl;
                            cin >> search_string;
                            results = recoverClient( search_string, vocabulary, index  );
                            for( int i = 0; i < results.size(); i++ ){
                                // results[i].show();
                            }
                            break;
                        }
                        case 4:{
                            cout << "Regresando al menu de clientes" << endl;
                            break;
                        }
                        default:{
                            cout << "Inserta una opción valida, por fa" << endl;
                            break;
                        }
                    }
                } while ( search_client_opt != 4 );
                break;
            }//*************************** Search for client
            case 3:{
                //Modify client
                string m_phone = "";
                Client oldClient;
                int pi, nrr;    //position in index and nrr
                Client newClient;
                cout << " Inserta tel telefono del cliente a modificar" << endl;
                cin >> m_phone;
                pi = inVocabulary( vocabulary, m_phone );   //If the phone is in the vocabulary. Get the position in the index to recover the nrr
                if( pi != -1 ){
                    //Search the position in the index
                    nrr = index[pi].nrr;
                    //Ask for the new info
                    oldClient = getClientInfo( nrr );
                    newClient.askForData();
                    modifyClient(nrr, oldClient, newClient, index, vocabulary );
                }else{
                    cout << "No hay conincidencias" << endl;
                }
                break;
            }//*************************** Modify for client
            case 4:{
                //Delete client
                string m_phone = "";
                Client oldClient;
                int pi, nrr;    //position in index and nrr
                Client newClient;
                cout << " Inserta tel telefono del cliente a modificar" << endl;
                cin >> m_phone;
                pi = inVocabulary( vocabulary, m_phone );   //If the phone is in the vocabulary. Get the position in the index to recover the nrr
                if( pi != -1 ){
                    //Search the position in the index
                    nrr = index[pi].nrr;
                    oldClient = getClientInfo( nrr );
                    deleteClient( nrr, oldClient, index, vocabulary );
                }else{
                    cout << "No hay conincidencias" << endl;
                }
                break;
            }//*************************** Delete for client
            case 5:{
                cout << "_____________________________________________" << endl; 
                cout << "Vocabulario: " << endl;
                cout << "Apellido\tPrimera aparicion en index" << endl;
                for( size_t i = 0; i < vocabulary.size(); i++ ){
                    cout << vocabulary[i].word <<" \t " << vocabulary[i].position_in_index << endl;
                }
                cout << "_____________________________________________" << endl; 
                cout << "Indice: " << endl;
                cout << "NRR\tSiguiente coincidencia" << endl;
                for( size_t i = 0; i < vocabulary.size(); i++ ){
                    cout << index[i].nrr <<" \t " << index[i].next << endl;
                }
                cout << "_____________________________________________" << endl;                   
                break;
            }//*************************** End of case show lists
            case 6:{
                //Save lists to files.
                replaceVocabularyFile( vocabulary );
                // replaceClientsFile( clients_book );
                replaceIndexFile( index );
                break;
            }//*************************** End of case save

            default:{

                break;
            }
        }   //End of clients switchmenu
    } while (  client_opt != 6 );
}//End of clients

//********************************** Definitions of some functions used up in clients program
void initializeClients(  vector<Word>& vocabulary, vector<Index_row>& index ){
    //Reading vocabulary and filling the vocabulary list
    ifstream inFile;
    string path = "./clases/Client/vocabulary.txt";
    string data = "";
    bool word_or_position = true;   //true means reading a word. False means reading the position of the word
    Word new_word;
    int position;
    inFile.open( path.c_str(), ios::app );
    if ( !inFile.fail() ){
        while( inFile >> data ){
            if( word_or_position ){
                new_word.word = data;
            }else if( !word_or_position ){
                position = stringToInt( data ); //Convert the id readed as string to integer
                new_word.position_in_index = position;
                vocabulary.push_back( new_word );   //Adding the new register
            }
            //Clear string and change the reading type
            data = "";
            word_or_position = !word_or_position;
        }
    }
    inFile.close();
    //Now filling the index file
    path = "./clases/Client/index.txt";
    data = "";
    bool nrr_or_next = true;   //true means reading a nrr. False means reading the position of the next position
    Index_row new_row;
    inFile.open( path.c_str(), ios::app );
    if ( !inFile.fail() ){
        while( inFile >> data ){
            if( nrr_or_next ){
                new_row.nrr = stringToInt( data );
            }else if( !nrr_or_next ){
                new_row.next = stringToInt( data );
                index.push_back( new_row );
            }
            //Clear string and change the reading type
            data = "";
            nrr_or_next = !nrr_or_next;
        }
    }
    inFile.close();
}
int inVocabulary( vector<Word>& vocabulary, string searchedWord ){
    for( size_t i = 0; i < vocabulary.size(); i++ ){
        if( trim(vocabulary[i].word) == trim(searchedWord) )
            return vocabulary[i].position_in_index;
    }
    return -1;
}
void deleteFromVocabularyAndIndex( vector<Index_row>& index, vector<Word>& vocabulary, string word ){
    int pi = -69;
    int oldpi;
    for( size_t i = 0; i < vocabulary.size(); i++ ){
        // cout << trim(vocabulary[i].word) <<"is not"<< trim(word) << endl;
        if( trim(vocabulary[i].word) == trim(word) ){
            // cout << "it is" << endl;
            vocabulary[i].word = "#deleted#";
            pi = vocabulary[i].position_in_index;
            vocabulary[i].position_in_index = -1;
            break;
        }
    }
    // cout << "the first app of " << word << "was on: " << pi << endl;
    index[pi].nrr = -1;
    oldpi = pi;
    // index[pi].next = -1;
    while( index[pi].next != -1 ){
        //Delete from the row and form the next
        pi = index[pi].next;
        index[oldpi].next = -1;
        oldpi = index[pi].next;
    }
}
void addToVocabularyAndIndex( string word, vector<Word>& vocabulary, vector<Index_row>& index, int nrr ){
    //Initialice the new row that will be added in index
    struct Index_row new_row;
    new_row.nrr = nrr;
    new_row.next = -1;
    int pi = inVocabulary( vocabulary, word );    //Position in index
    if( pi != -1 ){
        //Exists in vocabulary. Find the last ocurrence
        while( index[pi].next != -1 ){
            pi = index[pi].next;
        }   
        index[pi].next = index.size();
        index.push_back( new_row );
    }else{
        //Doesn't exists. add it
        struct Word new_word;
        new_word.word = word;
        new_word.position_in_index = index.size();
        vocabulary.push_back( new_word );
        index.push_back( new_row );
    }
}
void saveClient( Client c, vector<Word>& vocabulary, vector<Index_row>& index ){
    string file_path = "./clases/Client/clients_book.txt";
    //Saving to vocabulary and index all the phone, name and lastname of the new client if they doesn't exist
    int nrr = getTotalClients();
    ofstream t;
    addToVocabularyAndIndex( c.get_phone(), vocabulary, index, nrr );
    addToVocabularyAndIndex( c.get_name(), vocabulary, index, nrr );
    addToVocabularyAndIndex( c.get_lastname(), vocabulary, index, nrr );
    replaceVocabularyFile( vocabulary );
    replaceIndexFile( index );
    t.open(file_path.c_str(), std::ios::app);
    t << c.saveString() << endl;
}

void replaceVocabularyFile( vector<Word> vocabulary ){
    string file_path = "./clases/Client/vocabulary.txt";
    ofstream t;
    t.open(file_path.c_str(), ios::out);
    for( size_t i = 0; i < vocabulary.size(); i++ ){
        t << vocabulary[i].word << " " << vocabulary[i].position_in_index << endl;
    }
    t.close();
}
void replaceIndexFile( vector<Index_row> index ){
    string file_path = "./clases/Client/index.txt";
    ofstream t;
    t.open(file_path.c_str(), ios::out);
    for( size_t i = 0; i < index.size(); i++ ){
        t << index[i].nrr << " " << index[i].next << endl;
    }
    t.close();
}
//Searches in vocabulary, go throw index and recovers the nrr of the words 
vector<Client> recoverClient( string search_string, vector<Word>& vocabulary, vector<Index_row>& index ){
    vector<Client> results;
    vector<int> nrr_coincidences;
    int pi = inVocabulary( vocabulary, search_string );    //Position in index
    if( pi != -1 ){
        nrr_coincidences.push_back( index[pi].nrr );
        //Exists in vocabulary. For every ocurrence. push a new nrr
        while( index[pi].next != -1 ){
            nrr_coincidences.push_back( index[pi].nrr );
            pi = index[pi].next;
        }
        //Read file clients book and return the nrrs 
        ifstream inFile;
        string path = "clases/Client/clients_book.txt";
        int position;
        char data = '\0';
        string client_register = "";            //String readed from the file
        string phone, name, lastname, address; //substrings from the client register
        Client c;
        int counter;
        inFile.open( path.c_str(), ios::app );
        if ( !inFile.fail() ){
            position = inFile.tellg();
            for( int i = 0; i < nrr_coincidences.size(); i++ ){
                inFile.seekg( nrr_coincidences[i]*85 );      //Read the register of the coincidences
                counter = 85;                                    //The register has 85 chars
                while( inFile >> noskipws >> data && counter != 0 ){
                    client_register += data;
                    data = '\0';
                    counter--;
                }
                for( int j = 0; j < 10; j++ ){
                    //First 10 are phone
                    phone += client_register[j];
                    // cout << "phone: " << phone << endl;
                }
                for( int j = 10; j < 25; j++ ){
                    //First 25 are name
                    name += client_register[j];
                    // cout << "name: " << name << endl;
                }
                for( int j = 35; j < 60; j++ ){
                    //First 25 are lastname
                    lastname += client_register[j];
                    // cout << "lastname: " << lastname << endl;
                }
                for( int j = 60; j < 85; j++ ){
                    //First 25 are address
                    address += client_register[j];
                    // cout << "address: " << address << endl;
                }
                //Build the client and then push it to the lsit
                c.set_phone( phone );
                c.set_name( name );
                c.set_lastname( lastname );
                c.set_address( address );
                c.show();
                results.push_back( c );
            }
        }
        return results;
    }else{
        //Doesn't exists. add it
        cout << "No se encontraron coincidencias" << endl;
        return results;
    }
}
//Utility
int stringToInt( string n ){
    int number;
    stringstream ss;
    ss << n;
    ss >> number;
    return number;
}
int getTotalClients(){
    string path = "./clases/Client/clients_book.txt";
    string s;
    int sTotal = -1;
    ifstream in;
    in.open(path.c_str());
    while(!in.eof()) {
        getline(in, s);
        sTotal ++;	
    }
    cout << "THERE ARE " << sTotal << "lines" << endl;
    in.close();	
    return sTotal;
}
Client getClientInfo( int nrr ){
    //Read file clients book and return the client with the correct info
    ifstream inFile;
    string path = "clases/Client/clients_book.txt";
    int position;
    char data = '\0';
    string client_register = "";            //String readed from the file
    string phone, name, lastname, address; //substrings from the client register
    Client c;
    int counter;
    inFile.open( path.c_str(), ios::app );
    inFile.seekg( nrr * 85 );      //Read the register of the coincidences
    counter = 85;                                    //The register has 85 chars
    while( inFile >> noskipws >> data && counter > 0 ){
        client_register += data;
        data = '\0';
        counter--;
    }
    // cout << "Full client register: " << client_register << endl;
    for( int j = 0; j < 10; j++ ){
        //First 10 are phone
        phone += client_register[j];
        // cout << "phone: " << phone << endl;
    }
    for( int j = 10; j < 25; j++ ){
        //First 25 are name
        name += client_register[j];
        // cout << "name: " << name << endl;
    }
    for( int j = 35; j < 60; j++ ){
        //First 25 are lastname
        lastname += client_register[j];
        // cout << "lastname: " << lastname << endl;
    }
    for( int j = 60; j < 85; j++ ){
        //First 25 are address
        address += client_register[j];
        // cout << "address: " << address << endl;
    }
    //Build the client and then push it to the lsit
    c.set_phone( phone );
    c.set_name( name );
    c.set_lastname( lastname );
    c.set_address( address );
    // cout << "The old client info:"<<endl;
    // c.show();
    return c;
}
void modifyClient( int nrr, Client oldClient, Client newClient, vector<Index_row>& index, vector<Word>& vocabulary ){
    //Modify the corespondant vocabulary and index
    deleteFromVocabularyAndIndex( index, vocabulary, oldClient.get_phone() );
    deleteFromVocabularyAndIndex( index, vocabulary, oldClient.get_name() );
    deleteFromVocabularyAndIndex( index, vocabulary, oldClient.get_lastname() );
    //Now add the modified client to the vocabulary and index
    addToVocabularyAndIndex( newClient.get_phone(), vocabulary, index, nrr );
    addToVocabularyAndIndex( newClient.get_name(), vocabulary, index, nrr );
    addToVocabularyAndIndex( newClient.get_lastname(), vocabulary, index, nrr );
    replaceVocabularyFile( vocabulary );
    replaceIndexFile( index );
    //Go to the position of the register that has that nrr and overwrites the new info
    cout << "------ Cliente modificado -------" << endl;
    string file_path = "clases/Client/clients_book.txt";
    int start_of_client_register = nrr * 85;
    fstream fout( file_path.c_str(), fstream::in | fstream::out | fstream::binary );
    //Make space
    fout.seekp( start_of_client_register );
    fout.write( "                                                                                     ", 85 );
    //Write new client
    fout.seekp( start_of_client_register );
    fout.write( newClient.saveString().c_str(), 85 );
    fout.close();
}
void deleteClient( int nrr, Client oldClient, vector<Index_row>& index, vector<Word>& vocabulary ){
    cout << "Eliminando " ;
    oldClient.show();
    //Modify the corespondant vocabulary and index
    deleteFromVocabularyAndIndex( index, vocabulary, oldClient.get_phone() );
    deleteFromVocabularyAndIndex( index, vocabulary, oldClient.get_name() );
    deleteFromVocabularyAndIndex( index, vocabulary, oldClient.get_lastname() );
    replaceVocabularyFile( vocabulary );
    replaceIndexFile( index );
    //Go to the position of the register that has that nrr and overwrites the new info
    string file_path = "clases/Client/clients_book.txt";
    int start_of_client_register = nrr * 85;
    cout << "------ Cliente eliminado -------" << start_of_client_register << endl;
    fstream fout( file_path.c_str(), fstream::in | fstream::out | fstream::binary );
    //Make space
    fout.seekp( start_of_client_register );
    fout.write( "                                                                                     ", 85 );
    fout.close();
}