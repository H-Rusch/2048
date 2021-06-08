#ifndef FIELD_H_
#define FIELD_H_

class Field {

    private:
        unsigned long value;
        // information wether the field's value has been modified in the last turn by merging with another field
        bool changed = false;

    public:
        Field();

        // return the value of the Field
        unsigned long getValue();

        // set the value of the Field
        void setValue(unsigned long input);

        // set the value of changed to true, to indicate this field's valuse has been modified in a merge
        // reset this flag by setting the value to false
        void setChanged(bool change);

        // get information wether this field has been merged with another field this turn
        bool getChanged();

        // double the value of a Field when it is merged with another one
        unsigned long doubleValue();

        // reset the value of a Field to an uninitialized state
        void resetValue();

        // initialize an empty Field with a basic value of 2
        void initialize();

        // return the information wether a Field is empty or not
        bool isEmpty();
};

#endif // FIELD_H_
