#include<iostream>
#include<fstream>
#include<string>

using namespace std;

struct node
{
	int age;
	char gender;
	string name;
	char color;
	int *num_women;
	int *num_men;
	node *parent;
	node *left;
	node *right;
};

class RedBlackTree
{

public:
	node *root;
	RedBlackTree() : root(NULL){}
	void insert(string, char, int);
	void insertUpdate(node *);
	void leftRotate(node *);
	void rightRotate(node *);
	void print(node *);
	void travelTree(node *p);
	void updateNumberOfMenAndWomen(node *, int *, int *);
	void resetNumberOfMenAndWomen(node *);
	string nth_woman(node *, int);
	string nth_man(node *, int);
};

int main(int argc, char** argv){

	int age;
	string name;
	char gender;

	string input_file = argv[1];

	ifstream input(input_file.c_str());

	RedBlackTree RBT;

	while (!input.eof())
	{
		input >> name >> gender >> age;
		RBT.insert(name, gender, age);
	}

	input.close();

	cout << "Red-Black Tree:" << endl << endl;
	RBT.print(RBT.root);

	cout << endl << endl << "2nd youngest man: " << RBT.nth_man(RBT.root, 2) << endl;
	cout << "8th youngest woman: " << RBT.nth_woman(RBT.root, 8);

	return 0;
}

void RedBlackTree::insert(string name, char gender, int age)
{
	node *temp, *newnodeParent;
	node *newnode = new node;

	newnode->age = age;
	newnode->gender = gender;
	newnode->name = name;
	newnode->left = NULL;
	newnode->right = NULL;
	newnode->color = 'r';
	newnode->num_men = new int(0);
	newnode->num_women = new int(0);

	temp = root;
	newnodeParent = NULL;

	if (root == NULL)
	{
		root = newnode;
		newnode->parent = NULL;
	}
	else
	{
		while (temp != NULL)
		{
			newnodeParent = temp;
			if (temp->age < newnode->age)
				temp = temp->right;
			else
				temp = temp->left;
		}
		newnode->parent = newnodeParent;
		if (newnodeParent->age < newnode->age)
			newnodeParent->right = newnode;
		else
			newnodeParent->left = newnode;
	}
	insertUpdate(newnode);
	resetNumberOfMenAndWomen(root);
	travelTree(root);
}
void RedBlackTree::insertUpdate(node *newnode)
{
	node *temp;
	if (root == newnode)
	{
		newnode->color = 'b';
		return;
	}
	while (newnode->parent != NULL && newnode->parent->color == 'r')
	{
		node *g = newnode->parent->parent;

		if (g->left == newnode->parent)
		{
			if (g->right != NULL)
			{
				temp = g->right;
				if (temp->color == 'r')
				{
					newnode->parent->color = 'b';
					temp->color = 'b';
					g->color = 'r';
					newnode = g;
				}
			}
			else
			{
				if (newnode->parent->right == newnode)
				{
					newnode = newnode->parent;
					leftRotate(newnode);
				}
				newnode->parent->color = 'b';
				g->color = 'r';
				rightRotate(g);
			}
		}
		else
		{
			if (g->left != NULL)
			{
				temp = g->left;
				if (temp->color == 'r')
				{
					newnode->parent->color = 'b';
					temp->color = 'b';
					g->color = 'r';
					newnode = g;
				}
			}
			else
			{
				if (newnode->parent->left == newnode)
				{
					newnode = newnode->parent;
					rightRotate(newnode);
				}
				newnode->parent->color = 'b';
				g->color = 'r';
				leftRotate(g);
			}
		}
		root->color = 'b';
	}
}
void RedBlackTree::leftRotate(node *p)
{
	if (p->right == NULL)
		return;
	else
	{
		node *temp = p->right;
		if (temp->left != NULL)
		{
			p->right = temp->left;
			temp->left->parent = p;
		}
		else
			p->right = NULL;
		if (p->parent != NULL)
			temp->parent = p->parent;
		if (p->parent == NULL)
			root = temp;
		else
		{
			if (p == p->parent->left)
				p->parent->left = temp;
			else
				p->parent->right = temp;
		}
		temp->left = p;
		p->parent = temp;
	}
}
void RedBlackTree::rightRotate(node *p)
{
	if (p->left == NULL)
		return;
	else
	{
		node *temp = p->left;
		if (temp->right != NULL)
		{
			p->left = temp->right;
			temp->right->parent = p;
		}
		else
			p->left = NULL;
		if (p->parent != NULL)
			temp->parent = p->parent;
		if (p->parent == NULL)
			root = temp;
		else
		{
			if (p == p->parent->left)
				p->parent->left = temp;
			else
				p->parent->right = temp;
		}
		temp->right = p;
		p->parent = temp;
	}
}
void RedBlackTree::print(node *p){

	if (p == NULL)
		return;
	cout << "[";
	print(p->left);
	cout << p->name << "-" << p->age << "-" << p->gender;
	print(p->right);
	cout << "]";
}
void RedBlackTree::resetNumberOfMenAndWomen(node *p){

	if (p->left != NULL)
		resetNumberOfMenAndWomen(p->left);

	*(p->num_men) = 0;
	*(p->num_women) = 0;

	if (p->right != NULL)
		resetNumberOfMenAndWomen(p->right);

}
void RedBlackTree::travelTree(node *p){

	if (p->left != NULL)
		travelTree(p->left);

	updateNumberOfMenAndWomen(p, p->num_women, p->num_men);

	if (p->right != NULL)
		travelTree(p->right);
}
void RedBlackTree::updateNumberOfMenAndWomen(node *p, int *numberOFwomen, int *numberOFmen){

	if (p->left != NULL)
		updateNumberOfMenAndWomen(p->left, numberOFwomen, numberOFmen);

	if (p->gender == 'F')
		(*numberOFwomen)++;
	else if (p->gender == 'M')
		(*numberOFmen)++;

	if (p->right != NULL)
		updateNumberOfMenAndWomen(p->right, numberOFwomen, numberOFmen);

}
string RedBlackTree::nth_woman(node *p, int nth){

	int k, j;

	if (p->left != NULL)
		j = *((p->left)->num_women);

	if (p->left == NULL)
	{
		k = 1;
		j = 0;
	}
	else if (p->gender == 'F')
		k = j + 1;
	else if (p->gender == 'M')
		k = j;

	if (nth == k && p->gender == 'F')
		return p->name;
	else if (nth == k && p->gender == 'M')
	{
		if (j >= nth)
			return nth_woman(p->left, nth);
		else
			return nth_woman(p->right, nth - j);
	}

	if (nth < k)
		return nth_woman(p->left, nth);
	else
		return nth_woman(p->right, nth - k);
}
string RedBlackTree::nth_man(node *p, int nth){

	int k, j;

	if (p->left != NULL)
		j = *((p->left)->num_men);

	if (p->left == NULL)
	{
		k = 1;
		j = 0;
	}
	else if (p->gender == 'M')
		k = j + 1;
	else if (p->gender == 'F')
		k = j;

	if (nth == k && p->gender == 'M')
		return p->name;
	else if (nth == k && p->gender == 'F')
	{
		if (j >= nth)
			return nth_man(p->left, nth);
		else
			return nth_man(p->right, nth - j);
	}

	if (nth < k)
		return nth_man(p->left, nth);
	else
		return nth_man(p->right, nth - k);
}
