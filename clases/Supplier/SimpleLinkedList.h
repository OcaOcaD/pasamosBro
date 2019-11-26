#ifndef SIMPLELINKEDLIST_H
#define SIMPLELINKEDLIST_H
#include <iostream>
#include "Proveedor.h"
using namespace std;
template <class T1>
class Node{
	public:
		Node( T1 data );
		T1 get_data();
		Node* get_next();
		void set_data( T1 data );
		void set_next( Node * next );
	private:
		T1 data;
		Node* next;
};
template <class T1>
class SimpleLinkedList{
    public:
        SimpleLinkedList();
        int getCont();
        void add( T1 obj );
        T1 findAt(int pos);
        void showAll();
        T1 deleteWhere( int pos );
        T1 operator []( int pos );
        int find( T1 obj );
        virtual ~SimpleLinkedList();

    protected:

    private:
    	int cont;
    	Node<T1> * first;

};
/**************************************************************************************
    DEFINICI�N DE M�TODOS
**************************************************************************************/
/************************************************
	Node<T1>
************************************************/
template <class T1>
Node<T1>::Node ( T1 data ){
	this->data = data;
	next = nullptr;
}
template <class T1>
T1 Node<T1>::get_data(){
	return this->data;
}
template <class T1>
Node<T1>* Node<T1>::get_next(){
	return this->next;
}
template <class T1>
void Node<T1>::set_data( T1 data ){
    this->data = data;
}
template <class T1>
void Node<T1>::set_next( Node* next ){
    this->next = next;
}
/************************************************
	SimpleLinked List<T1>
************************************************/
template <class T1>
SimpleLinkedList<T1>::SimpleLinkedList()
{
    cont = 0;
    first = nullptr;
}

template <class T1>
int SimpleLinkedList<T1>::getCont(){
	return this->cont;
}
template <class T1>
void SimpleLinkedList<T1>::add( T1 obj ){
	Node<T1>* newNode = new Node<T1>(obj);
    if (!first){
        first = newNode;
    }
    else{
        Node<T1>* aux = first;
        while(aux->get_next())
            aux = aux->get_next();
        aux->set_next(newNode);
    }
    cont++;
}

template <class T1>
T1 SimpleLinkedList<T1>::findAt(int pos){
	int i;
	Node<T1> *aux = first;
	for ( i = 0; i < pos; i++){
		aux = aux->get_next();
	}
	return aux->get_data();
}

template <class T1>
void SimpleLinkedList<T1>::showAll(){
	int i=0;
	Node<T1> *aux = first;
	for (i = 0; i < cont; i++){
		cout << aux->get_data().toString();
		aux = aux->get_next();
	}
}

template <class T1>
T1 SimpleLinkedList<T1>::deleteWhere(int pos){	//Conocer el elemento anterior(aux). Y hacer que apune al elemnto sguiente. regresar el actual
	Node<T1> *aux = first;
	Node<T1> *e;
	if ( pos == 0 )	{	//Si la posici�n a eliminar es la primera
		first = first->get_next();
		e = aux;
	}else{
		int i;
		for ( i = 0; i < pos-1; i++){	//Me quedo en el elemento anterio al que quiero borrar en
			aux = aux->get_next();
		}
		e = aux->get_next();	//Pongo en un auxiliar elq ue se va a eliminar
		aux->set_next( e->get_next() );	//Reelazo la lista
	}
	T1 output = e->get_data();
	delete(e);	//
	cont--;
	return aux->get_data();
}
template <class T1>
T1 SimpleLinkedList<T1>::operator []( int pos ){
	int i;
	Node<T1> *aux = first;
	for ( i = 0; i < pos; i++){
		aux = aux->get_next();
	}
	return aux->get_data();
}
template <class T1>
int SimpleLinkedList<T1>::find( T1 obj ){
	for (int i = 0; i < cont; i++){
		if ( obj == findAt(i) ){
			return i;
		}
	}
	return -1;
}

template <class T1>
SimpleLinkedList<T1>::~SimpleLinkedList()
{
    //dtor
}
#endif // SIMPLELINKEDLIST_H


