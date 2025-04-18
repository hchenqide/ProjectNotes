### cadical

issues:
- typo cadical.hpp:390 without

- use mobical as fuzzer?


notes:
- propagate.cpp: search_assign()
  Assign a literal with reason, when reason points to external_reason placeholder, the literal is lazy-explained.

- external_propagate.cpp: explain_external_propagations()
  Called by analyze().


### minisat

issues:
- frozen is in SimpSolver.h, the core Solver doesn't eliminate variables, or we should put add_observed_var and all interfaces in SimpSolver

- implies() is not used, deleted


notes:
- uncheckedEnqueue()
  Assigned a literal without or with reason.
  x [IPASIR-UP] notify_assignment

- search()
  Propagate, analyze conflict and backtrack or start a new decision level.

  - propagate()
    Apply new assignmnts on clauses, propagate on new variables or generate a conflict. Returns the conflict clause.
    Proprogated variable points to its reason clause, whose first literal is the true unit and all other literals are false.
    [IPASIR-UP] cb_propagate
    [IPASIR-UP] cb_has_external_clause, cb_add_external_clause_lit

  - analyze()
    Analyze conflict clause, trace back implication graph, produce a learned-clause.
    [IPASIR-UP] cb_add_reason_clause_lit

    - litRedundant()
      Check if a literal can be removed from the learned clause.

  - cancelUntil()
    Unassign the literals until the specified level and put them back to the decision queue.
    x [IPASIR-UP] notify_backtrack

  - simplify()
    Remove top-level satisfied clauses from both original and learnt clause lists.

  - pickBranchLit()
    Choose the next literal to assume.
    x [IPASIR-UP] cb_decide

  [IPASIR-UP] cb_check_found_model

  x [IPASIR-UP] notify_new_decision_level


### ipasir-up

issues:
- Will any interface function be changed again? (virtual void notify_assignment())

- What if cb_propagate found a conflict? When to notify the conflict?

- Combine notify_assignment and cb_propagate?

- At cb_check_found_model the user propagator checks the assignment given by notify_assignment at level 0?

notes:
- notify_assignment()
  Notify the user propagator the newly assigned literals in a list.

- notify_new_decision_level()

- notify_backtrack()
  Notify the user propagator of the current backtrack level.

- cb_check_found_model()
  Ask for a check of the 

- cb_decide()
  Ask for external decision of the next literal to assume.

- cb_propagate()
  Ask for externally assigned literals, called in a loop to get all.

- cb_add_reason_clause_lit()
  Ask for the reason clause for an externally assigned literal during lazy explaination.

- cb_has_external_clause()
- cb_add_external_clause_lit()
  Ask for some more external clauses that the user wants to add.


### General

- data structures:
  - clause list
  - literal list
    - assignment
    - reason clause
  - assignment stack

- clauses are watched by:
  - two unassigned literals
  - one true literal
  - 


- When to ask for external clauses?

propagate:
- conflict: backtrack
    > GOTO propagate
- no-conflict:
    - has-external-clause: add_clause
      - is-conflict:
        > GOTO conflict
      - is-unit:
        > GOTO propagate
      - niether:
        > GOTO no-conflict
    - no-external-clause:
      - new-decision:
        > GOTO propagate
      - model-found:
        > GOTO end
end:


Whenever there is an assignment of variables and new clauses are added, these clauses can generate:
- conflict
- unit
- neither

// this function can be called during or after propagation
// this function can not be called when a conflict is found and backtrack is not yet finished ?
add_clause_during_solving() -> clause*? conflict
// add and connect the clause
// if this clause generates a conflict, return this clause as conflict
// if this clause produces a unit, enqueue the unit
// otherwise nothing special would happen

The hard part is how to make sure these clauses will be correctly connected to watching literals.


Facts:
- If a unit clause is produced at level k, both of its watching literals are assigned in level k, one false, the other true. After backtrack to level < k, this clause is still watched by those two literals, which are now unassigned.
- If a conflict clause is found at level k, both of its watching literals are assigned false in level k.


- If the added clause is a unit, the level of the unit will be the highest level of its other literals, k. And It should be watched by the two literals of level k.
// a literal of a lower level can be still pushed to the assignment stack for propagation, at backtrack it will not be unassigned and will stay at the back.

- If the added clause is a conflict and it contains two literals of the highest level, k, should first backtrack to level k (unassign k+1 ~ current), then do conflict analysis. These two will be its watching literals.
  If it contains one at the hightest level, the other at the second highest level k, should first backtrack to level k, then assign this as a unit with level k. These two will be its watching literals.


update:

add_clause_during_solving()
> allocate space for this clause
> search for:
  - two unassigned literals
    > do nothing
  - one unassigned literal, the other literal with the highest level k
    > assign this literal, mark with level k, (or backtrack to level k), propagate
  - two literals with the highest levels, k, l
    - k = l:
      > backtrack to level k/l
    - k < l:
      > backtrack to level k (or l-1?)
      > assign the literal (mark with level k), propagate
> connect with these two literals



during propagation, a new unit is marked as the highest level (this can be kept by clause) (but how to restore this after backtrack?)

the literals of a clause can be sorted by level, unassigned -> high level -> low level (but )


// 28.10

satisfied new clause update unit level and reason
level recalculation during backtrack to keep as much variables as possible


// 28.10

when the level of a variable is changed (always lower than before) or a new literal assigned at a lower level:
(this is only )


the level of unassigned variable can be seen as +inf always > p
