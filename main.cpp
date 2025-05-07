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

    Node* deleteNode(Node* root, int id, bool& found) {
        if (!root)
            return root;

        if (id < root->id)
            root->left = deleteNode(root->left, id, found);
        else if (id > root->id)
            root->right = deleteNode(root->right, id, found);
        else {
            found = true;
            if (!root->left || !root->right) {
                Node* temp = root->left ? root->left : root->right;
                delete root;
                return temp;
            }
            Node* temp = minValueNode(root->right);
            root->id = temp->id;
            root->contact = temp->contact;
            root->right = deleteNode(root->right, temp->id, found);
        }

        root->height = 1 + max(height(root->left), height(root->right));
        int balance = getBalance(root);

        if (balance > 1 && getBalance(root->left) >= 0)
            return rightRotate(root);

        if (balance > 1 && getBalance(root->left) < 0) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        if (balance < -1 && getBalance(root->right) <= 0)
            return leftRotate(root);

        if (balance < -1 && getBalance(root->right) > 0) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }

public:
    AVLTree() {
        root = nullptr;
    }

    void insert(int id, Contact contact) {
        bool duplicate = false;
        root = insert(root, id, contact, duplicate);
        if (duplicate)
            cout << "Error: Contact with ID " << id << " already exists." << endl;
        else
            cout << "Contact added successfully." << endl;
    }

    void search(int id) {
        Node* res = search(root, id);
        if (!res) {
            cout << "Contact not found." << endl;
        } else {
            cout << "Contact found:" << endl;
            cout << "ID: " << res->id << endl;
            cout << "Name: " << res->contact.name << endl;
            cout << "Phone: " << res->contact.phone << endl;
            cout << "Email: " << res->contact.email << endl;
        }
    }

    void deleteContact(int id) {
        bool found = false;
        root = deleteNode(root, id, found);
        if (found)
            cout << "Contact deleted successfully." << endl;
        else
            cout << "Contact not found." << endl;
    }

    void listContacts() {
        if (!root) {
            cout << "Address Book is empty." << endl;
        } else {
            cout << "Contacts in Address Book (sorted by ID):" << endl;
            inorder(root);
        }
    }

    void displayTreeStructure() {
        if (!root)
            cout << "Address Book is empty." << endl;
        else {
            cout << "Current AVL Tree:" << endl;
            displayTree(root);
        }
    }

};


int main() {
    AVLTree addressBook;
    int choice;

    while (true) {
        cout << "\nAddress Book Application\n"
             << "------------------------\n"
             << "1. Add New Contact\n"
             << "2. Search for Contact\n"
             << "3. Delete Contact (Optional)\n"
             << "4. List All Contacts (Sorted by ID)\n"
             << "5. Display Current Tree Structure\n"
             << "------------------------\n"
             << "Enter operation (1-5): ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear(); cin.ignore(10000, '\n');
            cout << "Invalid input. Please enter a number from 1 to 5." << endl;
            continue;
        }

        if (choice == 1) {
            int id;
            Contact contact;
            cout << "Enter unique ID (integer): ";
            cin >> id;
            cin.ignore();  // clear newline
            cout << "Enter name: ";
            getline(cin, contact.name);
            cout << "Enter phone: ";
            getline(cin, contact.phone);
            cout << "Enter email: ";
            getline(cin, contact.email);
            addressBook.insert(id, contact);
        }
        else if (choice == 2) {
            int id;
            cout << "Enter ID to search: ";
            cin >> id;
            addressBook.search(id);
        }
        else if (choice == 3) {
            int id;
            cout << "Enter ID to delete: ";
            cin >> id;
            addressBook.deleteContact(id);
        }
        else if (choice == 4) {
            addressBook.listContacts();
        }
        else if (choice == 5) {
            addressBook.displayTreeStructure();
        }
        else {
            cout << "Invalid choice. Please select between 1 and 5." << endl;
        }
    }

    return 0;
}
