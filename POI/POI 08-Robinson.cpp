
so how i thought about it was, we definately need to find positions where the boat can fit, and the do a bfs to find the solution


so how to find all fitting positions?

first lets try to find some order in which we would pass the position candidates so it would be easy for us to determine if it fits there
lets say that the symetry axis is horizontal and lets define the position of our boat by a point on its axis with the biggest height
so lets pass all the rows one by one, from left to right and maintain the obstacles which are contained within the boat
we can see that when we move right, the surface from which we need to pick up new obstacles is irregular so its kinda hard
to get fast info on it, so we can split our boat from its main point(the point which determines it) to the left, and from the main point
to the right, for the left part we have an irregular left side and the right part is just a column(which will be easy to query)
then lets see what happens with out obstacle maintaining, now we are solving for the left part(we will call it boat from now on)
it happens that when we move our boat to right only obstacles that are in that column have to be added, but that is too much for us
so we will try to find a way to reduce that, lets see which of those are actually relevant, thing to notice is that every obstacle 
will last for a certain interval in this row, so when we step on an obstacle we can just update our right boundary upto which we will have 
obstacles in our boat, and when we move to the right, we just need the obstacle closest to the centre, because those last the most
and all farther obstacles in that column exit the boat sooner, this is because the boat is symetric and it gradually increases 
to the right
