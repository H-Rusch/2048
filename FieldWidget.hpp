#ifndef FIELDWIDGET_HPP
#define FIELDWIDGET_HPP

#include <QLabel>

#include "Field.hpp"

class FieldWidget : public QLabel {
private:
    Field field;

public:
    // contructer which set the internal Field which this Widget represents
    FieldWidget(Field f);

    // fill the fields in the UI with the value corresponding to their Field
    // also style them in a color for faster recognition
    void draw();
};

#endif // FIELDWIDGET_HPP
