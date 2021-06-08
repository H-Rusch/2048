#include "Field.hpp"

Field::Field() {
    value = 0;
}

unsigned long Field::getValue() {
    return value;
}

void Field::setValue(unsigned long input) {
    value = input;
}

void Field::setChanged(bool change) {
    changed = change;
}

bool Field::getChanged() {
    return changed;
}

unsigned long Field::doubleValue() {
    value *= 2;
    return value;
}

void Field::initialize() {
    value = 2;
}

bool Field::isEmpty() {
    if (value == 0) {
        return true;
    } else {
        return false;
    }
}

void Field::resetValue() {
    value = 0;
}
