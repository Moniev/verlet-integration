#include "node.hpp"

void Node::addNode(Node *node) {
    if(children.size() < 4) {
        node->root = this;
        children.push_back(node);
    }
}

void Node::addNeighbour(Node *node) {
    neighbour_nodes.emplace_back(node);
}

void Node::removeNode(Node *node) {
    children.erase(find(children.begin(), children.end(), node));
} 

const std::vector<Node*> Node::getChildren() {
    return children;
}

bool Node::isAlmostLeaf(){
    if(!children.empty()) {
        Node *__child = children.front();
        return __child->children.empty();
    }
    return false;
}

bool Node::isLeaf() {
    return children.empty();
}

void Node::findNeigbourNodes(Node *main, Node* node) {
    Box *main_box = main->box;
    Box *node_box = node->box;
    
    if(node->isLeaf() && main_box->isAdjacent(node_box)) {
        main->addNeighbour(node);
    }

    std::vector<Node*> children = node->children;
    for( auto &__children : children) {
        findNeigbourNodes(main, __children);
    }
}