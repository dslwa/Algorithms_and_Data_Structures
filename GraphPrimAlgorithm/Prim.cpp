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

eNode* primAlgo(std::vector<Node*>& List, int startVertex) {

	int V = List.size();
	std::vector<int> colors(V, 0);
	colors[startVertex] = 1;
	eNode* res = nullptr;
	while (true) {
		int currentVertex = -1;
		int colorUpdater = -1;
		int minWeight = INT_MAX;
		for (int i = 0; i < V; i++) {
			if (colors[i] == 1) {
				Node* curr = List[i];
				while (curr) {
					if (colors[curr->to] == false && curr->weight <= minWeight) {
						colorUpdater = curr->to;
						minWeight = curr->weight;
						currentVertex = i;
					}
					curr = curr->next;
				}
			}
		}
		if (colorUpdater == -1)
			break;

		colors[colorUpdater] = 1;
		res = append(res, currentVertex, colorUpdater, minWeight);
	}

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
	eNode* h3 = primAlgo(List, 7);
	visit(h3); std::cout << "->Nullptr\n";
}
