//Program Description : Matrix Multiplication using pthreads.
//Author : Christina Tsui
//Creation Date : 9/20/17

#include <iostream>
#include <fstream>
#include <time.h>
#include <pthread.h>
#include <stdio.h>
#include <cstdlib>
#include <cstring>
#include <string.h>
#include <unistd.h>

//Matrix
int arrayA [100000000];
int arrayB [100000000];
int arrayC [100000000];

//Row
int m1;
int m2;

//Column
int k1=0;
int k2=0;

//Misc
int matrixID;
int IDcount;
time_t timeStart;
time_t timeEnd;
unsigned long seconds;
unsigned long ms;

//prototypes
int readFile();
void outputC();
void *job(void *_i);

//main
int main(){
    
    timeStart = time(NULL);//Get the start time
    
    if (int i = readFile() == 0 ){//Call fundtion to read from file and place into matrix array
                        std::cout << "Error: check file for possible mathmatical error (k1 != m2), and or negative number.\n";
        return 0;}//Leave if there was a negative number
    
    unsigned int ints[k1];
    pthread_t    threads[k1];
    
    for (unsigned int i = 0; i < k1; ++i) {
        ints[i] = i;
        pthread_create(&threads[i], NULL, job, &ints[i]);
    }
    
    for (unsigned int i = 0; i < k1; ++i) {
        pthread_join(threads[i], NULL);
    }
    
    outputC();//Call function to output the matrix
    
    timeEnd = time(NULL);//Get the end time
    
    seconds = (timeEnd - timeStart);//Get total seconds
    ms = seconds * 1000;//Get milliseconds
    
    printf ("Total execution time using %i threads is %lu seconds, %lu milliseconds ", k1, seconds, ms);
    
    return 0;
}//end main

//-----------------------------------------------------------------
//void *job(void *_i)
//Desc: Matrix multiplication A x B = C. Values then place into arrayC.
//	Each row taken in will be multiplied against columns.
//	Multiplied values are then added together.
//Receives: unsigned int i,
//
//Returns: 0;
//-----------------------------------------------------------------
void *job(void *_i) {
    unsigned int i = *((unsigned int *) _i);
    
    int B = 0;
    int sum = 0;
    int columnC = 0;
    
    for(int allColumns = 0; allColumns < k1; allColumns++){
        
        for(int columnIndex = 0; columnIndex < m1; columnIndex++)
        {
            sum += (arrayA[(m1*i)+ columnIndex]) * arrayB[B];//Get's A
            B+=m2;
            
        }
        
        arrayC[(i*m2)+columnC] = sum;
        
        columnC++;
        B=columnC;
        sum = 0;
        
    }
    
    printf("Created Worker Thread %lu for row %d ", (unsigned long)pthread_self(), i);
    
    pthread_exit(0);
}

//-----------------------------------------------------------------
//int readFile()
//Desc: User input a file name, the file is opened
//	The information in the file is then stored into
//	MxK and the Matrix Arrays.
//Receives:
//
//Returns: 0;
//-----------------------------------------------------------------
int readFile(){
    std::string filename;
    std::fstream myfile;
    
    std::cout << "Please enter a file name to write: ";
    getline( std::cin, filename );
    
    
    myfile.open(filename.c_str());
    
    if(myfile.is_open()){//Check to see if file is open
        while (!myfile.eof()){//If open, start to extact till end of file
            
            myfile >> m1 >> k1;//get initial matrix MxK
            
            if(m1 < 0 || k1 < 0){//Check for negative numbers in m1 and k1
                return 0;
            }
            
            for(int j = 0; j < (m1*k1); j++){//Calculate the Matrix A area
                
                myfile >> arrayA[j];//Fill up Matrix A
                
                if(arrayA[j] < 0){//Check for negative numbers in Matrix A
                    return 0;
                }
            }
            
            myfile >> m2 >> k2;//get initial matrix MxK
            
            if(k1 != m2){//check if mathmaticall possible
                return 0;
            }
            
            if(m2 < 0 || k2 < 0){//Check for negative numbers in m2 and k2
                return 0;
            }
            
            for(int k = 0; k < (m2*k2); k++){//Calculate the Matrix B area
                
                myfile >> arrayB[k];//Fill up Matrix B
                
                if(arrayB[k] < 0){//Check for negative numbers in Matrix B
                    return 0;
                }
            }
        }
    }else
        std::cout << "Error loading file\n";
    
    
    myfile.close();//Close file
    return 1;
}

//-----------------------------------------------------------------
//void outputC()
//Desc: User given the choice to output A x B = C .
//	If user chooses to output then it's on the screen.
//	Else it is saved into a file MatrixC.txt
//Receives: unsigned int i,
//
//Returns: 0;
//-----------------------------------------------------------------
void outputC(){
    char userChoice;
    int counter = 0;
    
    std::cout << "\nMatrix multiplication complete, would you like to save the data to a file?Y/N\n";
    std::cin >> userChoice;
    
    if(userChoice == 'Y' || userChoice == 'y')//Store data to file
    {
        
        std::ofstream myfile ("MatrixC.txt");//Create the file
        if (myfile.is_open())//Check if open
        {
            myfile << "Matrix A:\n";
            for(int count = 0; count < (m1*k1); count ++)//Size of matrix
            {
                myfile << arrayA[count] << " " ;//Store to file matrix value
                counter++;
                
                if(counter == (m1))//endline @ the correct value
                {
                    myfile << "\n";
                    counter = 0;
                }
            }
            counter = 0;
            
            myfile << "Matrix B:\n";
            for(int count = 0; count < (m2*k2); count ++){//Size of matrix
                
                myfile << arrayB[count] << " " ;//Store to file the matrix value
                counter++;
                
                if(counter == (m2))//Endline @ the correct value
                {
                    myfile << "\n";
                    counter = 0;
                }
            }
            counter = 0;
            
            //Thread ID
            //Created worker  thread  threadID  for  row
            myfile << "Matrix C = A x B: \n";//output matrixC
            for(int count = 0; count < (k1*m2); count ++){//Size of matrix
                
                myfile << arrayC[count] << " " ;//Outut matrix values
                counter++;
                
                if(counter == (k1))//Endline @ the correct value
                {
                    myfile << "\n";
                    counter = 0;
                }
            }
            
        }
        else
            std::cout << "Unable to open file";
        
    }
    else if(userChoice == 'N' || userChoice == 'n'){
        
        std::cout<< "Matrix A:\n";
        for(int count = 0; count < (m1*k1); count ++)//Size of matrix
        {
            std::cout <<arrayA[count] << " " ;//Out put matrix values
            counter++;
            
            if(counter == (m1))//Endline @ the correct value
            {
                std::cout << "\n";
                counter = 0;
            }
        }
        counter = 0;
        
        std::cout << "Matrix B:\n";
        for(int count = 0; count < (m2*k2); count ++){//Size of matrix
            
            std::cout << arrayB[count] << " " ;//Outut matrix values
            counter++;
            
            if(counter == (m2))//Endline @ the correct value
            {
                std::cout << "\n";
                counter = 0;
            }
        }
        counter = 0;
        
        //Thread ID
        //Created worker  thread  threadID  for  row
        std:: cout << "Matrix C = A x B: \n";//output matrixC
        for(int count = 0; count < (k1*m2); count ++){//Size of matrix
            
            std::cout << arrayC[count] << " " ;//Outut matrix values
            counter++;
            
            if(counter == (k1))//Endline @ the correct value
            {
                std::cout << "\n";
                counter = 0;
            }
        }
    }
    else
        std:: cout << "\nInvalid input, data has been saved to file MatrixC.txt.\n";
}
