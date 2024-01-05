# Author
Aidan Gibson 
ajg227

# Estimate of time to complete assignment
22 hours

# Actual time to complete assignment
| Date  | Time Started | Time Spent | Work completed                                                                                                        |
| :---: | -----------: | ---------: | :-------------------------------------------------------------------------------------------------------------------- |
| 12/1  |      9:48pm |       1 hour 3 minutes | Read specifications and began work on = override for BSTree.h/AVLTree.h/RBTree.h       |
| 12/7  |      10:20pm |      1 hour 39 minutes | Worked on getting BSTree Naive to work and various low level helper functions.           |
| 12/8  |       12:00am |       1 hour 46 minutes | Continued work on BSTree Naive tree, focusing on remove. |
| 12/8  |       8:00pm |       3 hours 34 minutes | Finished the initial version of remove and insert and began AVL counterparts. |
| 12/10  |       11:00pm |       1 hour | Continued working on AVL trees and fixing remove.  |
| 12/11      |        12:00 am     |      11 hours 40 minutes | Finished rest of AVL tree functionality, RB functionality. |
| 12/11      |        8:40 pm     |      1 hour 43 minutes | Wrote LOG.md and tested more edge cases, fixing issues with remove. |
|       |              |      22:25 | total time spent                                      

# Collaboration
I discussed some of the functions with Luke Reynolds and Sebastian Oronzco, though our implementations of them were radically different enough that we only discussed the broad stroaks. 

# Discussion
This problem set was definitely one of the hardest of the year, though admittedly the time I distributed to each function turned out to be different than I expected.  The main problem point was my implementation of remove, which was incredibly frustrating and had an absurdist number of edge cases.  It often felt like there weren't many elegant ways to fix edge cases beyond just brute forcing my code to catch them, so remove took a lot of repeated attempts to get working.  I admittedly didn't use many of the helper functions we had to design, but by the end I just wanted to ensure my code worked and didn't want to gamble with calling the helpers everywhere.  That being said, red black insertion actually wasn't that bad; the neighborhood data structure they gave us turned out to make it actually decently comprehensible.  AVL Rebalance wasn't too bad either, with direction providing a way to make the solution elegant.  In the end, I hope the additional testing I did on each main function paid off and that there weren't any major issues.