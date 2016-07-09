1)
When changing the initial starting point, the score either equally improved and
or worsened, sometimes significantly. It can be seen that the initial solution
generated has a significant impact on the final solution.

2)
When increasing the tabu list size, the average cost from the final solution
generated seemed to have decreased. When decreasing the tabu list size, the
average cost from the final solution generated seemed to have increased.

3)
When changing the tabu list size to be dynamic, the average cost from the final
solution seemed to not significantly change, but more better and worse seemed
to be generated.

4)
The aspiration criteria for this implementation is 'best solution so far'. When
this aspiration criteria was set, the solution cost decreased.

5)
When using less than the whole neighborhood to select the next solution, the
score worsened.

6)
// TODO Add a frequency based tabu list and/or aspiration critera (designed to
encourage the search to diversify).
