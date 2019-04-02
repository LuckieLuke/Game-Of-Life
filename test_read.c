#include <stdio.h>
#include <stdlib.h>
#include "simulation.h"
#include "reader.h"

int main(int argc, char **argv)
{
  board b = readFile(argv[1]);

  for (int i = 0; i < b->height; i++)
  {
    for (int j = 0; j < b->width; j++)
    {
      printf("%d ", b->life[i][j]);
    }
    printf("\n");
  }

  return 0;
}
