#ifndef NODETYPE_H
#define NODETYPE_H

#include <stdint.h>

namespace AST{

enum NodeType{
    ADDITION,
    BOOLEAN,
    CONDITIONALVALUE,
    CONJUNCTION,
    DISJUNCTION,
    EQUALITY,
    LESS,
    MATRIX,
    MULTIPLICATION,
    NEGATION,
    PI,
    POWER,
    RATIONAL,
    REALVARIABLE,
    UNDEFINED,
};

constexpr uint8_t num_types = UNDEFINED + 1;

}

#endif // NODETYPE_H
