#include <iostream>
#include <stack>
#include "nf.hpp"
using namespace std;

nf::NodeFrontEndWrapper NFWrap;
#define WRAPPER NFWrap

class BinaryTree
{
    class Node : public nf::BinaryTreeNode<Node, int> 
    {
    public:
        Node(int newData) : BinaryTreeNode<Node, int>(NFWrap.api())
        {
            setData(newData);
        }
        std::string representation() override {
            return std::string(std::to_string(getData()));
        }
    };

    Node *root;
    unsigned int el_count = 0;

public:
    BinaryTree()
    {
        root = NULL;
    }

    // Insert data to build a complete binary tree
    // The lowest level that is filled from left to right
    void insert(int data)
    {
        if (!root)
        {
            root = new Node(data);
            return;
        }

        Node *curr = root;
        while(true)
        {
            if (data < curr->getData())
            {
                if (curr->getLeft()) //curr->getLeft()
                    curr = curr->getLeft(); //curr->getLeft()
                else {
                    curr->setLeft(new Node(data)); //curr->getLeft() = new Node(data);
                    ++el_count;
                    return;
                }
            } else {
                if (curr->getRight())
                    curr = curr->getRight();
                else {
                    curr->setRight(new Node(data)); 
                    ++el_count;
                    return;
                }
            }
        }
    }
   
    bool _isComplete(Node *node)
    {
        if (!node || !node->getLeft() && !node->getRight())
            return true;
        if (node->getLeft() && node->getRight())
            return _isComplete(node->getLeft()) && _isComplete(node->getRight());
        return false;
    }

    // Check if the binary tree is complete
    bool isComplete()
    {
        return _isComplete(root);
    }

    void _inOrderPrintRec(Node *node)
    {
        if (!node) return;
        _inOrderPrintRec(node->getLeft());
        cout << " " << node->getData();
        _inOrderPrintRec(node->getRight());
    }

    void _preOrderPrintRec(Node *node)
    {
        if (!node) return;
        cout << " " << node->getData();
        _preOrderPrintRec(node->getLeft());
        _preOrderPrintRec(node->getRight());
    }

    void _postOrderPrintRec(Node *node)
    {
        if (!node) return;
        _postOrderPrintRec(node->getLeft());
        _postOrderPrintRec(node->getRight());
        cout << " " << node->getData();
    }

    // The order of inOrder traversal is left->root->getRight()
    void inOrderPrintRec()
    {
        cout << "In order traversal (recursive):";
        _inOrderPrintRec(root);
        cout << endl;
    }

    void inOrderPrint()
    {
        cout << "In order traversal:";
        stack<Node*> st;
		root->highlight();
		nf::Utils::delay(1000);
        st.emplace(root);
        Node *node = st.top();
        while (node == NULL || !st.empty())
        {
            if (node)
            {
                st.push(node);
                node = node->getLeft();
            } else {
                Node *pop_node = st.top();
                if (st.size() == 1 && pop_node == root) break;
                cout << " " << pop_node->getData();
				pop_node->highlight();
				nf::Utils::delay(1000);
                st.pop();
                node = pop_node->getRight();
            }
        }
        cout << endl;
    }

    // The order of preorder traversal is root->getLeft()->getRight()
    void preOrderPrintRec()
    {
        cout << "Pre order traversal:";
        _preOrderPrintRec(root);
        cout << endl;
    }

    void preOrderPrint()
    {
        cout << "Pre order traversal:";
        stack<Node*> st;
        st.emplace(root);
		root->highlight();
		nf::Utils::delay(1000);
        Node *node = st.top();
        while (node == NULL || !st.empty())
        {
            if (node)
            {
                cout << " " << node->getData();
				node->highlight();
				nf::Utils::delay(1000);
                st.push(node);
                node = node->getLeft();
            } else {
                Node *pop_node = st.top();
                if (st.size() == 1 && pop_node == root) break;
                st.pop();
                node = pop_node->getRight();
            }
        }
        cout << endl;
    }

    // The order of traversal is left->getRight()->root
    void postOrderPrintRec()
    {
        cout << "Post order traversal:";
        _postOrderPrintRec(root);
        cout << endl;
    }

    void postOrderPrint()
    {
        cout << "Post order traversal:";
        stack<Node*> st;
        stack<Node*> printst;
        st.emplace(root);
		root->highlight();
		nf::Utils::delay(1000);
        Node *node = st.top();
        while (node == NULL || !st.empty())
        {
            if (node)
            {
                printst.push(node);
                st.push(node);
                node = node->getRight();
            } else {
                Node *pop_node = st.top();
                if (st.size() == 1 && pop_node == root) break;
                st.pop();
                node = pop_node->getLeft();
            }
        }

        while (printst.size())
        {
            cout << " " << printst.top()->getData();
			printst.top()->highlight();
			nf::Utils::delay(1000);
            printst.pop();
        }

        cout << endl;
    }
};

