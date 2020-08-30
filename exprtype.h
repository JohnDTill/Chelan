#ifndef EXPRTYPE_H
#define EXPRTYPE_H

#include <stdint.h>

namespace Chelan{

enum ExprType{
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

    //Misc
    READ,
};

constexpr uint8_t num_types = UNDEFINED + 1;

}

#endif // EXPRTYPE_H
