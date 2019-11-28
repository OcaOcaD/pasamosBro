#include <sstream>
#include <string>
#include <vector>
#ifndef ACCOUNTS_H_
#define ACCOUNTS_H_
#define SIMPLEINDEX_H_
using namespace std;

int stringToIntAccounts( string numbers ){
    stringstream ss;
    int x;
    ss << numbers;
    ss >> x;
    return x;
}
string intToStringAccounts( int numbers ){
    stringstream ss;
    string x;
    if ( numbers < 10 ){
        ss << "0" << numbers;
    }else{
        ss << numbers;
    }
    ss >> x;
    return x;
}

//Read the deleted list from the deleted.txt and fill the deleted vector
vector<int> loadDeleted(){
    vector<int> deleted_list;
    ifstream inFile;
    string path = "./clases/Accounts/deleted.txt";
    string deleted_nrr;
    int nrr;
    inFile.open( path.c_str(), ios::app );
    if ( !inFile.fail() ){
        while( getline(inFile, deleted_nrr) ){
            nrr = stringToIntAccounts( deleted_nrr );
            deleted_list.push_back( nrr );
        }
    }
    inFile.close();
    return deleted_list;
}
//Add a register to the deleted list file
void addDeleted( int nrr ){
    ofstream outFile;
    string path = "./clases/Accounts/deleted.txt";
    outFile.open( path.c_str(), ios::out | ios::app );
    outFile << nrr << endl;
    outFile.close();
}
//RemoveFromDeleted
void rewriteDeleted( vector<int> deleted_list ){
    string path = "./clases/Accounts/deleted.txt";
    ofstream outFile;
    //Delete old deleted.txt
    if( remove( path.c_str() ) != 0 )
        perror( "Error deleting file" );
    else{
        outFile.open( path.c_str(), ios::out | ios::app );
        puts( "File successfully updated" );
        //Write it all again
        for (size_t i = 0; i < deleted_list.size(); i++)
        {
            outFile << deleted_list[i] << endl;
        }
        outFile.close();
    } 
}

void rewriteAccounts( vector<string> replacingFile ){
    ofstream outFile;
    string path = "./clases/Accounts/accounts.txt";
    string temp = "./clases/Accounts/temp.txt";
    outFile.open( temp.c_str(), ios::out | ios::app );
    //Write the new changed accounts in a  temporary file
    for (size_t i = 0; i < replacingFile.size(); i++){
        outFile << replacingFile[i] << endl;
    }
    outFile.close();    //Close the temp file
    //Delete the old accounts.txt file and replace it with the temporary
    if( remove( path.c_str() ) != 0 )
            perror( "Error deleting file" );
    else{
        puts( "File successfully deleted" );
        rename("./clases/Accounts/temp.txt","./clases/Accounts/accounts.txt");
    }
}

vector<string> explode(string ind_string, char delim){
    vector<string> result;
    string part = "";
    for( size_t i = 0; i < ind_string.size(); i++ ){
        if ( ind_string[i] == delim ){
            result.push_back( part );
            part = "";
        }else{
            part += ind_string[i];
        }
    }
    result.push_back( part );
    return result;
}
SimpleIndex distributeIndex( string index_string ){
    SimpleIndex aux;
    vector<string> part;
    part = explode( index_string, '|' );
    aux.set_nrr( stringToIntAccounts( part[0] ) );
    aux.set_key( part[1] );
    return aux;
    
}
void rewriteAllIndex( vector<SimpleIndex> simdex ){
    //Delete old index.txt
    string path = "./clases/Accounts/index.txt";
    if( remove( path.c_str() ) != 0 )
        perror( "Error deleting file" );
    else{
        //Write it all again
        for( size_t i = 0; i < simdex.size(); i++ ){
            simdex[i].writeIndexRow();
        }
        cout << "Hay "<< simdex.size() << "cuentas" << endl;
        puts( "File successfully updated" );
    }
    
}
vector<SimpleIndex> loadIndex(){
    vector<SimpleIndex> simdex;
    ifstream inFile;
    string path = "./clases/Accounts/index.txt";
    string ind_string;
    SimpleIndex aux_ind;
    int cont = 0;
    inFile.open( path.c_str(), ios::app );
    if ( !inFile.fail() ){
        while( getline(inFile, ind_string) ){
            aux_ind = distributeIndex( ind_string );
            simdex.push_back( aux_ind );
            cont++;
        }
    }
    inFile.close();
    return simdex;
}
vector<SimpleIndex> abc( vector<SimpleIndex> unordered ){
    string chain1, chain2;
    bool unresolved;
    int j;
    SimpleIndex temp;
    for (size_t k = 0; k < unordered.size(); k++ ){
        for (size_t i = 0; i < unordered.size()-1; i++){
            //Go through all the vector and compares by bubble sort
            unresolved = true;
            j = 0;
            chain1 = unordered[i].get_key();
            chain2 = unordered[i+1].get_key();
            while( unresolved == true ){
                if ( chain1[j] > chain2[j] ){
                    //Means that the first string is greater than the second one
                    //Swap the SimpleIndex registers on the unordered vector
                    temp = unordered[i];
                    unordered[i] = unordered[i+1]; 
                    unordered[i+1] = temp;
                    unresolved = false;
                }
                if ( chain1[j] < chain2[j] ){
                    //Means that the registers are on the right place
                    unresolved = false;
                }
                if ( chain1[j] == chain2[j] ){
                    //Means that the letters are teh same. So we compare the next one
                }
                j++;
            }
        }
    }
    return unordered;    
}
#endif // !ACCOUNTS_H_