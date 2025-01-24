#ifndef ANYTYPE_CPP
#define ANYTYPE_CPP

#include "AnyType.h"

AnyType::AnyType(int i): type(INT), ivalue (i) {}
AnyType::AnyType(double d): type(DOUBLE), dvalue (d) {}
AnyType::AnyType(char c): type(CHAR), cvalue (c) {}
AnyType::AnyType(bool b): type(BOOL), bvalue (b) {}


AnyType::AnyType(AnyType& other): type(other.type) {
    switch(type) {
        case INT: ivalue = other.ivalue; break;
        case DOUBLE: dvalue = other.dvalue; break;
        case CHAR: cvalue = other.cvalue; break;
        case BOOL: bvalue = other.bvalue; break;
        default: throw InvalidType();
    }
}

AnyType::AnyType(AnyType&& other): type(other.type) {
    switch(type) {
        case INT: ivalue = other.ivalue; break;
        case DOUBLE: dvalue = other.dvalue; break;
        case CHAR: cvalue = other.cvalue; break;
        case BOOL: bvalue = other.bvalue; break;
        default: throw InvalidType();
    }
    other.destroy_value();
}

AnyType& AnyType::operator=(AnyType& other) {
    if (this==&other) return *this;
    this->type = other.type;
    switch(type) {
        case INT: ivalue = other.ivalue; break;
        case DOUBLE: dvalue = other.dvalue; break;
        case CHAR: cvalue = other.cvalue; break;
        case BOOL: bvalue = other.bvalue; break;
        default: throw InvalidType();
    }   
    return *this;
}

AnyType& AnyType::operator=(AnyType&& other) {
    if (this==&other) return *this;
    this->type = other.type;
    switch(type) {
        case INT: ivalue = other.ivalue; break;
        case DOUBLE: dvalue = other.dvalue; break;
        case CHAR: cvalue = other.cvalue; break;
        case BOOL: bvalue = other.bvalue; break;
        default: throw InvalidType();
    }   
    other.destroy_value();
    return *this;
}

AnyType::~AnyType() {this->destroy_value();}

void AnyType::destroy_value() {
    switch(type) {
        case INT: ivalue = 0; break;
        case DOUBLE: dvalue = 0; break;
        case CHAR: cvalue = 0; break;
        case BOOL: bvalue = 0; break;
        default: throw InvalidType();
    } 
}

void AnyType::swap(AnyType& other) {
    if (this==&other) return;
    AnyType temp = *this;
    *this = other;
    other = temp;
}

AnyType::Type AnyType::getType() const {return type;}

AnyType::operator int() {
    if (type!=INT) throw InvalidType();
    return ivalue;
}

AnyType::operator char() {
    if (type!=CHAR) throw InvalidType();
    return cvalue;
}

AnyType::operator double() {
    if (type!=DOUBLE) throw InvalidType();
    return dvalue;
}

AnyType::operator bool() {
    if (type!=BOOL) throw InvalidType();
    return bvalue;
}

std::ostream& operator<<(std::ostream& os, const AnyType& obj) {
    std::cout<<obj.type<<"\t";
    switch(obj.type) {
        case AnyType::INT: os<<obj.ivalue; break;
        case AnyType::DOUBLE: os<<obj.dvalue; break;
        case AnyType::CHAR: os<<obj.cvalue; break;
        case AnyType::BOOL: os<<obj.bvalue; break;
        default: throw AnyType::InvalidType();
    }
    return os;
}


#endif