#include <stdio.h>
#include <stdlib.h>

#include "simulation.h"
#include "converter.h"

int isDifferent(board b)
{
  int i, j;
  for (i = 1; i < b->height - 1; i++)
    for (j = 1; j < b->width - 1; j++)
      if (b->life[i][j] != b->copy[i][j])
        return 1;

  return 0;
}

void printBoard(board b)
{
  int i, j;
  for (i = 1; i < b->height - 1; i++)
  {
    for (j = 1; j < b->width - 1; j++)
    {
      printf("%d", b->life[i][j]);
    }
    printf("\n");
  }
}

board generate(board b, int n, int sbs, char *output)
{
  int x[] = {0, 1, 0, -1, 1, 1, -1, -1};
  int y[] = {-1, 0, 1, 0, -1, 1, 1, -1};
  int i, j, k, neighbours = 8;
  int alive = 0;
  int gennumber = 0;
  char c;

  copy(b);

  while (gennumber < n)
  {
    for (i = 1; i < b->height - 1; i++)
    {
      for (j = 1; j < b->width - 1; j++)
      {
        for (k = 0; k < neighbours; k++)
        {
          if (b->copy[i + y[k]][j + x[k]] == 1)
            alive++;
        }
        if (b->copy[i][j] == 0 && alive == 3)
          b->life[i][j] = 1;
        else if (b->copy[i][j] == 1 && (alive < 2 || alive > 3))
          b->life[i][j] = 0;

        alive = 0;
      }
    }

    if (sbs)
    {
     printBoard(b);
     printf("Want to save it?\ny for YES, n for NO\n");
     scanf("%c", &c);
     if (c == 'y')
     {
      txtConvert(b, output, gennumber + 1);
      pngConvert(b, output, gennumber + 1);
      c = getchar();
     }
     else
     {
      c = getchar();
     }
    }
    else
    {
      txtConvert(b, output, gennumber + 1);
      pngConvert(b, output, gennumber + 1);
    }

    if (!isDifferent(b))
    {
      printf("Board is still after %d generations.\n", gennumber + 1);
      break;
    }

    gennumber++;

    copy(b);
  }

  return b;
}

void copy(board b)
{
  int i, j;
  for (i = 0; i < b->height; i++)
    for (j = 0; j < b->width; j++)
      b->copy[i][j] = b->life[i][j];
}

void delete (board b)
{
  int i;
  for (i = 0; i < b->height; i++)
  {
    free(b->life[i]);
    free(b->copy[i]);
  }
  free(b->life);
  free(b->copy);
  free(b);
}
