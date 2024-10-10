#include <iostream>
using namespace std;

// Definition of a BST Node
struct Node {
    int data;
    Node* left;
    Node* right;

    // Constructor
    Node(int value) : data(value), left(nullptr), right(nullptr) {}
};

// Class for Binary Search Tree
class BinarySearchTree {
private:
    Node* root;

    // Helper function for insertion
    Node* insert(Node* node, int value) {
        if (node == nullptr) {
            // If current node is null, create a new node
            return new Node(value);
        }

        if (value < node->data) {
            // Insert in the left subtree
            node->left = insert(node->left, value);
        }
        else if (value > node->data) {
            // Insert in the right subtree
            node->right = insert(node->right, value);
        }
        // If value is already present, do not insert duplicates
        return node;
    }

    // Helper function for searching
    bool search(Node* node, int value) const {
        if (node == nullptr) {
            return false; // Not found
        }

        if (value == node->data) {
            return true; // Found
        }
        else if (value < node->data) {
            return search(node->left, value); // Search in left subtree
        }
        else {
            return search(node->right, value); // Search in right subtree
        }
    }

    // Helper function for in-order traversal
    void inOrderTraversal(Node* node) const {
        if (node != nullptr) {
            inOrderTraversal(node->left);
            cout << node->data << " ";
            inOrderTraversal(node->right);
        }
    }

    // Helper function for pre-order traversal
    void preOrderTraversal(Node* node) const {
        if (node != nullptr) {
            cout << node->data << " ";
            preOrderTraversal(node->left);
            preOrderTraversal(node->right);
        }
    }

    // Helper function for post-order traversal
    void postOrderTraversal(Node* node) const {
        if (node != nullptr) {
            postOrderTraversal(node->left);
            postOrderTraversal(node->right);
            cout << node->data << " ";
        }
    }

    // Helper function to find the minimum value node
    Node* findMin(Node* node) const {
        while (node->left != nullptr)
            node = node->left;
        return node;
    }

    // Helper function for deletion
    Node* deleteNode(Node* node, int value) {
        if (node == nullptr) {
            return node; // Value not found
        }

        if (value < node->data) {
            node->left = deleteNode(node->left, value); // Go to left subtree
        }
        else if (value > node->data) {
            node->right = deleteNode(node->right, value); // Go to right subtree
        }
        else {
            // Node with only one child or no child
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            // Node with two children:
            // Get the inorder successor (smallest in the right subtree)
            Node* temp = findMin(node->right);

            // Copy the inorder successor's data to this node
            node->data = temp->data;

            // Delete the inorder successor
            node->right = deleteNode(node->right, temp->data);
        }
        return node;
    }

    // Helper function to deallocate memory
    void destroyTree(Node* node) {
        if (node != nullptr) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

public:
    // Constructor
    BinarySearchTree() : root(nullptr) {}

    // Destructor
    ~BinarySearchTree() {
        destroyTree(root);
    }

    // Public insertion method
    void insert(int value) {
        root = insert(root, value);
    }

    // Public search method
    bool search(int value) const {
        return search(root, value);
    }

    // Public in-order traversal
    void inOrderTraversal() const {
        inOrderTraversal(root);
        cout << endl;
    }

    // Public pre-order traversal
    void preOrderTraversal() const {
        preOrderTraversal(root);
        cout << endl;
    }

    // Public post-order traversal
    void postOrderTraversal() const {
        postOrderTraversal(root);
        cout << endl;
    }

    // Public deletion method
    void deleteNode(int value) {
        root = deleteNode(root, value);
    }
};

// Function to display menu
void displayMenu() {
    cout << "\nBinary Search Tree Operations:\n";
    cout << "1. Insert\n";
    cout << "2. Search\n";
    cout << "3. In-Order Traversal\n";
    cout << "4. Pre-Order Traversal\n";
    cout << "5. Post-Order Traversal\n";
    cout << "6. Delete\n";
    cout << "7. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    BinarySearchTree bst;
    int choice, value;

    while (true) {
        displayMenu();
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter value to insert: ";
            cin >> value;
            bst.insert(value);
            cout << value << " inserted into BST.\n";
            break;
        case 2:
            cout << "Enter value to search: ";
            cin >> value;
            if (bst.search(value)) {
                cout << value << " found in BST.\n";
            }
            else {
                cout << value << " not found in BST.\n";
            }
            break;
        case 3:
            cout << "In-Order Traversal: ";
            bst.inOrderTraversal();
            break;
        case 4:
            cout << "Pre-Order Traversal: ";
            bst.preOrderTraversal();
            break;
        case 5:
            cout << "Post-Order Traversal: ";
            bst.postOrderTraversal();
            break;
        case 6:
            cout << "Enter value to delete: ";
            cin >> value;
            bst.deleteNode(value);
            cout << value << " deleted from BST (if it existed).\n";
            break;
        case 7:
            cout << "Exiting program.\n";
            return 0;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
