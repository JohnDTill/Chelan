#ifndef NODETYPE_H
#define NODETYPE_H

#include <stdint.h>

namespace Chelan{

enum NodeType{
    //Scalar types
    SCALAR_ADDITION,
    CONDITIONALVALUE,
    SCALAR_MULTIPLICATION,
    PI,
    SCALAR_POWER,
    RATIONAL,
    REALVARIABLE,
    UNDEFINED,

    //Boolean types
    BOOLEAN,
    CONJUNCTION,
    DISJUNCTION,
    EQUALITY,
    LESS,
    NEGATION,

    //Matrix types
    MATRIX_ENUMERATION,

    //Set types
    SET_ENUMERATION,

    //Untyped types
    UNTYPED_ADDITION,
};

constexpr uint8_t num_types = UNDEFINED + 1;

}

#endif // NODETYPE_H
