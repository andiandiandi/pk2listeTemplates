#include "list.h"

#include <iostream>
#include <string>

using namespace std;

template<class T>
void ausgabe(T text){
    cout << text << endl;
}
int main()
{
    List<int> liste;
    liste.append(1);
    liste.insert(2, 2);
    List<int> liste2 = liste;
    cout << "Liste:" << endl;
    liste.visit_all(ausgabe<int>);
    liste.remove(2);
    cout << "Liste:" << endl;
    liste.visit_all(ausgabe<int>);
    cout << "Liste2:" << endl;
    liste2.visit_all(ausgabe<int>);




    return 0;
}
