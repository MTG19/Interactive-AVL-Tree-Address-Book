#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

struct Contact {
    string name;
    string phone;
    string email;
};

struct Node {
    int id; // key
    Contact contact; // data
    Node* left;
    Node* right;
    int height;

    Node(int id, Contact contact) {
        this->id = id;
        this->contact = contact;
        left = right = nullptr;
        height = 1;
    }
};

class AVLTree {
private:
    Node* root;

    int height(Node* n) {
        return n ? n->height : 0;
    }

    int getBalance(Node* n) {
        return n ? height(n->left) - height(n->right) : 0;
    }

    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;

        return x;
    }

    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;

        return y;
    }



int main() {
    cout << "Welcome to the Contact Management System!" << endl;
    return 0;
}