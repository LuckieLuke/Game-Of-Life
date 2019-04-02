#include <stdio.h>
#include "simulation.h"
#include "reader.h"
#include "converter.h"

int main(int argc, char **argv)
{
  board b = readFile(argv);
  txtConvert(b, argv[1], 1);
  pngConvert(b, argv[1], 1);
}
