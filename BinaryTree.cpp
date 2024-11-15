#include <string>
#include <cctype>
#include <iostream>
#include "Book.cpp"

using namespace std;


class BinaryTree{
    private:
        BookNode* root; //keeps track of the first node or root in the tree
    public:
        BinaryTree(){
            root = nullptr; //the root is first null when binary tree object is declared
        }
        bool insert(BookNode* book); //used to add book objects to the node
        BookNode* binarySearch(string title); //searches for given title in a tree(Using binary search algorithm)
};

bool BinaryTree::insert(BookNode* newNode){
    if(root==nullptr){ //if no root node, that means tree is empty, so new node becomes root node
        root=newNode;
        return true;

    }
    BookNode* temp = root; //starting at root node
    
    while(true){ //a return statement is needed to break this while loop
        int result = newNode->title.compare(temp->title); //comparing new node's title, and temp node's title alphabetically

        if(result == 0){ //if both nodes's titles are equal, then duplicate is detected --> FALSE
            return false;
        }

        else if(result < 0){ //new node's title is BEFORE temp node's title alphabetically
            if(temp->left==nullptr){ //if left node is empty, insert
                temp->left=newNode;
                return true;
            }
            temp = temp->left; //if not empty, move to next spot on the left
        }
        else if(result > 0){ //new node's title is AFTER of temp node's title alphabetically
            if(temp->right == nullptr){ //if right node is empty, insert
                temp->right=newNode;
                return true;
            }   
            temp = temp->right; //if not empty, move to next spot on the right
        }
    }
}

BookNode* BinaryTree::binarySearch(string title){
    if(root==nullptr){ //if null, then tree is empty
        return nullptr;
    }

    BookNode* temp = root; //starting from root value
    
    while(temp!= nullptr){
        int result = title.compare(temp->title); //comparing temp node's title, and user's title alphabetically

        if(result < 0){ //user's title is BEFORE of temp's title
            temp = temp->left;
        }
        else if(result > 0){ //user's title is AFTER temp's title
            temp = temp->right;
        }
        else{ //titles are equal
            if(temp->quantity <= 0){ //if out of stock return nullptr
                return nullptr;
            }
            return temp; //else return book
        }
    }

    return nullptr; //book was not found..
}