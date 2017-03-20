#include <stdio.h>

char mem[1024] = {0};

char * readfile(char * name)
{
    FILE * f = fopen(name,"r");
    if (f == NULL) return NULL;
    fseek(f,0,SEEK_END);
    int size = ftell(f);
    char * res = (char *)malloc(size);
    if (res == NULL) return NULL;

    rewind(f);
    int pos = 0;
    while (1) {
        char ch = fgetc(f);
        if(feof(f)) break;
        if (ch == '\r') continue;
        res[pos++] = ch;
    }
    res[pos] = 0;
    fclose(f);
    return res;
}

int eval(char *code)
{
    int pos = 0;
    char * ptr = mem;
    char ch;

    while ((ch = code[pos++])) {
        if (ch == '>') ptr++;
        else if (ch == '<') ptr--;
        else if (ch == '+') (*ptr)++;
        else if (ch == '-') (*ptr)--;
        else if (ch == ',') (*ptr) = getchar();
        else if (ch == '.') printf("%c",*ptr);
        else if (ch == '[') {
            if (*ptr == 0) {
                while(code[pos++] != ']');
            }
        }
        else if (ch == ']') {
            if (*ptr != 0) {
                while (code[pos--] != '[');
                pos += 2;
            }
        }
    }
    return 0;
}

int main (int argc,char *argv[])
{
    char *code = readfile(argv[1]);
    return eval(code);
}
