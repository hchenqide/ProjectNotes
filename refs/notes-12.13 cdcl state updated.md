state:
- search -> propagate
- propagate -> analyze(conflict) | simplify
- analyze(conflict) -> unsat | propagate
- simplify -> unsat | interact
- interact -> add | decide
- add -> unsat | propagate | analyze(conflict) | interact
- decide -> sat | propagate
- unsat
- sat
