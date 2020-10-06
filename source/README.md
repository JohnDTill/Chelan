# Chelan

This is an experiment with CAS data structures to evaluate mathematical expressions using an AST.

*State:* The system collects terms and actually avoids division by zero to using Boolean logic, comparisons, conditional value, and an undefined value. I am not sure if transforming `x/x` to a conditional value `{1, x!=0; undef, else` should be a canonical transformation. Also, there is quite a bit of complicated logic in simplifying conditional values and comparisons. `{x^-1, x!=0; undef, else` could be simplified to `x^-1` since `x^-1` evaluated at `x=0` is undefined. Comparison, even with constant irrational expressions, is hard. Can a sufficiently accurate approximation give you the correct answer?
