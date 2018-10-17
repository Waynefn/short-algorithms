# H-index problem

## Description

The definition of the h index is that a scholar with an index of h has published h papers each of which has been cited in other papers at least h times. (https://en.wikipedia.org/wiki/H-index)
Given a list which includes papers' citation times, return the index of h.

### Example

>Given [300,30,3,1], the output is 3,
>because there are only three numbers [300,30,3] which are greater or equal to 3.

>Given [5,4,100,7,1], the output is 4.

>Given [0,0,5001,300,1,1,1,1], the output is 2.



## Approach


An algorithm to compute thesis factor h-index which used by Google Scholar.
Here I list two algorithms:

1st is written in Python with a complexity of O(n*log n).

2nd is written in C++ with a complexity of O(n).
The method uses deque in STL.