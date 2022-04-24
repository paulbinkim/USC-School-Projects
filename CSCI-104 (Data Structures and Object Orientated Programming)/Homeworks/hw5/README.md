# Paul Kim, pbkim@usc.edu, Homework 5 (Code)

My program creates a Hashtable <string, T> data structure with quadratic probing for collision resolution in the file Hashtable.h. We only use strings made of lowercase letters, and no other characters. 

For the second problem, using a variable Hashtable size of 365, we test/confirm the Birthday Paradox. To do this, we run a test (10000) times that adds a randomly generated string into the hash table, and see if the first probe occurs under 23 times. After generating the tests, we see/conclude that approximately 50.7% of the time (varies between 0.5 - 0.51), the Birthday Paradox proves true and a first probe occurs in 23 things or less.

To run the test, "make" the file using the provided makefile, and run ./test

EX Outputs:
0.5092
0.5077
0.5023
0.5104
0.5052
0.4961
0.5154
0.5024

Roughly we get around "Approximately" 0.507

For the second problem (part 2), I pursued the "Ruin Quadratic Probing" idea, and found a sequence of inputs that causes the program to hang (provided a segmentation fault error). This should occur because we initially set the Hashtable to size 12, which is not a prime number (a requirement is the size should be prime), and since there are no more indexes that quadratic probing can access, seg fault occurs.

The following sequence of strings are in the code file "test2.cpp" stored in a character wordBank.

The sequences are a set of very similar strings "a", "aa", "aaa", "aaaa", "aaaaa", "aaaaaa".