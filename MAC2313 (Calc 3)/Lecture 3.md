# Dot Product

Two non-zero vectors are orthogonal (perpendicular) if the angle between them $\theta = \frac{\pi}{2}$
- Also perpendicular IFF $\vec{u} \cdot \vec{v} = 0$

Zero vector $\vec{0}$ is orthogonal to all other vectors
- $\vec{0} \cdot \vec{v} = 0$

## Orthogonal Projections

### Vector Projection

![[Images/MAC2313 Lecture 3 Image.png]]

Length = $\mid\mid \vec{u} \mid\mid \cos{\theta}$
Unit vector: $$\hat{v}=\frac{\vec{v}}{\mid\mid \vec{v} \mid\mid}$$
$$\text{proj}_{\vec{v}}{\vec{u}} = \mid\mid \vec{u} \mid\mid \cos{\theta} \times \frac{\vec{v}}{\mid\mid \vec{v} \mid\mid}
= \left(\frac{\vec{u} \cdot \vec{v}}{{\mid\mid\vec{v}\mid\mid}^2}\right)\vec{v}$$

### Scalar Projection:
The **scalar** projection of $\vec{u}$ onto $\vec{v}$
$$\mid\mid \vec{u} \mid\mid \cos{\theta} = \left(\frac{\vec{u} \cdot \vec{v}}{{\mid\mid\vec{v}\mid\mid}}\right)$$
### Work
$$W=Fd$$W = Work
F = Force
d = distance

Only holds if the force is directed along the line of motion.
\
Suppose a constant force $\vec F$ applied to an object resulting in a displacement $\vec D$.
![[Images/MAC2313 Lecture 3 Image 2.png]]
If $\theta$ is the angle between $\vec F$ and $\vec D$, then:
$$W =\mid\mid\vec{F}\mid\mid\ \mid\mid \vec D \mid\mid cos{\theta}$$
$$W=\vec{F}\cdot\vec{D}$$
