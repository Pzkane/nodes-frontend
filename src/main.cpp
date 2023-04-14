// DEMO
#include <string>
#include <chrono>
#include <vector>
#include <stdexcept>
#include <cassert>

// 1: Include wrapper header
#include "NodeFrontEndWrapper.hpp"

// 2: Define static wrapper instance ...
static nf::NodeFrontEndWrapper NFWrap;
// ... and macro
#define WRAPPER NFWrap
// 2.1: You can use custom settings
/*
static nf::NodeFrontEndWrapper NFWrap(nf::Context{
    sf::VideoMode{1920, 1080},
    sf::ContextSettings{24, 8, 8, 3, 0}
});
*/

///
/// Test and setup NF environment
///
int test04_nf_driver()
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
    nf::NodeImpl *node5 = api->addNode("W5", 450, 600);
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
struct MyNode : public nf::LinkedListNode<std::string>
{
    MyNode() : LinkedListNode<std::string>(NFWrap.api()) {}
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

    n1->setNext(*n2);

    return 0;
}

struct TestS
{
    std::string name;
    short age;
};

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
struct MyNodeTyped : public nf::LinkedListNode<TestS>
{
    MyNodeTyped() : LinkedListNode<TestS>(NFWrap.api()) {}
    std::string representation() override {
        return std::string("['" + getData().name + "', " + std::to_string(getData().age) + "]");
    }
};

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

struct MyNodeTypedDelayed : public nf::LinkedListNode<std::string>
{
    explicit MyNodeTypedDelayed(bool visible = true) : LinkedListNode<std::string>(NFWrap.api(), visible) {}
};

int test06_create_ll_with_delay() {
    /// 1. Setup with proper visiblities
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
    /// 1. Setup with proper visiblities
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

struct TestAddr {
    int addr;
    short number;
};

struct MyNodeTyped1 : public nf::LinkedListNode<TestAddr>
{
    MyNodeTyped1() : LinkedListNode<TestAddr>(NFWrap.api()) {}
    std::string representation() override {
        return std::string("{" + std::to_string(getData().addr) + " and " + std::to_string(getData().number) + "}");
    }
};

int test08_ll_with_transition() {
    // Reset padding
    NFWrap.api()->setLinkedListShiftPos({0, 700});
    // Dynamically create nodes
    std::vector<MyNodeTyped1> v;
    for(int i = 0; i < 5; ++i) {
        v.push_back(MyNodeTyped1{});
    }
    // Set next for each node
    MyNodeTyped1* n_preced = &v[0];
    short i = 0;
    for(auto& node : v) {
        n_preced->setData(TestAddr{i++, 42+i});
        if (!(&node == n_preced)) {
            n_preced->setNext(node);
            n_preced = &node;
        }
    }
    n_preced->setData(TestAddr{i++, 42+i});
    
    // TODO: Traverse with state changes
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
    test01_mynode();
    test02_typedmynode();
    test03_typed_linked_list_autoshift();
    test04_nf_driver();
    test06_create_ll_with_delay();
    test07_create_and_hide_ll_with_delay();
    test08_ll_with_transition();
    ///
    /// 2. Launch loop and handle events
    ///
    START_LOOP;
    return 0;
}
