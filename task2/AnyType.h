#ifndef ANYTYPE_H
#define ANYTYPE_H

#include <iostream>
#include <exception>

class AnyType {
    public:
        enum Type {INT, BOOL, CHAR, DOUBLE};
        struct InvalidType: public std::exception {};
    private:
        Type type;
        union {
            int ivalue;
            double dvalue;
            char cvalue;
            bool bvalue;
        };
        void destroy_value();
    public:
        AnyType(int i = 0);
        AnyType(double d);
        AnyType(char c);
        AnyType(bool b);
        AnyType(AnyType&);
        AnyType(AnyType&&);
        AnyType& operator=(AnyType&);
        AnyType& operator=(AnyType&&);
        ~AnyType();

        void swap(AnyType&);
        Type getType() const;
        operator int();
        operator char();
        operator double();
        operator bool();

        int getInt() ;
        double getDouble() ;
        char getChar() ;
        bool getBool() ;

        friend std::ostream& operator<<(std::ostream&, const AnyType&);
};


#endif