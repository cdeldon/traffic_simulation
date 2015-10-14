# MATLAB Fall 2015 – Research Plan

> * Group Name: **Road Blockers**
> * Group participants names: Carlo Del Don, Pol Welter
> * Project Title: **Traffic Flow Simulation: Red Light**

## General Introduction

Most of the major automotive manufacturers estimate that they will release an autonomous (self-driving) car within the next ten years. Indeed, autonomous vehicles promise to be capable of both safer and smoother traffic than human drivers can currently achieve. As self-driving cars will be introduced to our streets, we will inevitably have to deal with a situation where both human and robotic drivers *share* the road. For computers to be able to predict and evluate human driving, we require computer models that accurately reproduce human driving behaviour. In this sense, the understanding of traffic dynamics is as relevant as ever.

In this project we wil study the dynamics of traffic on a congested road. Available models (e.g. the *Intelligent Driver Model*, see next section) are able to predict the transition from smooth, homogenoeous traffic to stop-and-go waves, as the density of the vehicles exceeds a certain treshold. In a first step we want to reproduce the results that were previously obtained. In a second step, we aim to extend the model to accomodate time-dependent obstacles or bottlenecks, e.g. a traffic light, and investigate its effect on traffic flow. Possibly we might see that the stop-and-go waves forced by the traffic light might resonate with the natural stop-and-go waves that occur around static bottlenecks.


## The Model

We aim to implement the *Intelligent Driver Model* (IDM). The IDM, introduced by Treiber, Hennecke and Helbing [1] describes each vehicle's movement by an ordinary differential equation:

![equation](https://latex.codecogs.com/gif.latex?%5Cdot%20v_%5Calpha%20%3D%20a%5Cleft%281-%5Cleft%28%5Cfrac%7Bv_%5Calpha%7D%7Bv_0%7D%20%5Cright%20%29%5E%5Cdelta%20-%5Cleft%28%5Cfrac%7Bs%5E*%28v_%5Calpha%2C%20%5CDelta%20v_%5Calpha%29%7D%7Bs_%5Calpha%7D%20%5Cright%20%29%5E2%20%5Cright%20%29)

Each vehicle's acceleration is given as a function of its target speed, and the distance (gap) and the velocity difference to the leading vehicle.

This ODE will be integrated numerically. Previous research [1] suggests that a low order method such as Euler's Method will be suficiently accurate for this task. We may still try a higher order integrator, and see whether this does affect the results.

Note that the IDM does *not* model the finite reaction time of an actual human driver. Indeed, when this is taken into account, IDM simulations show very poor stability when compared to human driving [2]. This led to the conclusion that in reality drivers do look ahead further than only the nearest neighbour [2]. Note that at the present moment we do not plan to include reaction time in our project.

The road on which the vehicles travel is assumed to be single lane (no overtaking) and straight (constant speed limit, except for possible obstacles). All drivers and vehicles are assumed to be identical; with overtaking manouvers being impossible, there seems little opportunity in having drivers wanting to travel at different speeds.

We will expand the IDM to include time dependent obstacles, such as traffic lights. For this to work, drivers must pay attention to lights even if they are further away than the leading vehicle. We will introduce the dynamics required for making the decision whether a driver should brake at the sight of a yellow light or whether she should keep going.


## Fundamental Questions

 - can we reproduce the results from [x]?
 - Can traffic still be made unstable for low speeds (~50 km/h)?
    - phase diagram?
 - do maximum acceleration or breaking affect the traffic flow?
    - wavelength stop-and-go wave?
 - What are the effects of the traffic light at various frequencies?
    - which intervals allow good flow?
    - do we observe some kind of resonance?
    


## Expected Results

excpect to reproduce XXXXXXXXX
Instability at low speeds requires investigation. Will likely happen at some parameters, not sure whether those are realistic though.
Traffic light: High frequencies will drop troughput (lot of overhaed from acceleration). At this point we do not believe in resonance. Again, a phase transition might occur.


## References 
 * [1] Treiber, Martin, and Dirk Helbing. "Explanation of observed features of self-organization in traffic flow." *arXiv preprint cond-mat/9901239* (1999)
 * [2] Treiber, Martin, Arne Kesting, and Dirk Helbing. "Delays, inaccuracies and anticipation in microscopic traffic models." *Physica A: Statistical Mechanics and its Applications 360.1* (2006): 71-88.
 * [3] Gora, Paweł. "Traffic simulation framework." *Computer Modelling and Simulation (UKSim), 2012 UKSim 14th International Conference on*. IEEE, 2012.

## Research Methods

(Cellular Automata, Agent-Based Model, Continuous Modeling...) (If you are not sure here: 1. Consult your colleagues, 2. ask the teachers, 3. remember that you can change it afterwards)

