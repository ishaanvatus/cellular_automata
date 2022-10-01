# cellular_automata
Coding cellular automata from scratch 

A cellular automaton has an (ideally) infintie grid of cells, with each cell having a finite number of states usually 0 (dead) or 1 (alive), 
a set of cell close to each cell is defined as it's neighborhood and a rule is applied to it, usually a mathematical function involving it's neighbours and itself.
Each tick or generations these rules get applied to each cell at once (exceptions exist, look at: stochastic cellular automaton and asynchronous cellular automaton).

The concept was originally discovered in the 1940s by Stanislaw Ulam and John von Neumann while they were contemporaries at Los Alamos National Laboratory. 
While studied by some throughout the 1950s and 1960s, it was not until the 1970s and Conway's Game of Life, a two-dimensional cellular automaton,
that interest in the subject expanded beyond academia. In the 1980s, Stephen Wolfram engaged in a systematic study of one-dimensional cellular automata, 
or what he calls elementary cellular automata; his research assistant Matthew Cook showed that one of these rules is Turing-complete. 

Conway's Game of life is the most popular example but many other exist like Langton's Ant, Brian's Brain and many more.

Essentially any rule that's interesting enough while being simple enough (or not) is worth studying as a cellular automaton.
