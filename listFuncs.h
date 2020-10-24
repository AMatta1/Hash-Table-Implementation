// Name: Ankita Matta
// USC NetID: ankitama
// CSCI 455 PA5
// Fall 2019


//*************************************************************************
// Node class definition 
// and declarations for functions on ListType

// Note: we don't need Node in Table.h
// because it's used by the Table class; not by any Table client code.

// Note2: it's good practice to not put "using" statement in *header* files.  Thus
// here, things from std libary appear as, for example, std::string

#ifndef LIST_FUNCS_H
#define LIST_FUNCS_H
  

struct Node {
   std::string key;
   int value;

   Node *next;

   Node(const std::string &theKey, int theValue);

   Node(const std::string &theKey, int theValue, Node *n);
};


typedef Node * ListType;

//*************************************************************************
//add function headers (aka, function prototypes) for your functions
//that operate on a list here (i.e., each includes a parameter of type
//ListType or ListType&).  No function definitions go in this file.


// Elaborate explanation of below methods given in .cpp file


// Inserts a node(key-val) at the front of a list, allows duplicates here
void listInsert(std::string key, int val, ListType &list);

// Removes the node with key as 'target' and returns if removal successful or not
// In case of duplicate nodes, removes only first occurrence
bool listRemove(ListType &list, std::string target);

// Prints the contents of a list node by node
void listPrint(ListType list);

// Looks up a target in list and returns its value's address, if found
// In case of duplicate nodes, look ups only first occurrence
int * listLookup(ListType list, std::string target);

// Returns size or no. of nodes in a list
int chainSize(ListType list);

#endif
