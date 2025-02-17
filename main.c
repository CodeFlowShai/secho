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

void usage() {
    err("Usage: secho -s <string> [-n <number>] [-l] [-h] [-r] [-c <color>]\n");
}

int checkpipe() {
    if (!isatty(STDOUT_FILENO)) {
        return 1;
    }
    if (!isatty(STDERR_FILENO)) {
        return 1;
    }
    return 0;
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
    int c_used = 0;
    int wave = 0;
    int wave_direction = 0;
    int wave_space = -1;
    while ((opt = getopt(argc, argv, "n:s:c:rlhw")) != -1) {
        switch (opt) {
            case 'n':
                times = atoi(optarg);
                break;
            case 's':
                s = optarg;
                s_provided = 1;
                break;
            case 'c':
                c_used = 1;
                strlower(optarg);
                if (strcmp(optarg, "red") == 0) strcpy(c, "31");
                else if (strcmp(optarg, "green") == 0) strcpy(c, "32");
                else if (strcmp(optarg, "yellow") == 0) strcpy(c, "33");
                else if (strcmp(optarg, "blue") == 0) strcpy(c, "34");
                else if (strcmp(optarg, "magenta") == 0) strcpy(c, "35");
                else if (strcmp(optarg, "cyan") == 0) strcpy(c, "36");
                else if (strcmp(optarg, "white") == 0) strcpy(c, "37");
                else {
                    err("Invalid color!\n");
                    usage();
                    exit(1);
                }
                if (checkpipe() != 0) {
                    c_used = 0;
                }
                break;
            case 'h':
                usage();
            exit(0);
            case 'l':
                outNl = 0;
                break;
            case 'r':
                reverse = 1;
                break;
            case 'w':
                wave = 1;
                break;
            default:
                err("Invalid input!\n");
                usage();
                exit(1);
            }
    }

    if (times <= 0) {
        times = 1;
    }
    if (!s_provided) {
        err("Error: -s <string> is required!\n");
        exit(1);
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
        if (c_used == 1) {
            out(ansi_code);
        }
        if (wave == 1) {
            if (wave_space <= 0) {
                wave_direction = 1;
            } else if (wave_space >= 3) {
                wave_direction = 0;
            }
            if (wave_direction == 1) {
                wave_space++;
            } else {
                wave_space--;
            }
            for (int i = 0; i < wave_space; i++) {
                out(" ");
            }
        }        
        if (reverse == 1) {
            out(rev_s);
        } else {
            out(s);
        }
        if (c_used == 1) {
            out("\e[0m");
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