#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct ads
{
    int start, duration, profit;
};

struct weightedAds
{
    struct ads ad[1000];
    int value;
};
void print(struct ads arr[], int n){
	int i;
	 for(i=0;i<n;i++){
         printf("%d %d %d\n",arr[i].start,arr[i].duration, arr[i].profit);    
       }
}

int compare (struct ads ads1, struct ads ads2)
{
    int x = ((int)ads1.start+ (int)ads1.duration);
    int y = ((int)ads2.start + (int)ads2.duration);
    if (x > y) return  1;
    if (x < y) return -1;
    return 0;
}
void sorting(struct ads arr[], int n){
    struct ads tmp[1000];
    int i,j;
    for(i=0;i<n;i++){
    	for(j=i+1;j<6;j++){
    		if(compare(arr[i],arr[j])==1){
    			tmp[0]=arr[i];
    			arr[i]=arr[j];
    			arr[j]=tmp[0];
			}
		}
	}
}
int conflictCont(struct ads arr[], int i)//Çakýþmayan son reklamý kontrol eder
{
	int j;
    for (j=i-1; j>=0; j--)
    {
        if (arr[j].duration + arr[j].start <= arr[i].start)//baþlangýç ve bitiþ zamanlarý karþýlaþtýrýyoruz.
            { 

			return j;}
    }
    return -1;
}

int findMaxProfit(struct ads arr[], int n)
{
	int i,j;
    struct weightedAds prfArr[n];
    int size = 0;
    //Ýlk reklam bilgilerini prfArr dizisine ekliyoruz.
    prfArr[0].value = arr[0].profit;
    prfArr[0].ad[size++] = arr[0];

    for (i=1; i<n; i++) //Diðer reklamlar için i=1
    {

        int inclProf = arr[i].profit; 
        int l = conflictCont(arr, i); 
        if (l != - 1)
            inclProf += prfArr[l].value;//Eðer çakýþan reklam yoksa mevcut reklama önceki çakýþmayan reklam kazancýný ekliyoruz.

        if (inclProf > prfArr[i - 1].value)  
        {
            prfArr[i].value = inclProf;   //Hesapladýðýmýz kazanç önceki kazançtan yüksekse onu seçiyoruz.

            // önceki ve mevcut reklam dahil edilir.
            for (j=0; j<100; j++)
                prfArr[i].ad[j] = prfArr[l].ad[j];  //Seçilen önceki reklamlarýn isimlerini  ekliyoruz.
            prfArr[i].ad[size++] = arr[i];//mevcut reklamý da ekliyoruz.

        }
        else
            //kazanç yüksek deðilse mevcut reklamý dahil etmiyoruz.
            prfArr[i] = prfArr[i - 1]; 
    }
    printf("\nSecilen Reklamlar\n");
    for (i=0; i<100; i++)
    {
        struct ads j = prfArr[n-1].ad[i];
        if(j.start)
        printf("(%d, %d, %d)\n", j.start, j.duration, j.profit);
    }
        return prfArr[n-1].value;//max-kazanc
}

int main()
{
    struct ads arr[1000];
    FILE *Ufptr;
    Ufptr = fopen("Sample2.txt","r+");
    int i = 0;
    while((fscanf(Ufptr, "%d\t%d\t%d\n", &arr[i].start, &arr[i].duration, &arr[i].profit)) != EOF){i++;}
    fclose(Ufptr);
    printf("Okunan Matris\n");
    print(arr,i);
    printf("\nSirali Matris\n");
    sorting(arr,i);
    print(arr,i);
    printf("\nMaksimum Kazanc: %d", findMaxProfit(arr, i));
    
    return 0;
}
