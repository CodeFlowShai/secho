#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void out(char str[]) {
    write(1, str, strlen(str));
}

void err(char str[]) {
    write(2, str, strlen(str));
}

void strlower(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = tolower(str[i]);
    }
}

int main(int argc, char *argv[]) {
    int times = 1;
    char *s = NULL;
    int s_provided = 0;
    int outNl = 1;
    int reverse = 0;
    int opt;
    char c[3] = "0";

    while ((opt = getopt(argc, argv, "n:s:c:rlh")) != -1) {
        switch (opt) {
            case 'n':
                times = atoi(optarg);
                break;
            case 's':
                s = optarg;
                s_provided = 1;
                break;
            case 'c':
                strlower(optarg);
                if (strcmp(optarg, "red") == 0) strcpy(c, "31");
                else if (strcmp(optarg, "green") == 0) strcpy(c, "32");
                else if (strcmp(optarg, "yellow") == 0) strcpy(c, "33");
                else if (strcmp(optarg, "blue") == 0) strcpy(c, "34");
                else if (strcmp(optarg, "magenta") == 0) strcpy(c, "35");
                else if (strcmp(optarg, "cyan") == 0) strcpy(c, "36");
                else if (strcmp(optarg, "white") == 0) strcpy(c, "37");
                else {
                    err("Invalid color!\nUsage: secho -s <string> [-n <number>] [-l] [-h] [-r] [-c <color>]\n");
                    return 1;
                }
                break;
            case 'h':
                out("Usage: secho -s <string> [-n <number>] [-l] [-h] [-r] [-c <color>]\n");
                exit(0);
            case 'l':
                outNl = 0;
                break;
            case 'r':
                reverse = 1;
                break;
            default:
                err("Invalid input!\nUsage: secho -s <string> [-n <number>] [-l] [-h] [-r] [-c <color>]\n");
                return 1;
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

    char ansi_code[20];
    strcpy(ansi_code, "\e[");
    strcat(ansi_code, c);
    strcat(ansi_code, "m");

    for (int i = 0; i < times; i++) {
        out(ansi_code);
        if (reverse == 1) {
            out(rev_s);
        } else {
            out(s);
        }
        out("\e[0m");
        if (outNl == 1) {
            out("\n");
        }
    }
    if (outNl != 1) {
        out("\n");
    }
    return 0;
}
