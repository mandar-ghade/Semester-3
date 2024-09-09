$$
\newcommand{\xor}{\oplus}
\newcommand{\paren}[1]{\left(#1\right)}
\newcommand{\abs}[1]{\left|#1|\right|}
$$
# Predicate Logic
- *Extension* of propositional logic that permits concisely reasoning about whole *classes* of entities.
- E.g. $x\gt1$
- Neither true or false unless the value is specified.
- Can include *any* number of arguments.

## Application of Predicate Logic
- Formal notation of writing clear, concise and unambiguous mathematical definitions, axions, and theorems.
- Supported by *database query engines* (SQL)

- Proposition has 2 parts: the subject & the predicate
    - i.e. "The dog is sleeping"
        - Subject: "the dog"
        - Predicate: "is sleeping"
            - Takes an object and produces a proposition.
- Applying a predicate to an object produces a proposition.
- Predicate is modeled by $P(x)$ ($x$ is any object)
    - Becomes a proposition when an object is applied to the predicate.

### Universe of Discourse 
- The collection of values that a variable $x$ can take is called $x$'s *universe of discourse*.

### Quantifier Expression
- Allows us to quantify how many objects in the universe of discourse satisfy a given predicate.
- $\forall$ is the forall or universal quantifier:
    - $\forall x P(x)$ means *for all x in the u.d.*, P holds (p is a proposition given these arguments).
    - e.g. "All parking spaces at UF are full"
    - $\neg \forall \iff \exists$
- $\exists$ Is the exists or existential quantifer.
    - $\exists x P(x)$ means there exists an x in the u.d.
    - e.g. "At least one parking space at UF is full"
    - $\neg \exists \iff \forall$
- You can switch between quantifiers using equivalence laws. (AS LONG AS THEY'RE THE SAME)
    - Associative Property
- Commutative and distributive properties can be used for the same quantifiers.

#### Universal Quantifier $\forall$ 
- To prove that a proposition of the form:
    - $\forall x P(x)$ is false, it suffices to find a **counterexample** (one value in the universe of discourse in which P(x) is false)
$$\forall x P(x) \iff P(a) \land P(b) \land P(c) \land ...$$

#### Existential Quantifier $\exists$
$$\exists x P(x) \iff P(a) \lor P(b) \lor P(c) \lor ...$$

#### Scope of Quantifiers
- The part of a logical expression to which a quantifier is applifed.
- Scope exists inside each parenthesis.
- Each variable $x, y$ exist independently in their own scopes. (self-note)

##### Free and Bound Variables
- An expr $P(x)$ has a free variable $x$ (meaning $x$ undefined)
- Predicate does not make sense without quantiifer.
- An expression with *zero* free variables is an actual proposition.
- E.g. $P(x), \text{where x = 3}$ is another way to bind $x$

#### Notational Conventions
$$
\forall x \forall y \forall z \text{P(x,y,z)} \iff 
\forall \text{x,y,z} \text{P(x,y,z)} \iff
\forall \text{xyz} \text{P(x,y,z)}
$$
- Since they use the same quantifier their orders can change.
- Sometimes, the universe of discourse is restrited within the quantification.
    - e.g. : $\forall x \gt 0 \text{P(x)}$: "For all $x$ that are greater than zero, P($x$)."
    - e.g. : $\exists x \gt 0 \text{P(x)}$: "There is an $x$ greater than zero such that P($x$)"


#### Defining New Quantifiers
Ex: $\exists ! x \text{P(x)}$
    - "P($x$) is true of *exactly one $x$* in the universe of discourse."

#### Calculus Example
$$\lim_{x \to a} f(x) = L \iff \paren{\forall \epsilon \gt 0 : \exists \delta \gt 0 : \paren{
        \abs{x-a} \lt \delta
    } \implies \paren{
        \abs{f(x) - L} \lt \epsilon
    }
}$$


# Rules of Inference
- Pattern establishing that if we know that a set of hypotheses is true, then a certain related conclusion is true.
- Each rule corresponds to an implication that is a tautology.

## Theorems 
- Statement that has been proven based on previously established statements.

## Nature of Proofs
- In mathematics, a proof is:
    - Sequence of statements that form an *argument*.
    - Argument: Series of propositions. Last one called conclusion, rest are called premises.
    - Must be correct (well-reasoned, logically valid) and complete (clear, detailed).

## Modus Ponens & Tollens:
### Rule of **modus ponens**  (law of detachment)
- the mode of affirming
- $p$, $p \implies q$,
- $\therefore q$ 
### Rule of **modus tollens** (the mode of denying):
  $\neg q , p \implies q$ 
 $\therefore \neg p$  

##  Syllogism Inference Rules
#### Rule of hypothetical syllogism:
$p \implies q$ 
$q \implies r$ 
$\therefore p \implies r$ 

## Common Fallacies:
### Fallacy of affirming the conclusion
- "$p \implies q$ is true, and $q$ is true, so $p$ must be true" (No because $F \implies T$ is true)
* Ex: If you do every problem in the book, you will learn discrete mathematics. You learned discrete mathematics
### Fallacy of denying the hypothesis
* $p \implies q$ and $\neg p$ does not imply $\neg q$  

## Interference Rules for Quantifiers
### Universal Instantiation
### Universal generalization
### Existential instantiation
### Existential generalization


