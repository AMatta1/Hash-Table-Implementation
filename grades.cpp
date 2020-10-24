/*
 * grades.cpp
 * A program to test the Table class.
 * How to run it:
 *      grades [hashSize]
 * 
 * the optional argument hashSize is the size of hash table to use.
 * if it's not given, the program uses default size (Table::HASH_SIZE)
 *
 */

#include "Table.h"


// cstdlib needed for call to atoi
#include <cstdlib>
                          

using namespace std;

//*************************************************************************
// Utility functions used by this code
// These functions are defined at the bottom of the file

//  Displays the user prompt to enable entering and execution of commands
void userPrompt (Table * &grades);

// Prints 'score' coressponding to a 'name', if it exists
void printScore (int *valAddress, string userInput[], bool operationDone);

// Updates the 'score' corresponding to a 'name', if it exists
void changeScore (int *valAddress, string userInput[], bool operationDone);

// Displays appropriate message if a particular operation is unsuccessful
void printMessage (string userInput[], bool operationDone);

//*************************************************************************


int main(int argc, char * argv[]) {
   
   // gets the hash table size from the command line

   int hashSize = Table::HASH_SIZE;

   Table * grades;  // Table is dynamically allocated below, so we can call
   // different constructors depending on input from the user.

   if (argc > 1) {
      hashSize = atoi(argv[1]);  // atoi converts c-string to int

      if (hashSize < 1) {
         cout << "Command line argument (hashSize) must be a positive number" 
              << endl;
         return 1;
      }

      grades = new Table(hashSize);

   }
   else {   // no command line args given -- use default table size
      grades = new Table();
   }

   grades->hashStats(cout);
   
   // Calls method to drive the entire program by taking user input and calling methods accordingly
   userPrompt(grades);
   
   return 0;
   
}




/** 
   Message displaying all the valid 9 commands that the program will process once the user enters them.
   Will be displayed in 2 scenarios :
   
   1) User enters 'help' as the command to get list of all commands
   2) Usert enters incorrect command so this will be displayed along with the error message.
*/

void commandSummary() {
   
   cout << "Valid commands are: 'insert name score', 'change name newscore' , 'lookup name', " << endl;
      
   cout << "                     'remove name', 'print', 'size', 'stats', 'help', 'quit'." << endl;
       
}




/** 
   Method called when user enters an incorrect command name, i.e, anything other than the 9 valid command names
   mentioned in method commandSummary(). Also, commands are case-sensitive.
   
   So 'insert joe 123' will not throw an error , however  - as confirmed on Piazza - 'INSERT joe 123' will throw 3 errors,
   i.e, one for each word in the 'do' loop. The program will also keep waiting for input till correct number of arguments are 
   entered for a command.
   
   No. of Lines : 2   
*/

void invalidComment() {
   
   cout << "ERROR: invalid command" << endl;                                    // Error message to be displayed       
   
   commandSummary();                                                            // Displays the set of 9 valid commands as well
   
}




/** 
   Checks the command entered in the 0th index of the input array and accordingly reads in the 
   subsequent arguments from console depending on that particular type of command. These arguments 
   are stored in the next indices of the array, to generate a complete array for further processing 
   in other methods.
   
   @Param : userInput - User Input array(acts as a pointer to array itself) to read first element and store
            user provided arguments in subsequent indices.
   
   No. of Lines : 8      
*/

void readInput(string userInput[]) {
   
   string word;                                                                 // Word to be read in from user
   
   /* If command is 'insert' or 'change' - reads in the subsequent 2 words in the command as the arguments 
      'name' and 'score'/'newscore' for them */
   
   if(userInput[0] == "insert" || userInput[0] == "change") {
         
      for (int i = 1; i <= 2; i++) {                                            // Stores in indices 1 and 2 of array
         
         cin >> word;
         userInput[i] = word ;
         
      }
      
   }
   
   // If command is 'lookup' or 'remove' - reads in the next word in the command as the argument 'name' for them
   else if (userInput[0] == "lookup" || userInput[0] == "remove") {
         
      cin >> word;
      userInput[1] = word ;                                                     // Stores in index 1 of array
      
   }
   
}
      
 


