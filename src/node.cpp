#include "node.hpp"

void Node::addNode(Node *node) {
    if(children.size() < 4) {
        node->root = this;
        children.push_back(node);
    }
}

void Node::removeNode(Node *node) {
    children.erase(find(children.begin(), children.end(), node));
} 

const std::vector<Node*> Node::getChildren() {
    return children;
}

bool Node::isLeaf() {
    return children.empty();
}

