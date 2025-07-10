#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_BUFFER_SIZE 100

const char* keywords[] = {
    "auto", "break", "case", "char", "const", "continue", "default",
    "do", "double", "else", "enum", "extern", "float", "for", "goto",
    "if", "int", "long", "register", "return", "short", "signed",
    "sizeof", "static", "struct", "switch", "typedef", "union",
    "unsigned", "void", "volatile", "while"
};
#define NUM_KEYWORDS (sizeof(keywords) / sizeof(keywords[0]))

int is_keyword(const char* str) {
    for (int i = 0; i < NUM_KEYWORDS; i++) {
        if (strcmp(str, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}


int is_comment_start(const char* str, int idx) {
    return (str[idx] == '/' && str[idx + 1] == '/');
}

int is_multiline_comment_start(const char* str, int idx) {
    return (str[idx] == '/' && str[idx + 1] == '*');
}

int is_multiline_comment_end(const char* str, int idx) {
    return (str[idx] == '*' && str[idx + 1] == '/');
}

int is_number(const char* str) {
    int has_dot = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '.') {
            if (has_dot) return 0;
            has_dot = 1;
        } else if (!isdigit(str[i])) {
            return 0;
        }
    }
    return 1;
}

int main() {
    FILE *file;
    char input[1000];
    char buffer[MAX_BUFFER_SIZE];
    int buffer_index = 0;
    int inside_multiline_comment = 0;

    file = fopen("input.txt", "r");
    if (file == NULL) {
        printf("Error! File is empty.\n");
        return 0;
    }


    printf("Reading input from file\n");

    while (fgets(input, sizeof(input), file) != NULL) {
        for (int i = 0; input[i] != '\0'; i++) {
            char ch = input[i];

            if (is_comment_start(input, i)) {
                while (input[i] != '\n' && input[i]  != '\0') {
                    i++;
                }
                continue;
            }

            if (inside_multiline_comment) {
                if (is_multiline_comment_end(input, i)) {
                    inside_multiline_comment = 0;
                    i++;
                }
                continue;
            }

            if (is_multiline_comment_start(input, i)) {
                inside_multiline_comment = 1;
                i++;
                continue;
            }
            if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '=' || ch == '>' || ch == '<' || ch == '!' || ch == '&' || ch == '|' || ch == '^') {
                if (buffer_index > 0) {
                    buffer[buffer_index] = '\0';
                    if (is_keyword(buffer)) {
                        printf("Keyword: %s\n", buffer);
                    } else if (is_number(buffer)) {
                        printf("Number: %s\n", buffer);
                    } else {
                        printf("Token: %s\n", buffer);
                    }
                    buffer_index = 0;
                }
                printf("Operator: %c\n", ch);
            }
            
            else if (ch == '{' || ch == '}' || ch == '(' || ch == ')') {
                if (buffer_index > 0) {
                    buffer[buffer_index] = '\0';
                    if (is_keyword(buffer)) {
                        printf("Keyword: %s\n", buffer);
                    } else if (is_number(buffer)) {
                        printf("Comstant: %s\n", buffer);
                    } else {
                        printf("Token: %s\n", buffer);
                    }
                    buffer_index = 0;
                }
                printf("Seperator: %c\n", ch);
            }
            else if (isalnum(ch) || ch == '.') {
                buffer[buffer_index++] = ch;
            }
            else if (ch == ' ' || ch == '\n' || ch == '\t') {
                if (buffer_index > 0) {
                    buffer[buffer_index] = '\0';
                    if (is_keyword(buffer)) {
                        printf("Keyword: %s\n", buffer);
                    } else if (is_number(buffer)) {
                        printf("Number: %s\n", buffer);
                    } else {
                        printf("Token: %s\n", buffer);
                    }
                    buffer_index = 0;
                }
            }
        }
    }

    if (buffer_index > 0) {
        buffer[buffer_index] = '\0';
        if (is_keyword(buffer)) {
            printf("Keyword: %s\n", buffer);
        } else if (is_number(buffer)) {
            printf("Number: %s\n", buffer);
        } else {
            printf("Token: %s\n", buffer);
        }
    }

    fclose(file);
    return 0;
}
