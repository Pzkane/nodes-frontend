#ifndef SRC_MAIN_HPP
#define SRC_MAIN_HPP

// For Tests and Demo

#include "nf.hpp"

extern nf::NodeFrontEndWrapper NFWrap;

struct TestAddr {
    int addr;
    short number;
};

struct TestS
{
    std::string name;
    short age;
};

struct MyNodeTyped : public nf::LinkedListNode<MyNodeTyped, TestS>
{
    MyNodeTyped() : LinkedListNode<MyNodeTyped, TestS>(NFWrap.api()) {}
    std::string representation() override {
        return std::string("['" + getData().name + "', " + std::to_string(getData().age) + "]");
    }
};

struct MyNodeTyped1 : public nf::LinkedListNode<MyNodeTyped1, TestAddr>
{
    MyNodeTyped1() : LinkedListNode<MyNodeTyped1, TestAddr>(NFWrap.api()) {}
    std::string representation() override {
        return std::string("{" + std::to_string(getData().addr) + " and " + std::to_string(getData().number) + "}");
    }
};

struct MyNodeTypedDelayed : public nf::LinkedListNode<MyNodeTypedDelayed, std::string>
{
    explicit MyNodeTypedDelayed(bool visible = true) : LinkedListNode<MyNodeTypedDelayed, std::string>(NFWrap.api(), visible) {}
};

struct LoopTypeNode : public nf::LinkedListNode<LoopTypeNode, std::string> {
    LoopTypeNode() : LinkedListNode<LoopTypeNode, std::string>(NFWrap.api()) {}
};

struct DblLLNode : public nf::DoublyLinkedListNode<DblLLNode, std::string> {
    DblLLNode() : DoublyLinkedListNode<DblLLNode, std::string>(NFWrap.api()) {}
};

struct StringBTNode : public nf::BinaryTreeNode<StringBTNode, std::string> {
    StringBTNode() : BinaryTreeNode<StringBTNode, std::string>(NFWrap.api()) {}
};

struct StringGraphNode : public nf::GraphNode<StringGraphNode, std::string> {
    StringGraphNode() : GraphNode<StringGraphNode, std::string>(NFWrap.api()) {}
};

/**
 * @brief Due to WeightedGraphNode's virtual base it is also required to explicitly provide used GraphNode base class
*/
struct StringWeightGraphNode : public nf::WeightedGraphNode<StringWeightGraphNode, std::string> {
    StringWeightGraphNode()
        : GraphNode<StringWeightGraphNode, std::string>(NFWrap.api())
        , WeightedGraphNode<StringWeightGraphNode, std::string>(NFWrap.api()) {}
};

/**
 * @brief Due to OrientedGraphNode's virtual base it is also required to explicitly provide used GraphNode base class
*/
struct StringOrientedGraphNode : public nf::OrientedGraphNode<StringOrientedGraphNode, std::string> {
    StringOrientedGraphNode()
        : GraphNode<StringOrientedGraphNode, std::string>(NFWrap.api())
        , OrientedGraphNode<StringOrientedGraphNode, std::string>(NFWrap.api()) {}
};

/**
 * @brief Due to WeightedOrientedGraphNode's virtual base it is also required to explicitly provide used GraphNode base class
*/
struct StringWeightOrientedGraphNode : public nf::WeightedOrientedGraphNode<StringWeightOrientedGraphNode, std::string> {
    StringWeightOrientedGraphNode()
        : GraphNode<StringWeightOrientedGraphNode, std::string>(NFWrap.api())
        , WeightedOrientedGraphNode<StringWeightOrientedGraphNode, std::string>(NFWrap.api()) {}
};

#endif // SRC_MAIN_HPP