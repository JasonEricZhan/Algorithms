# flattest_lowest_hillclimbing solving by Dynamic Programming

Everytime walk from one point to another and count:
   
If going horizon or vertical only have to cost the energy: 

     start point's hieght + |start point's height - end point's height|
 
If going diagonal direction, then have to cost the energy: 

     start point's hieght + 1.4 * |start point's height - end point's height|

And find the lowest cost path
