# flattest_lowest_hillclimbing solving by Dynamic Programming

Everytime walk from one point to another and count:
   
If going horizon or vertical only have to cost the energy: 

     start point's hieght plus absolute value of (start point height - end point height)
 
If going diagonal direction, then have to cost the energy: 

     start point's hieght plus 1.4 muptily absolute value of (start point height - end point height)

And find the lowest cost path
