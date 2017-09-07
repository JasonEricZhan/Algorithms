# flattest_lowest_hillclimbing solving by Dynamic Programming

Everytime walk from one point to another and count:
   
If going horizon or vertical only have to cost the energy: 

     start point's hieght + |start point's height - end point's height|
 
If going diagonal direction, then have to cost the energy: 

     start point's hieght + 1.4 * |start point's height - end point's height|

Step by step to find the lowest cost path

Data input:

1.first one is number N means NXN board
2.The height of every point

Ex: 6X6 board

6
1 2 3 4 5 6 
7 8 9 10 11 12 
13 14 15 16 17 18 
19 20 21 22 23 24 
25 26 27 28 29 30 
31 32 33 34 35 36 
