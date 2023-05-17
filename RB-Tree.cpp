#include "./RB-Tree.hpp"

/********************/
/*		Public		*/
/********************/


RedBlackTree::RedBlackTree()
{
	this->nil = new Node(0);
	this->nil->left = this->nil;
	this->nil->right = this->nil;
	this->nil->p = this->nil;
	this->root = nil;
}

RedBlackTree::~RedBlackTree()
{
	//
}

void	RedBlackTree::Insert(int data)
{
	Node*	newNode = new Node(data);
	newNode->left = nil;
	newNode->right = nil;

	Node*	temp_root = this->root;
	Node*	temp_p = this->nil;

	while (temp_root != this->nil)
	{
		temp_p = temp_root;
		if (newNode->data < temp_root->data)
			temp_root = temp_root->left;
		else if (newNode->data > temp_root->data)
			temp_root = temp_root->right;
		else
		{
			cout << "Error.\nDublicate number forbiden!" << endl;
			return ;
		}
	}

	newNode->p = temp_p;

	if (this->root == this->nil)
	{
		this->root = newNode;
		this->root->color = false;
	}
	else if (newNode->data < temp_p->data)
		temp_p->left = newNode;
	else
		temp_p->right = newNode;

	if (newNode->p == nil || newNode->p->p == nil)
		return ;

	Insert_fixup(newNode);
}

void	RedBlackTree::Delete(int data)
{
	if (this->root == this->nil)
	{
		cout << "RB-Tree is a empty." << endl;
		return ;
	}

	Node* tmp_root = this->root;
	Node* tmp = Find_node(tmp_root, data);
	
	if (tmp)
		Delete_helper(tmp);
}

Node*	RedBlackTree::Search(int data)
{
	if (this->root == this->nil)
	{
		cout << "RB-Tree is a empty." << endl;
		return nullptr;
	}

	Node*	tmp_root = this->root;
	return Find_node(tmp_root, data);
}

void	RedBlackTree::Inorder_traversal()
{
	if (this->root == nil)
	{
		cout << "RB-Tree is a empty." << endl;
		return ;
	}

	Node*	temp_root = this->root;
	Inorder_traversal_helper(temp_root);
}

void	RedBlackTree::Preorder_traversal()
{
	if (this->root == nil)
	{
		cout << "RB-Tree is a empty." << endl;
		return ;
	}

	Node*	temp_root = this->root;
	Preorder_traversal_helper(temp_root);
}

void	RedBlackTree::Postorder_traversal()
{
	if (this->root == nil)
	{
		cout << "RB-Tree is a empty." << endl;
		return ;
	}

	Node*	temp_root = this->root;
	Postorder_traversal_helper(temp_root);
}



/********************/
/*		Private		*/
/********************/

void	RedBlackTree::Insert_fixup(Node* node)
{
	while (node->p->color == true && node != this->root)
	{
		if (node->p == node->p->p->left)
		{
			Node* uncle = node->p->p->right;
			
			if (uncle->color == true)
			{
				uncle->color = false;
				node->p->color = false;
				node->p->p->color = true;
				node = node->p->p;
			}
			else if (node == node->p->right)
			{
				node = node->p;
				Left_rotation(node);
			}
			node->p->color = false;
			node->p->p->color = true;
			Right_rotation(node->p->p);
		}
		else
		{
			Node* uncle = node->p->p->left;
			
			if (uncle->color == true)
			{
				uncle->color = false;
				node->p->color = false;
				node->p->p->color = true;
				node = node->p->p;
			}
			else if (node == node->p->left)
			{
				node = node->p;
				Right_rotation(node);
			}
			node->p->color = false;
			node->p->p->color = true;
			Left_rotation(node->p->p);
		}
	}

	this->root->color = false;
	this->nil->color = false;
}

void	RedBlackTree::Left_rotation(Node* node)
{
	if (node == this->nil)
		return ;
	Node* y = node->right;
	node->right = y->left;

	if (y->left != this->nil)
		y->left->p = node;
	
	y->p = node->p;

	if (node->p == this->nil)
		this->root = y;
	else if (node == node->p->left)
		node->p->left = y;
	else
		node->p->right = y;
	
	y->left = node;
	node->p = y;
}

void	RedBlackTree::Right_rotation(Node* node)
{
	if (node == this->nil)
		return ;
	Node* y = node->left;
	node->left = y->right;

	if (y->right != this->nil)
		y->right->p = node;
	
	y->p = node->p;

	if (node->p == this->nil)
		this->root = y;
	else if (node == node->p->left)
		node->p->left = y;
	else
		node->p->right = y;
	
	y->right = node;
	node->p = y;
}

