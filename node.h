#ifndef NODE_H
#define NODE_H

#include "nodetype.h"
#include <QString>
#include <vector>

namespace AST{

class Node{
public:
    const NodeType type;

protected:
    enum Precedence{
        PREC_NONE,
        PREC_DISJUNCTION, //DO THIS: logic nodes don't actually need precedence if
        PREC_CONJUNCTION, //         they are restricted to disjunctive normal form
        PREC_EQUALITY,
        PREC_LESS,
        PREC_NEGATION,
        PREC_ADDITION,
        PREC_MULTIPLICATION,
        PREC_POWER,
    };

public:
    Node(const NodeType& type);
    virtual ~Node();
    virtual Node* clone() const = 0;
    virtual void deleteChildren(){}
    virtual Node* evaluate() = 0;
    static Node* evaluateAndFree(Node* n);
    static void deleteRecursive(Node* n);
    static Node* remove(std::vector<Node*>& search, const Node* pattern, Precedence prec = PREC_NONE);
    static Node* remove(std::vector<Node*>& search, const Node* pattern, const std::vector<Node*>::iterator& end, Precedence prec = PREC_NONE);
    virtual QString toString(Precedence prec = PREC_NONE) const = 0;
    virtual QString getKey(Precedence = PREC_NONE) const;

protected:
    static Node* searchForUndefined(const std::vector<Node*>& args);
    template <Precedence prec = PREC_NONE> static bool compare(const Node* a, const Node* b){
        return a->getKey(prec) < b->getKey(prec);
    }
    static std::vector<Node*> cloneArgs(const std::vector<Node*> args);
    static bool isFalse(Node* n);
    static bool isTrue(Node* n);
};

}

#endif // NODE_H
