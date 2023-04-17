// DEMO
#include <string>
#include <chrono>
#include <vector>
#include <stdexcept>
#include <cassert>
#include <thread>
#include "main.hpp"

// 1: Include wrapper header
#include "NodeFrontEndWrapper.hpp"

// 2: Define [static] wrapper instance ...
nf::NodeFrontEndWrapper NFWrap;
#define WRAPPER NFWrap
// 2.1: You can use custom settings
/*
static nf::NodeFrontEndWrapper NFWrap(nf::Context{
    sf::VideoMode{1920, 1080},
    sf::ContextSettings{24, 8, 8, 3, 0}
});
*/

/**
 * 
 * How to declare and use custom type:
 * 
 * Declaration:
 * 1. Inherit from necessary object 
 *  1.1 Specify your own template type
 * 2. Define ctor and pass API pointer to the parent type
 * 3. Override necessary methods
 * 
 * Usage:
 * 1. See methods in documentation
 * 2. Explore the results!
 * 
 **/
struct MyNode : public nf::LinkedListNode<MyNode, std::string>
{
    MyNode() : LinkedListNode<MyNode, std::string>(NFWrap.api()) {}
};

///
/// Test MyNodeTyped with default representations
///
int test01_mynode()
{
    MyNode *n1 = new MyNode();
    n1->setPosition(150, 150);
    n1->setData(std::string("as"));
    n1->setData("as_c");

    MyNode *n2 = new MyNode();
    n2->setPosition(450, 150);
    n2->setData(8);

    n1->setNext(n2);

    return 0;
}

///
/// Test MyNodeTyped with object representation
///
int test02_typedmynode()
{
    MyNodeTyped n1;
    n1.setPosition(150, 250);
    n1.setData({"Joy", 55});

    MyNodeTyped n2;
    n2.setPosition(450, 250);
    n2.setData({});

    n1.setNext(n2);

    return 0;
}

int test03_typed_linked_list_autoshift() {
    MyNodeTyped n1;
    n1.setPosition(300, 450);
    n1.setData({"This", 88});

    MyNodeTyped n2;
    n2.setData({"That", 55});

    n1.setNext(n2);
    return 0;
}

///
/// Test and setup NF environment
///
int test04_connect_generic_nodes()
{
    // 3: Get api from wrapper
    nf::NodeFrontEnd* api = NFWrap.api();

    // 4 to N: Use api
    api->setWindowColor(sf::Color(210, 210, 210));
    for (int i = 0; i < 1; ++i)
    {
        nf::NodeImpl *node = api->addNode("w");
        node->setPosition(150, 50);
    }

    std::string txt;
    std::chrono::system_clock::time_point begin;
    std::chrono::system_clock::time_point end;

    nf::NodeImpl *node1 = api->addNode("W1", 150, 350);
    nf::NodeImpl *node2 = api->addNode("W2", 450, 350);
    nf::NodeImpl *node3 = api->addNode("W3", 560, 350);
    
    api->connectNodes(node1, node2);
    api->connectWeightNodes(node1, node2, 40);

    nf::NodeImpl *node = api->addNode("ss");
    node->setPosition(50, 50);
    node->setFillColor(sf::Color::Green); // overlap test

    nf::NodeImpl *node4 = api->addNode("W4", 150, 450);
    nf::NodeImpl *node5 = api->addNode("W5", 450, 450);
    api->connectOrientedNodes(node4, node5);

    nf::NodeImpl *node6 = api->addNode("W6", 150, 350);
    nf::NodeImpl *node7 = api->addNode("W7", 450, 350);
    api->connectWeightNodes(node6, node7, 1500);

    for (int i = 0; i < 1; ++i)
    {
        nf::Utils::delay(500);

        txt += std::to_string(i);
        if (node)
            node->setText(txt);
    }

    return 0;
}

int test06_create_ll_with_delay() {
    /// 1. Setup with proper visibilities
    MyNodeTypedDelayed n1;
    MyNodeTypedDelayed n2(false);
    n1.setPosition(650, 500);
    n1.setData("Delayed1");
    n2.setData("Delayed2");
    n1.setNext(n2);

    /// 2. Perform 'animation'
    nf::Utils::delay(700);
    n2.setVisibility(true);
    return 0;
}

int test07_create_and_hide_ll_with_delay() {
    /// 1. Setup with proper visibilities
    MyNodeTypedDelayed n1;
    MyNodeTypedDelayed n2(false);
    n1.setPosition(650, 600);
    n2.setPosition(750, 600);
    n1.setData("Delayed\nAndHid3");
    n2.setData("Delayed\nAndHid4");
    n1.setNext(n2);

    /// 2. Perform 'animation'
    nf::Utils::delay(500);
    n2.setVisibility(true);
    // Hide first node
    nf::Utils::delay(250);
    n1.destroy();
    // Hide second node
    nf::Utils::delay(250);
    n2.destroy();
    
    // Following calls to these nodes must throw 
    // because internal nodes were destroyed
    
    try {
        n2.destroy();
        assert(("Access to deleted node", false));
    } catch (std::runtime_error &err) {
        std::cout << "Assert success: " << err.what() << std::endl;
    }

    return 0;
}

