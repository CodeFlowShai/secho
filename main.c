#include <unistd.h>
#include <string.h>
#include <stdlib.h>
void out(char str[]) {
    write(1, str, strlen(str));
}
void err(char str[]) {
    write(2, str, strlen(str));
}

int main(int argc, char *argv[]) 
{
    int times = 1;
    char *s = NULL;
    int s_provided = 0;
    int outNl = 1;
    int reverse = 0;
    int opt;
    while ((opt = getopt(argc, argv, "n:s:rlh")) != -1) {
        switch (opt) {
            case 'n':
                times = atoi(optarg);
                break;
            case 's':
                s = optarg;
                s_provided = 1;
                break;
            case 'h':
                out("Usage: secho -s <string> [-n <number>] [-l] [-h]\nOptions:\n  -s <string>   Specify the string to print (required).\n  -n <number>   Repeat the string the specified number of times.\n  -l            Print all repetitions on the same line without newlines.\n  -h            Show this help message and exit.\n");
                exit(0);
            case 'l':
                outNl = 0;
                break;
            case 'r':
                reverse = 1;
                break;
            default:
                err("Invalid input!\nUsage: secho -s <string> [-n <number>] [-l] [-h]\nOptions:\n  -s <string>   Specify the string to print (required).\n  -n <number>   Repeat the string the specified number of times.\n  -l            Print all repetitions on the same line without newlines.\n  -h            Show this help message and exit.\n");
                exit(1);
        }
    }
    if (times <= 0) {
        times = 1;
    }
    if (!s_provided) {
        err("Error: -s <string> is required!\n");
        return 1;
    }
    char rev_s[strlen(s) + 1];
    if (reverse == 1) {
        for (int i = 0; i < strlen(s); i++) { 
            rev_s[i] = s[strlen(s) - 1 - i];
        }
        rev_s[strlen(s)] = 0;
    }

    for (int i = 0; i < times; i++) {
        if (reverse = 1) {
            out(rev_s);
        }
        else {
            out(s);
        }
        if (outNl == 1) {
            out("\n");
        }
    }
    if (outNl != 1) {
        out("\n");
    }
    return 0;
}
