#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "bst.h"

// Main Structure of a Node
struct _Node
{
  int data;
  struct _Node *left;
  struct _Node *right;
};

// Adding a node to a subtree
Node *addNode(Node *root, int data)
{
  Node *newNode = malloc(sizeof(Node));
  newNode->data = data;
  newNode->left = NULL;
  newNode->right = NULL;

  Node *temp;
  Node *prev = NULL;

  temp = root;
  while (temp)
  {
    prev = temp;
    if (temp->data > newNode->data)
      temp = temp->right;
    else if (temp->data < newNode->data)
      temp = temp->left;
    else
    {
      free(newNode);
      return NULL;
    }
  }
  if (prev == NULL)
    root = newNode;
  else
  {
    if (prev->data > newNode->data)
      prev->right = newNode;
    else
      prev->left = newNode;
  }
  return root;
}

// Freeing a node in a subtree
Node *freeSubtree(Node *N)
{
  if (N == NULL)
    return N;
  freeSubtree(N->left);
  freeSubtree(N->right);
  free(N);
}

// Helper function to remove a subtree
void removeSubtreeWorker(Node *R, int value)
{
  if (R == NULL)
    return;
  if (R->left && R->left->data == value)
  {
    freeSubtree(R->left);
    R->left = NULL;
    return;
  }
  if (R->right && R->right->data == value)
  {
    freeSubtree(R->right);
    R->right = NULL;
    return;
  }
  if (R->data < data)
    removeSubtreeWorker(R->left, value);
  else
    removeSubtreeWorker(R->right, value);
}

// Removing a subtree from root node R
Node *removeSubtree(Node *R, int value)
{
  if (R == NULL)
    return NULL;
  if (R->data == value)
  {
    freeSubtree(R);
    return NULL;
  }
  removeSubtreeWorker(R, value);
  return R;
}

// Function to display a subtree
void displaySubtree(Node *N)
{
  if (N == NULL)
  {
    return;
  }
  displaySubtree(N->right);
  printf("%d\n", N->data);
  displaySubtree(N->left);
}

// Counting the number of nodes in a subtree
int countNodes(Node *N)
{
  int count = 0;
  if (N == NULL)
    return 0;
  count = count + countNodes(N->right);
  count = count + countNodes(N->left);
  count = count + 1;
  return count;
}

// Removing a node from a subtree
Node *removeNode(Node *root, int value)
{
  // Ensure root isn't null.
  if (root == NULL)
  {
    return NULL;
  }

  if (data > root->data)
  { 
    // data is in the left sub-tree.
    root->left = removeNode(root->left, value);
  }
  else if (data < root->data)
  { 
    // data is in the right sub-tree.
    root->right = removeNode(root->right, value);
  }
  else
  { 
    // Found the correct node with data
    // Check the three cases - no child, 1 child, 2 child...
    // No Children
    if (root->left == NULL && root->right == NULL)
    {
      free(root);
      root = NULL;
    }
    // 1 child (on the right)
    else if (root->left == NULL)
    {
      Node *temp = root; // save current node
      root = root->right;
      free(temp);
    }
    // 1 child (on the left)
    else if (root->right == NULL)
    {
      Node *temp = root; // save current node
      root = root->left;
      free(temp);
    }
    // Two children
    else
    {
      // find minimal data of right sub tree
      Node *temp = root->left;
      while (temp->right != NULL)
      {
        temp = temp->right;
      }
      root->data = temp->data;                         // duplicate the node
      root->left = removeNode(root->left, root->data); // delete the duplicate
    }
  }
  return root; // parent node can update reference
}

// Counts the number of leaves in a subtree
int numberLeaves(Node *N)
{
  if (N == NULL)
    return 0;
  if (N->left == NULL && N->right == NULL)
    return 1;
  return numberLeaves(N->left) + numberLeaves(N->right);
}

// Measures the depth of a function
int nodeDepth(Node *R, Node *N)
{
  if (R == NULL || N == NULL)
    return -1;
  if (R == N)
    return 0;
  int subDepth = nodeDepth(R->data < N->data ? R->left : R->right, N);
  if (subDepth >= 0)
    return subDepth + 1;
  else
    return -1;
}

int subTreeTotal(Node *N) 
{
  if (N == NULL)
  {
    return 0;
  }
  else 
  {
    return N -> data + subTreeTotal(N -> right) + subTreeTotal(N -> left);
  }
}

// Returns the average of all nodes in a subtree
float avgSubtree(Node *N)
{
  if (N == NULL)
    return 0;
  
  return (float) subTreeTotal(N) / (float) countNodes(N);
}

// Creating a node function for balanced BST
Node *createNode(int value)
{
  Node *node = (Node *)malloc(sizeof(Node));
  node->data = value;
  node->left = node->right = NULL;
  return node;
}

// Inverting the tree function
int invertedTree(Node *N, int *array, int i)
{
  if (N == NULL)
    return i;
  i = invertedTree(N->right, array, i);
  array[i] = N->data;
  i++;
  i = invertedTree(N->left, array, i);
  return i;
}

// Balancing Tree Helper Function
Node *balancedTreeHelper(int array[], int start, int end)
{
  if (start > end)
    return NULL;
  int middle = start + (end - start) / 2;
  Node *N = createNode(array[middle]);
  N->data = array[middle];
  N->left = balancedTreeHelper(array, middle + 1, end);
  N->right = balancedTreeHelper(array, start, middle - 1);
  return N;
}

// Balancing Tree function
Node *balanceTree(Node *root)
{
  int n = countNodes(root);
  int *arr = malloc(sizeof(int) * n);
  invertedTree(root, arr, 0);
  int start = 0;
  int end = countNodes(root) - 1;
  Node *N = balancedTreeHelper(arr, start, end);
  free(arr);
  return N;
}
