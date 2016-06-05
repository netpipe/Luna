README
======


This is a small speed test for miNav. This program will create a map with 36 nodes (or 'waypoints') and connects them (I designed the map, you can have a look at it by opening the map.gif picture). It then 'solves' the WHOLE map storing ALL solutions for every possible pathfinding query. To test the accuracy of the results, a test of travelling from the top left corner of the map to the bottom right is performed. Only if the destination is reach will the program continue, otherwise it will be stuck in a continous loop... basically it's sink or swim test....

Also the positions given by the test can be validated by viewing the map.gif picture. The positions correspond to the pixel positions of the Node dots (well the top left hand corner of them... it's fireworks fault... :P).