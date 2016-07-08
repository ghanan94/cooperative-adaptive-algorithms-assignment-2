1)
The way this program works is on BLACK's turn, the program will attempt to do
the best move based on the min-max strategy. On WHITE's turn, the program will
do a random move on the first available position that has available moves.

2)
The min max strategy is applied by first calling a function that explicitly does
the max. This function (do_best_move) will calculate the scores from each of its
children, and choose the best child to move to. The function gets the scores
from each of its possible child by using a function named min_max_possible_score
which can do the max or min stage calculations depending on a parameter
calculate_min (when true, treats the node as a min; max otherwise). When
calculating the min, the current node's children are generated and the lowest
score from all the children are returned. When calculating the max, the current
node's children are generated and the highest score from all the children are
returned. Alpha-Beta pruning is also implemented. The min_max_possible_score
function also gets an alpha_beta parameter which represents the parent node's
current best score (this could be the max so far or min so far depending on if
the parent node is a max or min level node respectively). When calculate_min
parameter is set to true, and the alpha_beta value is greater than the
current score, then halt any further calculations because this node definately
wont be travelled to (parent node is a max, and if current score is equal to
or less than the parent's best node, this value won't be greater than the
current score for parent). Similarly, If the calculate_min is set to false, and
the alpha_beta value is less than the current score, halt any furthur calculations.
The min_max_possible_score will either call min_max_possible_score to calculate
scores on its children if the current depth is > 0, or just return the current
node's score. depth is used to keep track of how deep in the tree to go.

3)
Our current evaluation function determines the score by determining the
available moves for the current user, and the available moves for the other
user, and finds the difference (current_user_total_allowed_moves -
other_user_total_allowed_moves = score). This evaluation funcitons works really
well because, as the BLACK user approaches winning, their available moves
will increase, but the other user's available moves will decrease, which will
substantially increase the score. The highest score can only be obtained when
the other user has no available moves, and that is when the BLACK user wins.

Another evaluation function implemented, was how many moves the other user
has available times -1. This evaluation function has the highest possible score
of 0 (which is a win state for BLACK). This evaluation function lead to
undesirable results as BLACK took > 30 moves to win (sometimes > 100) and
sometimes, it seemed as though BLACK was making unintelligent moves.

Another evaluation function implemented, was similar to the current implementation,
but we only considered positions on the board with 2 or more black pieces. This
function had reasonable results with BLACk winning within 30 and 50 moves.
However, it still seemed as though BLACK was making unreasonable moves at times.

4)
New Game, computer is playing as BLACK

Player to move: BLACK
 -----------------------
| B10 | E0  | E0  | E0  |
| E0  | E0  | E0  | E0  |
| E0  | E0  | E0  | E0  |
| E0  | E0  | E0  | W10 |
 -----------------------

Player to move: WHITE
 -----------------------
| E0  | E0  | E0  | E0  |
| E0  | B1  | E0  | E0  |
| E0  | E0  | B9  | E0  |
| E0  | E0  | E0  | W10 |
 -----------------------

Player to move: BLACK
 -----------------------
| E0  | E0  | E0  | E0  |
| E0  | B1  | E0  | E0  |
| E0  | E0  | B9  | E0  |
| W7  | W2  | W1  | E0  |
 -----------------------

Player to move: WHITE
 -----------------------
| E0  | E0  | E0  | E0  |
| E0  | B1  | E0  | E0  |
| B8  | B1  | E0  | E0  |
| W7  | W2  | W1  | E0  |
 -----------------------

Player to move: BLACK
 -----------------------
| E0  | E0  | E0  | E0  |
| E0  | B1  | E0  | E0  |
| B8  | B1  | E0  | E0  |
| E0  | W3  | W3  | W4  |
 -----------------------

Player to move: WHITE
 -----------------------
| E0  | E0  | E0  | E0  |
| E0  | B1  | E0  | E0  |
| E0  | B2  | B2  | B5  |
| E0  | W3  | W3  | W4  |
 -----------------------

Player to move: BLACK
 -----------------------
| E0  | E0  | E0  | E0  |
| E0  | B1  | E0  | E0  |
| E0  | B2  | B2  | B5  |
| E0  | E0  | W4  | W6  |
 -----------------------

Player to move: WHITE
 -----------------------
| E0  | E0  | E0  | E0  |
| B1  | E0  | E0  | E0  |
| E0  | B2  | B2  | B5  |
| E0  | E0  | W4  | W6  |
 -----------------------

Player to move: BLACK
 -----------------------
| E0  | E0  | E0  | E0  |
| B1  | E0  | E0  | E0  |
| E0  | B2  | B2  | B5  |
| E0  | E0  | E0  | W10 |
 -----------------------

Player to move: WHITE
 -----------------------
| E0  | E0  | E0  | E0  |
| B1  | E0  | E0  | E0  |
| E0  | E0  | B2  | B5  |
| E0  | E0  | B2  | W10 |
 -----------------------
Player BLACK has won
Game over after 9 moves

It can be seen that BLACK immediately tries to trap the WHITE player with each
move. With each move, WHITE is allowed to do less and less moves, limiting it's
options and 'good' moves.
