1)
BFS: First the start node is added to a 'to-be-visited' queue. Then a while loop
is entered that will terminate when the 'to-be-visited' queue is empty. In the
loop, the node at the front of the queue is looked at, and checked if it is the
goal node. If it is the goal node, we end the loop. If it isn't the goal node,
the node is marked as visited. The node's neighbors (up, right, down, and
left nodes) are retrieved if they haven't already been visited or are already in
the 'to-be-visited queue'. These node's are updated with the cost to that node
(cost to currently visited node + 1) and then added to the 'to-be-visited'
queue at the end, in the order they were retrieved (up, right, down, left). If
the nodes already have been visited or are going to be visited, and the cost to
the node from the node currently being visisted is less, then the node's parent
node is updated with the current node along with the new cost. The node at the
front of the 'to-be-visited' queue is popped. After the loop as terminated
(no more nodes in the 'to-be-visited' queue), the end node is checked to see if
it has a parent. If it does, a solution exists; if it doesn't no solution exists.

DFS: Same as BFS except, instead of added the newly retrieved nodes to the end
of the queue, they are added to the front of the queue.

A*: Same as BFS except, at the beginning of each iteration of the loop, the
'to-be-visited' queue is sorted to order the queue by the estimated cost to
the goal node. The node at the front of the queue will be the node with
the lowest cost so far in the queue, and the node at the end of the queue will
be the node with the highest cost so far in the queue. The estimated cost to the
goal node (heuristic function) is the manchester distance between the node and
the goal node.



2)
Look at 3

3)
3.1)
BFS from S to E1
 ---------------------------------------------------
|         # #                       # #             |
| # # # # # # # # # #                               |
| # # # # #       #           # # # # # # #         |
|       # # #     #           # # # # # # #         |
|       # # #     # # #       # # # # # # #         |
|                 # # # ^ > > > > > > > > > > > E   |
|                 # # # ^     # # # # # # #         |
| # # # # # # #   # ^ > >                           |
|     ^ > > > > > > > #                           # |
|     ^               #                         # # |
|     ^           # # # # #     # #           # # # |
|     ^               #         # #         # # # # |
|     ^               #         # #   #     #     # |
|     S   #                     # #   #     #       |
|                               # #   #     #       |
|                               # #   #     #       |
|     # # #                           #     #       |
|     # # #   # #     # # #           #             |
|     #       # #     # # #           # # # # # #   |
| # # #       # #     # # #           # # # #       |
| # # #       # #     # # #           # #           |
|             # #     # # #           # #           |
|                     # # #           # #           |
|                                     # #           |
|                                                   |
 ---------------------------------------------------

DFS from S to E1
 ---------------------------------------------------
|         # #           ^ > > > > > # # ^ > > > > > |
| # # # # # # # # # #   ^         v > > >         v |
| # # # # #       #     ^     # # # # # # #       v |
|       # # #     #     ^     # # # # # # #       v |
|       # # #     # # # ^     # # # # # # #       v |
|                 # # # ^                       E v |
|                 # # # ^     # # # # # # #         |
| # # # # # # #   # ^ > >                           |
|     ^ > > > > > > > #                           # |
|     ^               #                         # # |
|     ^           # # # # #     # #           # # # |
|     ^               #         # #         # # # # |
|     ^               #         # #   #     #     # |
|     S   #                     # #   #     #       |
|                               # #   #     #       |
|                               # #   #     #       |
|     # # #                           #     #       |
|     # # #   # #     # # #           #             |
|     #       # #     # # #           # # # # # #   |
| # # #       # #     # # #           # # # #       |
| # # #       # #     # # #           # #           |
|             # #     # # #           # #           |
|                     # # #           # #           |
|                                     # #           |
|                                                   |
 ---------------------------------------------------

A* from S to E1
 ---------------------------------------------------
