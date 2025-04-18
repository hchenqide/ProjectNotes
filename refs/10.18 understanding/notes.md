## to discuss / to do

- difference between eager and lazy explaination

- benchmark for minisat

- refactor minisat library
  - merging files
  - using stl
  - removing entry point and options

- c++ template interface declairation for automatic fuzzer

- common header file for ipasir-up interface using virtual function

- change of the ipasir-up interface
  - add_clause not literal-wise

- extending ipasir-up interface refering to cvc5 injections on minisat
  - proposing the next decision literal

## CDCL

loop:
  decision
  propagate
    assigment
    conflict

## facts

-

an assigment of a variable during propagation is caused by a single clause whose all other literals are assigned or assumed

literal -> cause clause -> causing literal list

a conflict is a clause whose literals are all assigned

conflict clause -> literal list

-

conflict occurs at the latest decision lit with some previous decided lit
backtrack goes back to the nearest decision lit occurring in the conflict clause

-

fuzzer randomly generates input data based on interface schema

the fuzzer can be automatically acquired by the predefined schema

f<T>: (generate a random piece of data of type T)
void -> void
array<length, T> -> (length with probability distribution) random<limit(length)>, foreach: f<T>
struct{A, B, ...} -> struct{f<A>, f<B>, ...}
union{A, B, ...} (with prior probability) -> f<A>
union{A, B, ...} (without prior probability) = union{A, B, ...} (with prior probability 1/n)

bool = union{true, false}
nat[k] = union{0,1,2,...,k-1}


interactive fuzzer

T0 -> T1 -> ... -> void

function call f1(T1), f2(T2) ... = union{T1, T2, ...}


after calling the program, it outputs the type that needs to be further fulfilled
but all possible output type form a union, in the whole form a graph

p: T0 -> union{T00, T01, T02, ...}
T1 ->


program p
fuzzer f

-

fuzzer with trace

generated input leaves trace to be repeated