/** 
   Called from userPrompt() method. If the input command is 'insert' , takes in the subsequent 2
   arguments and processes them. Calls insert method of Table class to input the name-score entry in the
   hash table. Also calls method to print message if name already exists and hence, is not inserted.
   
   PRE : Input 'score' of 'insert' command must be able to be interpreted as int by stoi. So comMands like 'insert joe 123'
   will work and not 'insert joe abc' because we are not handling the type of arguments entered by user.
    
   @Param : userInput - User Input array (acts as a pointer to array itself) 
            operationDone - Variable indicating if insert performed successfully or not
            grades - Pointer to object of class table 
   
   No. of Lines : 4      
*/

void performInsert(string userInput[], bool operationDone, Table * &grades) {
   
   // Calls method to read the next arguments
   readInput(userInput);
   
   // Method of 'string' class used to convert 'score' argument provided by user from 'string' to 'int'.
   int val = stoi(userInput[2]);                                             
   
   // Calls insert method for hash table
   operationDone = grades -> insert(userInput[1], val); 
         
   // Prints message if name already exists in table
   printMessage(userInput, operationDone);              
   
}




/** 
   Called from userPrompt() method. If the input command is 'change', takes in the next argument from 
   console and processes it to call lookup method of Table class. Checks if 'name' exists and then calls 
   another method to change score to 'newscore' for that name. If name is absent, prints appropriate message.
   
   @Param : userInput - User Input array(acts as a pointer to array itself) 
            operationDone - Variable indicating if score changed successfully or not. Passed to another method
            grades - Pointer to object of class table
            
   No. of Lines : 3
      
*/
void performScoreChange(string userInput[], bool operationDone, Table * &grades) {
   
   readInput(userInput);                                                        // Calls method to read next argument 'name'
       
   int * valAddress = grades -> lookup(userInput[1]);                           // Calls lookup to check existance of name in table
      
   changeScore(valAddress, userInput, operationDone);                           // Calls method to change 'score' for 'name' if record exists
  
}




/** 
   Called from userPrompt() method. If the input command is 'lookup', takes in the next argument from 
   console and processes it to call lookup method of Table class. Checks if 'name' exists and print its
   associated score from hash table. If name is absent, prints appropriate message.
   
   @Param : userInput - User Input array(acts as a pointer to array itself) 
            operationDone - Variable indicating if name looked up successfully or not. Passed to another method
            grades - Pointer to object of class table
   
   No. of Lines : 3
*/

void performLookup(string userInput[], bool operationDone, Table * &grades) {
   
   readInput(userInput);                                                      // Calls method to read next argument 'name'
            
   int * valAddress = grades -> lookup(userInput[1]);                         // Calls lookup to check existence of name in table
        
   printScore(valAddress, userInput, operationDone);                          // Calls method to print 'score' for 'name' if record exists
     
}




/** 
   Called from userPrompt() method. If the input command is 'remove', takes in the next argument from 
   console and processes it. If 'name' exists and then removes that name-score entry from hash table 
   else prints appropriate message.
   
   @Param : userInput - User Input array(acts as a pointer to array itself) 
            operationDone - Variable indicating if removal done successfully or not
            grades - Pointer to object of class table
   
   No. of Lines : 3      
*/

void performRemoval(string userInput[], bool operationDone, Table * &grades) {
   
   readInput(userInput);                                                     // Calls method to read next argument 'name'
        
   operationDone = grades -> remove(userInput[1]);                           // Calls remove method and stores 'true' if removal done else 'false'
        
   printMessage(userInput, operationDone);                                   // Prints message if name doesn't exist in table

}




/** 
   Method that handles user input and execution of various other methods depending on the command entered.
   Maintains command tokens in an array, updates value of variable indicating success or failure of an 
   operation and accordingly calls other methods.
   
   Operations performed : insert, lookup, change, remove, print, stats, size and quit (all are case-sensitive)
   
   @Param : grades - Pointer to object of class table
   
   No. of Lines : 30    
*/

