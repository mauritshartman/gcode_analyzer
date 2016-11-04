#include <arguments.h>

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>


static struct option long_options[] =
{
    {"file",        required_argument,  0,  'f'},
    {"version",     no_argument,        0,  'v'},
    {"help",        no_argument,        0,  'h'},
    {0, 0, 0, 0}
};


static void print_help(void)
{
    char *helpstring = 
    "Usage: gcode_analyze [options]\n"
    "Options:\n"
    "  -f, --file               GCode file to process.\n"
    "  -h, --help               This help message.\n"
    "  -v, -?, --version        Version information.\n";
    printf(helpstring);
}


void parse_options(gcode_options *options, int argc, char *argv[])
{
    int c, option_index;

    while (true) {
        option_index = 0;
        c = getopt_long(argc, argv, "f:hv?", long_options, &option_index);
        if (c == -1) { break; }

        switch (c) {
            case 'f':
                options->filename = optarg;
                break;
            case '?':
            case 'h':
                print_help(); exit(0);
            case 'v':
                printf("%s\n", GCODE_VERSION); exit(0);
            default:
                abort();
        }
    }

}