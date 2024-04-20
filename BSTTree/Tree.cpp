#include <iostream>
class Tree {
	struct Node {
		int data;
		Node* left;
		Node* right;
		Node* parent;
	};
	Node* root = nullptr;
	Node* getNewNode(Node* par, int val) {
		Node* newNode = new Node;
		newNode->data = val;
		newNode->left = nullptr;
		newNode->right = nullptr;
		newNode->parent = par;
		return newNode;
	}
	Node* insert(Node*&root, int data, Node* parent = nullptr) {
		if (!root) {
			root = getNewNode(parent, data);
		}
		else if (data <= root->data) {
			root->left = insert(root->left, data, root);
		}
		else {
			root->right = insert(root->right, data, root);
		}
		return root;
	}
	void inorder(Node*& root) {
		if (!root) {
			return;
		}
		inorder(root->left);
		std::cout << root->data << " ";
		inorder(root->right);
	}
	Node* findMin(Node* p) {
		if (!p) return nullptr;
		if (!p->left) return p;
		return findMin(p->left);
	}
	Node* findMax(Node* p) {
		if (!p) return nullptr;
		if (!p->right) return p;
		return findMax(p->right);
	}
	Node* find(Node*&root, int d) {
		if (!root) return nullptr;
		if (d == root->data) {
			return root;
		}
		else if (d < root->data) {
			return find(root->left,d);
		}
		else {
			return find(root->right, d);
		}
	}
	Node* predecessor(Node* p) {
		if (p->left) {
			return findMax(p->left);
		}
		Node* pre = p->parent;
		while (pre && pre == p->left) {
			p = pre;
			pre = pre->parent;
		}
		return pre;
	}
	Node* succesor(Node* p) {
		if (p->right) {
			return findMin(p->right);
		}
		Node* succ = p->parent;
		while (succ && succ == p->right) {
			p = succ;
			succ = succ->parent;
		}
		return succ;
	}
	void remove(Node*& root, Node* nodeToRemove) {
		Node* replacementNode;
		if (nodeToRemove->left && nodeToRemove->right) {
			replacementNode = succesor(nodeToRemove);
		}
		else {
			replacementNode = nodeToRemove;
		}
		Node* tmp;
		if (replacementNode->left) {
			tmp = replacementNode->left;
		}
		else {
			tmp = replacementNode->right;
		}
		if (tmp) {
			tmp->parent = replacementNode->parent;
		}
		if (replacementNode->parent) {
			if (replacementNode == replacementNode->parent->left) {
				replacementNode->parent->left = tmp;
			}
			else {
				replacementNode->parent->right = tmp;
			}
		}
		else {
			root = tmp;
		}
		if (replacementNode != nodeToRemove) {
			nodeToRemove->data = replacementNode->data;
		}
		delete replacementNode;
	}
public:
	void insert(int d) {
		root = insert(root, d, nullptr);
	}
	void inorder() {
		inorder(root);
	}
	int getMin() {
		Node* x = findMin(root);
		return x->data;
	}
	int getMax() {
		Node* x = findMax(root);
		return x->data;
	}
	int getPredecessor(int data) {
		Node* x = find(root, data);
		Node* pre = predecessor(x);
		return pre->data;
	}
	int getSuccesor(int data) {
		Node* x = find(root, data);
		Node* suc = succesor(x);
		return suc->data;
	}
	void remove(int data) {
		Node* x = find(root, data);
		remove(root, x);
	}
};
int main() {
	Tree BST;
	int vals[] = { 0,2,-2,4,-4,8,-8 };
	for (int v : vals) {
		BST.insert(v);
	}
	BST.inorder(); std::cout << "\n";
	std::cout << "Minimum value is: " << BST.getMin() << "\n";
	std::cout << "Maximum value is: " << BST.getMax() << "\n";
	std::cout << "Predecessor of 8 is: " << BST.getPredecessor(8) << "\n";
	std::cout << "Predecessor of 0 is: " << BST.getSuccesor(0) << "\n";
	std::cout << "Tree after deleting 8: "; BST.remove(8); std::cout << "\n";
	BST.inorder();

}