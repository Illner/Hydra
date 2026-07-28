#ifndef Glucose_Clone_h
#define Glucose_Clone_h

namespace glucose {

    class Clone {
    public:
        virtual Clone* clone() const = 0;
    };
};   // namespace glucose

#endif
