// DEMO
#include <string>
#include <chrono>

#include "NodeFrontEndWrapper.hpp"

static nf::NodeFrontEndWrapper NFWrap;

int test_nf_driver()
{
    nf::NodeFrontEnd* api = NFWrap.api();

    api->setWindowColor(sf::Color(219, 189, 189));
    for (int i = 0; i < 1; ++i)
    {
        nf::_Node *node = api->addNode("w");
        node->setPosition(100, 100);
    }

    std::string txt;
    std::chrono::system_clock::time_point begin;
    std::chrono::system_clock::time_point end;
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

struct MyNode : public nf::LinkedListNode
{
    int data;

    // GENERATE WITH MACRO
    MyNode() : LinkedListNode(NFWrap.api()) {}
};

int test_mynode()
{
    MyNode *n1 = new MyNode();
    n1->setPosition(200, 200);
    n1->data = 4;

    MyNode *n2 = new MyNode();
    n2->setPosition(400, 400);
    n2->data = 8;

    n1->setNext(n2);

    // delete n1;
    // delete n2;

    return 0;
}

int main()
{
    test_mynode();
    test_nf_driver();
    say("DRIVER OUT");
    return 0;
}
