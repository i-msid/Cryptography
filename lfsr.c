#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>

// 10-bit LFSR with feedback polynomial x^10 + x^3 + 1
#define period 1026
int s[10];

void loadlfsr(){
     int i;
     for(i=0;i<10;i++) s[i]=!(drand48() < 0.5);
}
int lfsr(){
    int i,out,feed;
    feed=s[0]^s[7];
    out=s[0];
    for(i=0; i<9;i++) s[i]=s[i+1];
    s[9]=feed;
    return(out);
}
bool iseq(int s[],int init[]){
    for(int i=0;i<10;i++){
        if(s[i]!=init[i]){
            return false;
        }
    }
    return true;
}

int main(){
    int i;
    int init[10];
    srand48(time(NULL));
    loadlfsr();
    printf("Printing initial state\n");
    for(i=0;i<10;i++){
       printf("%d ",s[i]);
       init[i] = s[i];
    }
    //Printing output till period
    int count = 0;
    printf("\nPrinting output bits\n");
    while(!iseq(s,init)){
    //    printf("%d ",lfsr());
        lfsr();
        count++;
    }
    printf("period = %d\n",count);
    // for(i=0;i<period;i++){
    //    printf("%d ",lfsr());
    // printf("\nCheck repeatation\n");
    // printf("Printing state after 2^10-1 clocking\n");
    // for(i=0;i<10;i++)
    //    printf("%d ",s[i]);
    // printf("\nPrinting output bits\n");
    // for(i=0;i<period-1;i++)
    //    printf("%d ",lfsr());
    // printf("\n");
}