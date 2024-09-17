#mac2313
#lecture8
#calculus3
#curvature

$$
\newcommand{\ihat}{\hat{i}}
\newcommand{\jhat}{\hat{j}}
\newcommand{\khat}{\hat{k}}
\newcommand{\mag}[1]{\left\|#1\right\|}
\newcommand{\vcoords}[1]{\langle#1\rangle}
\newcommand{\wrap}[1]{\begin{equation}\begin{split}#1\end{split}\end{equation}}
\newcommand{\cross}[2]{#1 \times #2}
\newcommand{\abs}[1]{\vert #1 \vert}
\newcommand{\nullvec}{\vec 0}
\newcommand{\add}[2]{#1 + #2}
\newcommand{\pwrap}[1]{\left(#1\right)}
\newcommand{\that}{\hat{T}}
$$
Preface: [[U.T. Vector of Smooth Curve]]

Definition: ROC of the *direction* with respect to distance.

The curvature of a curve ($\kappa$) is

$$\wrap{
	\kappa &= \left|\frac{d\hat T}{dS}\right| \\
}$$ 

Key: 
- $\hat T$ = [[U.T. Vector of Smooth Curve#^0ad2cb |Unit Tangent Vector of a Smooth Curve]]
* S =  [[Arc Length#^8e3d2b |Arc Length or Distance]]


For any parametrized curve $\vec r(t)$ :
$$\wrap{
	\kappa(t) &= \frac{\mag{\that'(t)}}{\mag{\vec{r}\ '(t)}} \\
}$$
Alternatives:
$$
\wrap{
	\kappa(t) & = \frac{
	  \mag{
		  \cross{\vec{r}\ '(t)}{\vec{r}\ ''(t)}
		  }
	  }
	  {
		  \mag{
			  \vec{r}\ '(t)
		  }^3
	  } \space\space\space\space\space\text{(parametrized)}\\\\
			 & = \frac{\mag{f''(x)}}{
				 \pwrap{1+\left[f'(x)\right]^2}^{\pwrap{\frac{3}{2}}}
			 } \space\space\space\text{(non-parametrized)}
}
$$

Related: [[Motion Along A Curve]]