void userPrompt(Table * &grades) {
   
   // Constant indicating maximum size of 3 tokens in a command 
   const int MAX_SIZE = 3;
   
   // String array to hold user entred input
   string userInput[MAX_SIZE];
   
   bool keepgoing = true;                                                // Variable that is true except when user enters 'quit' command to exit
   bool operationDone = false;                                           // Variable indicating success or failure of an operation
    
   do {
            
      cout << "cmd>";                                                    // Reads command name as array's first element
      cin >> userInput[0];
       
      // If user enters command starting with 'insert'
      if (userInput[0] == "insert") {                                    // Inserts name-score entry if 'name' not present, else operation fails
         performInsert(userInput, operationDone, grades);
      }
      
      // If user enters command starting with 'change'
      else if (userInput[0] == "change") {                               // Change the 'score' for the 'name', if present
         operationDone = false;                                          // Again initialized to 'false' to remove previous value in variable
         performScoreChange(userInput, operationDone, grades);
      }
      
      // If user enters command starting with 'lookup'                   // Looks up name (if present) and prints it score
      else if (userInput[0] == "lookup") {
         operationDone = false;
         performLookup(userInput, operationDone, grades);
      }
    
      // If user enters command starting with 'remove'                   // Removes the name-score entry if 'name' present, else fails 
      else if (userInput[0] == "remove") {
         performRemoval(userInput, operationDone, grades);
      }
      
      // If user enters command 'print'
      else if (userInput[0] == "print") {                                // Prints out all names and scores in the table.
         grades -> printAll();
      }
      
      // If user enters command 'size'
      else if (userInput[0] == "size") {
         cout << grades -> numEntries() << endl;                         // Prints out the number of entries in the table
      }
    
      // If user enters command 'stats'
      else if (userInput[0] == "stats") {                                // Prints out statistics about the hash table at this point. 
         grades -> hashStats(cout);
      }
      
      // If user enters command 'help'
      else if (userInput[0] == "help") {
         commandSummary();                                                //Prints out a brief command summary.
      }
      
      // If user enters command 'quit'
      else if (userInput[0] == "quit") {                                  // Exits the program
         keepgoing = false;
      }
      
      // If user enters invalid command
      else {                                                              // If none of the above commands, prints Error message
         invalidComment();
      }
      
   } while (keepgoing);
   
}




/** 
   Updates the 'score' corresponding to a 'name' by changing it to a user provided 'newscore'
   Update done at address of 'score' itself.
   
   PRE : Input 'newscore' of 'change' command must be able to be interpreted as int by stoi. So comands like 'change joe 123'
   will work and not 'change joe abc' because we are not handling the type of arguments entered by user.
   
   @Param : userInput - User Input array (acts as a pointer to array itself) 
            operationDone - Variable indicating if score changed successfully or not
            valAddress - Address location of score that needs to be changed
   
   No. of Lines : 5
*/

void changeScore(int * valAddress,string userInput[], bool operationDone){
   
   // If score location exists, i.e. record is present, updates that to 'newscore' and sets operationDone to true.
   if (valAddress) {
   
      int val = stoi(userInput[2]);                                      // Converts user provided 'newscore' from 'string' to 'int'                
      *valAddress = val;
      operationDone = true;
      
   }
   
   printMessage(userInput, operationDone);                               // Prints message if name doesn't exist in table 
  
}




/** 
   Prints 'score' coressponding to a 'name' if it exists. Else, prints appropriate message
   
   @Param : userInput - User Input array (acts as a pointer to array itself) 
            operationDone - Variable indicating if name looked successfully or not
            valAddress - Address location of score that needs to be printed
   
   No. of Lines : 4
*/

void printScore (int * valAddress, string userInput[], bool operationDone) {
   
   // If score location exists, i.e. record is present, prints that score and sets operationDone to true. 
   if (valAddress) {
           
      cout << "Score of student '" << userInput[1] << "' is: " << *valAddress << endl;
      operationDone = true; 
             
   }
   
   printMessage(userInput, operationDone);                               // Prints message if name doesn't exist in table
   
}




/** 
   Called from multiple methods and displays appropriate message if operation unsuccessful depending on the
   command being executed.
   
   @Param : userInput - User Input array (acts as a pointer to array itself) 
            operationDone - Received variable indicating if operation completed successfully or not
            
   No. of Lines : 5
*/

void printMessage(string userInput[], bool operationDone ) {
   
   // Checks if operation failed
   if (!operationDone) {
      
      // Message to be printed if 'name' already exists during 'insert' operation
      if (userInput[0] == "insert") {
         
         cout << "Insert Unsuccessful! Entry '" << userInput[1] << "' already exists." << endl; 
      
      }
      
      // Message to be printed if 'name' doesn't exist during 'change' / 'lookup' or 'remove' operation
      else if (userInput[0] == "change" || userInput[0] == "lookup" || userInput[0] == "remove") {
         
         cout << "Entry for '" << userInput[1] << "' doesn't exist." << endl;  
         
      }
      
   }
   
}
      
    

 





