#include <iostream>
#include <string>
#include "Book.cpp"

using namespace std;

// key--> ISBN
//Value -->Book

class HashTable{
    private:
        static const int SIZE = 7; //size of address
        BookNode* dataMap[SIZE]; //will hold pointers to nodes
    public:
        int hash(string ISBN); //used to give key-value pairs an integer address
        void set(BookNode* book); //creating node and putting it in the hash table based on integer recieved from hash function
        BookNode* get(string ISBN); //recieve ISBN, and return book
};

int HashTable::hash(string ISBN){ //recieve key from user
    int hash = 0; // declaring hash value
    for(int i=0; i<ISBN.length();i++){ //looping throush ISBN string
        int asciiValue = int(ISBN[i]); // calculating and receiving the ascii value of the ISBN at character 'i'
        hash = (hash + asciiValue * 23) % SIZE; //calculating and adding to the hash value
    }
    return hash;
}

void HashTable::set(BookNode* newNode){
    int index = hash(newNode->ISBN); //getting the index address for the object that will be created based on ISBN
    if(dataMap[index]==nullptr){ //if there are no nodes at the index address then add to it
        dataMap[index] = newNode;
    }
    else { //if there are nodes at the index address, add to linked list
        BookNode* temp = dataMap[index];
        while(temp->next != nullptr){ //checking to see if node is NOT pointing to another node 
            temp = temp->next; //move onto next
        }
        temp->next=newNode; //new node is added to linked list at address
    }

}

BookNode* HashTable::get(string ISBN){
    int index = hash(ISBN); //finding index of key
    BookNode* temp = dataMap[index]; //finding location on the datamap(aka hash table)
    while(temp != nullptr){ //if NOT null
        if(temp->ISBN == ISBN){ //if ISBN matches, then return
            if(temp->quantity <= 0){ //if quantity is 0 or less, the book cannot be reserved
                return nullptr;
            }
            return temp; 
        }
        temp = temp->next; //move onto next
    }
    return nullptr; //if not found in hash table, return nullptr
}


