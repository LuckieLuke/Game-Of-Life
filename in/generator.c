#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define RANDOMGENERATION "randomgeneration.txt"

int main(int argc, char **argv) {

    int height = argc > 1 ? atoi(argv[1]) : 50;
    int width = argc > 2 ? atoi(argv[2]) : 50;

    FILE *outputfile = fopen(RANDOMGENERATION, "w");

    srand(time(NULL));
    int randombool;
 	int i, j;

    fprintf(outputfile, "%d %d\n", height, width);

    for (i = 0; i < height; i++)
		{
        for (j = 0; j < width; j++)
			{
           	 	randombool = rand() % 2;
          	  	fprintf(outputfile, "%d", randombool);
       		}
    		fprintf(outputfile,"\n");
   	 	}
    fclose(outputfile);
    return 0;
}
