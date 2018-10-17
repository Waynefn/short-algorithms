# 24Games
The game could see https://en.wikipedia.org/wiki/24_Game 

Given four numbers which are greater than 0 and smaller than 14.

Return the possible equation which the result is 24.

Example,
Given [5,5,4,2], return "((5+5)*2)+4"

Given [6,6,7,11], return "(6*11)-(6-7)"



# Method

My method is to use a tree to iterate all situations.

To avoid considering priority grade, I use a Suffix expression.

But the difficulty is to delete the same result, 5*6 to 6*5.
