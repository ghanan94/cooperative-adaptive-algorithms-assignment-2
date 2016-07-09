1)
When changing the initial starting point, the score either equally improved and
or worsened, sometimes significantly. It can be seen that the initial solution
generated has a significant impact on the final solution.

2)
When changing the tabu list size, the average cost of the solutions decreased
by approximately 30.

3)
When changing the tabu tenure to be generated dynamically (a random value
between 0 and a MAX_TABU_TENURE), a small improvement was observed. Before,
an average cost of 1345 was observed, whereas after the dynamic tenure, an
average cost of 1310 was observed.

4)
The aspiration criteria for this implementation is 'best solution so far'. When
this aspiration criteria was set, the solution cost decreased.

5)
When using less than the whole neighborhood to select the next solution, the
score worsened.

6)
// TODO Add a frequency based tabu list and/or aspiration critera (designed to
encourage the search to diversify).
