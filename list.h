
#ifndef LIST_H
#define LIST_H

#include "iterator.h"

#include <string>
#include <iostream>

template<typename T> class List{
private:

    class Node{
    private:
        T text;
        Node * next;
    public:
        Node(T text_):text{text_},next{nullptr} {};
        ~Node();
        T getText(){
            return text;
        }
        void setNext(Node * n){
            next = n;
        }
        Node * getNext(){
            return next;
        }
    };

    class ListIterator: public Iterator{
    private:
        Node * current;
    public:
        ListIterator(Node * element);
        ~ListIterator();
        bool hasNext();
        T next();
    };

    Node * firstElement;
    Node * lastElement;
public:
    /* Erzeugt eine leere Liste. */
List();
~List();
List(const List &copyList);
/* Fuegt den Text (in konstanter Zeit) an der letzten */
/* Listenposition hinzu. */
/* Liefert den Wert 1, wenn das Element eingefuegt werden */
/* konnte. Ansonsten wird der Wert 0 geliefert. */
int append(T text);
/* Fuegt ein neues Element an der Position p ein. */
/* Das erste Element der Liste befindet sich an der */
/* Position 0. */
/* Das Element, das sich aktuell an der Position p befindet,*/
/* wird nach rechts geschoben. */
/* Falls sich weniger als p Elemente in der Liste befinden, */
/* wird der Text am Ende angefuegt. */
int insert(T text, int p);
/* Loescht das Element an der Position p. Das erste */
/* Element befindet sich an der Position 0. */
/* Falls das p-te Element nicht existiert, wird das letzte */
/* Element geloescht. Die Anzahl der geloeschten Elemente */
/* wird als Funktionswert geliefert. */
int remove(int p);
/* Liefert den Text an der p-ten Listenposition. */
/* Das erste Listenelement befindet sich an der Position 0. */
/* Falls das p-te Element nicht existiert, wird nullptr */
/* geliefert. */
T get(int p);

void visit_all(void (*work)(T t));
void print();
ListIterator * getIterator();
};



using namespace std;



bool isPartOf(const char* w1,const char* w2){
int i=0;
int j=0;


    while(w1[i]!='\0'){
        if(w1[i] == w2[j]){

            int init = i;
            while (w1[i] == w2[j] && w2[j]!='\0'){
                j++;
                i++;
            }
            if(w2[j]=='\0'){
                return true;
            }
            j=0;
        }
    i++;

    }

    return false;
}

template<typename T> List<T>::Node::~Node(){

    if(next)
        delete next;

};


template<typename T> List<T>::List() {firstElement = nullptr; lastElement = nullptr;};
template<typename T> List<T>::~List() {

    Node * currentNode = firstElement;

    while(currentNode){

        Node * nextNode = currentNode->getNext();
        currentNode->setNext(nullptr);
        delete currentNode;
        currentNode = nextNode;

    }

};

template<typename T> List<T>::List(const List &copyList){

    if(!copyList.firstElement){
        firstElement = nullptr;
        lastElement = nullptr;
        return;
    }

    Node * nn = new Node(copyList.firstElement->getText());
    Node * runner = nn;
    Node * current = copyList.firstElement->getNext();

    firstElement = nn;

    while(current){

        Node * temp = new Node(current->getText());
        runner->setNext(temp);
        runner = temp;

        current = current->getNext();
    }

    lastElement = runner;

}

template<typename T>List<T>::ListIterator::ListIterator(Node * element): current{element} {};
template<typename T>List<T>::ListIterator::~ListIterator(){};

template<typename T> bool List<T>::ListIterator::hasNext(){
    return current;
}

template<typename T> T List<T>::ListIterator::next(){
        Node * ret = current;
        current = current->getNext();
        return ret->getText();
}

template<typename T> int List<T>::insert(T text, int p){
    Node * node = new Node(text);

    if(!firstElement && !lastElement){
        firstElement = node;
        lastElement = firstElement;
        return 1;
    }

    if(firstElement == lastElement){
        if(p==0){
            node->setNext(lastElement);
            firstElement = node;
        }else{
            firstElement->setNext(node);
            lastElement = node;
        }
        return 1;
    }

    if(p==0){
        node->setNext(firstElement);
        firstElement = node;
        return 1;
    }


    Node * prev = firstElement;
    Node * temp = prev->getNext();



    while(p>1){
        if(!temp->getNext()){
            return append(text);
        }
        prev = prev->getNext();
        temp = temp->getNext();
        p--;
    }

    node->setNext(temp);
    prev->setNext(node);

    return 1;
}


template<typename T> int List<T>::append(T text){
    Node * node = new Node(text);

    if(!firstElement && !lastElement){
        firstElement = node;
        lastElement = node;
        return 1;
    }

    lastElement->setNext(node);
    lastElement = lastElement->getNext();


    return 1;
}

template<typename T> int List<T>::remove(int p){

    Node * prev = firstElement;
    Node * current = prev->getNext();

    if(p==0){
        Node * next = firstElement->getNext();
        firstElement->setNext(nullptr);
        delete firstElement;
        firstElement = next;
        return 1;
    }

    while(p>1){
            if(!current->getNext()){
                break;
            }
        prev = prev->getNext();
        current = current->getNext();
        p--;
    }

    Node * temp = current->getNext();
    current->setNext(nullptr);
    if(current==lastElement)
        lastElement = prev;
    delete current;
    prev->setNext(temp);


}

template<typename T> T List<T>::get(int p){

    Node * temp = firstElement;

    while(p>0){
        if(temp==lastElement)
            return nullptr;
        temp = temp->getNext();
        p--;
    }

    return temp->getText();

}

template<typename T> void List<T>::visit_all(void (*work)(T t)){

    Node * n = firstElement;
    while(n){
        work(n->getText());
        n=n->getNext();
    }

}

template<typename T> void List<T>::print(){
    Node * n = firstElement;
    while(n){
        cout << n->getText() << endl;
        n=n->getNext();
    }
}



template<typename T> typename  List<T>::ListIterator * List<T>::getIterator(){
    return new List<T>::ListIterator(firstElement);
}


#endif // LIST_H
