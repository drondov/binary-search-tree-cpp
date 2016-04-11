#include <iostream>

namespace BST {
	template <typename T> class Node {
		T value;
		Node<T>* left;
		Node<T>* right;
		Node<T>* parent;
	public:
		inline Node<T> (T v);
		inline T getValue();
		inline void setValue(T v);
		inline Node<T>* getLeftNode();
		inline void setLeftNode(Node<T>* node);
		inline Node<T>* getRightNode();
		inline void setRightNode(Node<T>* node);
		inline Node<T>* getParent();
		inline void setParent(Node<T>* node);
	};

	template <typename T> class Tree {
		Node<T>* root;
	public:
		Tree<T>();
		Tree<T>(Node<T>* node);
		void add(T v);
		void removeByKey(T key);
		void removeNode(Node<T>* node);
		Node<T>* maximum();
		Node<T>* minimum();
		Node<T>* predecessor(Node<T>* node);
		Node<T>* successor(Node<T>* node);
		Node<T>* search(T val);
	};

	template <typename T>
	inline Node<T>::Node(T v) {
		using namespace std;
		value = v;
		left = NULL;
		right = NULL;
		parent = NULL;
	}

	template <typename T>
	inline T Node<T>::getValue() {
		return this->value;
	}

	template <typename T>
	inline void Node<T>::setValue(T v) {
		this->value = v;
	}

	template <typename T>
	inline Node<T>* Node<T>::getLeftNode() {
		return this->left;
	}

	template <typename T>
	inline void Node<T>::setLeftNode(Node<T>* node) {
		this->left = node;
	}

	template <typename T>
	inline Node<T>* Node<T>::getRightNode() {
		return this->right;
	}

	template <typename T>
	inline void Node<T>::setRightNode(Node<T>* node) {
		 this->right = node;
	}

	template <typename T>
	inline Node<T>* Node<T>::getParent() {
		return this->parent;
	}

	template <typename T>
	inline void Node<T>::setParent(Node<T>* node) {
		 this->parent = node;
	}


	template <typename T>
    Tree<T>::Tree() {
		this->root = NULL;
	}

	template <typename T>
    Tree<T>::Tree(Node<T>* node) {
		this->root = node;
	}

	template <typename T>
	void Tree<T>::add(T v) {
		Node<T>* addedNode = new Node<T>(v);
		if(this->root == NULL) {
			this->root = addedNode;
			return;
		}
		
		Node<T>* currentNode = root;
		while(currentNode) {
			if(v < currentNode->getValue()) {
				if(currentNode->getLeftNode()) {
					currentNode = currentNode->getLeftNode();
				} else {
					addedNode->setParent(currentNode);
					currentNode->setLeftNode(addedNode);
					return;
				}
			} else {
				if(currentNode->getRightNode()) {
					currentNode = currentNode->getRightNode();
				} else {
					addedNode->setParent(currentNode);
					currentNode->setRightNode(addedNode);
					return;
				}
			}
		}

	}

	template <typename T>
	void Tree<T>::removeByKey(T key) {
		this->removeNode(this->search(key));
	}

	template <typename T>
	void Tree<T>::removeNode(Node<T>* node) {
		if(!node) return;
		Node<T>* parent = node->getParent();

		if(!node->getLeftNode()) {
			if(!parent) {
				this->root = node->getRightNode();
				delete node;
				return;
			}
			if(parent->getRightNode() == node) {
				parent->setRightNode(node->getRightNode());
			} else {
				parent->setLeftNode(node->getRightNode());
			}
			delete node;
			return;
		}

		if(!node->getRightNode()) {
			if(!parent) {
				this->root = node->getLeftNode();
				delete node;
				return;
			}
			if(parent->getLeftNode() == node) {
				parent->setLeftNode(node->getLeftNode());
			} else {
				parent->setRightNode(node->getLeftNode());
			}
			delete node;
			return;
		}

		/**
		 * Most complicated case with
		 * 2 child
		 */
		
		Node<T>* minNode = node->getRightNode();
		while(minNode->getLeftNode()) {
			minNode = minNode->getLeftNode();
		}
		Node<T>* minNodeParent = minNode->getParent();
		
		Node<T>* rightChild = minNode->getRightNode();

		minNode->setLeftNode(node->getLeftNode());
		node->getLeftNode()->setParent(minNode);
		minNode->setRightNode(node->getRightNode());
		node->getRightNode()->setParent(minNode);

		
		if(parent) {
			if(parent->getLeftNode() == node) {
			parent->setLeftNode(minNode);
			} else {
				parent->setRightNode(minNode);
			}
		} else {
			this->root = minNode;
		}
		minNode->setParent(parent);

		minNodeParent->setLeftNode(rightChild);
		if(rightChild) {
			rightChild->setParent(minNodeParent);
		}

		delete node;

	}

	template <typename T>
	Node<T>* Tree<T>::maximum() {
		Node<T>* currentNode = this->root;
		if(!currentNode) return NULL;
		while(currentNode->getRightNode()) {
			currentNode = currentNode->getRightNode();
		}
		return currentNode;
	}

	template <typename T>
	Node<T>* Tree<T>::minimum() {
		Node<T>* currentNode = this->root;
		if(!currentNode) return NULL;
		while(currentNode->getLeftNode()) {
			currentNode = currentNode->getLeftNode();
		}
		return currentNode;
	}

	template <typename T>
	Node<T>* Tree<T>::predecessor(Node<T>* node) {
		if(!node) return node;

		if(node->getLeftNode()) {
			Node<T>* currentNode = node->getLeftNode();
			while(currentNode->getRightNode()) {
				currentNode = currentNode->getRightNode();
			}
			return currentNode;
		}
		
		Node<T>* parent = node->getParent();
		while(parent && parent->getLeftNode() == node) {
			node = parent;
			parent = node->getParent();
		}
		return parent;
	}

	template <typename T>
	Node<T>* Tree<T>::successor(Node<T>* node) {
		if(!node) return node;

		if(node->getRightNode()) {
			Node<T>* currentNode = node->getRightNode();
			while(currentNode->getLeftNode()) {
				currentNode = currentNode->getLeftNode();
			}
			return currentNode;
		}
		
		Node<T>* parent = node->getParent();
		while(parent && parent->getRightNode() == node) {
			node = parent;
			parent = node->getParent();
		}
		return parent;
		
	}

	template <typename T>
	Node<T>* Tree<T>::search(T val) {
		Node<T>* currentNode = this->root;
		while(currentNode) {
			if(currentNode->getValue() == val)
				return currentNode;
			if(val < currentNode->getValue()) {
				currentNode = currentNode->getLeftNode();
			} else {
				currentNode = currentNode->getRightNode();
			}
		}
		return NULL;
	}

};