#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Student
{
    int id;
    string name;
    Student *left;
    Student *right;
};

Student *createNode(int id, string name)
{
    Student *newNode = new Student();
    newNode->id = id;
    newNode->name = name;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Student *insert(Student *root, int id, string name)
{
    if (root == NULL)
    {
        return createNode(id, name);
    }
    if (id < root->id)
    {
        root->left = insert(root->left, id, name);
    }
    else if (id > root->id)
    {
        root->right = insert(root->right, id, name);
    }
    return root;
}

Student *search(Student *root, int id)
{
    if (root == NULL || root->id == id)
    {
        return root;
    }
    if (id < root->id)
    {
        return search(root->left, id);
    }
    return search(root->right, id);
}

void inorder(Student *root)
{
    if (root != NULL)
    {   
        inorder(root->left);
        cout << "ID: " << root->id << " | Name: " << root->name << endl;
        inorder(root->right);
    }
}

void freeMemory(Student *root)
{
    if (root == NULL)
        return;
    freeMemory(root->left);
    freeMemory(root->right);
    delete root;
}

int main()
{
    Student *root = NULL;
    ifstream file("students.txt");

    int id;
    string name;

    while (file >> id)
    {
        file.ignore();       
        getline(file, name); 
        root = insert(root, id, name);
    }
    file.close();

    cout << "\nStudent Records (Sorted by ID):\n";
    inorder(root);

    cout << "\nEnter student ID to search: ";
    cin >> id;
    Student *result = search(root, id);

    if (result != NULL)
    {
        cout << "Student Found -> ID: " << result->id << ", Name: " << result->name << endl;
    }
    else
    {
        cout << "Student not found!" << endl;
    }

    freeMemory(root);

    return 0;
}
