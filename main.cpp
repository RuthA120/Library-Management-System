#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include "HashTable.cpp"
#include "BorrowedBookStack.cpp"
#include "BinaryTree.cpp"
#include "ReserveBookQueue.cpp"

using namespace std;
//error handling

void initializeBooks(string fileName, vector<BookNode*>& books){
    ifstream file; //getting file
    file.open(fileName);
    string line="";
    getline(file, line); //ignoring header line
    line="";
    while(getline(file, line)){
        stringstream inputString(line);
        vector<string> bookInfo; //stores all of the info for each book
        string field; //temporarily holds string for each field
        bool inQuotes = false; //checks if it is in quotes
        string quotedField; //will be used to get title that has quotes

        while(getline(inputString, field, ',')){ //looping through each section of the line
            if(!inQuotes){ //not in quotes
                if(!field.empty() && field.front()=='"'){ //check to see if field starts with quote(mainly looking for title)
                    inQuotes=true;
                    quotedField=field;
                }
                else{
                    bookInfo.push_back(field); //adding to vector
                }
            }
            else {
                quotedField += "," + field; //adding to quoted field string

                if(!field.empty() && field.back()=='"'){ //checking to see if the field ends in a quote
                    inQuotes = false; //end of title info
                    bookInfo.push_back(quotedField); //adding to vector
                    quotedField = ""; //empty
                }
            }

        }
        
        //receiving all of the important information from the bookInfo vector
        string ISBN = bookInfo.at(0); //getting ISBN info
        string title = bookInfo.at(1); //getting title info
        string author = bookInfo.at(2); //getting author info
        double price = stod(bookInfo.at(3)); //getting price info
        int quantity = stoi(bookInfo.at(4)); //getting quantity info
        
        BookNode* book = new BookNode(ISBN, title, author, price, quantity); //creating a book node
        books.push_back(book); //adding to vector

    }

    file.close(); //close file
}


int main(){
    vector<BookNode*> books; //initializing vector to add all the books from the library
    initializeBooks("books.csv", books); //calling function to add all the books from the library

    HashTable* hashTable = new HashTable(); //initializing a hash table that will allow for books to be called by ISBN
    for(int i=0; i<books.size();i++){ //calling set function to add books to the hash table
        hashTable->set(books.at(i));
    }

    BinaryTree* bt = new BinaryTree(); //initializing a binary tree that will allow for books to be called by string
    for(int i=0; i<books.size();i++){ //calling insert function to add books to binary tree
        bt->insert(books.at(i));

    }

    Queue* reservedBooks = new Queue(); //queue that will display reserved books 
    Stack* trackReservedBooks = new Stack(); //stack that will keep track of recently reserved books


    cout << endl; //for spacing
    cout << endl; //for spacing

    string userinput; //string input from user
    BookNode* programBook; //book node
    bool notValid = true; //checks if recieved node is null

    cout << "*Reserving 10 books*" << endl;
    for(int i=0; i<10; i++){ //user reserving 10 books
        while(notValid==true){ //marked as true
            cout << endl; // for spacing
            cout << "Please type the ISBN or the title for the book you are looking for." << endl; 
            getline(cin, userinput); //getting user input
    
            programBook = bt->binarySearch(userinput); //first search through binary search tree(check to see if valid title)
            if(programBook != nullptr){ //valid title recieved
                break; //break out of loop and reserve
            }
            else{//invalid title recieved -- either ISBN or not available
                programBook = hashTable->get(userinput); //search through hash table(check to see if valid ISBN)

                if(programBook != nullptr){ //if valid ISBN, break and reserve
                    break;
                }
            }

            //What user typed is not available in library...
            cout << endl; //for spacing 
            cout << "You typed a book that is NOT available in our library OR a book that is out of stock at the moment." << endl;
            cout << "Please try again..." << endl;
            cout << endl;
        }

        //What user typed IS available in library
        reservedBooks->reserveBook(programBook); //adding book to queue for reserved books
        trackReservedBooks->addBorrowedBook(programBook); //adding book to stack for tracking recently reserved books

    }

    cout << endl; //for spacing
    cout << endl; //for spacing

    cout << "*Reserving 2 of the same books*" << endl;
    while(notValid==true){ //marked as true
            cout << endl; // for spacing
            cout << "Please type the ISBN or the title for the book you are looking for." << endl; 
            getline(cin, userinput); //getting user input
    
            programBook = bt->binarySearch(userinput); //first search through binary search tree(check to see if valid title)
            if(programBook != nullptr){ //valid title recieved
                if(programBook->quantity>2){
                    break; //break out of loop and reserve
                }
            }
            else{//invalid title recieved -- either ISBN or not available
                programBook = hashTable->get(userinput); //search through hash table(check to see if valid ISBN)

                if(programBook != nullptr){ //if valid ISBN, break and reserve
                    if(programBook->quantity>2){
                        break;
                    }
                }
            }

            //What user typed is not available in library...
            cout << endl; //for spacing 
            cout << "You typed a book that is NOT available in our library OR a book that is out of stock at the moment OR has less than 2 copies." << endl;
            cout << "Please try again..." << endl;
            cout << endl;
    }

    BookNode* sameBook1 = programBook;
    reservedBooks->reserveBook(sameBook1); //adding book to queue for reserved books
    trackReservedBooks->addBorrowedBook(sameBook1); //adding book to stack for tracking recently reserved books

    BookNode* sameBook2 = programBook;
    reservedBooks->reserveBook(sameBook2); //adding book to queue for reserved books
    trackReservedBooks->addBorrowedBook(sameBook2); //adding book to stack for tracking recently reserved books

    cout << "*Next availability for '" << sameBook2->title << "': " << sameBook2->quantity << " books left.*" << endl; //telling user availability of book

    cout << endl; //for spacing

    trackReservedBooks->returnLastBook(); //returning most recently reserved book
    cout << endl; //for spacing

    cout << "*Returning book*" << endl; //returning book
    reservedBooks->linearSearchReturnBook(sameBook2); //using linear search algorithm to find book and add it back to storage

    cout << endl; //for spacing
    cout << endl; //for spacing

    BookNode* sameBook3 = programBook; //calling hash table get function to retrieve book by ISBN
    cout << "*Reserving same book*" << endl; //adding book to queue for reserved books
    reservedBooks->reserveBook(sameBook3); //adding book to stack for tracking recently reserved books

    return 0;
}