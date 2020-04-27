# Boolean Canonical Form

There is quite a bit of historical study in Boolean canonical forms. The most popular normal form seems to be the "disjunctive normal form". To follow the form, you must honor the usual rules of precedence (NEGATION > CONJUNCTION > DISJUNCTION) and eliminate parenthesis from the expression. In other words, a Negation node cannot have a Conjunction or Disjunction node as its child, and a Conjunction node cannot have a child Disjunction.

De Morgan's laws hold for n-ary terms, so we use:

```
¬(A ∨ B ∨ C) ⇒ ¬A ∧ ¬B ∧ ¬C
¬(A ∧ B ∧ C) ⇒ ¬A ∨ ¬B ∨ ¬C
```

That covers negation, and isn't too bad. The case of disjunction as a child of conjunction is unfortunate. The distributive law applies so that:

```
A ∧ B ∧ (C ∨ D ∨ E)  ⇒  A ∧ B ∧ C  ∨
                        A ∧ B ∧ D  ∨
                        A ∧ B ∧ E
```

That is a far greater explosion of terms than we prefer, but we can live with it. If we apply De Morgan's laws when evaluating Negation nodes, and the distributive law when evaluating Conjunction nodes, then **the evaluated result will be in disjunctive normal form**.