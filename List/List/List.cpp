#include <iostream>

class List {
	struct Node {
		Node* next;
		int data;
	};
	Node* head = nullptr;
	Node* pushBack(Node*& head, int val) {
		Node* newNode = new Node;
		newNode->data = val;
		newNode->next = head;
		head = newNode;
		return head;
	}
	Node* append(Node*& head, int d) {
		Node* nodeToAdd = new Node;
		nodeToAdd->data = d;
		if (!head) {
			nodeToAdd->next = head;
			head = nodeToAdd;
			return head;
		}
		Node* tmp = head;
		while (tmp->next) {
			tmp = tmp->next;
		}
		nodeToAdd->next = nullptr;
		tmp->next = nodeToAdd;
		return head;
	}
	void visit(Node*& head) {
		Node* tmp = head;
		while (tmp) {
			std::cout << tmp->data << " ";
			tmp = tmp->next;
		}
	}
	void remove(Node*& head, int index) {
		if (index == 1) {
			Node* tmp = head->next;
			delete head;
			head = tmp;
		}
		Node* tmp = head;
		for (int i = 0; i < index - 1; i++) {
			tmp = tmp->next;
		}
		Node* tmp2 = tmp->next;
		tmp->next = tmp2->next;
		delete tmp2;
	}
public:
	void pushBack(int d) {
		head = pushBack(head, d);
	}
	void append(int d) {
		head = append(head, d);
	}
	void print() {
		visit(head);
	}
	void remove(int data) {
		remove(head, data);
	}
};

int main() {
	List list;
	int vals[] = { 1,2,3,4,5,6,7,8,9 };
	for (int i : vals) {
		list.append(i);
	}
	list.print(); std::cout << "\n";
	list.pushBack(0);
	list.print(); std::cout << "\n";
	list.remove(3);
	list.print(); std::cout << "\n";
}