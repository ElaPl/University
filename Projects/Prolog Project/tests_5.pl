%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Tests for task 5, Mozaika iloczynow
% VERSION: 0.2
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

taskArity(2). % 2 is the number of input arguments, solve has arity 3

testSimpleSolution( Correct, Result) :-
  Correct == Result.

simple_test(2, [ [2,0] ], ( [4,5], [ ((1,1),(1,2)) ]) ).
simple_test(3, [[1,6,1],[1,6,6]], ( [4,4,4], [((1,1),(1,2)), ((2,1),(2,2)), ((1,3),(2,3))] )).
simple_test(4, [[5,8,4,0], [5,3,0,4], [6,3,4,2]], ([5,6,7,8], [((3,2),(2,3)), ((2,2),(1,1)), ((2,4),(1,4)), ((3,3),(3,4)), ((1,3),(1,2)), ((2,1),(3,1))])).

% 187 sekund.

count_test(4, [[5,8,4,0], [5,3,0,4], [6,3,4,2]], 1).
count_test(4, [[0,8,4,0], [5,3,0,4], [6,3,4,2]], 0).
count_test(3, [[2,0,3], [2,4,0]], 2).

