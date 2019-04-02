#include <stdio.h>
#include <stdlib.h>
#include "simulation.h"
#include "reader.h"

int main(int argc, char **argv)
{
  board b = readFile(argv[1]);
  b = generate(b, atoi(argv[3]), 0, argv[2]);
  return 0;
}
