#include <iostream>
#include <string>
#pragma once

using namespace std;

class BookNode{
    public:
        //variables that hold book info
        string ISBN;
        string title;
        string author;
        double price;
        int quantity;
        //pointers:
            //next and prev: for hash table
            //left and right: for binary tree
        BookNode* next;
        BookNode* prev;
        BookNode* left;
        BookNode* right;

        BookNode(){ //no parameters passed, book object
            ISBN = "";
            title = "";
            author = "";
            price = 0.0;
            quantity = 0;
            next = nullptr;
            prev = nullptr;
            left = nullptr;
            right = nullptr;
        }

        BookNode(string ISBN, string title, string author, double price, int quantity){ //parameter passed book object
            this->ISBN = ISBN;
            this->title = title;
            this->author = author;
            this->price = price;
            this->quantity = quantity;
            next = nullptr;
            prev = nullptr;
            left = nullptr;
            right = nullptr;
        }
    
        void print(); //used to print book information
        void decreaseQuantity(); //when book is reserved --> decrease quantity
        void increaseQuantity(); //when book is returned --> increase quantity
        void returnQuantity(); //returning availability for book

};

void BookNode::returnQuantity(){
    cout << "Availability for " << title << ": ";
    if(quantity==0){ //no books --> not available
        cout << "Not available." << endl;
    }
    else{ //books --> available
        cout << quantity << " books available." << endl;
    }
}

void BookNode::increaseQuantity(){ //increase quantity
    quantity++;
}

void BookNode::decreaseQuantity(){ //decrease quantity
    quantity--;
}

void BookNode::print(){ //printing book info
    cout << ISBN << ": " << endl;
    cout <<"\t Title: " << title << endl;
    cout <<"\t Author: " << author << endl;
    cout <<"\t Price: $" << price << endl;
    cout <<"\t Quantity: " << quantity << endl;
}

