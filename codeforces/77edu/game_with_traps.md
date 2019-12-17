#Problem D educational codeforces round
There are m soldiers, which has an agility Ai.
You must get into a path of n+1 squares in which there are k traps
Each trap has three values l, r and d.
l represents the location
d is the danger, which means that if there is any soldier that has less than d agility and steps over it armes dies.
r represents the point in which you can disarm a trap.
I don't die due to traps.
I have t moves to get to the last spot.
Each move takes 1 second and you can move with or without your soldiers, but they cannot walk by themselves.
You may move backward and forward.
If you are in a place to disarm a trap you can do that without consuming any time

I must find the maximum number of soldiers possible to complete the path within t moves


My Idea

To iterate over the the path and disarm any trap whose disarmation square is the current position, also check if the next one is an armed trap, and in case it is you do two different recursive calls, in which one will not disarm that trap and kill any soldier whose agility is lower than the danger, and the other path would be to go alone to the disarmation point and then come back with the squad. While doing this if the time consumed is greater than the maximum allowed you break the path, otherwise you continue and you compute the max number of soldiers of those who ended the path, saving the max and returning that.
Actually you don't need to compute the soldiers who would die, only the minimal agility of those who got through and only do the computation at the end. Also in order to optimize we could calculate if the number of the steps till the end + the numbers of steps we already took + the steps to disarm the bomb is less than the maximum and otherwise break this path.
Actually we could optimize it even more and do a more complete dp, by storing somewhere all the time consumed via each path and also the minimum agility to go through that specific path, so if we encounter that same square again we could only check the viable paths and do no unnecessary calculation again.

Time complexity: We would have to iterate over it at least once so the minimum is O(n), but we could also have lots of traps and for each have different paths, but... since we are now using dp we would only need to do each path calculation once, so that wouldn't be exponential time anymore, but polynomial, probably O(n) but with a larger constant.

We could use the recursive approach but i don't like it very much and the iterative is also more efficient, so let's try to create some build-up approach. We could start from the last spot and keep going back, computing the time needed to go from there to the end, but that wouldn't check if the trap can be disarmed before. Actually we could first iterate over it and find only those who have disarming points after the trap and remove all the others. Then for those who remain we could find the time needed to disarm it, so we would iterate over it backwards and keep computing those paths and their values, doing no more computation, only taking what we've computed, so it would definitively be O(n) time complexity, since we are just going over each item three times and the expanded complexity would be smh like n+k+k, so that is linear. Now I only have to implement it.
Actually I don't need to do this first iteration causa I just found out that all disarming point are after the trap, so we only need to compute the time needed to disarm and do the same thing. Overall the performace will still be linear.

There is another solution that I think is actually better because that one would end up being square time because we would have to compare to each of the previous step to compute all the possible paths and that would double every time until reaching 2^k, if all paths were possible. So not that good. The other solution I tought of is to do a binary search answer which would be way better because it passes the time limit.
It would work by saving a interval of possible min number of soldiers and then going through those paths with the possible number of soldiers and then save the possible answers and try to improve those until you find the final answer.

I submitted it but there was a problem because I didn't consider that we could disarm multiple traps at the same "travel" of the person without its crew, and after analyzing it i found out that we could simply create a pointer which would represent the end of the "travel" which is the furthest away disarming point of all the ones that we've visited and go disarming every thing that we've passed.
