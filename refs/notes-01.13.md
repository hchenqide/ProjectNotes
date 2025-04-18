- reason lit from var
- lazily added clauses are always forgettable
- lazily adding clause assert vs throw
- add_reason_clause_lit must not interleave between lits


lazy explaination skip pure unit clause, otherwise requires chronological backtracking
(when the lazy clause is a unit, analyze won't work)


even though with lazy explaination, all clauses are still used in the end. (root level non-lazy)
