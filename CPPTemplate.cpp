// CPPTemplate.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Program for binary tree.
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Node {
public:
    int data;
    Node* right;
    Node* left;

    Node()
    {
        data = 0;
        right = NULL;
        left = NULL;
    }
    Node(int data)
    {
        this->data = data;
        this->right = NULL;
        this->left = NULL;
    }
};

class BinarySearchTree {
    Node* head;

public:
    BinarySearchTree() { head = NULL; }

    void insertNode(int);

    void printList();

    void deleteNode(int);

    bool search(int);
};

void BinarySearchTree::deleteNode(int item)
{
    Node* deleteNode = head, * parentNode = NULL, * replaceNode = NULL, * replaceNodeParent = NULL;
    int currentIndex = 0;
    parentNode = deleteNode;

    if (head == NULL) {
        cout << "List empty." << endl;
        return;
    }

    bool FoundItem = (deleteNode->data == item);

    // then follow delete logic.
    while (!FoundItem) {
        parentNode = deleteNode;
        if (item > deleteNode->data && deleteNode->right != NULL) {
            deleteNode = deleteNode->right;
        }
        else if(item < deleteNode->data && deleteNode->left != NULL){
            deleteNode = deleteNode->left;
        }
        else {
            cout << "Data is not in list." << endl;
            return;
        }
        FoundItem = (deleteNode->data == item);
    }
    
    // if there is nothing to the right, delete.
    if (deleteNode->right == NULL) {
        parentNode->left = deleteNode->left;
        delete deleteNode;
        return;
    }

    // There is something to the right, so we need to replace deleteNode. 
    replaceNode = deleteNode->right;
    replaceNodeParent = deleteNode;

    while (replaceNode->left != NULL) {
        replaceNodeParent = replaceNode;
        replaceNode = replaceNode->left;
    }
    // Delete pointer to replaceNode
    if (replaceNode->data > replaceNodeParent->data) replaceNodeParent->right = NULL;
    else replaceNodeParent->left = NULL;
    deleteNode->data = replaceNode->data;
    delete replaceNode;
}

void BinarySearchTree::insertNode(int data)
{
    Node* newNode = new Node(data);

    if (head == NULL) {
        head = newNode;
        cout << "Head set. (head is " << head->data << ")" << endl;
        return;
    }

    Node* temp = head;
    bool nextNodeIsValid = ((temp->right != NULL && data > temp->data) || (temp->left != NULL && data < temp->data));

    while (nextNodeIsValid) {
        if (data > temp->data) {
            temp = temp->right;
            nextNodeIsValid = ((temp->right != NULL && data > temp->data) || (temp->left != NULL && data < temp->data));
        }
        else {
            temp = temp->left;
            nextNodeIsValid = ((temp->right != NULL && data > temp->data) || (temp->left != NULL && data < temp->data));
        }
    }

    if (data > temp->data) {
        temp->right = newNode;
    }
    else {
        temp->left = newNode;
    }
    cout << "Value set. (head is " << head->data << " and value set is " << newNode->data << ").";
    cout << " Parent node's value is " << temp->data << endl;
}

// Function to print the
// nodes of the BST.
void BinarySearchTree::printList()
{
    Node* temp = head;

    if (head == NULL) {
        cout << "List empty" << endl;
        return;
    }

    vector<Node*> ParentRow{};
    vector<Node*> ChildRow{};
    ParentRow.push_back(temp);

    while (ParentRow.size() > 0) {
        // Print the row
        for (int i = 0; i < ParentRow.size(); i++) {
            cout << ParentRow[i]->data << " ";

            if (ParentRow[i]->left != NULL) ChildRow.push_back(ParentRow[i]->left);
            if (ParentRow[i]->right != NULL) ChildRow.push_back(ParentRow[i]->right);
        }
        cout << endl;
        
        ParentRow = ChildRow; // want to Write it, not reference it
        ChildRow = {};
    }
}

bool BinarySearchTree::search(int data) 
{
    if (head == NULL) return false;
    if (head->data == data) return true;

    Node* temp = head;
    bool nextNodeIsValid = ((temp->right != NULL && data > temp->data) || (temp->left != NULL && data < temp->data));


    while (nextNodeIsValid) {
        if (data > temp->data) {
            temp = temp->right;
            nextNodeIsValid = ((temp->right != NULL && data > temp->data) || (temp->left != NULL && data < temp->data));
        }
        else {
            temp = temp->left;
            nextNodeIsValid = ((temp->right != NULL && data > temp->data) || (temp->left != NULL && data < temp->data));
        }
        if (data == temp->data) return true;
    }

    return false;
}

// Driver Code
int main()
{
    BinarySearchTree list;

    list.insertNode(9);
    list.insertNode(5);
    list.insertNode(15);
    list.insertNode(6);
    list.insertNode(2);
    list.insertNode(133);
    list.insertNode(12);
    list.insertNode(166);
    list.insertNode(162);
    list.insertNode(52);
    list.insertNode(49);
    list.insertNode(70);
    list.insertNode(1000);
    list.insertNode(900);
    list.insertNode(1100);
    list.deleteNode(15);
    list.printList();
    std::cout << "searching for 1100. Was found: " << list.search(1100) << std::endl;
    std::cout << "searching for 717. Was found: " << list.search(717) << std::endl;

    return 0;
}