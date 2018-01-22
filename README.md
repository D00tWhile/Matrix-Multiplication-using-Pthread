# Matrix-Multiplication-using-Pthread
The program (Matrix) uses input from the user to create and solve Matrix multiplication. 

*******************************************************
*  Name      :   Christina Tsui      
*  Student ID:    106060236            
*  Class     :  CSCI 3453           
*  LAB#       :      1            
*  Due Date  :  September 25, 2076
*******************************************************


                 Read Me


*******************************************************
*  Description of the program
*******************************************************

The program (Matrix) uses input from the user to create two
Matrix. The matrix data is stored and used A x B = C. 
Each row of the result matrix is done via a separate worker thread. 
The data is saved to a file or to the user output. 
The run time of the program and the worker thread IDs are also 
provided to the user. 

*******************************************************
*  Source files
*******************************************************

Name:  OSLab1.cpp
	Main program.  Sends user to the main function.  
   
*******************************************************
*  Circumstances of programs
*******************************************************

   The program runs successfully.  
   
   The program was developed and tested on both Mac using XCode.
   It was compiled, run, and tested on gcc ouray.cudenver.edu and
   engrlab.cudenver.edu


*******************************************************
*  How to build and run the program
*******************************************************

1. Uncompress the homework.  The homework file is compressed.  
   To uncompress it use the following commands 
       % unzip [homework_filename]

   Now you should see a directory named homework with the files:
        main.cpp
        
2. Build the program.

    Change to the directory that contains the file by:
    % cd [directory_name] 

    Compile the program by:
    % make

3. Run the program by:
   % ./[file_name]  (e.g., ./Matrix)

4. Delete the obj files, executables, and core dump by
   %./make clean
