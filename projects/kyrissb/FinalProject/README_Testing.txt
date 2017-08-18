Liz Coenen | Chris Glodosky | Brandon Kyriss
CS 362 - Summer 2017
Final Project - Part B

Partition Unit Tests and Random Tester:

Our partition tests and random tester are cotained within the file
URLValidatorTestSuite.java, in the src directory of URLValidatorCorrect
and URLValidatorInCorrect. Although we fixed the bugs we located, we reset
the fixes so you can see that errors that are identified by the patition
tests.

The partition tests are as follows:

public void testURIAuthorities()
public void testURIAuthorities()
public void testURIPorts()
public void testURIPaths()
public void testURIQueries()

The random tester is:

public void testFullURLs()

There are two global boolean variables that can be set prior to running
the test suite:

1) outputAll: 
	
- True = Every iteration of each test will output results to the console
         (not just failed tests). This was added to ensure that the random
         tester was actually testing all possible permutations and should
         should generally be set to false for readable output.
- False = Output lines are only printed when a test iteration fails.

2) runFullURLTest:

- True: The test suite runs all partition tests and the random tester.
- False: Only the partition tests will be run