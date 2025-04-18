changes:
- the proof patch misses output when simplifying a clause, added
- drup-trim outputs 0 when couldn't match a clause, changed to 1
- cb_check_found_model returns false just continues the loop and there might not be actually a clause next time


assignments batch notify:
- before first decision, all assigments are root level, assigned literals will only be more, any conflict will cause unsat, notify all new assignments before each interact
- after each decision, notify new level
- before each decision, 

(so notify backtrack should also merge)
(the difference between two interactions are just: 1. go to target level (backtrack or remain on current level) 2. any new assignments on the target level)
(all new assignments are on the same current level)

*update:
assignments and backtrack batch nofity:
- solver keep next unnotified index notify_next on the assignment stack
- before interaction, notify assignments in the range [notify_next, assignment.end())
- if backtracks, always move notify_next back to the end
- if there used to be multiple backtracks, before notify assignments also notify backtrack once at the current level
