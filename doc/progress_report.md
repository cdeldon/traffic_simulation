# Progress report
15/11/2015

## Design decisions

At a fairly early stage we decided on separating the **simulation engine** and the **data analysis tools**. The former shall be fed with simulation parameters, such as road length, number of cars, etc., run it, and store the data in a file for later use. The latter will be used to manipulate and study the data produced, possibly automatically running the simulation engine with new parameter sets. We decided not to code the simulation engine in MATLAB, but in C++ instead (contact us if you'd like to hear more details on this decision.). The second part will be done in MATLAB, leveraging its powerful high level functionality for data analysis.

## Current state

At this point, the first half i.e. the engine is largely implemented. It allows placement of arbitrary many static obstacles and traffic lights.

Some **basic** plotting routines are also in place. However, for the convenience of not having to load the MATLAB environment for a single plot, it is currently written in PYTHON.

## The Model

### Periodic boundaries
As outlined in our original [proposal](https://github.com/polwel/traffic_simulation/blob/master/README.md), we have implemented the *Intelligent Driver Model*, as described in [1]. We were originally intending to (qualitatively) reproduce the results presented in this paper. However it seems as if we **missed a crucial detail**.

In the original paper [1] by Treiber at al., the vehicles spawn at a given rate on a upstream 'ramp', travel down the road, and are removed as they reach its end. We estimated that it would be much more convenient to treat the road as periodic. The road is thus essentially a ring structure (think of a roundabout). This is an assumption also made in e.g. [2].

However, it turns out that the mere presence of a static obstacle does not produce an unstable traffic flow. Indeed, in order to trigger the instability, Treiber at al. increased the vehicle influx for a brief moment. This 'wave' would then scatter at the inhomogeneity and provoke the unstable flow. In our simulation traffic seems to remain perfectly smooth, vehicles just go slightly slower around the obstacle. I am confident that this is just a question of the initial parameters though, and that we will be able to make traffic collapse on an obstacle.

Reworking our simulation in order to account for arbitrary influx currently seems not to be easy. Since studying static obstacles was not our original plan, we will likely just continue with what we currently have.

### Stability of free road traffic
As mentioned, the few experiments that have been performed so far did not show a decrease in stability by an obstacle. However, we *are able* to produce unstable traffic on a **free** road.
Here is a plot of such an instability.

![Waves on free road](/doc/img/free_waves.png)

Note how the wavelength remains constant for the entire simulation run. Also note that the waves run in direction opposite to the traffic flow.

### Traffic light
As it was our original plan, we made some changes to the IDM equation to make it fit for traffic lights. Doing so was surprisingly complicated, as a light is modeled by a repulsive potential, yet we want the first car to stop exactly in front of it, and *stay there*. We also want  drivers to decide to keep going if a light suddenly goes *red* (read: *yellow)* just in front of them, or whether they can comfortably slow down. We had major troubles with numerical stability due to the point like nature of the traffic light: the cars would oscillate in front of the light, at some point pass the line ever so slightly, and then drive off. This has been solved by 'clamping' the car in front of the light.

## Research questions
As planned we will continue to study the effects of traffic lights on the flow. 

* Can we create similar density waves as above for vehicle densities that would normally be stable?
* Can the light also be stabilising?
* What parameters influence these waves?

If we fail to find any interesting effects related to the traffic light, we can still study the density waves that appear on the free road (see above), e.g. find how the wavelength depends on parameters such as the acceleration.


## References
 * [1] Treiber, Martin, and Dirk Helbing. "Explanation of observed features of self-organization in traffic flow." *arXiv preprint cond-mat/9901239* (1999)
 * [2] Buslaev, A. P., Tatashev, A. G., & Yashina, M. V. (2007). "Stability of Flows on Networks." In Traffic and Granular Flow’05 (pp. 427-435). Springer Berlin Heidelberg.
