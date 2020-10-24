// pa5list.cpp
// a program to test the linked list code necessary for a hash table chain

// You are not required to submit this program for pa5.

// We gave you this starter file for it so you don't have to figure
// out the #include stuff.  The code that's being tested will be in
// listFuncs.cpp, which uses the header file listFuncs.h

// The pa5 Makefile includes a rule that compiles these two modules
// into one executable.

#include <iostream>
#include <string>
#include <cassert>

using namespace std;

#include "listFuncs.h"


int main() {

   ListType a = new Node ("Ankita", 30);
   
   cout << "List a is :" << endl; 
   listPrint(a);
   cout<<endl;
   
   ListType b = new Node ("Bhavika", 12, a);
   
   cout << "List b is :" << endl;
   listPrint(b);
   cout<<endl;
   
   ListType c = new Node ("Chirag", 13, b);
   
   cout << "List c is :"<<endl;
   listPrint(c);
   cout<<endl;
   
   
   ListType d = new Node ("Aarushi", 15, NULL);
   
   cout << "List d is :" <<endl;
   listPrint(d);
   cout<<endl;
   
   ListType e = new Node ("Himali", 77, d);
   
   cout << "List e is :"<<endl;
   listPrint(e);
   cout<<endl;
   
   
   
   listInsert("Diksha" , 56, c);
   
   //cout<< " returned address is:" << listLookup(c,"Diksha")<<endl;;

   listInsert("Ekteshwar" , 1, c);
   listInsert("Falguni" , 1, c);
   listInsert("Ekteshwar" , 2, c);
   listInsert("Falguni" , 2, c);
   listInsert("Ekteshwar" , 3, c);
   listInsert("Falguni" , 3, c);
   
   cout << "List c after more inserts is :" <<endl;
   listPrint(c);
   cout<<endl;
   
   cout << "Inserting 'Diksha' again "<<endl;
   listInsert("Diksha" , 56, c);
   listInsert("Diksha" , 100, c);
   listInsert("Diksha" , 100000, c);
   
   cout<< " First returned address is:" << listLookup(c,"Diksha")<<endl;
   
   cout << "New List c after all operations  is :"<<endl;
   listPrint(c);
   cout<<endl;
   
   listRemove (c,"Chirag");
   
   cout << "New List c  after removing Chirag is :"<<endl;
   listPrint(c);
   cout<<endl;
   
   cout<<endl;
   
   listRemove (e,"Aarushi");
   
   cout << "New List e after removing Aarushi is :"<<endl;
   listPrint(e);
   cout<<endl;
   
   listRemove (c,"Diksha");
   
   cout << "New List c after removing Diksha is :"<<endl;
   listPrint(c);
   cout<<endl;
   
   listRemove (e,"Raman");
   
   cout << "New List e  after removing Raman is :"<<endl;
   listPrint(e);
   cout<<endl;
   
   ListType f = NULL;
   listRemove (f,"Tom");
   
   cout<< " returned address is:" << listLookup(c,"Ekteshwar")<<endl;
   cout<< " returned address is:" << listLookup(c,"Diksha")<<endl;
   
   cout << "New List c after updating value using lookup  is :"<<endl;
   listPrint(c);
   cout<<endl;
   
   cout<< " returned address is:" << listLookup(c,"Diksha")<<endl;;  
   
   cout << "New List f after updating value using lookup  is :"<<endl;
   listPrint(c);
   cout<<endl;
   
   
   
   ListType g = NULL;
   cout << "Inserting Happy "<<endl;
   listInsert("Happy" , 56, g);
   
   cout << "New List g  is :"<<endl;
   listPrint(g);
   cout<<endl;
  
   return 0;
  
}
