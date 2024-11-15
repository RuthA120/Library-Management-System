//Return books that have recently been borrowed
#include <iostream>
#include <string>
#include <vector>
#include "Book.cpp"

//Use a stack for tracking recently borrowed books
//Return the above book reserved by 2 people and lend it out again

using namespace std;

class Stack{
    private:
        vector<BookNode*> borrowed_books; //using a vector to implement stack
    public:
        void addBorrowedBook(BookNode* book); //adding a book to stack(LIFO)
        void returnLastBook(); //returning last book reserved
};

void Stack::addBorrowedBook(BookNode* book){ //add book node to the end of vector
    borrowed_books.push_back(book);
}

void Stack::returnLastBook(){
    BookNode* last_book = borrowed_books.back(); //getting last book reserved from stack
    cout << "Last Book Reserved: " << endl; 
    last_book->print();  //printing
}