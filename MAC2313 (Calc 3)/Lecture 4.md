$$
\newcommand{\ihat}{\hat{i}}
\newcommand{\jhat}{\hat{j}}
\newcommand{\khat}{\hat{k}}
\newcommand{\vmat}[1]{\begin{vmatrix}#1\end{vmatrix}}
\newcommand{\bmat}[1]{\begin{bmatrix}#1\end{bmatrix}}
\newcommand{\smallmag}[1]{\mid#1\mid}
\newcommand{\mag}[1]{\left\|#1\right\|}
\newcommand{\dot}[2]{#1 \cdot #2}
\newcommand{\cross}[2]{#1 \times #2}
\newcommand{\vcoords}[1]{\langle#1\rangle}
\newcommand{\wrap}[1]{\begin{equation}\begin{split}#1\end{split}\end{equation}}
\newcommand{\abs}[1]{\vert #1 \vert}
\newcommand{\nullvec}{\vec 0}
\newcommand{\add}[2]{#1 + #2}
\newcommand{\pwrap}[1]{\left(#1\right)}
$$
# The Cross Product

Given two vectors $\vec u = \vcoords{u_1, u_2, u_3}$ & $\vec{v} = \vcoords{v_1,v_2,v_3}$, 

The cross product $\cross{\vec u}{\vec v}$ is defined by:

$$\wrap{
	\cross{\vec u}{\vec v} & = \vmat{
		\ihat & \jhat & \khat \\
		 u_1 & u_2 & u_3 \\
		 v_1 & v_2 & v_3
	} \\ \\
	& = \vcoords{u_2v_3 - u_3v_2, u_3v_1-u_1v_3,u_1v_2-u_2v_1}
}
$$
The vector $\cross{\vec u}{\vec v}$ is orthogonal to both $\vec u$ and $\vec v$.

If $\theta$ is the angle between the nonzero vectors $\vec u$ and $\vec v$, then

$$\wrap{\mag{\cross{\vec u}{\vec v}}
& = \space\mag{\vec u}\space\mag{\vec v}\sin{\theta}}$$

Area of a parallelogram determined by the vectors $\vec u$ and $\vec v$ is 
$$\wrap{A & = \space\space\text{base} \times \text{height} \\
		  & = \space\mag{\vec u}\space\mag{\vec v}\sin{\theta} \\
		  & = \space\mag{\cross{\vec u}{\vec v}}
}$$

Colinear:
- Two nonzero vectors are colinear if they are parallel.

$\vec u$ and $\vec v$ are parallel if $\cross{\vec u}{\vec v}=\nullvec$.

## Algebraic properties
$$\cross{\vec u}{\vec v} = -\cross{\vec v}{\vec u}$$
(Remember you can factor out a -1 because it's just a scalar)
$$\cross{\vec u}{\vec u} = \nullvec$$ Distributive Property:
$$\cross{\left({c \vec u}\right)}{\vec v} = c \left(\cross{\vec u}{\vec v}\right) 
= \cross{\vec u}{\left(c \vec v\right)}$$
$$\cross{\vec u}{\left(\add{\vec v}{\vec w}\right) = 
\add{\cross{\vec u}{\vec v}}}{\cross{\vec u}{\vec w}}$$
Triple Product
$$\dot{\vec u}{\pwrap{\cross{\vec v}{\vec w}}} = \dot{\pwrap{\cross{\vec u}{\vec v}}}{\vec w}$$

Associative Property DOES NOT hold.

## Triple Product

![[MAC2313 Lecture 4 Image 1.png]]

$$\wrap{
\text{Volume of a parllelepiped}
& = \pwrap{\text{height}}\pwrap{\text{area of the base}} \\
& = \pwrap{
		\text{height}}
	\pwrap{
		\mag{\cross{\vec v}{\vec w}}
	} \\
& = \pwrap{
		\mag{\vec u} \cos{\theta}
	}
	\pwrap{
		\mag{\cross{\vec v}{\vec w}}
	} \\ \\
& = \space
    \mag{\vec u} 
    \space
    \mag{
	    \cross{\vec v}{\vec w}
	 }
    \cos{\theta} 
    \space\space\space
    \pwrap{\text{Rearranged}}
    \\
& = \space
	\dot{\vec u}{
	\pwrap{
		   \cross{\vec v}{\vec w}
		}
	} \\
& = \vmat{
		u_1 & u_2 & u_3 \\ 
		v_2 & v_2 & v_3 \\
		w_1 & w_2 & w_3
	}
\space\space\space\pwrap{\text{Determinant}}
} $$

## Application - Torque

$$\vec \tau = \vec r\times\vec F$$
$$\mag{\vec \tau}=\mag{\cross{\vec r}{\vec F}}$$
$$\mag{\vec {\tau}} = \mag{\vec r} \mag{\vec F} \sin{\theta}$$
Greatest at $\frac{\pi}{2}$ .
(torque = position vec * force vec)