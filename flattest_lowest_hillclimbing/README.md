# flattest and lowest hill climbing problem solved by Dynamic Programming

There are two rules:

1.Every step just can walk to adjacent point, and can't go back, so there is three directions:horizon, vertical, diagonal.

2.Path must in the slope of 1/2~2, and can't go out the region make by four lines(two lines slope are 1/2,two lines slope are 2), otherwise it's illegal.


Everytime walk from one point to another and count:
   
If going horizon or vertical only have to cost the energy: 

     start point's hieght + |start point's height - end point's height|
 
If going diagonal direction, then have to cost the energy: 

     start point's hieght + 1.4 * |start point's height - end point's height|

_Note:Coordinate of each point is represented by (row , column)_

Step by step to find the lowest cost path from (0,0) to (N,N)



<b> Data input</b>:

1.first one is number N means NXN board

2.The heights of every point, and are scanned by sequential order,
ie:

(0,0) ,(0,1), (0,2).......(N,N-1) ,(N,N)

Ex: 6X6 board

6
1 2 3 4 5 6 
7 8 9 10 11 12 
13 14 15 16 17 18 
19 20 21 22 23 24 
25 26 27 28 29 30 
31 32 33 34 35 36 


<b>Output</b>:

lowest cost and the path represent by coordinates
