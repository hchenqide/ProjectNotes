## properties

`trail`:  stack of assigned literals

`qhead`: the next literal on `trail` to propagate

`order_heap`: the priority queue of literals to be assumed

`watches`: the clauses 

## functions

`propagate`: propagate the literals on `trail`



## diff minisat -> cvc5/minisat

git diff --name-status --no-index ./minisat/minisat ./cvc5/src/prop/minisat > diff_minisat_digest.txt
git diff --diff-filter=M -w --no-index ./minisat/minisat ./cvc5/src/prop/minisat > diff_minisat.diff