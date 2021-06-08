#include "FieldWidget.hpp"

FieldWidget::FieldWidget(Field f) {
    field = f;
    setAlignment(Qt::AlignCenter);
}

void FieldWidget::draw() {
    unsigned long value = field.getValue();
    if (value == 0) {
        setText("");
        setStyleSheet(  "border: 2px solid black;"
                        "background-color: rgb(255, 229, 204);");
    } else {
        setText(QString::number(value));
        if (value == 2) {
            setStyleSheet(  "border: 2px solid black;"
                            "background-color: rgb(255, 204, 153);"
                            "font-size: 18px;");
        } else if (value == 4) {
            setStyleSheet(  "border: 2px solid black;"
                            "background-color: rgb(255, 153, 51);"
                            "font-size: 18px;");
        } else if (value == 8) {
            setStyleSheet(  "border: 2px solid black;"
                            "background-color: rgb(255, 128, 0);"
                            "font-size: 18px;");
        } else if (value == 16) {
            setStyleSheet(  "border: 2px solid black;"
                            "background-color: rgb(204, 102, 0);"
                            "color: white;"
                            "font-size: 18px;");
        } else if (value == 32) {
            setStyleSheet(  "border: 2px solid black;"
                            "background-color: rgb(255, 153, 153);"
                            "color: white;"
                            "font-size: 18px;");
        } else if (value == 64) {
            setStyleSheet(  "border: 2px solid black;"
                            "background-color: rgb(255, 102, 102);"
                            "color: white;"
                            "font-size: 18px;");
        } else if (value == 128) {
            setStyleSheet(  "border: 2px solid black;"
                            "background-color: rgb(255, 0, 0);"
                            "color: white;"
                            "font-size: 18px;");
        } else if (value == 256) {
            setStyleSheet(  "border: 2px solid black;"
                            "background-color: rgb(255, 102, 255);"
                            "color: white;"
                            "font-size: 18px;");
        } else if (value == 512) {
            setStyleSheet(  "border: 2px solid black;"
                            "background-color: rgb(204, 0, 204);"
                            "color: white;"
                            "font-size: 18px;");
        } else if (value == 1024) {
            setStyleSheet(  "border: 2px solid black;"
                            "background-color: rgb(51, 51, 255);"
                            "color: white;"
                            "font-size: 18px;");
        } else if (value == 2048) {
            setStyleSheet(  "border: 2px solid black;"
                            "background-color: rgb(0, 102, 204);"
                            "color: white;"
                            "font-size: 12px;");
        } else {
            setStyleSheet(  "border: 2px solid black;"
                            "background-color: rgb(0, 51, 0);"
                            "color: white;"
                            "font-size: 18px;");
        }
    }
}
