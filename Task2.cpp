#include <iostream>
#include <fstream>

using namespace std;

struct Node
{
    int key;
    Node *left;
    Node *right;
};

Node *createNode(int key)
{
    Node *newNode = new Node();
    newNode->key = key;
    newNode->left = newNode->right = nullptr;
    return newNode;
}

Node *insert(Node *root, int key)
{
    if (root == nullptr)
        return createNode(key);
    if (key < root->key)
        root->left = insert(root->left, key);
    else
        root->right = insert(root->right, key);
    return root;
}

int treeHeight(Node *root)
{
    if (root == nullptr)
        return 0;
    return 1 + max(treeHeight(root->left), treeHeight(root->right));
}

int main()
{
    Node *root = nullptr;
    ifstream inFile("keys.txt");
    int key;

    if (!inFile)
    {
        cout << "Error opening file!" << endl;
        return 1;
    }

    while (inFile >> key)
    {
        root = insert(root, key);
    }

    inFile.close();

    cout << "Height of the BST: " << treeHeight(root) << endl;

    return 0;
}
