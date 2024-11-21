#ifndef NODE_HPP
#define NODE_HPP

#include "box.hpp"


class Node{
    static int i;

    public:
        int idx;
        Box box;
        Node *root;
        std::vector<Node*> children;

        Node() = default;
        Node(Box __box) 
            : box(__box) {
            i++;
            idx = i;
        }
        ~Node() {
            i--;
        }
        void addNode(Node *node) {
            if(children.size() < 4) {
                node->root = this;
                children.push_back(node);
            }
        };

        void deleteNode(int i) {
            children.erase(children.begin() + i);
        }

        const std::vector<Node*> getChildren() {
            return children;
        }
        bool isLeaf();

        void updateParticles();

        const Box getBox();
};

#endif 