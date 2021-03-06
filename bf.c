#include <stdio.h>
#define MEMLEN 1024
/*our memery */
char mem[MEMLEN] = {0};

/*get source code */
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

/* evel inter code */
int eval(char *code)
{
    if (!code) return 0;
    int ip = 0;
    char * ptr = mem;
    char ch;

    while ((ch = code[ip++])) {
        if (ch == '>') ptr++;
        else if (ch == '<') ptr--;
        else if (ch == '+') (*ptr)++;
        else if (ch == '-') (*ptr)--;
        else if (ch == ',') (*ptr) = getchar();
        else if (ch == '.') printf("%c",*ptr);
        else if (ch == '[') {
            if (*ptr == 0) {
                while(code[ip++] != ']');
            }
        }
        else if (ch == ']') {
            if (*ptr != 0) {
                while (code[ip--] != '[');
                ip += 2;
            }
        }
        if (ptr < mem || ptr > (mem+MEMLEN-1))
        {
            printf("out of memery[%ld]\n",ptr-mem);
            return 0;
        }
    }
    return 0;
}

int main (int argc,char *argv[])
{
    char *code = readfile(argv[1]);
    return eval(code);
}
