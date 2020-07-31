/*** FileOperations -- modified for macOS computers
 ***
 ***/

#include "FileOperations.h"

int readHeightField(const char *fileName, int *width, int *depth, int heights[][MAX_DEPTH])
{
    FILE *inputFile;
    int nRead, i, j;
    
    printf("Opening height field file \"%s\" for input...\n", fileName);
    inputFile = fopen(fileName, "r");
    if (inputFile == NULL) {
        printf("Unable to open file for input\n");
        return GL_FALSE;
    }
    
    nRead = fscanf(inputFile, "%d %d", width, depth);
    if (nRead != 2) {
        printf(" Couldn't read width and height from file.");
        printf(" Width: %d, Height: %d\n", *width, *depth);
    }
    
    if(*width <= 0 || *depth <= 0) {
        printf("Invalid value for width or depth...");
    }
    
    
    printf("Reading heights...\n");
    
    for(j=0; j < *depth; j++) {
        for (i=0; i < *width; i++) {
            nRead = fscanf(inputFile, "%d", &heights[i][j]);
            if(nRead != 1)
                printf("Bad or incomplete height data.");
        }
    }
    
    
    fclose(inputFile);
    printf(" Height field complete.\n");
    return GL_TRUE; 
    
}


