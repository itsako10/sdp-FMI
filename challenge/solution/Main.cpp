#include <iostream>

struct Node
{
	int data;
	Node* left;
	Node* right;
};

void initialize(Node* node, int data)
{
	node->data = data;
	node->left = NULL;
	node->right = NULL;
}

Node* buildBinBalTree(Node* root, const int* sorted_arr, int size)
{
	if (size == 0)
	{
		return NULL;
	}

	int right_size = size / 2;
	if (size % 2 == 0)
	{
		right_size = right_size - 1;
	}
	root = new Node();
	initialize(root, sorted_arr[size / 2]);
	root->left = buildBinBalTree(root->left, sorted_arr, size / 2);
	root->right = buildBinBalTree(root->right, sorted_arr + (size / 2) + 1, right_size);
	return root;
}

void printBinTree(const Node* root)
{
	if (root == NULL)
	{
		return;
	}
	printBinTree(root->left);
	std::cout << root->data << " ";
	printBinTree(root->right);
}

void free(Node* root)
{
	if (root == NULL)
	{
		return;
	}
	free(root->left);
	free(root->right);
	delete root;
}

int main()
{
	int arr[7] = { 7, 11, 23, 48, 53, 119, 2019 };

	Node* root2 = NULL;
	root2 = buildBinBalTree(root2, arr, 7);

	printBinTree(root2);
	std::cout << std::endl;

	free(root2);

	return 0;
}