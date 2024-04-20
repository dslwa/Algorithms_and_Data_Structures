#include <iostream>
#include <vector>
#include <fstream>

struct Node {
    int weight;
    int num;
    Node* next;
};

Node* addFront(Node* head, int n, int w) {
    Node* nodeToAdd = new Node;
    nodeToAdd->num = n;
    nodeToAdd->weight = w;
    nodeToAdd->next = head;
    head = nodeToAdd;
    return head;
}

void show(Node* head) {
    Node* tmp = head;
    while (tmp) {
        std::cout << tmp->num << "/" << tmp->weight << "->";
        tmp = tmp->next;
    }
}

struct nodeEdge {
    int to;
    int from;
    int weight;
    nodeEdge* next;
};

nodeEdge* pushBack(nodeEdge*& head, int t, int f, int w) {
    nodeEdge* nodeToAdd = new nodeEdge;
    nodeToAdd->to = t;
    nodeToAdd->from = f;
    nodeToAdd->weight = w;
    nodeToAdd->next = head;
    head = nodeToAdd;
    return head;
}

void visitEdge(nodeEdge* head) {
    nodeEdge* tmp = head;
    while (tmp) {
        std::cout << tmp->from << "/" << tmp->to << "/" << tmp->weight << "->";
        tmp = tmp->next;
    }
}

std::vector<std::vector<int>> createMatrix() {
    int numVertices, numEdges;
    std::fstream read;
    read.open("graph.txt");

    if (!read.is_open()) {
        std::cerr << "Error";
        exit(EXIT_FAILURE);
    }

    read >> numVertices >> numEdges;
    std::vector<std::vector<int>> grid(numVertices, std::vector<int>(numVertices, 0));

    int x, y, w;
    for (int i = 0; i < numEdges; i++) {
        read >> x >> y >> w;
        grid[x][y] = w;
        grid[y][x] = w;
    }

    read.close();
    return grid;
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

nodeEdge* edgeList(nodeEdge*& head) {
    int numVertices, numEdges;
    std::fstream read;
    read.open("graph.txt");
    read >> numVertices >> numEdges;
    if (!read.is_open()) {
        std::cerr << "Error";
        exit(EXIT_FAILURE);
    }
    int x, y, w;
    for (int i = 0; i < numEdges; i++) {
        read >> x >> y >> w;
        head = pushBack(head, x, y, w);
        head = pushBack(head, y, x, w);
    }

    read.close();
    return head;
}

std::vector<Node*> generateLN(nodeEdge* head) {
    std::fstream read;
    read.open("graph.txt");
    int numVertices;
    read >> numVertices;
    std::vector<Node*> generated(numVertices, nullptr);
    nodeEdge* tmp = head;
    while (tmp) {
        Node* nodeFrom = new Node;
        nodeFrom->num = tmp->to;
        nodeFrom->weight = tmp->weight;
        nodeFrom->next = generated[tmp->from];
        generated[tmp->from] = nodeFrom;

        Node* nodeTo = new Node;
        nodeTo->num = tmp->from;
        nodeTo->weight = tmp->weight;
        nodeTo->next = generated[tmp->to];
        generated[tmp->to] = nodeTo;
        tmp = tmp->next;
    }

    read.close();
    return generated;
}
nodeEdge* generateLE(std::vector<Node*> x) {
    std::fstream read;
    read.open("graph.txt");
    int numVerticies, numEdges;
    read >> numVerticies >> numEdges;
    nodeEdge* res = nullptr;
    for (int i = 0; i < numVerticies; i++) {
        Node* tmp = x[i];
        while (tmp) {
            nodeEdge* newNode = new nodeEdge;
            res = pushBack(res, i, tmp->num, tmp->weight);
            tmp = tmp->next;
        }
    }
    read.close();
    return res;
}

nodeEdge* generateLEfromMatrix(std::vector<std::vector<int>> x) {
    std::fstream read;
    read.open("graph.txt");
    int numVerticies, numEdges;
    nodeEdge* res = nullptr;
    read >> numVerticies >> numEdges;
    for (int i = 0; i < numVerticies; i++) {
        for (int j = 0; j < numVerticies; j++) {
            if (x[i][j] != 0) {
                res = pushBack(res, i, j, x[i][j]);
            }
        }
    }
    read.close();
    return res;
}
int main() {

    nodeEdge* head = nullptr;
    std::cout << "Adjacency Matrix from.txt\n";
    std::vector<std::vector<int>> grid = createMatrix();
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            std::cout << grid[i][j] << "\t";
        }
        std::cout << "\n";
    }

    std::cout << "\nAdjacency List from.txt\n";
    std::vector<Node*> grid1 = createList();
    for (int i = 0; i < grid1.size(); i++) {
        std::cout << "List[" << i << "]->";
        show(grid1[i]);
        std::cout << "->NULL\n";

    }

  
    std::cout << "\nList of Edges from .txt\n";
    nodeEdge* list = edgeList(head);
    std::cout << "List -> "; visitEdge(list); std::cout << "->NULL\n";


    std::cout << "\nAdjacency List from LE\n";
    std::vector<Node*> gen = generateLN(list);
    for (int i = 0; i < gen.size(); i++) {
        std::cout << "List[" << i << "]->";
        show(gen[i]);
        std::cout << "->NULL\n";

    }
    std::cout << "\nList of Edges from LN\n";
    nodeEdge* t = generateLE(grid1);
    std::cout << "List -> "; visitEdge(t); std::cout << "NULL\n";

    std::cout << "\nList of Edges from matrix\n";
    nodeEdge* x = generateLEfromMatrix(grid);
    std::cout << "List -> "; visitEdge(t); std::cout << "NULL\n";
   
    return 0;
}