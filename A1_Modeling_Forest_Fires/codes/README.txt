README

Time: 09/07/2016
Author: Qi Zheng


1. There are two c source files within the folder:

1.1 The "step-wise_print-out.c" codes would print out the transient forest size (number of trees) and the average size (P) until that point at the end of each time step together with the step number. The form could be like:
Time Step Number		Transient Forest Size		Average Forest Size

Also, the average forsest size over the complete simulation period (1000 time steps) would be printed out at the very end.

You can change the F and G values at the global variable sections to test the codes with different growth parameter G and the ignition factor f. Number of time steps could be changed in the main function.


1.2 “P-g-f_study.c” codes would print out the average forest size (P) as a function of growth parameter G at F=0.01. You can change F values to view changes in P.



2. To compile and run the scource codes on Jinx:

2.1 Type in:
gcc step-wise_print-out.c -std=c99 -o myprog

2.2 If compilation was successful, executing ls should now show you a file called myprog 

2.3 Running the executable file can be done by typing in:
./myprog


You can replace the name "step-wise_print-out.c" in Step 2.1 with "P-g-f_study.c" and repeat the same process if you would like to run the other file.