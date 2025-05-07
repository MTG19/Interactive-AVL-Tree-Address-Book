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

    Node* insert(Node* node, int id, Contact contact, bool& duplicate) {
        if (!node)
            return new Node(id, contact);

        if (id < node->id)
            node->left = insert(node->left, id, contact, duplicate);
        else if (id > node->id)
            node->right = insert(node->right, id, contact, duplicate);
        else {
            duplicate = true;
            return node;
        }

        node->height = 1 + max(height(node->left), height(node->right));

        int balance = getBalance(node);

        if (balance > 1 && id < node->left->id)
            return rightRotate(node);

        if (balance < -1 && id > node->right->id)
            return leftRotate(node);

        if (balance > 1 && id > node->left->id) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        if (balance < -1 && id < node->right->id) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    Node* search(Node* node, int id) {
        if (!node || node->id == id)
            return node;
        if (id < node->id)
            return search(node->left, id);
        return search(node->right, id);
    }

    void inorder(Node* node) {
        if (!node) return;
        inorder(node->left);
        cout << "ID: " << node->id
             << ", Name: " << node->contact.name
             << ", Phone: " << node->contact.phone
             << ", Email: " << node->contact.email << endl;
        inorder(node->right);
    }

    void displayTree(Node* node, int space = 0, int indent = 5) {
        if (!node) return;
        space += indent;
        displayTree(node->right, space);
        cout << setw(space) << node->id << endl;
        displayTree(node->left, space);
    }

    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current->left)
            current = current->left;
        return current;
    }

};



int main() {
    cout << "Welcome to the Contact Management System!" << endl;
    return 0;
}