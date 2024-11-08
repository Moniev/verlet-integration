#ifndef NODE_HPP
#define NODE_HPP

#include "box.hpp"


class Node{
    public:
        Box &box;
        std::unique_ptr<Node> root;
        std::vector<std::unique_ptr<Node>> children;

        /* TO BE COMPLETED */
        Node(Box &__box) 
            : box(__box)
        {}

};

#endif