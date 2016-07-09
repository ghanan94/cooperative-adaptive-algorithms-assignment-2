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
When looking at less than the whole neighborhood to select the next solution
(only looking at 50 % of neighbors), the solutions being generated had an
average cost that decreased by approximately 10.

6)
After adding a frequency-based tabu-list tenure, the search seems to have both
improved and worsened. Some solution results seem to have hit better costs, but
other results seem to have equally worse costs. The average cost returned seems
to have stayed constant.
