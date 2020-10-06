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
    BOOLEAN_VALUE,
    CONJUNCTION,
    DISJUNCTION,
    EQUALITY,
    LESS,
    NEGATION,

    //Matrix types
    MATRIX_ADDITION,
    MATRIX_ENUMERATION,
    MATRIX_MULTIPLICATION,
    MATRIX_NUMERIC,

    //Set types
    SET_ENUMERATION,

    //Misc
    READ,
};

}

#endif // EXPRTYPE_H