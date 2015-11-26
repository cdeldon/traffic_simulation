# TODO LIST
- [ ] Implement flux sweep
- [ ] and run it
- [x] sweep density in plots of order parameter
- [ ] find nice settigs for traffic light and/or obstacles
- [ ] sweep traffic light swithcing frequency, plot throughput







# MATLAB Fall 2015 – Research Plan

> * Group Name: **Road Blockers**
> * Group participants names: Carlo Del Don, Pol Welter
> * Project Title: **Traffic Flow Simulation: Red Light**

## General Introduction

Most of the major automotive manufacturers estimate that they will release an autonomous (self-driving) car within the next ten years. Indeed, autonomous vehicles promise to be capable of both safer and smoother traffic than human drivers can currently achieve. As self-driving cars will be introduced to our streets, we will inevitably have to deal with a situation where both human and robotic drivers *share* the road. For computers to be able to predict and evaluate human driving, we require computer models that accurately reproduce human driving behaviour. In this sense, the understanding of traffic dynamics is as relevant as ever.

In this project we will study the dynamics of traffic on a congested road. Available models (e.g. the *Intelligent Driver Model* [1], see next section) are able to predict the transition from smooth, homogenoeous traffic to stop-and-go waves, as the density of the vehicles exceeds a certain treshold. In a first step we want to reproduce these results. In a second step, we aim to extend the model to accomodate time-dependent obstacles or bottlenecks, e.g. a traffic light, and investigate its effect on traffic flow. Possibly we might see that the stop-and-go waves forced by the traffic light might resonate with the natural stop-and-go waves that occur around static bottlenecks.


## The Model

We aim to implement the *Intelligent Driver Model* (IDM). The IDM, introduced by Treiber, Hennecke and Helbing [1] describes each vehicle's movement by an ordinary differential equation:

![equation](https://latex.codecogs.com/gif.latex?%5Cdot%20v_%5Calpha%20%3D%20a%5Cleft%281-%5Cleft%28%5Cfrac%7Bv_%5Calpha%7D%7Bv_0%7D%20%5Cright%20%29%5E%5Cdelta%20-%5Cleft%28%5Cfrac%7Bs%5E*%28v_%5Calpha%2C%20%5CDelta%20v_%5Calpha%29%7D%7Bs_%5Calpha%7D%20%5Cright%20%29%5E2%20%5Cright%20%29)

Each vehicle's acceleration is given as a function of its target speed, and the distance (gap) and the velocity difference to the leading vehicle.

This ODE will be integrated numerically. Previous research [1] suggests that a low order method such as Euler's Method will be sufficiently accurate for this task. We may still try a higher order integrator, and see whether this does affect the results.

Note that the IDM does *not* model the finite reaction time of an actual human driver. Indeed, when a realistic reaction time is included, IDM-like simulations show very poor stability when compared to empiric human driving [2]. This led to the conclusion that in reality drivers do look ahead further than only the nearest neighbour [2]. Note that at the present moment we do not plan to reaction time into account in our project.

The road on which the vehicles travel is assumed to be single lane (no overtaking) and straight (constant speed limit, except for possible obstacles). All drivers and vehicles are assumed to be identical; with overtaking manouvers being impossible, there seems little opportunity in having drivers wanting to travel at different speeds.

We will expand the IDM to include time dependent obstacles, such as traffic lights. For this to work, drivers must pay attention to lights even if they are further away than the leading vehicle. We will thus introduce the dynamics required for making the decision whether a driver should brake at the sight of a yellow light or whether she is close already and should keep going.


## Fundamental Questions
#### 1. Can we reproduce the transition to stop and go waves in congested traffic?
The first step of our project will consist in reproducing the results obtained in [1]. In particular, we will verify the existence of a phase transition from smooth, homogeneous flow at low vehicle densities to congested stop-and-go traffic at high densities. This implementation will yield us a foundation upon which we can build our extensions.

#### 2. Can this behaviour still be observed at low speeds/accelerations?
As we plan to study the effects of a traffic light, which is typically not found on highways, but on roads with lower speed limits, we will investigate the effects of desired target speed on the stability of the flow. We will possibly try to draw a phase diagram presenting desired speed vs density. Phases that are to be expected include

1. smooth flow, 
2. stop-and-go or jam,
3. crash.

Apart from speed limit, the accceleration/breaking behaviour is likely to influence the stability. We will also investigate these effects.

Particular attention will be paid to the evolution of the wavelength of occuring stop-and-go waves.

#### 3. How does a traffic light influence the flow? What is the importance of the duration of green light periods?
The traffic light will impose stop-and-go waves of a certain frequency on the vehicles. We will try to understand if and how these interact with the traffic's natural tendency to form waves of a certain wavelength.
Lastly we will study the effective throughput at various switching frequencies of the light (at e.g. fixed duty-cycle). Which switching interval yields best vehicle troughput?


## Expected Results
For the first part, we expect to reproduce the results from [1].

Wether the traffic can be rendered unstable over a wide range of velocities remains to be seen. We are confident that a corresponding change in maximum acceleration should yield this behaviour. We are not sure whether the resulting parameters required for instability at low speeds are realistic though.

Finally concerning the traffic light, we expect that high switching frequencies result in lower troughput, due to the overhead during acceleration and breaking. Possibly the optimal solution is trivial: have the period equal the simulation length, such that half of the vehicles can quickly pass, while the second half is just stuck until the simulation ends.

At this point in time we estimate that any resonance behaviour is unlikely. However, we might still see a phase transition in wavelength (from natural stop-and-go to traffic light dominated).


## References 
 * [1] Treiber, Martin, and Dirk Helbing. "Explanation of observed features of self-organization in traffic flow." *arXiv preprint cond-mat/9901239* (1999)
 * [2] Treiber, Martin, Arne Kesting, and Dirk Helbing. "Delays, inaccuracies and anticipation in microscopic traffic models." *Physica A: Statistical Mechanics and its Applications 360.1* (2006): 71-88.
 * [3] Gora, Paweł. "Traffic simulation framework." *Computer Modelling and Simulation (UKSim), 2012 UKSim 14th International Conference on*. IEEE, 2012.
