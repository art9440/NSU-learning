#include <stdio.h>
#include <string.h>
#include <ctype.h>


void minInTail(char *str, int j, char change){   //Finding the minimum in the maximum
    char minn = 'A', temp;                       //in the tail and
    int minindex;                                //change with current number
    for (int i = j; i < strlen(str); i++)
        if (str[i] > change && str[i] < minn) {
            minn = str[i];
            minindex = i;
        }
    temp = str[j - 1];
    str[j - 1] = minn;
    str[minindex] = temp;
}


void tailReverse(char *str, int j){ //tail reversal
    char temp;
    for (int i = j, k = 0; k < (strlen(str) - 1 - j);i++, k++){
        temp = str[i];
        str[i] = str[strlen(str) - 1 - k];
        str[strlen(str) - 1 - k] = temp;
    }
}


int checkForDecrission(char * str){            //checking for the possibility of using
    for (int j = strlen(str) - 1; j > 0; j--)  //the Dijkstra algorithm
        if (str[j - 1] < str[j]) {
            return j;
        }
    return 0;
}


void Deikstra(char *str, int n){       //Enumeration of permutations according
    for (int i = 0; i < n; i++) {      // to Dijkstra 's algorithm
        int tailstart;
        if (checkForDecrission(str) == 0)
            exit(0);
        tailstart = checkForDecrission(str);
        minInTail(str, tailstart, str[tailstart - 1]);
        tailReverse(str, tailstart);
        printf("%s\n", str);
    }
}


int CheckforErrors(char *str){            //Check input for errors
    for (int i = 0;i < strlen(str); i++)
        if ((str[i] < "0" && str[i] > "9") ||
            (strchr(str,str[i]) - str != i)
            || isdigit(str[i]) == 0)
            return 0;
    return 1;
}


int main(){
    char str[10];
    int n;
    gets(str);
    scanf("%d", &n);

    if (CheckforErrors(str) == 0){
        printf("bad input");
        return 0;
    }

    Deikstra(str, n);


    return 0;
}
