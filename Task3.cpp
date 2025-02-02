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
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node *insert(Node *root, int key)
{
    if (root == NULL)
    {
        return createNode(key);
    }
    if (key < root->key)
    {
        root->left = insert(root->left, key);
    }
    else
    {
        root->right = insert(root->right, key);
    }
    return root;
}

int findHeight(Node *root)
{
    if (root == NULL)
    {
        return 0;
    }
    int leftHeight = findHeight(root->left);
    int rightHeight = findHeight(root->right);
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

void bubbleSort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

Node *buildBalancedBST(int arr[], int start, int end)
{
    if (start > end)
    {
        return NULL;
    }
    int mid = (start + end) / 2;
    Node *root = createNode(arr[mid]);
    root->left = buildBalancedBST(arr, start, mid - 1);
    root->right = buildBalancedBST(arr, mid + 1, end);
    return root;
}

int main()
{
    ifstream inFile("keys.txt");
    if (!inFile)
    {
        cout << "Error opening file!" << endl;
        return 1;
    }

    const int SIZE = 500;
    int keys[SIZE], count = 0;

    while (count < SIZE && inFile >> keys[count])
    {
        count++;
    }
    inFile.close();

    Node *root1 = NULL;
    for (int i = 0; i < count; i++)
    {
        root1 = insert(root1, keys[i]);
    }
    int height1 = findHeight(root1);
    cout << "Height of BST (Unsorted Insertion): " << height1 << endl;

    bubbleSort(keys, count);
    Node *root2 = buildBalancedBST(keys, 0, count - 1);
    int height2 = findHeight(root2);
    cout << "Height of BST (Sorted Insertion - Balanced): " << height2 << endl;

    return 0;
}
