# MATLAB Fall 2015 – Research Plan

> * Group Name: Road Blockers
> * Group participants names: Carlo Del Don, Pol Welter
> * Project Title: Traffic Flow Simulation: Red Lights

## General Introduction

automated vehicles, need to study dynamics of human driving behaviour.
Create models for trafic simulations. Notable example: Intelligent Driver Model (see next section).
Notable feature of ths model: phase transition: smooth flow vs. stop-and-go waves vs crash.
Want to reproduce this behaviour. Extract relevatnt parameters that are responsible for phase transition (possibly: phase diagram).
Next step: study effects of traffic light.
    - forces stop-and-go waves upon vehicles
    - vary period of light -> resonance?
    - some period should allow optimal throughput

## The Model

Intelligent Driver Model introduced by ????. (Cellular automata?) Each vehicle's acceleration is determined by target speed, and gap to the leading vehicle.
Integrate diff. eqn. with e.g. Euler's method. Write down the equation. Single lane road.

Add traffic light to model (i.e. expand the model to include time dependant bottlenecks). Drivers need to anticipate the light. Neglect reaction time.


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

(Add the bibliographic references you intend to use)
(Explain possible extension to the above models)
(Code / Projects Reports of the previous year)


## Research Methods

(Cellular Automata, Agent-Based Model, Continuous Modeling...) (If you are not sure here: 1. Consult your colleagues, 2. ask the teachers, 3. remember that you can change it afterwards)
