// !test format_string_error
// !test warn_format_string_error
#include <cstdio>

int main(int argc, char *argv[]) {
    char buffer[100];
    char format[200]= "Hello!";

    printf("%s", format);

    return 0;
}