Node*	RedBlackTree::Find_node(Node* node, int data)
{
	if (node == this->nil)
	{
		cout << "Element not found." << endl;
		return nullptr;
	}

	if (node->data == data)
		return node;

	if (data < node->data)
		return Find_node(node->left, data);
	return Find_node(node->right, data);
}

void	RedBlackTree::Delete_helper(Node* node)
{
	bool	original_color = node->color;
	Node*	x;

	if (node->left == this->nil)
	{
		x = node->right;
		Transplant(node, node->right);
	}
	else if (node->right == this->nil)
	{
		x = node->left;
		Transplant(node, node->left);
	}
	else
	{
		Node* y = Minimum(node->right);
		original_color = y->color;
		x = y->right;

		if (y->p == node)
			x->p = y;
		else
		{
			Transplant(y, y->right);
			y->right = node->right;
			y->right->p = y;
		}
	
		Transplant(node, y);
		y->left = node->left;
		y->left->p = y;
		y->color = node->color;
	}

	delete node;

	if (original_color == false)
		Delete_fixup(x);
}

void	RedBlackTree::Transplant(Node* u, Node* v)
{
	if (u->p == this->nil)
		this->root = v;
	else if (u == u->p->left)
		u->p->left = v;
	else
		u->p->right = v;
	v->p = u->p;
}

Node*	RedBlackTree::Minimum(Node* node)
{
	if (node->left == this->nil)
		return node;
	
	return Minimum(node->left);
}

void	RedBlackTree::Delete_fixup(Node* node)
{
	while (node != this->root && node->color == false)
	{
		if (node == node->p->left)
		{
			Node* w = node->p->right;

			if (w->color == true)
			{
				w->color = false;
				node->p->color = true;
				Left_rotation(node->p);
				w = node->p->right;
			}

			if (w->left->color == false && w->right->color == false)
			{
				w->color = true;
				node = node->p;
			}
			else if (w->right->color == false)
			{
				w->left->color = false;
				w->color = true;
				Right_rotation(w);
				w = node->p->right;
			}

			w->color = node->p->color;
			node->p->color = false;
			w->right->color = false;
			Left_rotation(node->p);
			node = this->root;
		}
		else
		{
			Node* w = node->p->left;

			if (w->color == true)
			{
				w->color = false;
				node->p->color = true;
				Left_rotation(node->p);
				w = node->p->left;
			}

			if (w->right->color == false && w->left->color == false)
			{
				w->color = true;
				node = node->p;
			}
			else if (w->left->color == false)
			{
				w->right->color = false;
				w->color = true;
				Right_rotation(w);
				w = node->p->left;
			}

			w->color = node->p->color;
			node->p->color = false;
			w->left->color = false;
			Left_rotation(node->p);
			node = this->root;
		}
	}
	this->root->color = false;
	this->nil->color = false;
}

void	RedBlackTree::Inorder_traversal_helper(Node* node)
{
	if (node == this->nil)
		return ;
	
	Inorder_traversal_helper(node->left);

	cout << endl;

	if (node == this->root)
		cout << "__ ROOT __" << endl;
	cout << "data:\t" << node->data << endl;
	if (node->color == false)
		cout << "color:\t" << "BLACK" << endl;
	else
		cout << "color:\t" << "RED" << endl;
	
	cout << endl;

	Inorder_traversal_helper(node->right);
}

void	RedBlackTree::Preorder_traversal_helper(Node* node)
{
	if (node == this->nil)
		return ;
	

	cout << endl;

	if (node == this->root)
		cout << "__ ROOT __" << endl;
	cout << "data:\t" << node->data << endl;
	if (node->color == false)
		cout << "color:\t" << "BLACK" << endl;
	else
		cout << "color:\t" << "RED" << endl;
	
	cout << endl;

	Preorder_traversal_helper(node->left);
	Preorder_traversal_helper(node->right);
}

void	RedBlackTree::Postorder_traversal_helper(Node* node)
{
	if (node == this->nil)
		return ;
	
	Postorder_traversal_helper(node->left);
	Postorder_traversal_helper(node->right);

	cout << endl;

	if (node == this->root)
		cout << "__ ROOT __" << endl;
	cout << "data:\t" << node->data << endl;
	if (node->color == false)
		cout << "color:\t" << "BLACK" << endl;
	else
		cout << "color:\t" << "RED" << endl;
	
	cout << endl;
}