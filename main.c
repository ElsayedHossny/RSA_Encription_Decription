#include <stdio.h>
#include <stdlib.h>

#define Key_ENC 17
/*
#define N 6893
#define F_N 6720
*/
int F_N;
int binaryNum[10];


int decToBinary(int n){
    int i = 0;
    while (n > 0) {
        binaryNum[i] = n % 2;
        n = n / 2;
        i++;
    }
    return i-1;
}

int MulInverse_EEA(int PHI_N){
    //////////////////////////////////Check_gcd///////////////////////////////////////////////
int Big=0,Small=0,d=0;
int Arr_R[10],Arr_Q[10],T0=0,T1=1;
    if(Key_ENC == PHI_N){
        return 0;
    }else if(Key_ENC > PHI_N){
        Big=Key_ENC;
        Small=PHI_N;
        }else{
        Big=PHI_N;
        //printf("B %d\n",Big);
        Small=Key_ENC;
    }
    int i = 0;
    while (Small > 1) {
        Arr_R[i]=Big%Small;
        Arr_Q[i]=Big/Small;
        //printf("Arr_Q[i]=%d   Arr_R[i]=%d\n",Arr_Q[i] ,Arr_R[i]);
        Big=Small;
        Small=Arr_R[i];
        i++;
    }
    //////////////////////////////////To Find Multiplicative_inverse/////////////////////////////////////////////
    for(int j=0 ; j<i ;j++){
        d= T0 - (Arr_Q[j]*T1);
        T0 =T1;
        T1=d;
    }
    if(d<0){
       d=d+PHI_N;
    }else{
       d=d%PHI_N;
    }
    return d;
}

int Encryption_RSA(int plain , int N_Mode){
    int Length=0 , Rem=plain;
    Length = decToBinary(Key_ENC);
    // I don't Need last bit -> i use (Length-1)
     for (int j = (Length-1); j >= 0; j--){
        if(binaryNum[j]==0){
            Rem=(Rem*Rem); //aquare
        }else{
            Rem=(Rem*Rem);//aquare + Mul
            Rem=Rem%N_Mode;
            Rem=(Rem*plain);
        }
        Rem=Rem%N_Mode;
     }
     return Rem;
}

int Decryption_RSA(int Cipher , int N_Mode){
    int Length=0 , Rem=Cipher , dec_Key=0;
    dec_Key=MulInverse_EEA(F_N);
    Length = decToBinary(dec_Key);
    // I don't Need last bit -> i use (Length-1)
     for (int j = (Length-1); j >= 0; j--){
        if(binaryNum[j]==0){
            Rem=(Rem*Rem); //aquare
        }else{
            Rem=(Rem*Rem);//aquare + Mul
            Rem=Rem%N_Mode;
            Rem=(Rem*Cipher);
        }
        Rem=Rem%N_Mode;
     }
     return Rem;
}


int main()
{
int Y,X,N ;

printf("Enter Mode : ");
scanf("%d",&N);
printf("\nEnter PHI_Mode : ");
scanf("%d",&F_N);

Y=Encryption_RSA(3,N);
X=Decryption_RSA(Y,N);
printf("\nY= %d   X=%d\n",Y ,X);

    return 0;
}


