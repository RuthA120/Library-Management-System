#include <iostream>
#include <string> 
#include <vector>
#include "Book.cpp"

//FIFO - First in First out

using namespace std;

class Queue{
    private:
        vector<BookNode*> reserved_books; //using vector to implement queue
    public:
        void reserveBook(BookNode* book); //used to reserve books and add to beginning of list
        void linearSearchReturnBook(BookNode* book); //using linear search algorithm to search for book and add back to library storage
};

void Queue::linearSearchReturnBook(BookNode* book){ //passed book node
    for(int i=0; i<reserved_books.size();i++){ //looping through queue
        if(reserved_books.at(i)==book){ //if match...
            reserved_books.erase(reserved_books.begin() + i); //remove node and shift queue
            book->increaseQuantity(); //increasing quantity once book is returned
            book->print(); //printing book to show its returned
            
            break; //break out of loop
        }
    }
}

void Queue::reserveBook(BookNode* book){ //pass book node
    book->decreaseQuantity(); //decrease quantity of book
    reserved_books.insert(reserved_books.begin(), book); //insert to beginning of queue(FIFO)
    book->print(); //print to show reserved book
}
