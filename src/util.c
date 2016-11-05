#include "util.h"

#include <string.h>
#include <ctype.h>


// Stores the trimmed input string into the given output buffer, which must be
// large enough to store the result.  If it is too small, the output is
// truncated.
size_t strip(char *out, size_t len, const char *str)
{
    const char *end;
    size_t out_size;

    if (len == 0) { return 0; }

    // Trim leading space
    while (isspace((unsigned char)*str)) { str++; }

    if (*str == 0) { // All spaces?
        *out = 0;
        return 1;
    }

    // Trim trailing space
    end = str + strlen(str) - 1;
    while(end > str && isspace((unsigned char)*end)) { end--; }
    end++;

    // Set output size to minimum of trimmed string length and buffer size minus 1
    out_size = (end - str) < len - 1 ? (end - str) : len - 1;

    // Copy trimmed string and add null terminator
    memcpy(out, str, out_size);
    out[out_size] = 0;

    return out_size;
}