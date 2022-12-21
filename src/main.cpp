// DEMO
#include <string>
#include <chrono>

// 1: Include wrapper header
#include "NodeFrontEndWrapper.hpp"

// 2: Define static wrapper instance
static nf::NodeFrontEndWrapper NFWrap;

int test_nf_driver()
{
    // 3: Get api from wrapper
    nf::NodeFrontEnd* api = NFWrap.api();

    // 4 - N: Use api

    api->setWindowColor(sf::Color(219, 189, 189));
    for (int i = 0; i < 1; ++i)
    {
        nf::_Node *node = api->addNode("w");
        node->setPosition(100, 100);
    }

    std::string txt;
    std::chrono::system_clock::time_point begin;
    std::chrono::system_clock::time_point end;

    nf::_Node *node1 = api->addNode("W1", 300, 300);
    nf::_Node *node2 = api->addNode("W2", 400, 300);
    nf::_Node *node3 = api->addNode("W2", 400, 300);
    
    api->connectNodes(node1, node2);
    api->connectWeightNodes(node1, node2, 40);

    nf::_Node *node = api->addNode("ss");
    node->setFillColor(sf::Color::Green); // overlap test
    for (int i = 0; i < 1; ++i)
    {
        begin = std::chrono::system_clock::now();

        do {
            end = std::chrono::system_clock::now();
            /* do nothing */
        } while (std::chrono::duration_cast<std::chrono::seconds>(end - begin).count() < 1);
        std::cout << std::chrono::duration_cast<std::chrono::seconds>(end - begin).count() << std::endl;

        txt += std::to_string(i);
        if (node)
            node->setText(txt);
    }
    return 0;
}

struct MyNode : public nf::LinkedListNode<std::string>
{
    // GENERATE WITH MACRO
    MyNode() : LinkedListNode<std::string>(NFWrap.api()) {}
};

int test_mynode()
{
    MyNode *n1 = new MyNode();
    n1->setPosition(200, 200);
    n1->setData(std::string("as"));
    n1->setData("as_c");

    MyNode *n2 = new MyNode();
    n2->setPosition(400, 400);
    n2->setData(8);

    n1->setNext(*n2);

    // delete n1;
    // delete n2;

    return 0;
}

struct TestS
{
    std::string name;
    short age;
};

struct MyNodeTyped : public nf::LinkedListNode<TestS>
{
    std::string representation() {
        return std::string("['" + getData().name + "', " + std::to_string(getData().age) + "]");
    }

    // GENERATE WITH MACRO
    MyNodeTyped() : LinkedListNode<TestS>(NFWrap.api()) {}
};

int test_typedmynode()
{
    MyNodeTyped n1;
    n1.setPosition(250, 250);
    n1.setData({"Joy", 55});

    MyNodeTyped n2;
    n2.setPosition(450, 450);
    n2.setData({});

    n1.setNext(n2);

    // delete n1;
    // delete n2;

    return 0;
}

int main()
{
    test_mynode();
    test_typedmynode();
    test_nf_driver();
    say("DRIVER OUT");
    return 0;
}
