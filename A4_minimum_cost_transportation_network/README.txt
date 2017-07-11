/**************************************************************************/
/*					README					   */
/* All docs, please refer to the  
/***********************4321`	AQWSEDRTYUIOPZA[]\**************************************************/azXDCFVBNJMK,L.;/'


I. This software set includes two parts:
1. Codes to compute MST for a given graph
2. Codes to compute the new MST when a new edge has been added


II. There are two folders:
1. "src" folder contains all source files (codes)
2. "data" folder contains all input graphs (.gr files). The output (computed) new graphs (.txt files) will also be placed in the "data" folder.

III. Input and Output
1. In the first part, "compute_MST.c" will take a "name.gr" graph file as input file, and output the MST graph named as "name_MST.txt" in the same "data" folder;
2. In the second part, "reCompute.c" will take the output file (automatically named as "name_MST.txt" by the codes in the first parts) from part one, and the new edge data from the "new_edge.txt" file, and output the updated MST graph named as "name_MST_new_edge.txt" in the same folder.

IV. New Edges
The "new_edge.txt" file contains the new edge (format: u, v, w)to be added to the origianl graph, you can change the data to create a new edge to be added and run reCompute.c on any computed MST graph to get an updated MST graph. 


V. Command Line
The command lines for running the software for both parts will take an argument of the input file name. So use the following command line to execute the program (in Windows):
-------------------------------------------------------------------------------------------------------------------------------
For Part 1:
gcc compute_MST.c -o compute_MST
.\compute_MST input_graph_name(without file extension!)
-------------------------------------------------------------------------------------------------------------------------------
For Part 2:
gcc reCompute.c -o  reCompute
.\reCompute MSTgraph_name


/************************************************************/
/*  			COMMAND LINE EXAMPLES		   	    */
/************************************************************/
Part 1
-------------- -------------------------------------------------------------------------
gcc compute_MST.c -o compute_MST				    
.\compute_MST rmat1		

Part 2
---------------------------------------------------------------------------------------
gcc reCompute.c -o reCompute
.\reCompute rmat1_MST




The codes should work well. Feel free to shoot me an email (qzheng61@gatech.edu) if you should have any questions, or if any problem occurs! Thank you!

