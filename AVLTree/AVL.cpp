#include <iostream>
class AVL {
    struct Node {
        int height = 0;
        int key = 0;
        Node* left = nullptr;
        Node* right = nullptr;
        Node* parent = nullptr;
    };
    Node* root = nullptr;
    Node* getNewNode(int data, Node* parent) {
        Node* newNode = new Node;
        newNode->height = 0;
        newNode->key = data;
        newNode->left = nullptr;
        newNode->right = nullptr;
        newNode->parent = parent;
        return newNode;
    }
    int getHeight(Node* node) {
        if (node == nullptr) {
            return -1;
        }
        return node->height;
    }
    void updateHeight(Node* node) {
        if (node != nullptr) {
            int leftHeight = getHeight(node->left);
            int rightHeight = getHeight(node->right);
            node->height = 1 + std::max(leftHeight, rightHeight);
        }
    }
    Node* search(Node* p, int data) {
        if (!p) return nullptr;
        if (data == p->key) {
            return p;
        }
        else if (data < p->key) {
            return search(p->left, data);
        }
        else {
            return search(p->right, data);
        }
    }
    int balanceFactor(Node* p) {
        if (!p) {
            return 0;
        }
        return getHeight(p->left) - getHeight(p->right);
    }
    Node* findMin(Node* p) {
        if (!p) return nullptr;
        if (!p->left) {
            return p;
        }
        return findMin(p->left);
    }
    Node* findMax(Node* p) {
        if (!p) return nullptr;
        if (!p->right) {
            return p;
        }
        return findMax(p->right);
    }
    void inorder(Node* root) {
        if (!root) {
            return;
        }
        int bf = balanceFactor(root);
        inorder(root->left);

        std::cout << "data: " << root->key << " ";
        if (!root->parent) {
            std::cout << "|Parent: NULL ";
        }
        else {
            std::cout << "|Parent: " << root->parent->key << " ";
        }
        std::cout << " |Height " << root->height << " |Balance factor " << bf << "\n";
        inorder(root->right);
    }
    Node* succesor(Node* p) {
        if (p->right) {
            return findMin(p->right);
        }
        Node* succ = p->parent;
        while (succ && p == succ->right) {
            p = succ;
            succ = succ->parent;
        }
        return succ;
    }
    Node* predecessor(Node* p) {
        if (p->left) {
            return findMax(p->left);
        }
        Node* pre = p->parent;
        while (pre && p == pre->left) {
            p = pre;
            pre = pre->parent;
        }
        return pre;
    }
    Node* rotateLeft(Node*& root, Node* nodeToRotate) {
        Node* newRoot = nodeToRotate->right;
        Node* T2 = newRoot->left;

        newRoot->left = nodeToRotate;
        nodeToRotate->right = T2;

        newRoot->parent = nodeToRotate->parent;
        nodeToRotate->parent = newRoot;
        if (T2) {
            T2->parent = nodeToRotate;
        }

        if (root == nodeToRotate) {
            root = newRoot;
        }
        else {
            if (newRoot->parent->left == nodeToRotate) {
                newRoot->parent->left = newRoot;
            }
            else if (newRoot->parent->right == nodeToRotate) {
                newRoot->parent->right = newRoot;
            }
        }
        updateHeight(nodeToRotate);
        updateHeight(newRoot);

        return newRoot;
    }
    Node* rotateRight(Node*& root, Node* nodeToRotate) {
        Node* newRoot = nodeToRotate->left;
        Node* T2 = newRoot->right;

        newRoot->right = nodeToRotate;
        nodeToRotate->left = T2;

        newRoot->parent = nodeToRotate->parent;
        nodeToRotate->parent = newRoot;
        if (T2) {
            T2->parent = nodeToRotate;
        }

        if (root == nodeToRotate) {
            root = newRoot;
        }
        else {
            if (newRoot->parent->left == nodeToRotate) {
                newRoot->parent->left = newRoot;
            }
            else if (newRoot->parent->right == nodeToRotate) {
                newRoot->parent->right = newRoot;
            }
        }
        updateHeight(nodeToRotate);
        updateHeight(newRoot);

        return newRoot;
    }
    Node* insert(Node*& root, int data, Node* parent = nullptr) {
        if (!root) {
            root = getNewNode(data, parent);
        }
        else if (data <= root->key) {
            root->left = insert(root->left, data, root);
        }
        else {
            root->right = insert(root->right, data, root);
        }
        updateHeight(root);
        int bf = balanceFactor(root);
        if (bf > 1 && data < root->left->key) {
            return rotateRight(root, root);
        }
        if (bf > 1 && data > root->left->key) {
            rotateLeft(root, root->left);
            return rotateRight(root, root);
        }
        if (bf < -1 && data > root->right->key) {
            return rotateLeft(root, root);
        }
        if (bf < -1 && data < root->right->key) {
            rotateRight(root, root->right);
            return rotateLeft(root, root);
        }
        return root;
    }
    bool remove(Node*& root, Node* nodeToRemove) {
        Node* ReplacementNode;

        if (nodeToRemove->left && nodeToRemove->right) {
            ReplacementNode = succesor(nodeToRemove);
        }
        else {
            ReplacementNode = nodeToRemove;
        }

        Node* tmp;

        if (ReplacementNode->left) {
            tmp = ReplacementNode->left;
        }
        else {
            tmp = ReplacementNode->right;
        }

        if (tmp) {
            tmp->parent = ReplacementNode->parent;
        }

        if (ReplacementNode->parent) {

            if (ReplacementNode == ReplacementNode->parent->left) {
                ReplacementNode->parent->left = tmp;
            }
            else {
                ReplacementNode->parent->right = tmp;
            }
        }
        else {
            root = tmp;
        }

        if (ReplacementNode != nodeToRemove) {
            nodeToRemove->key = ReplacementNode->key;
        }
        delete ReplacementNode;
        updateHeight(root);
        int bf = balanceFactor(root);
        if (bf > 1 && balanceFactor(root->left) >= 0) {
            rotateRight(root, root);
        }
        if (bf > 1 && balanceFactor(root->left) < 0) {
            rotateLeft(root->left, root->left);
            rotateRight(root, root);
        }
        if (bf < -1 && balanceFactor(root->right) <= 0) {
            rotateLeft(root, root);
        }
        if (bf < -1 && balanceFactor(root->right) > 0) {
            rotateRight(root->right, root->right);
            rotateLeft(root, root);
        }
        return true;
    }
public:
    void displayInorder() {
        std::cout << "Inorder:\n";
        inorder(root);
        std::cout << "\n";
    }
    void insertion(int data) {
        root = insert(root, data, nullptr);
    }
    Node* search(int data) {
        return search(root, data);
    }
    Node* getRoot() {
        return root;
    }
    void deletion(int data) {
        Node* nodeToDelete = search(data);
        if (nodeToDelete == nullptr) {
            std::cerr << "Error: Node with data " << data << " not found in the tree.\n";
            return;
        }
        remove(root, nodeToDelete);
    }
};
int main()
{
    AVL avl;
    int vals[] = { 2,12, 65, 32, 5, 27, 3, 10, 75, 34, 4,19,36,35 };
    for (int i : vals) {
        avl.insertion(i);
    }
    avl.deletion(12);
    avl.deletion(35);
    avl.displayInorder();

}