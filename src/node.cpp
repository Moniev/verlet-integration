#include "node.hpp"

void Node::addNode(Node *node) {
    if(children.size() < 4) {
        node->root = this;
        children.push_back(node);
    }
}

void Node::deleteNode(int i) {
    children.erase(children.begin() + i);
}

const std::vector<Node*> Node::getChildren() {
    return children;
}

void Node::updateParticles() {
    
}

const Box Node::getBox() {
    return box;
}