#ifndef NODE_HPP
#define NODE_HPP

#include "box.hpp"


class Node{
    public:
        Box box;
        Node *root;
        std::vector<Node*> children;

        Node(Box __box) 
            : box(__box)
            {}

        void addNode(Node *node) {
            if(children.size() < 4) {
                node->root = this;
                children.push_back(node);
            }
        };

        void deleteNode(int i) {
            children.erase(children.begin() + i);
        }

        const std::vector<Node*>& getChildren() {
            return children;
        }

        void updateParticles();
};

#endif