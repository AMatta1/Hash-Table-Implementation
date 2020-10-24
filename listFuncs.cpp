// listFuncs.cpp  Implementation for methods in header file 

#include <iostream>
#include <cassert>

#include "listFuncs.h"

using namespace std;

Node::Node(const string &theKey, int theValue) {
   key = theKey;
   value = theValue;
   next = NULL;
}

Node::Node(const string &theKey, int theValue, Node * n) {
   key = theKey;
   value = theValue;
   next = n;
}

//*************************************************************************


/** 
   Creates a new node with the specified name and score and inserts at the front of the linked list passed to it.
   Does not filter out any name-score entry even if repeated - creates and inserts node irrespective of 
   that. So, 'Joe 123' and 'Joe 123' will be two different nodes.
   Any repeated name to be inserted are filtered out in Table class (that uses this function) and not here. 
   
   @Param : insertKey - key/name to be inserted in list
            val - Corresponding value/score for the key/name
            list -Linked list at the front of which the node has to be inserted (It's a pointer to the list)
            
   PRE: list is a well-formed list
   POST: list is same as list, but with item inserted at front

   No. of Lines : 1   
*/

void listInsert(string insertKey, int val,ListType &list) { 
   
   /* Uses 3-arg constructor to create a node with given 'insertKey' and corresponding 'val'
      Next pointer of this node points to the first node of the received list */
   
   list = new Node(insertKey, val, list);   
    
}                                           
   
                 


/** 
   Removes the 'target' node i.e, the node with the specified key/name from the provided list.
   Traverses the list for this, and checks the position of target if present, deletes it , releasing
   the node memory. In case of multiple entries for a target (if this file is run as standalone) , then 
   only the first entry with 'target' removed, not all. Remaining entries will stay in list.
   
   @Param : list - Linked list from which the node with a specific key has to be removed
            target - Key/name to be removed from the list
   @Return : wasRemoved - boolean variable indicating if removal successful or not
            
   PRE: list is a well-formed list
   POST: list is the same as list but with the node with key as 'target' deleted.
         
   No. of Lines : 20
*/

bool listRemove(ListType &list, string target) {               
   
   bool wasRemoved = false;                                          // Variable indicating if removal was successful
  
   if (list == NULL) {                                               // If list is NULL, return 'false' as removal unsuccessful
                                  
      return wasRemoved;  
      
   }
   
   /* If target is the first node itself, create a new pointer variable to the list starting from the second node
      and delete(release memory) for the first node and list now starts from second node. Returns 'true' and exits. */
      
   if (list != NULL && list -> key == target) {            
      
      ListType save = list -> next;                                      
      delete list;                                                   // Release node memory i.e remove it from list
      list = save;                                                      
      wasRemoved = true; 
      return wasRemoved;                                             // Return true as removal successful and exit
      
   }
   
   // If target is not the first node in list, we need to check for it further
   ListType prev = list;                                                         // Pointer variable to the front of the list
   ListType curr =  list -> next;                                                // Pointer variable to the second node of the list 
   
   /* Traverse the list by moving the pointers till either we run out of nodes in list
      or the target node is found while traversing. Both pointers are simultaneously advanced 
      by one during the process. So at the end , if target is found, 'curr' points to it.*/
   
   while(curr != NULL && curr -> key != target) {                                 
   
      prev = curr;
      curr = curr -> next;
      
   }
   
   //If we don't run out of list, we check for target
   if (curr != NULL ) {
      
      // If target found, 'prev' breaks bond with target node and prev's next now points to next of target
      if (curr -> key == target) {
         prev -> next = curr -> next;
         delete curr;                                               // Release node memory i.e remove it from list
         wasRemoved = true;                                        
      }
      
   }
   
   return wasRemoved;
   
}

      


/** 
   Searches for a key/name in the list and returns the address of its value/score , if found
   Else returns NULL(0). In case of multiple entries for a target (if this file is run as standalone) , then 
   address of the value of the first occurrence is returned.
   
   @Param : list - Linked list in which the target has to be searched
            target - key/name that has to be searched
   @Return : *address - address of the value corresponding to the target, NULL(0) if not found
   
   PRE: list is a well-formed list
   
   No. of Lines : 10
*/

int * listLookup(ListType list, string target) {
   
   ListType p = list;                                               // Pointer variable to the front of the list
   
   // Pointer to hold the address of the value/score corresponding to the target
   int * address = NULL;
   
   if (list == NULL) {                                              // If list in NULL, return NULL (or 0) meaning target not found and exit
      return address; 
   }
   
   /* Traverse the list and if target found, store the address of its value and break out of loop,
      else keep traversing till we run out of nodes */
   
   while(p != NULL) {
      
      if (p -> key == target) {
         address = &(p -> value);                                   // Holds the value's address
         break;                                                       
      }
      
      p = p -> next;
      
   }
  
   return address;                                                   
   
}




/** 
   Prints the contents (key/name and value/score) of the provided list - node by node
   
   @Param : list - Linked list whose contents have to be printed
   PRE: list is a well-formed list
   
   No. of Lines : 4
*/

void listPrint(ListType list) {                        
   
   ListType p = list;                                               // Pointer variable to the front of the list
   
   // Keep printing key and values till we run out of nodes by advancing the pointer 
   while (p != NULL) {
      
      cout << p -> key << " " << p -> value << endl ;
      p = p -> next;                                                  
      
   }
   
}




/** 
   Finds the size or no. of nodes in the specifies linked list
   
   @Param : list - Linked list whose size has to be returned
   @Return : size - Size or number of nodes in list
            
   PRE: list is a well-formed list
   
   No. of Lines : 9
*/

int chainSize(ListType list) {
   
   int size = 0;                                                    // Variable to hold linked list's size
   
   if (list == NULL) {                                              // Return 0 if list is NULL
      return size;
   }
   
   /* If list is not NULL, traverse through it by advancing the pointer and incrementing
      the size counter whenever a node is encountered. */
   
   else {
      ListType p = list;
   
      while(p != NULL) {                                            
         size ++ ;                                                  // Increase size by 1 in every iteration
         p = p -> next;
      }
       
      return size;
   }
   
}
      
   