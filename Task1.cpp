#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

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
    const int N = 500;
    int keys[N];
    Node *root = nullptr;

    srand(time(0));

    ofstream outFile("keys.txt");
    if (!outFile)
    {
        cout << "Error opening file!" << endl;
        return 1;
    }

    for (int i = 0; i < N; i++)
    {
        keys[i] = rand() % 10000;     
        outFile << keys[i] << endl;  
        root = insert(root, keys[i]); 
    }
    outFile.close();
    cout << "Keys stored in 'keys.txt'" << endl;
    return 0;
}
