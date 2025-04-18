before a new decision: (currently at level p, p >= 0)

add_external_clause:

> if there's 0~true literal, discard the clause
> if there's a 0~false literal, ignore the literal
> 
- empty
  > terminate with unsat
    how to terminate? (after unsat, the solver can not be used anymore?)
- unit: l
  - unassigned
    > assign level 0~l with this as reason (put at the back of the trace, will stay despite backtrack)
    > propagate
  - k~true, 1 <= k <= p
    > reassign level 0~l with this as reason
    > add_external_clause
  - k~false, 1 <= k <= p
    > reassign level 0~l with this as reason
    > backtrack to level k-1 with l to be repropagated
    > propagate
- two or more
  > sort the literals by: (low to high)true, unassigned, (high to low)false
  > the first two literals are k1~l1, k2~l2, 1 <= ki <= p or unassigned
  > watch l1, l2
  - k1~true, k2~true:
    > add_external_clause
  - k1~true, unassigned:
    > add_external_clause
  - k1~true, k2~false:
    - k1 <= k2:
      > add_external_clause
    - k1 > k2:
      > assign level k2~l1 with this as reason
      > add_external_clause
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


literals reassigned to lower level than backtrack target level stays on the trace and are to be propagated. 
do they need to be re propagated? (only the value reassigned one need to, level reassigned one don't)
(no, there should be other units discovered and reassigend to their actual levels)

can adding a clause be called during propagation?


operations and effects:
- propagate a literal on the trace
  > the watches of clauses changed
  > a new literal appended on the trace
  > a conflict clause discovered, propagation of this literal stopped, literals at least of this level will be unassigned
- backtrace to level k
  > all literals on the trace section of level k+1, ..., p are cleared and put back to the decision heap
  > 
