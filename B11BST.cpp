#include <iostream>
#include <string>
using namespace std;

// Node structure
struct Node {
    string key;      // Keyword
    string meaning;  // Meaning
    Node* left;
    Node* right;

    Node(string k, string m) {
        key = k;
        meaning = m;
        left = right = NULL;
    }
};

// BST Dictionary Class
class BSTDictionary {
private:
    Node* root;

    // Insert a new keyword
    Node* insert(Node* root, string key, string meaning) {
        if (root == NULL)
            return new Node(key, meaning);
        if (key < root->key)
            root->left = insert(root->left, key, meaning);
        else if (key > root->key)
            root->right = insert(root->right, key, meaning);
        else
            cout << "Keyword already exists!\n";
        return root;
    }

    // Find minimum node (used in deletion)
    Node* findMin(Node* root) {
        while (root->left != NULL)
            root = root->left;
        return root;
    }

    // Delete a keyword
    Node* deleteNode(Node* root, string key) {
        if (root == NULL)
            return root;

        if (key < root->key)
            root->left = deleteNode(root->left, key);
        else if (key > root->key)
            root->right = deleteNode(root->right, key);
        else {
            // Node with one or no child
            if (root->left == NULL) {
                Node* temp = root->right;
                delete root;
                return temp;
            }
            else if (root->right == NULL) {
                Node* temp = root->left;
                delete root;
                return temp;
            }

            // Node with two children
            Node* temp = findMin(root->right);
            root->key = temp->key;
            root->meaning = temp->meaning;
            root->right = deleteNode(root->right, temp->key);
        }
        return root;
    }

    // Search a keyword
    Node* search(Node* root, string key, int &comparisons) {
        if (root == NULL || root->key == key)
            return root;

        comparisons++;
        if (key < root->key)
            return search(root->left, key, comparisons);
        return search(root->right, key, comparisons);
    }

    // Update meaning of a keyword
    bool update(Node* root, string key, string newMeaning) {
        if (root == NULL)
            return false;
        if (root->key == key) {
            root->meaning = newMeaning;
            return true;
        }
        if (key < root->key)
            return update(root->left, key, newMeaning);
        return update(root->right, key, newMeaning);
    }

    // Display in ascending order (Inorder Traversal)
    void inorder(Node* root) {
        if (root != NULL) {
            inorder(root->left);
            cout << root->key << " : " << root->meaning << endl;
            inorder(root->right);
        }
    }

    // Display in descending order (Reverse Inorder Traversal)
    void reverseInorder(Node* root) {
        if (root != NULL) {
            reverseInorder(root->right);
            cout << root->key << " : " << root->meaning << endl;
            reverseInorder(root->left);
        }
    }

    // Calculate height of BST (Maximum comparisons in worst case)
    int getHeight(Node* root) {
        if (root == NULL)
            return 0;
        return 1 + max(getHeight(root->left), getHeight(root->right));
    }

public:
    BSTDictionary() {
        root = NULL;
    }

    void insert(string key, string meaning) {
        root = insert(root, key, meaning);
    }

    void deleteKeyword(string key) {
        root = deleteNode(root, key);
    }

    void searchKeyword(string key) {
        int comparisons = 1;
        Node* result = search(root, key, comparisons);
        if (result != NULL)
            cout << "Keyword found: " << result->key << " -> " << result->meaning << " (Comparisons: " << comparisons << ")\n";
        else
            cout << "Keyword not found! (Comparisons: " << comparisons << ")\n";
    }

    void updateKeyword(string key, string newMeaning) {
        if (update(root, key, newMeaning))
            cout << "Keyword updated successfully.\n";
        else
            cout << "Keyword not found.\n";
    }

    void displayAscending() {
        cout << "Dictionary (Ascending Order):\n";
        inorder(root);
    }

    void displayDescending() {
        cout << "Dictionary (Descending Order):\n";
        reverseInorder(root);
    }

    void maxComparisons() {
        cout << "Maximum comparisons needed in worst case: " << getHeight(root) << endl;
    }
};

// Main function
int main() {
    BSTDictionary dict;
    int choice;
    string key, meaning;

    do {
        cout << "\nDictionary Operations:\n";
        cout << "1. Insert\n2. Delete\n3. Search\n4. Update\n5. Display (Ascending)\n6. Display (Descending)\n7. Max Comparisons\n8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                cout << "Enter keyword: ";
                getline(cin, key);
                cout << "Enter meaning: ";
                getline(cin, meaning);
                dict.insert(key, meaning);
                break;
            case 2:
                cout << "Enter keyword to delete: ";
                getline(cin, key);
                dict.deleteKeyword(key);
                break;
            case 3:
                cout << "Enter keyword to search: ";
                getline(cin, key);
                dict.searchKeyword(key);
                break;
            case 4:
                cout << "Enter keyword to update: ";
                getline(cin, key);
                cout << "Enter new meaning: ";
                getline(cin, meaning);
                dict.updateKeyword(key, meaning);
                break;
            case 5:
                dict.displayAscending();
                break;
            case 6:
                dict.displayDescending();
                break;
            case 7:
                dict.maxComparisons();
                break;
            case 8:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 8);

    return 0;
}
