a)
i) A solution representation can be an array of routes. A route will be
represented as an array of customers that will be visited in a specific order.
The first element will be visited first, the last element will be visited last.
It is implicitly implied that the route starts and ends at the depot.

ii) A neighborhood operator can be finding customers that have the highest
travel distances from their neighbours and remove them from their routes. They
will then randomly be added to another route. Also, two random customers each in
random routes can be exchanged/swapped.

iii) The objective function is to find the minimum travel distance for each of
the trucks. In other words, the sum of the distances each truck has to travel
including the distance from depot to first customer, distance between each
customer, and last customer to depot.

b) If the constraint of a maximum route duration was required, a check would
need to be required in the neighbourhood operator to make sure a neighbour that
violates these conditions is generated or returned.
