#include <stdio.h>
#include <stdlib.h>

#include "reader.h"
#include "simulation.h"

int checkFile(char *input)
{
  FILE *inputfile = fopen(input, "r");
  int height = -1;
  int width = -1;
  fscanf(inputfile, "%d", &height);
  fscanf(inputfile, "%d", &width);
  fclose(inputfile);
  if (height > 0 && width > 0)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

board readFile(char *input)
{
  if (!checkFile(input))
  {
    printf("Wrong board size!\n");
    exit(EXIT_FAILURE);
  }

  FILE *inputfile = fopen(input, "r");
  if (inputfile == NULL)
  {
    printf("Cannot open %s file!\n", input);
    exit(EXIT_FAILURE);
  }

  board b = NULL;
  b = malloc(sizeof(struct b));
  if (b == NULL)
  {
    printf("Memory fail!\n");
    exit(EXIT_FAILURE);
  }

  fscanf(inputfile, "%d", &(b->height));
  fscanf(inputfile, "%d", &(b->width));

  int i, j;
  i = fgetc(inputfile);

  b->width += 2;
  b->height += 2;

  b->life = NULL;
  b->copy = NULL;
  b->life = malloc(b->height * sizeof(int *));
  b->copy = malloc(b->height * sizeof(int *));

  if (b->life == NULL || b->copy == NULL)
  {
    printf("Memory fail!\n");
    exit(EXIT_FAILURE);
  }

  for (j = 0; j < b->height; j++)
  {
    b->life[j] = NULL;
    b->copy[j] = NULL;
  }

  for (j = 0; j < b->height; j++)
  {
    b->life[j] = malloc(b->width * sizeof(int));
    if (b->life[j] == NULL)
    {
      printf("Memory fail!\n");
      exit(EXIT_FAILURE);
    }

    b->copy[j] = malloc(b->width * sizeof(int));
    if (b->copy[j] == NULL)
    {
      printf("Memory fail!\n");
      exit(EXIT_FAILURE);
    }
  }

  for (i = 0; i < b->width; i++)
  {
    b->life[0][i] = 0;
    b->life[b->height - 1][i] = 0;
  }

  for (i = 0; i < b->height; i++)
  {
    b->life[i][0] = 0;
    b->life[i][b->width - 1] = 0;
  }

  int temp;

  for (i = 1; i < b->height - 1; i++)
  {
    for (j = 1; j < b->width - 1; j++)
    {
      if (!feof(inputfile))
      {
        temp = fgetc(inputfile);
        if (temp == 9 || temp == 10 || temp == 11 || temp == 13 || temp == 32)
        {
          j--;
        }
        else
        {
          if (temp == 49)
          {
            b->life[i][j] = 1;
          }
          else
          {
            b->life[i][j] = 0;
          }
        }
      }
      else
      {
        b->life[i][j] = 0;
      }
    }
  }

  fclose(inputfile);
  return b;
}
