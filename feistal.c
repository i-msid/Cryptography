// author : Siddharth Mani Tiwari : 201851126
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

long long power(long long a, long long b) {
    if (b == 0)
        {return 1;}
    long long res = power(a, b / 2);
    if (b % 2)
        {return res * res * a;}
    else
       { return res * res;}
}


void converter(unsigned long long int x, int arr[])
{
    int curr=0;
    while(x!=0){
        arr[curr]=x%2;
        x=x>>1;
        curr++;
    }
}
void Sbox(int temp,int tarr[]){
    temp=(temp+1)%16; int curr=0;
    while(temp!=0){
        tarr[curr]=temp%2;
        temp=temp>>1;
        curr++;
    }
}


unsigned long long F(int L0[],int R0[],int key[],int L1[],int R1[]){
    int X0[32];
    for(int i=0;i<32;i++){X0[i]=R0[i]^key[i];} // L0=1........0 R0=0000000....0, key 1
    printf("XOR: ");
    for(int i=0;i<32;i++){printf("%d",X0[i]);}
    printf("\n");
    // 1
    // L0=0000 R0=0001
    // key = 0001
    // Xor = 0000
    // b1 = 00, b2 =00; xor = 0101; b1 =01; b2=01
    for(int i=31;i>=0;i-=4){
        int temp = (X0[i])+(X0[i-1]*2)+(X0[i-2]*4)+(X0[i-3]*8);

        // printf("%d\n",temp);
        int tarr[4]; memset(tarr,0,4*sizeof(int));
        Sbox(temp,tarr);
        X0[i]=tarr[0];
        X0[i-1]=tarr[1];
        X0[i-2]=tarr[2];
        X0[i-3]=tarr[3];
    }
    printf("Xor karne k baad: ");
    for(int i=0;i<32;i++){
        printf("%d ",X0[i]);
    }
    printf("\n");
    for(int i=0;i<32;i++){
        L1[i]=R0[i];
        R1[i]= X0[i]^L0[i];
    }
    printf("L1: ");
    for(int i=0;i<32;i++){
        printf("%d ",L1[i]);
    }
    printf("\n");

    printf("R1: ");
    for(int i=0;i<32;i++){
        printf("%d ",R1[i]);
    }
    printf("\n");
    unsigned long long output=0;
    for(int i=0;i<64;i++){
        if(i<32){
            output += R1[31-i]*power(2,i);
            // printf("%llu\n",output);
        }
        else{
            output+=L1[63-i]*power(2,i);
            // printf("%llu\n",output);
        }
    }
    return output;
}



int main()
{

    // taking input
    int inp[100],key[100],inp1[100],key1[100];
    memset(inp1,0,100*sizeof(int));
    memset(key,0,100*sizeof(int));


    // 0000000000000000000001
    unsigned long long input,enc=0,dec=0;
    printf("input: ");
    scanf("%llu",&input);
    converter(input,inp1);
    unsigned long K;
    printf("Key: ");
    scanf("%lu",&K);
    long long k1 = K;
    int curr=31;
    while (k1!=0)
    {
        key[curr]=k1%2;
        curr--;
        k1=k1>>1;
    }
    
    // converter((unsigned long long)K,key);
    for(int i=63;i>=0;i--){inp[63-i]=inp1[i];}
    // for(int i=31;i>=0;i--){key[31-i]=key1[i];}

    int L0[32],R0[32];
    for(int i=0;i<64;i++){
        if(i<32){
            L0[i]=inp[i];
        }
        else{
            R0[i-32] = inp[i];
        }
    }
    printf("Key: ");
    for(int i=0;i<32;i++){printf("%d ",key[i]);}
    printf("\n");
    for(int i=0;i<32;i++){printf("%d ",L0[i]);}
    printf("\n");
    for(int i=0;i<32;i++){printf("%d ",R0[i]);}
    printf("\n");
    int L1[32],R1[32];
    int L2[32],R2[32];
    // memset(L1,0,32*sizeof(int));
    // memset(R1,0,32*sizeof(int));
    // memset(L2,0,32*sizeof(int));
    // memset(R2,0,32*sizeof(int));
    enc = F(L0,R0,key,L1,R1);
    

    printf("ENCRYPTED: %llu\n",enc);


    dec = F(R1,L1,key,L2,R2);
    unsigned long long output=0;
    for(int i=0;i<64;i++){
        if(i<32){
            output += L2[31-i]*power(2,i);
            // printf("%llu\n",output);
        }
        else{
            output+=R2[63-i]*power(2,i);
            // printf("%llu\n",output);
        }
    }
    printf("DEC: %llu\n",output);

    return 0;
}