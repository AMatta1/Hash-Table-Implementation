// Table.cpp  Table class implementation


#include "Table.h"
#include "listFuncs.h"               

#include <iostream>
#include <string>
#include <cassert>

using namespace std;


// listFuncs.h has the definition of Node and its methods.  -- when
// you complete it it will also have the function prototypes for your
// list functions.  With this #include, you can use Node type (and
// Node*, and ListType), and call those list functions from inside
// your Table methods, below.

#include "listFuncs.h"


/******************************************************************************************************************
 REPRESENTATION INVARIANTS :
 
 1) No. of hash buckets = hashSize (for both fixed size array of size 'HASH_SIZE' or dynamic array of size 'hSize').
 2) Hash Table is an array with indices in range [0,hashSize).
 3) 0 <= Hash bucket index < hashSize.
 4) Instance Variable numOfEntries >= 0; (It can't be < 0).
 5) 0 <= numOfNonEmptyBuckets <= hashSize (It can't be < 0 or > hashSize ).

********************************************************************************************************************/


/** 
   Creates an empty hash table of size HASH_SIZE and initializes the required instance variables 
   (size and no. of entries in table)
   
   No. of Lines : 6   
*/

Table::Table() {
   
   for (int i = 0; i < HASH_SIZE; i++) {                          // Initializes a fixed sized array of pointers with NULL
      
      hashTableFixed[i] = NULL;
      
   }
   
   ListType * tempPtr = hashTableFixed;                           // Creates a temporary pointer to the fixed size array of pointers
   hashTable = tempPtr;                                           // The instance variable pointer 'hashTable' now points to same address as tempPtr
   
   // Instance variables initialized
   hashSize = HASH_SIZE;
   numOfEntries = 0;
   
}




/** 
   Creates an empty hash table of user specified size and initializes the required instance variables 
   (size and no. of entries in table)
   
   @Param : hSize - size of hash table provided by user
   
   No. of Lines : 4   
*/

Table::Table(unsigned int hSize) {
   
   /* Creating a dynamic array of pointers of user provided size. This size is fixed 
      once dynamic array is created */
         
   hashTable = new ListType[hSize]();                                                      
   
   // Instance variables initialized
   hashSize = hSize;
   numOfEntries = 0;

}




/** 
   Looks up the address of a value for a key in the hash table. Can be used to find or update that
   value.
   
   @Param : key - key/name to be looked up
   @Return : lookupPtr - Address of the value corresponding to this key or NULL if key not present
   
   No. of Lines : 4   
*/

int * Table::lookup(const string &key) {
   
   int * lookupPtr = NULL;                                        // Pointer variable to hold address of the value
   
   unsigned int arrayIndex = hashCode(key);                       // Generating hashcode for input key
     
   /* Calls listLookup function to check if key exists in hash table. For this, the only linked
      list checked is at the hash bucket with index 'arrayIndex'. Hence, implements hashtable principle. */
   
   lookupPtr = listLookup(hashTable[arrayIndex], key);          
      
   return lookupPtr;                                           
   
}




/** 
   Removes the hashtable entry with the given key.
   
   @Param : key - key/name whose entry has to be removed from hashtable
   @Return : removalDone - Boolean variable to indicate if removal was successful (true) 
             or unsuccessful (false)
   
   No. of Lines : 6   
*/

bool Table::remove(const string &key) {
   
   bool removalDone = false;                                      // Variable to indicate success or failure of removal
   
   unsigned int arrayIndex = hashCode(key);                       // Generating hashcode for input key
   
   /* Calls listRemove function to check if key exists in hash table. If yes, it is removed else 
      returns false if absent. For this, the only linked list checked is at the hash bucket with index 
      'arrayIndex'. Hence, implements hashtable principle. */
   
   removalDone = listRemove(hashTable[arrayIndex], key);
      
   if (removalDone) {
      numOfEntries -- ;                                           // If key found and removed, decrements no. of entries in table by 1
   }
         
   return removalDone;  
   
}




