#include <iostream>
#include "bst.h"

using namespace std;

void testDataInsert(BST::Tree<int>* tree) {
	tree->add(50);
	tree->add(76);
	tree->add(21);
	tree->add(4);
	tree->add(32);
	tree->add(64);
	tree->add(15);
	tree->add(52);
	tree->add(14);
	tree->add(100);
	tree->add(83);
	tree->add(2);
	tree->add(3);
	tree->add(70);
	tree->add(87);
	tree->add(80);
}

void print(BST::Tree<int>* tree) {
	using namespace BST;
	Node<int>* node = tree->search(100);

	while(node) {
		cout << node->getValue() << " ";
		node = tree->predecessor(node);
	}
	cout << endl;
}

int main() {
	using namespace BST;

	Tree<int>* tree = new Tree<int>();
	testDataInsert(tree);

	cout << "Maximum value: " << tree->maximum()->getValue() << endl;
	cout << "Minimum value: " << tree->minimum()->getValue() << endl;

	/**
	 * Test predecessor, search and remove in 
	 * one place
	 */
	print(tree);
	tree->removeByKey(80);
	print(tree);
	tree->removeByKey(70);
	print(tree);
	tree->removeByKey(87);
	print(tree);
	tree->removeByKey(50);
	print(tree);

	return 0;
}