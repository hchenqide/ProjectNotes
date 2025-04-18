### General

notes:
- a literal is assigned by:
  - interal propagation (original or learned clause)
  - decision (no reason)
  - external propagation (new clause for interal propagation or no reason)

- a clause can be:
  - the reason clause of a root-level assigned variable
  - satisfied by a root-level literal but not its reason (eliminated)
  - the reason of a propagated literal
  - satisfied by an assumed literal
  - unknown
  - unsatisfied as a conflict clause (transient)

- a newly added clause will be added directly to the watching list and used for the next propagation
  - during root-level propagation
    - removed due to true literals
    - pruned of false literals
    - provide a root-level
    - be a conflict and cause UNSAT
  - during assumptions
    - satisfied by root level true literals and will be removed
    - satisfied by assumed true literals and will not be referred to until backtrack
    - unassigned literals swapped as the watchers
    - immediately provide a new unit for later propagation (as the learned clause)
    - immediately provide a conflict ?

- After backtrack to a certain level, all variables assigned until this level are unassigned.
  The clause that is:
  - the reason clause for a propagated variable until this level: the last watching literals will still be its watching literals
    (suppose a literal is assumed on level k, during propagation, this clause became a unit and causing the assignment of its last watching literal)
    on level k-1, this clause has two  watches
  - the conflict clause: ?
  - satisfied by a literal before this level: untouched
  - unsatisfied: still watched by two literals

- Conflict analysis returns a list of literals that contributes to the conflict.
  A new clause of the negation of each of them is added.
  The negation of the one of them which is of highest level should now be propagated true.
  Can there be more than one literals that are of the highest level after analysis?

- states:
  - adding initial clauses before solving
    ... clauses simplified
    ... units assigned
    ... unsat early discovered
    -> keep adding more clauses
  [start solving]
  - first propagation

    ...
  - deciding on the next literal to assume

  All propagations finished, no more new units, the state is stable before the next decision.
  If new clauses are added, propagation will be triggered if a new unit occurs.
  After the 
  During propagation, new clauses can be added and immediately used for propagation, new assignments of variables can be appended to the trace.

  Whenever there's no more unpropagated variable on the trace or no more new clauses to be added, it is stable.


- a literal is:
  - permanently true/false (at level 0)
  - assumed true/false at level k > 0
  - propagated true/false at level k > 0
  - unassigned

- a clause
  - contains permanent true literal: removed
  - contains permanent false literal: shortened
  all clauses now don't contain any permanently assigned literals (or contain but not discovered)
  watched by two literals
  - two unassigned literals
  - 

(stop considering really removing clauses)



// 26.10

- initial condition
  - a variable is:
    - unassigned
    - assigned at level k unpropagated
    - assigned at level k propagated

  - a clause is watched by:
    - two unassigned literals
    - at least one true literal


- [at level k]
  at least one unpropagated level-k literal

  all clauses are connected with:
  - two unassigned literals
  - one or two unpropagated true literals
  - one unpropagated false literal, one unassigned literal
  - two unpropagated false literals

  [a literal is being propagated]

  the affected clauses that:
  - found another


# 10.24 msat.h
``` cpp
#include <vector>

using var = unsigned int;
using lit = int;
using clause = std::vector<lit>;

template <class T>
using ref_ptr = T*;

class Propagator {
protected:
    Solver& solver;

public:
    virtual int pick_literal() { return 0; }
    virtual void on_assignment(lit l) {}
};

class MSat {
public:
    MSat(ref_ptr<Propagator> propagator) {}
    void reserve_variable(var v);
    void add_clause(clause c);
    void solve();

protected:
    void assign_literal(lit l);
};

class Solver : private MSat {
public:
    MSat::reserve_variable;
    MSat::add_clause;
};
```
