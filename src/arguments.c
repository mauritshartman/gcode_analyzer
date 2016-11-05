#include <arguments.h>

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>


static struct option long_options[] =
{
    {"file",        required_argument,  0,  'f'},
    {"version",     no_argument,        0,  'v'},
    {"help",        no_argument,        0,  'h'},
    {"output",      required_argument,  0,  'o'},
    {0, 0, 0, 0}
};


static void print_help(void)
{
    char *helpstring = 
    "Usage: gcode_analyze [options]\n"
    "Options:\n"
    "  -f, --file               GCode file to process.\n"
    "  -h, --help               This help message.\n"
    "  -o, --output             Output format (JSON, XML)\n"
    "  -v, -?, --version        Version information.\n";
    printf(helpstring);
}


static void set_option_defaults(gcode_options *options)
{
    options->output = JSON;
}


void parse_options(gcode_options *options, int argc, char *argv[])
{
    int c, option_index;

    set_option_defaults(options);

    while (true) {
        option_index = 0;
        c = getopt_long(argc, argv, "f:ho:v?", long_options, &option_index);
        if (c == -1) { break; }

        switch (c) {
            case 'f':
                options->filename = optarg;
                break;
            case '?':
            case 'h':
                print_help(); exit(0);
            case 'o':
                if (!strcmp(optarg, "JSON")) { options->output = JSON; }
                else if (!strcmp(optarg, "XML")) { options->output = XML; }
                else {
                    fprintf(stderr,"Incorrect output format %s\n", optarg);
                    exit(EXIT_FAILURE);
                }
                break;
            case 'v':
                printf("%s\n", GCODE_VERSION); exit(0);
            default:
                abort();
        }
    }
}