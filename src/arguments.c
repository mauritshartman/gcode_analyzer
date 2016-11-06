#include <arguments.h>

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <math.h>


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


/* Determine the feedrate from the JSON profile */
static void parse_profile_feedrate(gcode_options *options)
{
    float fr_x, fr_y;
    bool fr_x_found = false, fr_y_found = false;
    json_t *axes, *axis, *speed;

    if ((axes = json_object_get(options->profile, "axes")) != NULL) {     // Axes object is specified
        // Retrieve x axis speed:
        if ((axis = json_object_get(axes, "x")) != NULL) {
            if ((speed = json_object_get(axis, "speed")) != NULL) {
                fr_x = json_real_value(speed);
                fr_x_found = true;
            }
        }
        
        // Retrieve y axis speed:
        if ((axis = json_object_get(axes, "y")) != NULL) {
            if ((speed = json_object_get(axis, "speed")) != NULL) {
                fr_y = json_real_value(speed);
                fr_y_found = true;
            }
        }
    }

    if (fr_x_found && fr_y_found) {
        options->feedrate = fminf(fr_x, fr_y);
        printf("Parsed X and Y feedrates\n");
    }
    else if (fr_x_found && !fr_y_found) {
        options->feedrate = fr_x;
        printf("Parsed X feedrate\n");
    }
    else if (!fr_x_found && fr_y_found) {
        options->feedrate = fr_y;
        printf("Parsed X feedrate\n");
    }
}


/* */
static void parse_profile_offsets(gcode_options *options)
{
    json_t *extruder, *offset_array, *offset, *val1, *val2;
    char buf[64];
    uint16 i;

    if ((extruder = json_object_get(options->profile, "extruder")) != NULL) {
        if ((offset_array = json_object_get(extruder, "offsets")) != NULL) {
            if (json_is_array(offset_array)) {
                // Fetch the offset for the two extruders:
                for (i = 0; i < 2; i++) {
                    if ((offset = json_array_get(offset_array, i)) != NULL) {  // Should be an X, Y tuple
                        val1 = json_array_get(offset, 0);
                        val2 = json_array_get(offset, 1);
                        if (val1 != NULL && val2 != NULL) {
                            options->offsets[i] = vector3D_init(
                                (float)json_real_value(val1),
                                (float)json_real_value(val2),
                                0.0);
                            printf("Parsed extruder %d offsets: %s\n", i, vector3D_str(options->offsets[i], buf, sizeof(buf)));
                        }
                        else { return; }
                    }
                }
            }
        }
    }
}


/* Parse a given JSON file with printer profiles
 * http://docs.octoprint.org/en/master/api/printerprofiles.html#profile
 */
static void parse_profile(gcode_options *options, const char *profile_fname)
{
    json_t *root, *name;
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

    // Parse feedrate and offsets:
    parse_profile_feedrate(options);
    parse_profile_offsets(options);

    // Display basic profile information:
    name = json_object_get(root, "name");
    if (json_is_string(name)) {
        printf("Parsed printer profile '%s'\n", json_string_value(name));
    }
}


/* Default options */
static void set_option_defaults(gcode_options *options)
{
    options->output = JSON;
    options->profile = NULL;
    options->feedrate = 2000;       // some somewhat sane default if axes speeds are insane...
    options->offsets[0] = NULL;
    options->offsets[1] = NULL; 
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