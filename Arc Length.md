#mac2313
#lecture9
#arclength

$$
\newcommand{\mag}[1]{\left\|#1\right\|}
\newcommand{\vcoords}[1]{\langle#1\rangle}
\newcommand{\wrap}[1]{\begin{equation}\begin{split}#1\end{split}\end{equation}}
\newcommand{\abs}[1]{\vert #1 \vert}
\newcommand{\nullvec}{\vec 0}
\newcommand{\add}[2]{#1 + #2}
\newcommand{\pwrap}[1]{\left(#1\right)}
$$
# 2D
The length of a plane curve with parametric equations

$x=f(t)$ 
$y=g(t)$

$a\le t\le b$

$$\wrap{
	L & = \int_a^b{\sqrt{\left[f'(t)\right]^2+\left[g'(t)\right]^2}\ dt} \\
	  & = \int_a^b{\sqrt{\pwrap{\frac{dx}{dt}}^2+\pwrap{\frac{dy}{dt}}^2} dt}
}$$

Remember to take absolute value!
# 3D
Consider the curve $\vec r(t) = \vcoords{f(t), g(t), h(t)}$, $a\le t \le b$ 

Where $f', g', h'$ are continuous,

If curve is traversed exactly once as $t$ increases from $[a, b]$ , then its length is:

$$
\wrap {
	L &= \int_a^b{\sqrt{[f'(t)]^2+[g'(t)^2]+[h'(t)^2]} \ dt}
}
$$

## Arc Length Function

"How far we've gone after some time $t$"

Suppose that $C$ is a piecewise smooth curve given by a vector-valued function $\vec r (t) = \vcoords{f(t),g(t),h(t)}$, $a\le t\le b$ .

$$
s(t) = \int_a^t{
	\sqrt{
		[f'(u)]^2+
		[g'(u)]^2+
		[h'(u)]^2
	}
	du
}
$$

^8e3d2b

### The Fundamental Theorem of Calculus tells us:
- $s$ is a differentiable function of $t$ 
and:
$$ \frac{ds}{dt}= 
	\sqrt{
		[f'(u)]^2+
		[g'(u)]^2+
		[h'(u)]^2
	}
$$

## Re-parameterization of a Curve
tldr: Gives us a function that gets the position at a certain arc length.
- Needs position & start point. Plug position into $s(t)$. Then solve $t$. Use that $t$ (in terms of $s$) in the position vector to get $\vec r(s)$. 

Aka:
Puts $\vec r (t)$ in terms of $s$ = arc length.
Gets us $\vec r(s)$ 

If given:
- $\vec r(t)$ 
	- Curve (in terms of $t$).
- $s(t)$
	- Arc length function.

1. Solve for $t$ as a function of $s$ :
	- $t=t(s)$ 
2. Re-parametrize curve in terms of $s$ by substituting for $t$:
	- $\vec r = \vec r\pwrap{t\pwrap{s}}$