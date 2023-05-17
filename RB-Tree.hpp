#pragma once

#include <iostream>

using std::cout;
using std::endl;


struct Node
{
	Node*		left;
	Node*		right;
	Node*		p;
	int			data;
	bool		color;

	Node(int new_data) : left(nullptr), right(nullptr), p(nullptr), data(new_data), color(true) {};
};


class RedBlackTree
{
public:
	RedBlackTree();
	~RedBlackTree();

	void	Insert(int data);
	void	Delete(int data);
	Node*	Search(int data);

	void	Inorder_traversal();
	void	Preorder_traversal();
	void	Postorder_traversal();

private:
	Node*	root;
	Node*	nil;

	void	Insert_fixup(Node* node);
	void	Left_rotation(Node* node);
	void	Right_rotation(Node* node);

	Node*	Find_node(Node* node, int data);
	void	Delete_helper(Node* node);
	void	Transplant(Node* u, Node* v);
	Node*	Minimum(Node* node);
	void	Delete_fixup(Node* node);

	void	Inorder_traversal_helper(Node* node);
	void	Preorder_traversal_helper(Node* node);
	void	Postorder_traversal_helper(Node* node);
};