|         # #                       # #             |
| # # # # # # # # # #                               |
| # # # # #       #           # # # # # # #         |
|       # # #     #           # # # # # # #         |
|       # # #     # # #       # # # # # # #         |
|                 # # # ^ > > > > > > > > > > > E   |
|                 # # # ^     # # # # # # #         |
| # # # # # # #   # ^ > >                           |
|     ^ > > > > > > > #                           # |
|     ^               #                         # # |
|     ^           # # # # #     # #           # # # |
|     ^               #         # #         # # # # |
|     ^               #         # #   #     #     # |
|     S   #                     # #   #     #       |
|                               # #   #     #       |
|                               # #   #     #       |
|     # # #                           #     #       |
|     # # #   # #     # # #           #             |
|     #       # #     # # #           # # # # # #   |
| # # #       # #     # # #           # # # #       |
| # # #       # #     # # #           # #           |
|             # #     # # #           # #           |
|                     # # #           # #           |
|                                     # #           |
|                                                   |
 ---------------------------------------------------

3.2)
BFS from S to E2
 ---------------------------------------------------
|         # #                       # #             |
| # # # # # # # # # #                               |
| # # # # #       #           # # # # # # #         |
|     E # # #     #           # # # # # # #         |
|     ^ # # #     # # #       # # # # # # #         |
|     < < < < < ^ # # #                             |
|               ^ # # #       # # # # # # #         |
| # # # # # # # ^ #                                 |
|     ^ > > > > >     #                           # |
|     ^               #                         # # |
|     ^           # # # # #     # #           # # # |
|     ^               #         # #         # # # # |
|     ^               #         # #   #     #     # |
|     S   #                     # #   #     #       |
|                               # #   #     #       |
|                               # #   #     #       |
|     # # #                           #     #       |
|     # # #   # #     # # #           #             |
|     #       # #     # # #           # # # # # #   |
| # # #       # #     # # #           # # # #       |
| # # #       # #     # # #           # #           |
|             # #     # # #           # #           |
|                     # # #           # #           |
|                                     # #           |
|                                                   |
 ---------------------------------------------------

DFS from S to E2
 ---------------------------------------------------
|         # #                       # #             |
| # # # # # # # # # #                               |
| # # # # #       #           # # # # # # #         |
|     E # # #     #           # # # # # # #         |
|     ^ # # #     # # #       # # # # # # #         |
|     < ^   < < ^ # # #                             |
|       < < v   ^ # # #       # # # # # # #         |
| # # # # # # # ^ #                                 |
|     ^ > > > > >     #                           # |
|     ^               #                         # # |
|     ^           # # # # #     # #           # # # |
|     ^               #         # #         # # # # |
|     ^               #         # #   #     #     # |
|     S   #                     # #   #     #       |
|                               # #   #     #       |
|                               # #   #     #       |
|     # # #                           #     #       |
|     # # #   # #     # # #           #             |
|     #       # #     # # #           # # # # # #   |
| # # #       # #     # # #           # # # #       |
| # # #       # #     # # #           # #           |
|             # #     # # #           # #           |
|                     # # #           # #           |
|                                     # #           |
|                                                   |
 ---------------------------------------------------

A* from S to E2
 ---------------------------------------------------
|         # #                       # #             |
| # # # # # # # # # #                               |
| # # # # #       #           # # # # # # #         |
|     E # # #     #           # # # # # # #         |
|     ^ # # #     # # #       # # # # # # #         |
|     < < < < < ^ # # #                             |
|               ^ # # #       # # # # # # #         |
| # # # # # # # ^ #                                 |
|     ^ > > > > >     #                           # |
|     ^               #                         # # |
|     ^           # # # # #     # #           # # # |
|     ^               #         # #         # # # # |
|     ^               #         # #   #     #     # |
|     S   #                     # #   #     #       |
|                               # #   #     #       |
|                               # #   #     #       |
|     # # #                           #     #       |
|     # # #   # #     # # #           #             |
|     #       # #     # # #           # # # # # #   |
| # # #       # #     # # #           # # # #       |
| # # #       # #     # # #           # #           |
|             # #     # # #           # #           |
|                     # # #           # #           |
|                                     # #           |
|                                                   |
 ---------------------------------------------------