struct StringGraphNode : public nf::GraphNode<StringGraphNode, std::string> {
    StringGraphNode() : GraphNode<StringGraphNode, std::string>(NFWrap.api()) {}
};

struct MyNode : public nf::LinkedListNode<MyNode, std::string>
{
    MyNode() : LinkedListNode<MyNode, std::string>(NFWrap.api()) {}
};


int main()
{
    NFWrap = nf::NodeFrontEndWrapper();
    StringGraphNode* gnode = new StringGraphNode();
    gnode->setPosition(500,250);
    MyNode *n1 = new MyNode();
    n1->setPosition(150, 150);
    n1->setData(std::string("as"));
    n1->setData("as_c");
    BinaryTree bt = BinaryTree();


    /* initialize random seed: */
    srand(time(NULL));

    cout << "Binary tree is complete: " << (bt.isComplete() ? "True" : "False") << endl;

    // Add from 5 to 15 elements
    // Change to constant for easier debugging if necessary
    // bt.insert(20);
    // bt.insert(10);
    // bt.insert(40);
    // bt.insert(5);
    // bt.insert(15);
    // bt.insert(35);
    // bt.insert(45);
    // cout << bt.isComplete() << endl;
    // for (int i = 0; i < rand() % 10 + 5; i++)
    // {
    //     bt.insert(i);
    //     cout << "Inserted " << i << ": binary tree is complete:" << (bt.isComplete() ? "True" : "False") << endl;
    // }

    // cout << "Binary tree is complete: " << (bt.isComplete() ? "True" : "False") << endl;
    // bt.insert(20); cout << "Binary tree is complete: " << (bt.isComplete() ? "True" : "False") << endl;
    // bt.insert(10); cout << "Binary tree is complete: " << (bt.isComplete() ? "True" : "False") << endl;
    // bt.insert(40); cout << "Binary tree is complete: " << (bt.isComplete() ? "True" : "False") << endl;
    // bt.insert(5); cout << "Binary tree is complete: " << (bt.isComplete() ? "True" : "False") << endl;
    // bt.insert(15); cout << "Binary tree is complete: " << (bt.isComplete() ? "True" : "False") << endl;
    // bt.insert(35); cout << "Binary tree is complete: " << (bt.isComplete() ? "True" : "False") << endl;
    // bt.insert(45); cout << "Binary tree is complete: " << (bt.isComplete() ? "True" : "False") << endl;
    // bt.insert(4);
    // bt.insert(6);
    // bt.insert(16);
    // bt.insert(18);
    // bt.insert(17);
    // bt.insert(19);

	int ms = 250;
    NFWrap.api()->setWindowColor(sf::Color(210, 210, 210));
    cout << "Binary tree is complete: " << (bt.isComplete() ? "True" : "False") << endl;
    nf::Utils::delay(ms);
    bt.insert(20);
    cout << "Binary tree is complete: " << (bt.isComplete() ? "True" : "False") << endl;
    nf::Utils::delay(ms);
    bt.insert(10);
    cout << "Binary tree is complete: " << (bt.isComplete() ? "True" : "False") << endl;
    nf::Utils::delay(ms);
    bt.insert(40);
    cout << "Binary tree is complete: " << (bt.isComplete() ? "True" : "False") << endl;
    nf::Utils::delay(ms);
    bt.insert(5);
    cout << "Binary tree is complete: " << (bt.isComplete() ? "True" : "False") << endl;
    nf::Utils::delay(ms);
    bt.insert(15);
    cout << "Binary tree is complete: " << (bt.isComplete() ? "True" : "False") << endl;
    nf::Utils::delay(ms);
    bt.insert(17);
    cout << "Binary tree is complete: " << (bt.isComplete() ? "True" : "False") << endl;
    nf::Utils::delay(ms);
    bt.insert(16);
    cout << "Binary tree is complete: " << (bt.isComplete() ? "True" : "False") << endl;
    nf::Utils::delay(ms);
    bt.insert(35);
    cout << "Binary tree is complete: " << (bt.isComplete() ? "True" : "False") << endl;
    nf::Utils::delay(ms);
    bt.insert(45);
    cout << "Binary tree is complete: " << (bt.isComplete() ? "True" : "False") << endl;
    nf::Utils::delay(ms);


    // bt.inOrderPrintRec();
    bt.inOrderPrint();
    // bt.preOrderPrintRec();
    bt.preOrderPrint();
    // bt.postOrderPrintRec();
    bt.postOrderPrint();

    START_LOOP;
    return 0;
}