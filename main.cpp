#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <limits>
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

    void displayTree(Node* node, int space = 0, int indent = 4) {
        if (!node) return;

        space += indent;

        // Print right subtree first (top of console)
        displayTree(node->right, space);

        // Print current node
        cout << endl;
        for (int i = indent; i < space; i++)
            cout << " ";
        cout << node->id;

        // Print left subtree (bottom of console)
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
            cout<< "\nCurrent AVL Tree Structure Horizontally:\n";
            displayTree(root);
        }
    }

    bool exists(int id) {
        return search(root, id) != nullptr;
    }

};


int main() {
    AVLTree addressBook;
    int choice;

    cout << "------------------------"
            "\nAddress Book Application\n"
             << "------------------------\n";
    while (true) {
        cout << "\nChoose what do you want to do:\n"
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
            int mode;
            cout << "\nChoose input method:\n"
                 << "1. Manual input (cin)\n"
                 << "2. Read from file\n"
                 << "Enter choice: ";

            while (!(cin >> mode) || (mode != 1 && mode != 2)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Please enter a valid choice (1 or 2): ";
            }

            if (mode == 1) {
                int count;
                cout << "\nHow many contacts do you want to add? ";
                while (!(cin >> count) || count <= 0) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Please enter a valid positive number: ";
                }

                for (int i = 0; i < count; ++i) {
                    int id;
                    Contact contact;
                    cout << "\nAdding contact #" << (i + 1) << endl;

                    cout << "Enter unique ID (integer): ";
                    while (true) {
                        cin >> id;

                        if (cin.fail()) {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "Invalid input. ID must be an integer.\nPlease enter valid ID: ";
                            continue;
                        }

                        if (addressBook.exists(id)) {
                            cout << "This ID already exists. Please enter a different ID.\nPlease try another ID: ";
                            continue;
                        }

                        break; // valid id
                    }

                    cin.ignore(); // clear newline after ID
                    cout << "Enter name: ";
                    getline(cin, contact.name);
                    cout << "Enter phone: ";
                    getline(cin, contact.phone);
                    cout << "Enter email: ";
                    getline(cin, contact.email);

                    addressBook.insert(id, contact);
                }
            }
            // File input
            else if (mode == 2) {
                string filename;
                ifstream infile;

                while (true) {
                    cout << "\nEnter file name: ";
                    cin >> filename;
                    infile.open(filename);
                    if (!infile) {
                        cerr << "Error: Could not open file. Try again.\n";
                        infile.clear();
                        continue;
                    }
                    break;
                }

                int count;
                infile >> count;
                if (infile.fail() || count <= 0) {
                    cerr << "Invalid contact count in file. Make sure the first line is a positive number.\n";
                    infile.close();
                    continue;
                }

                for (int i = 0; i < count; ++i) {
                    int id;
                    Contact contact;
                    infile >> id;
                    infile.ignore(); // skip newline before getline
                    getline(infile, contact.name);
                    getline(infile, contact.phone);
                    getline(infile, contact.email);

                    if (infile.fail()) {
                        cerr << "Error reading contact #" << (i + 1) << ". Check the file format.\n";
                        break;
                    }

                    if (addressBook.exists(id)) {
                        cout << "Duplicate ID " << id << " found in file. Skipping this contact.\n";
                        continue;
                    }

                    addressBook.insert(id, contact);
                }

                infile.close();
            }


            else {
                cout << "Invalid input method. Please choose 1 or 2.\n";
            }
        }
        else if (choice == 2) {
            int id;
            cout << "Enter ID to search: ";
            while (true) {
                cin >> id;

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input. ID must be an integer.\nPlease try again: ";
                    continue;
                }

                break; // valid id
            }
            addressBook.search(id);
        }
        else if (choice == 3) {
            int id;
            cout << "Enter ID to delete: ";
            while (true) {
                cin >> id;

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input. ID must be an integer.\nPlease try again: ";
                    continue;
                }

                break; // valid id
            }
            addressBook.deleteContact(id);
        }
        else if (choice == 4) {
            addressBook.listContacts();
        }
        else if (choice == 5) {
            addressBook.displayTreeStructure();
            cout << endl;
        }
        else {
            cout << "Invalid choice. Please select between 1 and 5." << endl;
        }
    }

    return 0;
}

