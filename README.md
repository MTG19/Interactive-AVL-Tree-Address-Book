
# 📘 Interactive AVL Tree Address Book

An interactive console-based Address Book application built with C++ using an **AVL Tree** for efficient storage, searching, and deletion of contact information.

## 🚀 Features

- 📌 Store contact info with a unique integer ID as the key.
- 📤 Add new contacts (with ID uniqueness check).
- 🔍 Search for contacts by ID.
- 🗑️ Delete existing contacts.
- 📜 List all contacts (in-order traversal = sorted by ID).
- 🌳 Display the structure of the AVL Tree visually.
- 🧠 Automatically balances the tree after insertions and deletions for optimal performance.

## 🛠️ Technologies Used

- Language: **C++**
- Data Structure: **AVL Tree** (Self-balancing Binary Search Tree)
- CLI: **Interactive menu-based interface**

## 🎮 How to Use

1. **Compile the code**:

2. **Run the program**:

3. **Choose from the menu**:

   ```
   Address Book Application
   ------------------------
   1. Add New Contact
   2. Search for Contact
   3. Delete Contact (Optional)
   4. List All Contacts (Sorted by ID)
   5. Display Current Tree Structure
   ------------------------
   Enter operation (1-5):
   ```

## 🧪 Example Interactions

### ➕ Add New Contact

```
Enter operation (1-5): 1
Enter unique ID (integer): 310
Enter name: Omar Hassan
Enter phone: 010-876-5432
Enter email: omar.hassan@example.com
Contact added successfully.
```

### ❌ Duplicate ID

```
Enter operation (1-5): 1
Enter unique ID (integer): 310
Error: Contact with ID 310 already exists.
```

### 🔍 Search

```
Enter operation (1-5): 2
Enter ID to search: 310
Contact found:
ID: 310
Name: Omar Hassan
Phone: 010-876-5432
Email: omar.hassan@example.com
```

### 🗑️ Delete

```
Enter operation (1-5): 3
Enter ID to delete: 310
Contact deleted successfully.
```

### 📋 List Contacts

```
Enter operation (1-5): 4
Contacts in Address Book (sorted by ID):
ID: 150, Name: John Doe, Phone: 012-345-6789, Email: john.doe@example.com
ID: 210, Name: Peter Jones, Phone: 011-123-7890, Email: peter.jones@example.org
```

### 🌳 Display Tree

```
Enter operation (1-5): 5
Current AVL Tree:
210
/ \
150 310
```

