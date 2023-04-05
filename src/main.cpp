// DEMO
#include <string>
#include <chrono>

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
int test_nf_driver()
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
        begin = std::chrono::system_clock::now();

        do {
            end = std::chrono::system_clock::now();
            /* do nothing during interval */
        } while (std::chrono::duration_cast<std::chrono::seconds>(end - begin).count() < 1);
        std::cout << std::chrono::duration_cast<std::chrono::seconds>(end - begin).count() << std::endl;

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
int test_mynode()
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
int test_typedmynode()
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

int test_typed_linked_list_autoshift() {
    MyNodeTyped n1;
    n1.setPosition(300, 450);
    n1.setData({"This", 88});

    MyNodeTyped n2;
    n2.setData({"That", 55});

    n1.setNext(n2);
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
    test_mynode();
    test_typedmynode();
    test_typed_linked_list_autoshift();
    test_nf_driver();
    ///
    /// 2. Launch loop and handle events
    ///
    LOOP;
    return 0;
}