int test08_ll_with_transition() {
    // Reset padding
    NFWrap.api()->setLinkedListShiftPos({0, 550});
    // Dynamically create nodes
    MyNodeTyped1* head = new MyNodeTyped1();
    head->setData(TestAddr{0, 42});

    MyNodeTyped1* curr = head;
    for(size_t i = 1; i < 5; ++i) {
        nf::Utils::delay(500);
        MyNodeTyped1* node = new MyNodeTyped1();
        node->setData(TestAddr{i, 42+i});
        curr->setNext(*node);
        // curr->highlight();
        curr = node;
    }
    
    // Traverse with state changes and highlight
    curr = head;
    short i = 0;
    while(curr != nullptr) {
        ++i;
        nf::Utils::delay(500);
        curr->highlight();
        // Insert into middle
        if (i == 2) {
            nf::Utils::delay(500);
            MyNodeTyped1* middle = new MyNodeTyped1();
            middle->setPosition(375, 650);
            middle->setData(TestAddr{0,1});
            auto* tmp = curr->getNext();
            nf::Utils::delay(500);
            curr->setNext(middle);
            nf::Utils::delay(500);
            middle->setNext(tmp);
        }

        // Replace 4th original node
        if (i == 4) {
            nf::Utils::delay(500);
            MyNodeTyped1* new_4th = new MyNodeTyped1();
            new_4th->setData(TestAddr{1,2});
            new_4th->setPosition(600, 650);
            auto* tmp = curr->getNext();
            nf::Utils::delay(500);
            curr->setNext(new_4th);
            nf::Utils::delay(500);
            new_4th->setNext(tmp->getNext());
            nf::Utils::delay(500);
            delete tmp;
        }

        curr = curr->getNext();
    }

    return 0;
}

void cycle_nodes(LoopTypeNode* curr) {
    do {
        curr->highlight();
        nf::Utils::delay(750);
        curr = curr->getNext();
    } while(1);
}

static std::thread testloop;

int test09_ll_loop_on_thread() {
    NFWrap.api()->setLinkedListHighlightThickness(2);
    LoopTypeNode* lhead = new LoopTypeNode();
    lhead->setPosition(450, 750);
    lhead->setData("loop!");
    
    LoopTypeNode* curr = lhead;
    for(size_t i = 0; i < 5; ++i) {
        LoopTypeNode* node = new LoopTypeNode();
        node->setData("loop!");
        if (i == 0) node->setPosition(100, 900);
        curr->setNext(*node);
        curr = node;
    }
    curr->setNext(lhead); // enclose
    curr = lhead;
    testloop = std::thread(cycle_nodes, curr);

    return 0;
}

int test10_dbl_ll() {
    DblLLNode *left = new DblLLNode();
    left->setPosition(250, 50);
    DblLLNode *head = new DblLLNode(),
              *right = new DblLLNode(),
              *r_right = new DblLLNode();

    head->setData("HEAD");
    left->setData("Left");
    right->setData("Right");
    r_right->setData("R Right");

    head->setPrevious(left);
    head->setNext(right);
    right->setNext(r_right);
    r_right->setPrev(right);
    
    return 0;
}

int test11_bt_nodes() {
    StringBTNode *root = new StringBTNode(),
                 *left = new StringBTNode(),
                 *right = new StringBTNode(),
                 *l_right = new StringBTNode(),
                 *r_right = new StringBTNode(),
                 *r_left = new StringBTNode();
    root->setPosition(800, 100);
    root->setLeft(left);
    root->setRight(right);
    right->setLeft(l_right);
    right->setRight(r_right);
    left->setPosition(root->getPosition().x-200, right->getPosition().y);
    left->setRight(r_left);

    return 0;
}

///
/// Driver
///
int main(int argc, char** argv)
{
    ///
    /// 1. Setup environment
    ///
    unsigned test_suite = (
       test01_mynode() 
     + test02_typedmynode()
     + test03_typed_linked_list_autoshift()
     + test04_connect_generic_nodes()
     + test06_create_ll_with_delay()
     + test07_create_and_hide_ll_with_delay()
    //  + test08_ll_with_transition()
    //  + test09_ll_loop_on_thread()
    //  + test10_dbl_ll()
     + test11_bt_nodes()
    );
    if (test_suite != 0) return test_suite;
    say("Tests have passed!");
    ///
    /// 2. Launch loop and handle events
    ///
    START_LOOP;
    
    testloop.join();
    return 0;
}
