#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <png.h>

#include "simulation.h"


void txtConvert(board b, char *output, int gennumber)
{
  char *c = malloc(sizeof(*c) * 5);
  char *filename = malloc(sizeof(*filename) * (strlen(output) + 11));
  if (filename == NULL)
  {
    printf("Problem with file!\n");
    exit(EXIT_FAILURE);
  }
  filename[strlen(output)] = '\0';

  if (filename == NULL || c == NULL)
  {
    printf("Memory fail!\n");
    exit(EXIT_FAILURE);
  }

  int tmp = gennumber;
  int n = 3;
  c[4] = '\0';
  while (tmp != 0)
  {
    c[n] = '0' + (tmp % 10);
    tmp /= 10;
    n--;
  }
  while (n + 1 != 0)
  {
    c[n] = '0';
    n--;
  }

  filename = strcpy(filename, output);
  filename = strcat(filename, "/");
  filename = strcat(filename, c);
  filename = strcat(filename, ".txt");

  FILE *outputfile = fopen(filename, "w");
  if (outputfile == NULL)
  {
    printf("Cannot open %s file\n", filename);
    fclose(outputfile);
    exit(EXIT_FAILURE);
  }

  int i, j;

  fprintf(outputfile, "%d %d\n", b->height - 2, b->width - 2);

  for (i = 1; i < b->height - 1; i++)
  {
    for (j = 1; j < b->width - 1; j++)
    {
      fprintf(outputfile, "%d", b->life[i][j]);
    }
    fprintf(outputfile, "\n");
  }
  fclose(outputfile);
  free(c);
  free(filename);
}

void pngConvert(board b, char *output, int gennumber)
{
  int x, y;

  int width, height;
  png_byte color_type;
  png_byte bit_depth;

  png_structp png_ptr;
  png_infop info_ptr;
  png_bytep *row_pointers;

  width = b->width - 2;
  height = b->height - 2;
  bit_depth = 8;
  color_type = PNG_COLOR_TYPE_GRAY;

  row_pointers = (png_bytep *)malloc(sizeof(png_bytep) * height);
  for (y = 0; y < height; y++)
    row_pointers[y] = (png_byte *)malloc(sizeof(png_byte) * width);

  for (y = 0; y < height; y++)
  {
    png_byte *row = row_pointers[y];
    for (x = 0; x < width; x++)
    {
      row[x] = b->life[y + 1][x + 1] == 1 ? 0 : 255;
    }
  }

  char *c = malloc(sizeof(*c) * 5);
  char *filename = malloc(sizeof(*filename) * (strlen(output) + 11));
  if (filename == NULL)
  {
    printf("Problem with file!\n");
    exit(EXIT_FAILURE);
  }
  filename[strlen(output)] = '\0';

  if (filename == NULL || c == NULL)
  {
    printf("Memory fail!\n");
    exit(EXIT_FAILURE);
  }

  int tmp = gennumber;
  int n = 3;
  c[4] = '\0';
  while (tmp != 0)
  {
    c[n] = '0' + (tmp % 10);
    tmp /= 10;
    n--;
  }
  while (n + 1 != 0)
  {
    c[n] = '0';
    n--;
  }

  filename = strcpy(filename, output);
  filename = strcat(filename, "/");
  filename = strcat(filename, c);
  filename = strcat(filename, ".png");

  FILE *fp = fopen(filename, "wb");
  if (!fp)
    printf("[write_png_file] Cannot open %s file\n", filename);

  png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

  if (!png_ptr)
    printf("[write_png_file] png_create_write_struct\n");

  info_ptr = png_create_info_struct(png_ptr);
  if (!info_ptr)
    printf("[write_png_file] png_create_info_struct failed\n");

  if (setjmp(png_jmpbuf(png_ptr)))
    printf("[write_png_file] Error during init_io\n");

  png_init_io(png_ptr, fp);

  if (setjmp(png_jmpbuf(png_ptr)))
    printf("[write_png_file] Error during writing header\n");

  png_set_IHDR(png_ptr, info_ptr, width, height,
               bit_depth, color_type, PNG_INTERLACE_NONE,
               PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

  png_write_info(png_ptr, info_ptr);

  if (setjmp(png_jmpbuf(png_ptr)))
    printf("[write_png_file] Error during writing bytes\n");

  png_write_image(png_ptr, row_pointers);

  if (setjmp(png_jmpbuf(png_ptr)))
    printf("[write_png_file] Error during end of write\n");

  png_write_end(png_ptr, NULL);
  png_destroy_write_struct(&png_ptr, &info_ptr);

  for (y = 0; y < height; y++)
    free(row_pointers[y]);
  free(row_pointers);

  free(c);
  free(filename);
  fclose(fp);
}