/** 
   Inserts a name-score pair/entry in table after checking if it already exists in table or not.
   If it does, insertion fails else it is inserted.
   
   Hence, it filters any attempts to insert a duplicate key/name in the table
   
   @Param : key - key/name to be inserted
            value - Corresponding value/score to be inserted
   @Return : insertDone - Boolean variable to indicate if insert was successful (true) 
             or unsuccessful (false)
   
   No. of Lines : 7   
*/

bool Table::insert(const string &key, int value) {
   
   bool insertDone = false ;                                      // Variable to indicate success or failure of insert
   
   unsigned int arrayIndex = hashCode(key);                       // Generating hashcode for input key
   
   // First looks up key in the table.
   if(!lookup(key)) {
   
      /* If key not already present, calls listInsert function to create and insert a new node for 
         the key-value pair. For this, we provide the list pointer at hash bucket with index 'arrayIndex'. 
         Hence, implements hashtable principle. */
         
      listInsert(key, value, hashTable[arrayIndex]);  
      numOfEntries ++ ;                                           // Incrementing no. of table entries by 1
      insertDone = true;                                          // Insert successful
      
   }
     
   return insertDone; 
   
}




/** 
   Accessor for no. of entries in table
   
   @Return : numOfEntries - No. of key/name - value/score pairs in table
   
   No. of Lines : 1   
*/

int Table::numEntries() const {
   
   return numOfEntries; 
   
}




/** 
   Prints all hash table pairs (name-score)
   
   No. of Lines : 3   
*/
void Table::printAll() const {
   
   /* Traverses the table bucket-by-bucket and calls listPrint method to print contents of all linked lists
      at these locations one per line */
         
   for (int i = 0; i < hashSize; i++) {                   
      
      if (hashTable[i] != NULL) {
         
         listPrint(hashTable[i]);
         
      }
      
   }
   
}
         
       
  

/** 
   Prints out hash table statistics by calling instance variable and other class methods
   like numEntries(), nonEmptyBuckets() and longestChainSize().
   
   @Param : out - output stream to print the output to (can be cout or cerr)
   
   No. of Lines : 4   
*/

void Table::hashStats(ostream &out) const {
    
   cout << "number of buckets: " << hashSize << endl;                                // Prints hash table size
   
   cout << "number of entries: " << numEntries() << endl;                            // Prints no. of entries in table
   
   cout << "number of non-empty buckets: " << nonEmptyBuckets() << endl;             // Prints no. of non empty buckets
   
   cout << "longest chain: " << longestChainSize() << endl;                          // Prints longest chain size in table
   
}




/** 
   Determines size of the longest chain in table.
   
   @Return : longestChain - size of the longest chain in hash table.
   
   No. of Lines : 6   
*/

int Table::longestChainSize() const { 
   
   int longestChain = chainSize(hashTable[0]);                                       // Variable to hold size of longest chain
   
   /* One-by-one comparing size of all chains with one another to determine the 
      longest chain. Calls chainSize method in listFunc.cpp */
   
   for (int i = 1; i < hashSize; i++) {     
      
      int size =  chainSize(hashTable[i]) ;
      
      if (size > longestChain) {
       
         longestChain = size;
         
      }
      
   }
  
   return longestChain;
   
}




/** 
   Determines no. of non - empty buckets or indices in hash table.
   
   @Return : numOfNonEmptyBuckets - no. of non - empty buckets or indices in hash table.
   
   No. of Lines : 6   
*/

int Table::nonEmptyBuckets() const {
   
   int numOfNonEmptyBuckets = 0;                                                     // Variable to hold the value to be returned
   
   /* Checks all the buckets one by one to get size of chains at their location.
      Then checks if they are empty(0) or not (> 0) */
         
   for (int i = 0; i < hashSize; i++) {
       
      int size = chainSize(hashTable[i]);
                           
      if(size > 0) {                                                         
           
         numOfNonEmptyBuckets ++ ;                                                   // If empty, increments variable by 1
         
      }
      
   }
     
   return numOfNonEmptyBuckets;
}




