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

int main() {
    cout << "Welcome to the Contact Management System!" << endl;
    return 0;
}