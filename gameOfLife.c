#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

#include "reader.h"
#include "simulation.h"
#include "converter.h"

char *usage =
    "Usage: %s input-file output-directory [-n n_generations] [-s sbs_value]\n"
    "           - input-file is .txt file with first generation\n"
    "           - output-directory is a path to output files destination\n"
    "           - n_generations must be > 0, but < 9999\n"
    "           - if -n is not given, n_generations = 50\n"
    "           - -s is an step-by-step option\n"
    "           - sbs_value is to be non-zero number\n"
    "           - if executed with sbs_value = 0, treated like no -s flag\n";

int main(int argc, char **argv)
{
    int opt, sbs = 0;
    int n = 50;
    char *progname = malloc(sizeof(*progname) * (strlen(argv[0]) + 1));
    if (progname == NULL)
    {
        printf("Memory fail!\n");
        exit(EXIT_FAILURE);
    }
    progname = strcpy(progname, argv[0]);

    char *input = malloc(sizeof(char) * (strlen(argv[1]) + 1));
    if (input == NULL)
    {
        printf("Memory fail!\n");
        exit(EXIT_FAILURE);
    }
    input = strcpy(input, argv[1]);

    char *output = malloc(sizeof(char) * (strlen(argv[2]) + 1));
    if (output == NULL)
    {
        printf("Memory fail!\n");
        exit(EXIT_FAILURE);
    }
    output = strcpy(output, argv[2]);

    while ((opt = getopt(argc, argv, ":n:s:")) != -1)
    {
        switch (opt)
        {
        case 'n':
            n = atoi(optarg);
            break;
        case 's':
            sbs = atoi(optarg);
            break;
        default:
            fprintf(stderr, usage, progname);
            exit(EXIT_FAILURE);
        }
    }

    if (optind != argc - 2 || n > 9999)
    {
        fprintf(stderr, usage, progname);
        exit(EXIT_FAILURE);
    }

    board b = readFile(input);
    generate(b, n, sbs, output);
    delete (b);

    free(progname);
    free(input);
    free(output);

    return 0;
}
