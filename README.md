# RSMCP_insts
Instances for the Restricted Steiner Multi Cycle Problem used in SEA2018 (http://drops.dagstuhl.de/opus/volltexte/2018/8961)

## Folders
- `allInsts` are all instances available to use
- `testInsts` are the instances used to produce the results show in the work
- `generator` the method used to create the RSMCP instances

## From the section about instances

We used two types of instances to test our algorithms. Since, to the best of our knowledge, there is no previous empirical study on the \IRestrictedSteinerP, the type 1 instances were adapted from a set of instances for the multi-commodity one-to-one pickup-and-delivery traveling salesman problem (m-PDTSP)~\cite{HernandezPerez2009987}. Moreover, we proposed the type 2 instances which were randomly generated.

Hernández-Pérez and Salazar-González \cite{HernandezPerez2009987}
generated a set of instances to the m-PDTSP.
For each instance, they generated $2n-2$ uniformly random points with coordinates from  $-500$ to $500$,
a vertex in position 0 with coordinates $(0,0)$ and a vertex in position
$2n-1$ also with coordinates $(0,0)$.
%(corresponding to Class 3 of \cite{HernandezPerez2009987}).
We only take into account the vertex distribution of these instances.
For each $i in {0, ..., n-1}$, we consider vertex $i$ as a pickup point of an agent and $i+n$ as its corresponding delivery point.
There are 210 instances, each with 6, 11 or 16 pickup-and-delivery pairs.
This set of instances is the type 1.

We also generated a set of instances, which we call type 2, by varying 4 parameters. In each instance the vertices correspond to points distributed in a square of dimensions $100000 \times 100000$.
%
The number of pickup-and-delivery pairs is 16, 32, 64, 128 or 256.
The square is uniformly divided in $1\times 1$, $2\times 2$, $3\times 3$,
$4\times 4$ or $5\times 5$ frames, and each pair of pickup and delivery is in the same frame.
For the instances with more than one frame, we vary the space between these.
This space, which we call a gap, has 0\%, 10\%, 20\%, 30\% or 40\% of the frame's size. The gap can be seen as a rectangle separating the different frames (see Figure~\ref{fig:muro}).
The location of each vertex is chosen uniformly at random.
For each combination of number of agents, number of frames, and gap size, 3 instances were generated with different seeds. Notice that for the instances with division $1\times 1$ there is no gap.
Therefore, we generated a total of 315 instances.


 @article{HernandezPerez2009987,
title = "The multi-commodity one-to-one pickup-and-delivery traveling salesman problem ",
journal = "European Journal of Operational Research ",
volume = "196",
number = "3",
pages = "987 - 995",
year = "2009",
note = "",
author = "Hip\'olito Hern\'andez-P\'erez and Juan-Jos\'e Salazar-Gonz\'alez",
keywords = "Traveling salesman",
keywords = "Pickup-and-delivery",
keywords = "Branch-and-cut",
keywords = "Dial-a-Ride "
}
