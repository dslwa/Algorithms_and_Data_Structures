#include <iostream>
#include <vector>
#include <fstream>

struct Node {
	int to;
	int weight;
	Node* next;
};

Node* addFront(Node* head, int t, int w) {
	Node* nodeToAdd = new Node;
	nodeToAdd->to = t;
	nodeToAdd->weight = w;
	nodeToAdd->next = head;
	head = nodeToAdd;
	return head;
}
void Visit(Node* head) {
	Node* tmp = head;
	while (tmp) {
		std::cout << tmp->to << "/" << tmp->weight << "->";
		tmp = tmp->next;
	}
}

struct eNode {
	int from;
	int to;
	int weight;
	eNode* next;
};

eNode* append(eNode*& head1, int f, int t, int w) {
	eNode* nodeToAdd = new eNode;
	nodeToAdd->from = f;
	nodeToAdd->to = t;
	nodeToAdd->weight = w;
	nodeToAdd->next = nullptr;

	if (head1 == nullptr) {
		head1 = nodeToAdd;
	}
	else {
		eNode* last = head1;
		while (last->next != nullptr) {
			last = last->next;
		}
		last->next = nodeToAdd;
	}

	return head1;
}


eNode* eList() {
	std::fstream read;
	read.open("graph.txt");
	if (!read.is_open()) {
		std::cerr << "Error";
		exit(EXIT_FAILURE);
	}
	int numVerticies, numEdges;
	read >> numVerticies >> numEdges;
	int x, y, w;
	eNode* head1 = nullptr;
	for (int i = 0; i < numEdges; i++) {
		read >> x >> y >> w;
		head1 = append(head1, x, y, w);
		head1 = append(head1, y, x, w);
	}
	return head1;
}

void visit(eNode*& head1) {
	eNode* tmp = head1;
	while (tmp) {
		std::cout << tmp->from << "/" << tmp->to << "/" << tmp->weight << "->";
		tmp = tmp->next;
	}
}

std::vector<Node*> createList() {
	int numVertices, numEdges;
	std::fstream read;
	read.open("graph.txt");

	if (!read.is_open()) {
		std::cerr << "Error";
		exit(EXIT_FAILURE);
	}

	read >> numVertices >> numEdges;

	std::vector<Node*> list(numVertices, nullptr);
	int x, y, w;
	for (int i = 0; i < numEdges; i++) {
		read >> x >> y >> w;
		list[x] = addFront(list[x], y, w);
		list[y] = addFront(list[y], x, w);
	}
	read.close();
	return list;
}

eNode* kruskalAlgo(std::vector<Node*>& List, int startVertex) {

	int V = List.size();
	std::vector<int> colors(V, 0);
	std::vector<int> forest(V, 0);
	eNode* res = nullptr;
	return res;
}
int main() {
	std::vector<Node*> List = createList();
	for (int i = 0; i < List.size(); i++) {
		std::cout << "List[" << i << "]->";
		Visit(List[i]);
		std::cout << "->NULLPTR\n";
	}

	std::cout << "\nPrimAlgoList->";
	eNode* h3 = kruskalAlgo(List, 7);
	visit(h3); std::cout << "->Nullptr\n";
}
