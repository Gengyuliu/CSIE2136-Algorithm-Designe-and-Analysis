#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <algorithm>
using namespace std;


typedef struct Element{
    int pos;
    int a;
    int c;
    int s;
}Element;





int main(int argc, char *argv[])
{
    Element *E = (Element*)malloc(7*sizeof(Element));
    memset(E, 0, 7*sizeof(E));
    for (int i = 0; i < 7; ++i){
        printf("%d %d %d %d\n", E[i].pos, E[i].a, E[i].c, E[i].s);
    }
    int i = 5;
    int j = 7;
    printf("%d\n", min(i, j));
    return 0;
}
