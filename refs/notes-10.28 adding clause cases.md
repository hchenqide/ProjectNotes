### CDCL with incremental solving

an added clause during solving at level p:

- satisfied by true literals: |{ki~li}| >= 1, 0 <= ki <= p
  - ∃i, ki = 0
    > discard the clause
  - ∀i, ki >= 1
    > remove all 0~false literals
    - one true: k~l
      - no more other
        > assign level 0~l with this as reason
      - at least one other unassigned: j
        > watch l, j
      - all other 1+~false, the highest false q~l', 1 <= q <= p
        - q >= k
          > watch l, l'
        - q < k
          > assign level q~l with this as reason
          > watch l, l'
    - at least two true: k1~l1, k2~l2
      > watch l1, l2
- not yet satisfied (all unassigned or false)
  > remove all 0~false literals
  - empty
    > terminate with unsat
  - only one unassigned: l
    > assign level 0~l with this as reason
  - at least two unassigned: l1, l2
    > watch l1, l2
  - unit (one unassigned: l, all other false, the highest q~l', 1 <= q <= p)
    > assign level q~l with this as reason
    > watch l, l'
  - conflict (all false)
    - unit k~l
      > backtrack to level 0 (or k-1?)
      > assign level 0~l with this as reason
    - the highest two k1~l1, k2~l2, 1 <= k1 <= k2
      - k1 = k2 = k
        > watch l1, l2
        > backtrack to level k
        > do conflict analysis and backtrack again
      - k1 < k2
        > backtrack to level k1 (or k2-1?)
        > assign level k1~l2 with this as reason
        > watch l1, l2


0~false literal propagation: (all affected clauses are shortened by this, producing)
- empty clause
  > terminate with unsat
- unit clause
  - a true literal: k~l
    - k = 0
      > remove this clause
    - k > 0
      > assign level 0~l with this as reason
  - a false literal: k~l, k >= 1
    > backtrack to level 0 (or k-1?)
    > assign level 0~l with this as reason
  - an unassigned literal
    > assign level 0~l with this as reason
- at least two literals
  > normal propagation


backtrack with level reassignment: (to keep as many assigned literals as possible)
> keep the literals with actual level < backtrack level on the back of the stack and propagate them again
> new assignments of a literal with its actual level