/**
Test Case: Contact Management Program

Input Data (input.txt):
-----------------------------
3
101
Ahmed Ali
01012345678
ahmed@example.com
102
Sara Nabil
01098765432
sara@example.com
103
Kareem Hassan
01234567890
kareem@example.com

1. Add New Contact:
-------------------
1. When the user chooses option "1" (Add New Contact):
   - Expected behavior: User is prompted to enter contact details.
   - Example input:
     Enter contact ID: 104
     Enter contact name: John Doe
     Enter contact phone: 01122334455
     Enter contact email: john@example.com
   - Expected Output: "Contact with ID 104 inserted successfully."
   - The contact with ID 104 should be added to the list.

2. When trying to add a contact with an existing ID:
   - Example input:
     Enter contact ID: 101
     Enter contact name: Duplicate Name
     Enter contact phone: 01122334456
     Enter contact email: duplicate@example.com
   - Expected Output: "Error: Contact with ID 101 already exists."

2. Search for Contact:
----------------------
3. When the user chooses option "2" (Search for Contact):
   - Expected behavior: User is prompted to enter the contact ID.
   - Example input:
     Enter contact ID: 102
   - Expected Output:
     ID: 102
     Name: Sara Nabil
     Phone: 01098765432
     Email: sara@example.com

4. Searching for a non-existing contact ID:
   - Example input:
     Enter contact ID: 999
   - Expected Output: "Error: Contact with ID 999 not found."

3. Delete Contact :
-----------------------------
5. When the user chooses option "3" (Delete Contact):
   - Expected behavior: User is prompted to enter the contact ID to delete.
   - Example input:
     Enter contact ID: 103
   - Expected Output: "Contact with ID 103 deleted successfully."
   - The contact with ID 103 should be removed from the contact list.

6. Trying to delete a non-existing contact ID:
   - Example input:
     Enter contact ID: 999
   - Expected Output: "Error: Contact with ID 999 not found."

4. List All Contacts (Sorted by ID):
-----------------------------------
7. When the user chooses option "4" (List All Contacts):
   - Expected behavior: All contacts are displayed, sorted by their IDs.
   - Expected Output:
     ID: 101
     Name: Ahmed Ali
     Phone: 01012345678
     Email: ahmed@example.com

     ID: 102
     Name: Sara Nabil
     Phone: 01098765432
     Email: sara@example.com

     ID: 104
     Name: John Doe
     Phone: 01122334455
     Email: john@example.com
   - Contacts should be sorted by their IDs in ascending order.

5. Display Current Tree Structure:
--------------------------------
8. When the user chooses option "5" (Display Current Tree Structure):
   - Expected behavior: The tree structure should display the current state of the contact list (in the form of a horizontal tree).
   - Example output:
         103
    102
         101

6. Invalid Input for Menu Choices:
--------------------------------
9. When the user enters an invalid choice (not between 1 and 5):
   - Example input: 6
   - Expected Output: "Error: Invalid choice. Please enter a number between 1 and 5."

10. Invalid Input for Contact ID:
---------------------------------
11. When the user enters a non-numeric value for contact ID:
    - Example input: abc
    - Expected Output: "Error: Invalid contact ID. Please enter a valid numeric ID."

12. When the user enters a contact ID with letters (not a valid phone number):
    - Example input: 010ABCDE
    - Expected Output: "Error: Invalid phone number. Please enter a valid phone number."

13. When the user enters a contact email that is not valid:
    - Example input: john@.com
    - Expected Output: "Error: Invalid email address. Please enter a valid email."

14. When the user enters missing data for contact name or phone:
    - Example input:
      Enter contact ID: 105
      Enter contact name: (blank)
      Enter contact phone: 01133445566
      Enter contact email: johnnew@example.com
    - Expected Output: "Error: Contact name cannot be empty."

15. When the user enters missing phone or email data:
    - Example input:
      Enter contact ID: 106
      Enter contact name: New User
      Enter contact phone: (blank)
      Enter contact email: newuser@example.com
    - Expected Output: "Error: Contact phone cannot be empty."

16. When the user enters invalid data format in the Add/Update process:
    - Example input:
      Enter contact ID: 107
      Enter contact name: Invalid User
      Enter contact phone: 123
      Enter contact email: invaliduser.com
    - Expected Output: "Error: Invalid phone number or email format."


 **/