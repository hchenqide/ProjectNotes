## facts

### adding or removing clauses

- adding new clause to SAT? might be UNSAT.

- adding new clause to UNSAT? still UNSAT.

- removing a clause from SAT? still SAT.

- removing a clause from UNSAT? might be SAT.

> SAT < UNSAT core <= UNSAT

### relations between two clauses

- irrelevant

- implying (subsuming)

### relations between a set of clauses and another clause

- irrelevant

- tightly implying

- untightly implying

## solving methods

### preprocessing

### inprocessing


## SMT

SMT solvers encodes the logical parts to SAT solvers,

SAT solver gives an assignment,

SMT solver checks the assigment and maybe generates further constraints to SAT solver.


When SAT solver outputs SAT the whole problem can be SAT/undetermined/UNSAT by SMT solver.

if undetermined, SMT solver calls SAT solver incrementally.

When SAT solver outputs UNSAT the whole problem is UNSAT.

## IPASIR interface (Incremental PAssive SatisfIability Result)

## IPASIR-UP interface

user propagator

propagation (unit propagation) occurs when a literal is assigned or assumed true

typically, clauses will be shortened on false literal or removed on true literal

when SMT solver is notified of a literal assignment, it can do early checks based on its own external knowledge



## Todo

simplify minisat

- merge SimpSolver and Solver in one .h and one .cpp file

- use std::vector, etc

- remove parsing steps