BFS from (0, 0) to (24, 24)
 ---------------------------------------------------
|         # #                       # # ^ > > > > E |
| # # # # # # # # # #   ^ > > > > > > > >           |
| # # # # #       #     ^     # # # # # # #         |
|       # # #     #     ^     # # # # # # #         |
|       # # #     # # # ^     # # # # # # #         |
|                 # # # ^                           |
|                 # # # ^     # # # # # # #         |
| # # # # # # #   # ^ > >                           |
|           ^ > > > > #                           # |
|           ^         #                         # # |
|           ^     # # # # #     # #           # # # |
|           ^         #         # #         # # # # |
|           ^         #         # #   #     #     # |
|         # ^                   # #   #     #       |
|           ^                   # #   #     #       |
|           ^                   # #   #     #       |
|     # # # ^                         #     #       |
|     # # # ^ # #     # # #           #             |
|     # ^ > > # #     # # #           # # # # # #   |
| # # # ^     # #     # # #           # # # #       |
| # # # ^     # #     # # #           # #           |
| ^ > > >     # #     # # #           # #           |
| ^                   # # #           # #           |
| ^                                   # #           |
| S                                                 |
 ---------------------------------------------------

DFS from (0, 0) to (24, 24)
 ---------------------------------------------------
|         # #           ^ > > > > > # # ^ > > > > E |
| # # # # # # # # # #   ^         v > > >           |
| # # # # #       #     ^     # # # # # # #         |
|       # # #     #     ^     # # # # # # #         |
|       # # #     # # # ^     # # # # # # #         |
|                 # # # ^                           |
|                 # # # ^     # # # # # # #         |
| # # # # # # #   # ^ > >                           |
|           ^ > > > > #                           # |
|           ^         #                         # # |
|           ^     # # # # #     # #           # # # |
|           ^         #         # #         # # # # |
|           ^         #         # #   #     #     # |
|         # ^                   # #   #     #       |
|           ^                   # #   #     #       |
|           ^                   # #   #     #       |
|     # # # ^                         #     #       |
|     # # # ^ # #     # # #           #             |
|     # ^ > > # #     # # #           # # # # # #   |
| # # # ^     # #     # # #           # # # #       |
| # # # ^     # #     # # #           # #           |
| ^ > > >     # #     # # #           # #           |
| ^                   # # #           # #           |
| ^                                   # #           |
| S                                                 |
 ---------------------------------------------------

A* from (0, 0) to (24, 24)
 ---------------------------------------------------
|         # #                       # # ^ > > > > E |
| # # # # # # # # # #   ^ > > > > > > > >           |
| # # # # #       #     ^     # # # # # # #         |
|       # # #     #     ^     # # # # # # #         |
|       # # #     # # # ^     # # # # # # #         |
|                 # # # ^                           |
|                 # # # ^     # # # # # # #         |
| # # # # # # #   # ^ > >                           |
|           ^ > > > > #                           # |
|           ^         #                         # # |
|           ^     # # # # #     # #           # # # |
|           ^         #         # #         # # # # |
|           ^         #         # #   #     #     # |
|         # ^                   # #   #     #       |
|           ^                   # #   #     #       |
|           ^                   # #   #     #       |
|     # # # ^                         #     #       |
|     # # # ^ # #     # # #           #             |
|     # ^ > > # #     # # #           # # # # # #   |
| # # # ^     # #     # # #           # # # #       |
| # # # ^     # #     # # #           # #           |
| ^ > > >     # #     # # #           # #           |
| ^                   # # #           # #           |
| ^                                   # #           |
| S                                                 |
 ---------------------------------------------------
