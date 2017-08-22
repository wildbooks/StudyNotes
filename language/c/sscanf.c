#include <stdio.h>

/*
 *  sscanf巧妙移位
 * */
int main(void)
{
    int i;
    char buf[]="11 12 13 14";
    char *buffer=buf;
    unsigned int value;
    int  ret;

    printf("%s\n", buffer);
    for (i = 0; i <4 ; i++) {
        //ret = sscanf((char *)buffer, "%x,%s", &value, buffer);
        ret = sscanf((char *)buffer, "%x", &value);
        buffer+=3;
        printf("%x\tret=%d\n", value, ret);
        if (ret <= 0)
            break;
    }

    return ret;
}
