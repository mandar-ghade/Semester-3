# Foundations: Logic and Proofs

## Propositional Logic
* Study of the meanings of sentences. Using algebra.
	* Ex: Distributive Property in Algebra
- The logic of compound statements made from simpler statements using *Boolean connectives*.

### Proposition
* ($p$, $q$, $r$, $...$)
- A statement ($\text{i.e}$ declarative statement) with a definite meaning, having a truth value (either $\color{lightblue} \text{true}$ (T) or $\text{\color{red} false}$ (F)).
	- Ex: "It is raining."
	- Ex: "1 + 2 = 5" 
	- NOT: "Yeah, I sorta dunno, whatever..." (vague)
	- NOT: "1 + 2" (no truth value can be made)
### Operators / Connectives
- Combines one or more operand expression into larger expression
- Unary - Takes 1 operator
- Binary - Takes 2 operators
#### Boolean Operators
- Negation (NOT $\neg$) - transforms a prop. into logical negation.
	- Unary
	- $p$: "I have brown hair"
	- $\neg{p}$ : "I do not have brown hair"
- Conjunction (AND $\land$) - combines 2 propositions to form logical conjunction.
	- $p \land q$
	* A conjunction will have $2^n$ rows with $n$ variables.
	- $\neg$ and $\land$ operations together are universal (sufficient for any truth table).
- Disjunction (OR $\lor$) - combines 2 propositions by their logical *disjunction*
	- $p \lor q$
	- Ex: "Either that care has a bad engine, or that car has a bad carburetor".
	- Is also called *inclusive or*, includes the possibility they are both true.
- Exclusion-Or (XOR $\oplus$) - combines two propositions to form the logical "exclusive or": logical *inequality*.
	* $p$ = "I will earn a A in this course"
	* $q$ = "I will drop this course"
	- $p\oplus q$  =
		- "I will either earn an A for this course, or I will drop it (but not both)"!
	- Called *exclusive or*, because it excludes the possibility that both $p$ and $q$ are true.
	- Cannot build proposition with just "$\oplus$" and "$\neg$" because they are *not* universal.
- Implication (IF) (REMEMBER NOT CAUSAL)
	- The implication $p \implies q$ states that $p$ implies $q$. 
	- FALSE *only* in the case that $p$ is true but $q$ is false.
	- "If I'm elected, taxes will be lowered (can go either way)".
	- $p$: Hypothesis (antecedent or premise)
	- $q$: Conclusion (consequence)
	- $p \implies q$ 
		- does not imply that $p$ causes $q$.
		- does not imply that $p$ or $q$ are ever true.
	- ##### Inverse, Converse, Contrapositive
		- $p \implies q$ 
		- Inverse: $\neg p\implies\neg q$
		- Converse: $q \implies p$
		- Contrapositive: $\neg{q} \implies \neg{p}$
- Bi-conditional (IFF)
	- $p \leftrightarrow q$
	- States that $p$ is true *if and only if* (IFF) $q$ is true: Logical equality
	- TRUE only when both $p \implies q$ and $q \implies p$ are TRUE.
	- $p \leftrightarrow q$ : "If and only if it is raining, the home team wins."
	- Means that $p$ and $q$ have the same truth value.
	- $p \leftrightarrow q$  means $\neg(p \oplus q)$ 



##### Precedence of Logical Operators
1. $\neg$
2. $\land$
3. $\lor$
4. $\neg$ 
5. $\implies$
6. $\leftrightarrow$

###### Examples:
- $f \land (p \lor q)$: "I just saw my old friend, and either he's grown or I've shrunk"

#### Bits and Bit Operations
- Bit is a binary (base 2) digit: 0 or 1.
	- 1: true
	- 0: false
- Bit strings
	- Bit string of length $n$ is an ordered series or sequence of $n\geq0$  bits.
	- By convention, bit strings are written left to write: $e.g.$ the first bit of "1001101010" is 1.
	- By convention, the first bit is the most significant bit.
- Bitwise Operations
	- Boolean operators can be extended to operate on bit strings as well as bits.



## Equivalence rules & derivations
### Propositional Equivalence
- Two *syntactically* different compound propositions may be semantically identical (mean the same). We call them *equivalent*.
	- Learn how to *prove* equivalences using symbolic derivations.

### Tautologies and Contradictions
- *Tautology* is a compound proposition that is true *no matter what* the truth values of its ingredients (atomic propositions) are!
	- Ex: $p \lor \neg{p}$  (always true)
* Contradiction is a comp. prop. that is false no matter what
	* Ex: $p \land \neg{p}$ (always false)
* Other comp. props are *contingencies*.
### Proving Equivalences
- $P$ and $Q$ logically equivalent IFF $P$ and $Q$ contains same truth values as each other in *all* rows of their truth tables.
- Compound proposition $P$ is logically equivalent to $Q$,  IFF ($P \leftrightarrow Q$ ) the compound proposition $P\implies Q$ is a *tautology*.

### Equivalence Laws
- Identity: 
	- $p\land T \leftrightarrow p$
	- $p \lor F \leftrightarrow p$
- Domination:
	- $p\lor T \leftrightarrow T$
	- $p\land F \leftrightarrow F$
- Idempotent:
	- $p \lor p \leftrightarrow p$
	- $p \land p \leftrightarrow p$
- Double negation:
- Commutative:
- Associative
- Distributive:
- De Morgan's:
	- $\neg{p \land q} \leftrightarrow \neg{p} \lor \neg{q}$ 
- Implication:
	- 