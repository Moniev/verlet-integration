#ifndef NODE_HPP
#define NODE_HPP

#include "box.hpp"


class Node{
    public:
        int current_depth;
        int max_depth;
        Box *box;
        Node *root;
        std::vector<Node*> children;

        Node() = default;
        Node(Box *__box) {
            this->box = __box;
        }

        void addNode(Node *node);
        const std::vector<Node*> getChildren();
        bool isLeaf();
        void removeNode(Node *node);
};

#endif 