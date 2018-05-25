#include <stdio.h>
#include <float.h>
#include <stdlib.h>
#include <math.h>

typedef struct Point{
    int x, y;
}Point;

//Função utilizada no qsort (para ordenar com relação a X)
int compareX(const void*, const void*);
//Função utilizada no qsort (para ordenar com relação a X)
int compareY(const void*, const void*);
//Função para calcular a distancia entre dois pontos
float distancia(Point, Point);
//Função para calcular pontos mais próximos na força bruta
float ForcaBruta(Point P[], int);
//Função para encontrar os pontos mais próximos de um faixa de tamanho determinado
float proximoFaixa(Point strip[], int, float);
//Função recursiva para encontrar a menor distamcia
float proximo(Point P[], int);

int main(){
    Point P[] = {{21, 29}, {40, 50}, {12, 30}, {5, 1}, {12, 17}, {23, 4}};
    int n = sizeof(P) / sizeof(Point);
    printf("The smallest distance is %f\n", proximo(P, n));
    return 0;
}

int compareX(const void* a, const void* b){
    Point *p1 = (Point *)a,  *p2 = (Point *)b;
    return (p1->x - p2->x);
}

int compareY(const void* a, const void* b){
    Point *p1 = (Point *)a,   *p2 = (Point *)b;
    return (p1->y - p2->y);
}
 
float distancia(Point p1, Point p2){
    return sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
}
 
float ForcaBruta(Point P[], int n){
    float min = FLT_MAX; //Maior valor de um float (para comparações)
    for (int i = 0; i < n; ++i){
        for (int j = i+1; j < n; ++j){
            if (distancia(P[i], P[j]) < min){
                min = distancia(P[i], P[j]);
            }
        }
    }
    return min;
}
 
float proximoFaixa(Point strip[], int size, float d){
    float min = d;
 
    qsort(strip, size, sizeof(Point), compareY); 
    for (int i = 0; i < size; ++i){
        for (int j = i+1; j < size && (strip[j].y - strip[i].y) < min; ++j){
            if (distancia(strip[i],strip[j]) < min){
                min = distancia(strip[i], strip[j]);
            }
        }
    } 
    return min;
}
 
float proximo(Point P[], int n){
    qsort(P, n, sizeof(Point), compareX);
    if (n <= 3){
        return ForcaBruta(P, n);
    }

    int mid = n/2;
    Point midPoint = P[mid];
 
    float dl = proximo(P, mid);
    float dr = proximo(P + mid, n-mid);
 
    float d;
    d = (dl < dr) ? dl: dr;
 
    Point strip[n];
    int j = 0;
    for (int i = 0; i < n; i++){
        if (abs(P[i].x - midPoint.x) < d){
            strip[j] = P[i], j++;
        }
    }
    return (d < proximoFaixa(strip, j, d))? d : proximoFaixa(strip, j, d);
}