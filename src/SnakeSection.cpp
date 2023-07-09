#include "SnakeSection.h"

SnakeSection::SnakeSection(sf::Vector2f startPosition) {
    section.setSize(Vector2f(20, 20));
    section.setFillColor(Color::Green);
    section.setPosition(startPosition);
    this->position = startPosition;
}

Vector2f SnakeSection::getPosition() {
    return position;
}

void SnakeSection::setPosition(sf::Vector2f newPosition) {
    this->position = newPosition;
}

RectangleShape SnakeSection::getShape() {
    return this->section;
}

void SnakeSection::update() {
    section.setPosition(position);  // Tells rectangle to move to actual position
}

