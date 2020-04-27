### Avoiding Division by 0 with a Symbolic Denominator
Chelan has a nifty design which makes it relatively straightforward to collect like-arguments with different constants. For example, given the addition `x + 2*x`, the two arguments will have a key collision indicating that the results should be collected, `3*x`. The same applies for multiplication `x*x^2` ⇒ `x^3`. However, a naive implementation ignores the crucial edge case of division by zero. `x^-1*x^2` ⇒ `x` is *not* correct, the actual simplification is

![⁜f⏴⁜^⏴ x⏵⏴2⏵⏵⏴x⏵ ⇒ ⁜c⏴x⏵⏴x≠0⏵⏴undefined⏵⏴x=0⏵](./Images/IntroEquation.svg)

#### Conditions

So what are the conditions we need to worry about? We are in the clear to collect terms iff:

1. The denominator is non-zero, e.g. `π/π` ⇒ `1`.
2. Both initial exponents are positive, e.g. `x*x^2` ⇒ `x^3`.
3. The final exponent is negative: `x*x^-2` ⇒ `x^-1`

Notes:

* (3) still has the potential for a singularity, but that information is kept in the final expression.
* There are pitfalls in the implementation of (3). `x*x^-1*x^-1` would meet the criteria, but you could easily evaluate `(x*x^-1)*x^-1` and miss it.
* There are some fine details to determine if (2) requires strictly-positive values and (3) requires strictly negative values. Zero to the zeroth power `0^0` may be regarded as either 1, 0, or undefined.

Given the above, we are free to make the simplification `x^a*x^b` ⇒ `x^(a+b)` if the following condition is met: `x ≠ 0 ∨ (a > 0 ∧ b > 0) ∨ a+b < 0`.

Technically, we should qualify this:

* `x ≠ 0 ∨ (a ≥ 0 ∧ b ≥ 0) ∨ a+b < 0` if 0^0 defined
* `x ≠ 0 ∨ (a > 0 ∧ b > 0) ∨ a+b ≤ 0` if 0^0 undefined

#### Handling Uncertainty

If the condition is True, we can collect exponents, and of course if the condition is False, we can indicate that the expression is undefined. However, it is likely we will not be able to determine either outcome, this is symbolic evaluation after all.

We need to consider what action to take when the result is indeterminable. For example, given `x^2*x^a`, we have:

![⁜^⏴x⏵⏴2⏵×⁜^⏴x⏵⏴a⏵ ⇒ ⁜c⏴⁜^⏴x⏵⏴2+a⏵⏵⏴x≠0 ∨ a > 0 ∨ a ≤ -2⏵⏴undefined⏵⏴x=0 ∧ -2 < a ≤ 0⏵](./Images/EvalToCase.svg)

Potential actions to take in the CAS are:

* Simplify to a case expression
* Bifurcate the solution process
* Collect terms and record some "assumption"
* Take no action with an indeterminable condition

I do not know the best answer.
