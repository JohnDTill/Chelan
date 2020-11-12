#ifndef CHELAN_H
#define CHELAN_H

#include <QDebug>

#include "expr/absolutevalue.h"
#include "expr/boolean.h"
#include "expr/call.h"
#include "expr/conditionalvalue.h"
#include "expr/conjunction.h"
#include "expr/disjunction.h"
#include "expr/equality.h"
#include "expr/function.h"
#include "expr/less.h"
#include "expr/matrixaddition.h"
#include "expr/matrixenumeration.h"
#include "expr/matrixmultiplication.h"
#include "expr/matrixnumeric.h"
#include "expr/negation.h"
#include "expr/pi.h"
#include "expr/rational.h"
#include "expr/readglobal.h"
#include "expr/readlocal.h"
#include "expr/realvariable.h"
#include "expr/scalaraddition.h"
#include "expr/scalarmultiplication.h"
#include "expr/scalarpower.h"
#include "expr/undefined.h"
#include "stmt/assign.h"
#include "stmt/block.h"
#include "stmt/declareassign.h"
#include "stmt/if.h"
#include "stmt/print.h"
#include "stmt/return.h"
#include "stmt/while.h"

#endif // CHELAN_H
