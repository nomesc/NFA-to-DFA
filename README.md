# NFA-to-DFA
Converts a nondeterministic finite automaton into a deterministic finite automaton.


The input file "date.out" must contain:

Number of input symbols
Eg:2

The set of input symbols
Eg:ab

Number of states
Eg:5

Number of final states
Eg:2

The final states
Eg:0 2

And the states:
(First state is the start state)

Eg
  1 0     a 1 1           b 2 0 3
  From state q0 you can go with 'a' towards q1 and with 'b' towards q0 and q3.

  /////////
Eg
  1 3     a 0             b 1 0
  From state q3 you can go with 'a' towards no state and with 'b' towards q0.
  /////////
Eg
  1 4     a 3 0 2 3       b 0
  From state q4 you can go with 'a' towards q0, q2 and q3 and with 'b' towards no state.
  /////////

 Eg of input:
2
ab
5
2 0 2
1 0     a 1 1           b 2 0 3
1 1     a 1 2           b 1 4
1 2     a 1 2           b 1 2
1 3     a 0             b 1 0
1 4     a 3 0 2 3       b 0
