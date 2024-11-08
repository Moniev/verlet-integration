#include "box.hpp"

const float Box::getRight()
{
    return left + width;
}   

const float Box::getTop()
{
    return bottom + height;
}

const sf::Vector2f Box::getCenter()
{
    return sf::Vector2f{left + width / 2, bottom + height/2};
}


const sf::Vector2f Box::getSize()
{
    return sf::Vector2f{width, height};
}

const bool Box::contains(Box &box)
{
    return left <= box.left 
    && box.getRight() <= getRight() 
    && getTop() <= box.getTop()
    && bottom <= box.bottom;
}

const bool Box::intersects(Box &box)
{
    return !(left >= box.getRight() 
    || getRight() <= box.left 
    || bottom >= box.getTop()
    || getTop() <= box.bottom);
}