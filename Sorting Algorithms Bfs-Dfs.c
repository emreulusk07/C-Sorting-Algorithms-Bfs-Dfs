#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define boyut 5

// EMRE ULUIÞIK
typedef struct NODE
{
    int data;
    int gezilmis;

} node;

node* ilkDugum[boyut];
int komsuDizi[boyut][boyut];

int stack[boyut];
int top = -1;
int dugumSayi = 0;

//=======================================================================================================
//=======================================================================================================

int queue[boyut];
int arkaTaraf = -1;
int onTaraf = 0;
int kuyrukSayi = 0;

//========================================================================================================
//========================================================================================================

void queueu(int x)
{
    arkaTaraf++;
    queue[arkaTaraf] = x;
    kuyrukSayi++;
}

int dequeueu()
{
    kuyrukSayi--;
    return queue[onTaraf++];
}

void DFS()
{
    int i, dugumIndex, gezilmemisD;

    ilkDugum[0]->gezilmis = 1;
    dugumIndex=0;
    printf("%d ", ilkDugum[dugumIndex]->data);

    push(0);
    while(top != -1)
    {
        gezilmemisD = kalanKomsuGez(stack[top]);
        if(gezilmemisD == -1)
            pop();

        else
        {
            ilkDugum[gezilmemisD]->gezilmis = 1;
            printf("%d ", ilkDugum[gezilmemisD]->data);
            push(gezilmemisD);
        }
    }

    for(i=0; i<dugumSayi ;i++)
        ilkDugum[i]->gezilmis = 0;

}

//========================================================================================================
//========================================================================================================

void push(int x)
{
    top++;
    stack[top] = x;
}

int pop()
{
    return stack[top--];
}

void BFS()
{
    int i, dugumIndex, temp, gezilmemisD;

    ilkDugum[0]->gezilmis = 1;
    dugumIndex=0;
    printf("%d ", ilkDugum[dugumIndex]->data);

    queueu(0);
    while(kuyrukSayi != 0)
    {
        temp = dequeueu();
        while((gezilmemisD = kalanKomsuGez(temp)) != -1)
        {
            ilkDugum[gezilmemisD]->gezilmis = 1;
            printf("%d ", ilkDugum[gezilmemisD]->data);
            queueu(gezilmemisD);
        }
    }

    for(i=0; i<dugumSayi ;i++)
        ilkDugum[i]->gezilmis = 0;

}

int kalanKomsuGez(int dugumIndex)
{
    int i;
    for(i=0; i<dugumSayi ;i++)
    {
        if(komsuDizi[dugumIndex][i]>0 && ilkDugum[i]->gezilmis==0)
            return i;
    }
    return -1;
}

void dugumEkle(int x)
{
    node *dugum = (node*) malloc(sizeof(node));
    dugum->data = x;
    dugum->gezilmis = 0;
    ilkDugum[dugumSayi] = dugum;
    dugumSayi++;
}

void kenarEkle(int bas,int son, int mesafe)
{
    komsuDizi[bas][son] = mesafe;
    komsuDizi[son][bas] = mesafe;
}

int main()
{
    int i, j, k, random, sayilar[boyut];
    srand(time(NULL));

    for(i=0; i<boyut ;i++)
    {
        for(j=0; j<boyut ;j++)
        {
            komsuDizi[i][j] = 0;
        }
    }

    for(k=0; k<boyut; k++)
    {
        random = (rand()%49)+1;
        sayilar[k] = random;
        printf("%d.sayi: %d\n", k+1, random);
        dugumEkle(random);
    }
    printf("\n");

    kenarEkle(0,1,100);
    kenarEkle(0,2,200);
    kenarEkle(0,3,300);
    kenarEkle(1,4,400);
    kenarEkle(2,4,500);

    int secim;
    printf("1-> BFS ile isleme devam et..\n2-> DFS ile isleme devam et..\n\nSeciminizi yapiniz: ");
    scanf("%d", &secim);
    if(secim==1)
    {
        printf("\nSayilarin BFS gore yazilmis hali\n");
        BFS();
        printf("\n");
    }
    else if(secim==2)
    {
        printf("\nSayilarin DFS gore yazilmis hali\n");
        DFS();
        printf("\n");
    }
    else
    {
        printf("Yanlis secim..\n\n");
        main();
    }

    return 0;
}
