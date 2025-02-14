#include <iostream>
#include <string>

using namespace std;

// Structure for Student
struct Student
{
    int id;
    string name;
    Student *left;
    Student *right;

    Student(int i, string n)
    {
        id = i;
        name = n;
        left = NULL;
        right = NULL;
    }
};

// Function to insert student into the tree
Student *insert(Student *root, int id, string name)
{
    if (root == NULL)
    {
        return new Student(id, name);
    }

    if (id < root->id)
    {
        root->left = insert(root->left, id, name);
    }
    else
    {
        root->right = insert(root->right, id, name);
    }

    return root;
}

// Function to display tree structure with indentation
void displayTree(Student *root, int level = 0)
{
    if (root == NULL)
    {
        return;
    }

    displayTree(root->right, level + 1);

    for (int i = 0; i < level; i++)
    {
        cout << "   ";
    }
    cout << root->id << " - " << root->name << endl;

    displayTree(root->left, level + 1);
}

// Function to find a student by partial name
void searchByName(Student *root, string partialName)
{
    if (root == NULL)
    {
        return;
    }

    if (root->name.find(partialName) != string::npos)
    {
        cout << "Found: " << root->name << " (ID: " << root->id << ")\n";
    }

    searchByName(root->left, partialName);
    searchByName(root->right, partialName);
}

// Function to find the smallest node in the tree
Student *findMin(Student *root)
{
    while (root->left != NULL)
    {
        root = root->left;
    }
    return root;
}

// Function to delete a student by ID
Student *deleteStudent(Student *root, int id)
{
    if (root == NULL)
    {
        return NULL;
    }

    if (id < root->id)
    {
        root->left = deleteStudent(root->left, id);
    }
    else if (id > root->id)
    {
        root->right = deleteStudent(root->right, id);
    }
    else
    {
        if (root->left == NULL)
        {
            Student *temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == NULL)
        {
            Student *temp = root->left;
            delete root;
            return temp;
        }

        Student *temp = findMin(root->right);
        root->id = temp->id;
        root->name = temp->name;
        root->right = deleteStudent(root->right, temp->id);
    }

    return root;
}

int main()
{
    Student *root = NULL;
    int choice, id;
    string name;

    while (true)
    {
        cout << "\nMenu:\n";
        cout << "1. Add Student\n";
        cout << "2. Display Tree\n";
        cout << "3. Delete Student\n";
        cout << "4. Search by Name\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter Student ID: ";
            cin >> id;
            cin.ignore(); // To clear the buffer
            cout << "Enter Student Name: ";
            getline(cin, name);
            root = insert(root, id, name);
            cout << "Student added successfully!\n";
            break;

        case 2:
            cout << "\nTree Structure:\n";
            displayTree(root);
            break;

        case 3:
            cout << "Enter ID to delete: ";
            cin >> id;
            root = deleteStudent(root, id);
            cout << "Student deleted successfully!\n";
            break;

        case 4:
            cout << "Enter name to search: ";
            cin.ignore();
            getline(cin, name);
            cout << "Search results:\n";
            searchByName(root, name);
            break;

        case 5:
            cout << "Exiting program...\n";
            return 0;

        default:
            cout << "Invalid choice! Try again.\n";
        }
    }

    return 0;
}
