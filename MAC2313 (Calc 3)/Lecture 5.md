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
# Equations of Line and Planes

![[MAC2313 Lecture 5 Image 1.png]]

![[MAC2313 Lecture 5 Image 2.png]]

Two planes that are not parallel intersect in a straight line, and the angle $\theta$ between the two planes is defined as the **acute angle** between their normal vectors.

### Line of Intersection:
Normal vectors are perpendicular to the direction vector.
$\vec n_1 \bot \vec v$
$\vec n_2 \bot \vec v$
$\therefore \cross{\vec n_1}{\vec n_2}=\vec v$ 


## Distance
The distance D from a point $P_1(x_1, y_1, z_2)$ to the plane $ax+by+cz+d=0$ is:
$$\wrap{
D & = \frac{|ax_1+by_1+cz_1+d|}{\sqrt{a_2+b_2+c_2}} \\
  & = \mag{\vec u}\mag{\cos \theta} \\
  & = \mag{\vec u}\pwrap{\frac{\mag{\dot{\vec u}{\vec n}}}{\mag{\vec u}\mag{\vec n}}} \\ 
  & = \mag{\vec u}\pwrap{\frac{\mag{\dot{\vec u}{\vec n}}}{\mag{\vec n}}}
}$$
### Distance between two planes

Pick a point that satisfies either plane equation given, then choose the other's normal vector components to plug in the formula to get the distance between the two planes.