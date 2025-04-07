#include <iostream>
#include <cstring>
#include <cctype>  
using namespace std;

struct node {
    char data;
    node *left;
    node *right;
};

class tree {
public:
    node *top;  
    void expression(char []);
    void display(node *);
    void deletion(node *node);
};

class stack1 {
public:
    node *data[30];
    int top;
    stack1() {
        top = -1;
    }
    bool empty() {
        return top == -1;
    }
    void push(node *p) {
        if (top < 29) {  
            data[++top] = p;
        } else {
            cout << "Stack overflow" << endl;
        }
    }
    node *pop() {
        if (!empty()) {
            return data[top--];
        } else {
            cout << "Stack underflow" << endl;
            return nullptr; 
        }
    }
};

void tree::expression(char prefix[]) {
    stack1 s;
    int len = strlen(prefix);
    
    for (int i = len - 1; i >= 0; i--) {
        node *newNode = new node;
        newNode->left = nullptr;
        newNode->right = nullptr;

        if (isalpha(prefix[i])) { 
            newNode->data = prefix[i];
            s.push(newNode);
        } else if (prefix[i] == '+' || prefix[i] == '-' || prefix[i] == '*' || prefix[i] == '/') {  
            node *t2 = s.pop();
            node *t1 = s.pop();
            
            if (t1 == nullptr || t2 == nullptr) {
                cout << "Error: Insufficient operands for operator " << prefix[i] << endl;
                return;
            }
            
            newNode->data = prefix[i];
            newNode->left = t2;
            newNode->right = t1;
            s.push(newNode);
        }
    }
    
    if (!s.empty()) {
        top = s.pop();  
    } else {
        cout << "Error: Invalid prefix expression" << endl;
    }
}

void tree::display(node *top) {
    if (top != nullptr) {
        display(top->left);
        display(top->right);
        cout << top->data;
    }
}

void tree::deletion(node *node) {
    if (node == nullptr) {
        return;
    }
    deletion(node->left);
    deletion(node->right);
    cout << "Deleting node: " << node->data << endl;
    delete node;  
}

int main() {
    tree t;
    char exp1[20];

    int ch;
    do {
        cout << "1. Enter prefix expression" << endl;
        cout << "2. Display postfix Expression" << endl;
        cout << "3. Deletion" << endl;
        cout << "4. Exit" << endl;
        cout << "Choose an option: ";
        cin >> ch;

        switch (ch) {
        case 1:
            cout << "Enter the expression: ";
            cin >> exp1;
            t.expression(exp1);
            break;
        case 2:
            if (t.top != nullptr) {
                t.display(t.top);
                cout << endl;
            } else {
                cout << "Tree is empty." << endl;
            }
            break;
        case 3:
            t.deletion(t.top);
            t.top = nullptr; 
            break;
        case 4:
            cout << "END OF CODE" << endl;
            break;
        default:
            cout << "Choose a valid option." << endl;
            break;
        }
    } while (ch != 4);

    return 0;
}

