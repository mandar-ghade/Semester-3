#mac2313 
#lecture9

$$
\newcommand{\pos}{r(t)}
\newcommand{\posvec}{\vec r(t)}
\newcommand{\that}{\hat T}
\newcommand{\tvec}{\vec T}
\newcommand{\nhat}{\hat N}
\newcommand{\bwrap}[1]{\left[#1\right]}
\newcommand{\magnitude}[3]{\sqrt{\bwrap{#1}^2+\bwrap{#2}^2+\bwrap{#3}^2}}
$$
Let $C$ be a smooth curve represented by $\posvec = \vcoords{f(t), g(t), h(t)}$

The velocity vector, speed, and acceleration vectors are defined:
# Velocity
$$\vec v = \vec r \ '(t)$$
# Speed
$$\mag{\hat v(t)}=\mag{\vec r \ ' (t)}=\magnitude{f'(t)}{g'(t)}{h'(t)}$$
# Acceleration

$$\vec a(t)=\hat r \ ''(t)= \hat v '(t)$$

## Components of Acceleration

We use $\that$ and $\nhat$ to gain insight on how moving object accelerate.

The two ways to change the velocity of an object:

1. Change its speed (after... $a \parallel \that$) 
	- Produces acceleration in the direction of $\that$
		- "tangential" - $a_t$ 
			- Slide-y (Slides and translates)

2. Change its [[U.T. Vector of Smooth Curve |direction of motion]] (after... $a \parallel \nhat$)
	- Produces acceleration in the direction of $\nhat$ 
		- "normal" - $a_n$ 
			- Spins
		- "centripetal"

Because $\vec a$  is written as a linear combination of $\that$ and $\nhat$, 
acceleration vector $\vec a$  lies in the plane determined by $\that$ and $\nhat$ .

### Formula
$$
\wrap{
	a & = \pwrap{\mag{\vec v}'}\pwrap{\that}
	    + \pwrap{\mag{\vec v}}\pwrap{\that\ '} \\
	  & = \pwrap{\mag{\vec v}'}\pwrap{\that}
	    + \pwrap{\mag{\vec v}}\pwrap{\that '}\pwrap{\nhat} \\
	  & = a_t+\pwrap{\nhat}a_n 
	
}
$$
Notice simplification to $a_t$ and $a_n$.

Justification for simplification:
(**Curvature Theorem**)

#### Tangential Component of Acceleration
$$a_t = \mag{\vec v}'\pwrap{\that} = \dot{\vec a}{\that} = \frac{\dot{\vec v}{\vec a}}{\mag{\vec v}}$$
#### Normal Component of Acceleration
$$a_n = \mag{\vec v}\pwrap{\that '} = \dot{\vec a}{\nhat}=\frac{\mag{\cross{\vec v}{\vec a}}}{\mag{\vec v}}$$
