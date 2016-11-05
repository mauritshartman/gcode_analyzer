#include <arguments.h>

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>


static struct option long_options[] =
{
    {"profile",      required_argument,  0,  'p'},
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
    "  -p, --profile            Configuration file with profile settings.\n"
    "  -f, --file               GCode file to process.\n"
    "  -h, --help               This help message.\n"
    "  -o, --output             Output format (JSON, XML)\n"
    "  -v, -?, --version        Version information.\n";
    printf(helpstring);
}


/* Parse a given JSON file with printer profiles
 * http://docs.octoprint.org/en/master/api/printerprofiles.html#profile
 */
static void parse_profile(gcode_options *options, const char *profile_fname)
{
    json_t *root, *data, *name;
    json_error_t error;
    FILE *profile_file = fopen(profile_fname, "r");

    // Try to read and parse the JSON printer profile file:
    if (!profile_file) {
        fprintf(stderr,"Unable to open printer profile file %s\n", profile_fname);
        exit(EXIT_FAILURE);
    }
    root = json_loadf(profile_file, 0, &error);     // No flags passed - default behavior
    if (!root) {
        fprintf(stderr, "Parsing error in printer profile file: on line %d: %s\n", error.line, error.text);
        exit(EXIT_FAILURE);
    }
    fclose(profile_file);
    options->profile = root;

    // Display basic profile information:
    name = json_object_get(root, "name");
    if (json_is_string(name)) {
        printf("Successfully parsed printer profile '%s'\n", json_string_value(name));
    }
}


/* Default options */
static void set_option_defaults(gcode_options *options)
{
    options->output = JSON;
    options->profile = NULL;
}


/* Parse all given commandline options: */
void parse_options(gcode_options *options, int argc, char *argv[])
{
    int c, option_index;

    set_option_defaults(options);

    while (true) {
        option_index = 0;
        c = getopt_long(argc, argv, "p:f:ho:v?", long_options, &option_index);
        if (c == -1) { break; }

        switch (c) {
            case 'p':
                parse_profile(options, optarg);
                break;
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