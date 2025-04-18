before a new decision: (currently at level p, p >= 0)

add_external_clause:

> sort the literals by index to find tautological clauses
> (can be found during propagation)
> 
> sort the literals by: (low to high)true, unassigned, (high to low)false
>
> if front is 0~true literals, discard the clause
> trim back 0~false literals, ignore the literal
>
- empty
  > terminate with unsat
    how to terminate? (after unsat, the solver can not be used anymore?)
- unit: l
  > backtrack to level 0
  > assign 0~l
  > propagate
- two or more
  > the first two literals are k1~l1, k2~l2, 1 <= ki <= p or unassigned
  > watch l1, l2
  - unassigned, unassigned:
    > add_external_clause
  - unassigned, k2~false:
    > assign level k2~l1 with this as reason
    > propagate
  - k1~false, k2~false
    - k1 = k2 = k
      > backtrack to level k
      > analyze_conflict, backtrack, propagate
    - k1 > k2
      > reassign level k2~l1 with this as reason
      > backtrack to level k2 (or k1-1?) with l1 to be repropagated
      > propagate


state:
- propagate -> analyze(conflict) | ask_new
- analyze(conflict) -> unsat | propagate
- ask_new -> add | decide
- add -> unsat | propagate | analyze(conflict) | ask_new
- decide -> unsat | sat | propagate
- unsat
- sat

