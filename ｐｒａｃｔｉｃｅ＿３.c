#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char expr[32];
char boolean[32];
int pos=0;

int evaluate_prefix(){
    if(pos==strlen(boolean)) return;
    int value1,value2;
    char c,op1,op2;
    c=boolean[pos++];
    if(c=='&'||c=='|'){
        op1=evaluate_prefix();
        op2=evaluate_prefix();
        if(op1-'0')
            value1=1;
        else
            value1=0;
        if(op2-'0')
            value2=1;
        else
            value2=0;

        if(c=='&')
            return (value1&value2)+'0';
        else
            return (value1|value2)+'0';
    }
    else
        return c;
}

int main(){
    scanf("%s",expr);
    for(int i=0;i<16;i++){
        strcpy(boolean,expr);
        for(int j=0;j<strlen(expr);j++){
            if(boolean[j]=='A')
                boolean[j]=((i>>3)&1)+'0';
            else if(boolean[j]=='B')
                boolean[j]=((i>>2)&1)+'0';
            else if(boolean[j]=='C')
                boolean[j]=((i>>1)&1)+'0';
            else if(boolean[j]=='D')
                boolean[j]=(i&1)+'0';
        }
        printf("%d %d %d %d ",((i>>3)&1),((i>>2)&1),((i>>1)&1),i&1);
        printf("%d",evaluate_prefix()-'0');
        printf("\n");
        pos=0;
    }
}
