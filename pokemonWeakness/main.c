// ConsoleApplication2.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//
#include "stdafx.h"
#define NumofType 18
#define PrintTypeNameByNum(x) PrintTypeName((PokeType)x)
enum PokeType {	Normal,	Fighting,	Flying,	Poison,	Ground,	Rock,	Bug,
                Ghost,	Steel,	Fire,	Water,	Grass,	Eletric,	Psychic,	Ice,	Dragon,	Dark,	Fairy
              };
int PrintTypeName(PokeType a) {
    switch (a) {
    case Normal:
        printf("Normal ");
        break;
    case Fighting:
        printf("Fighting ");
        break;
    case Flying:
        printf("Flying ");
        break;
    case Poison:
        printf("Poison ");
        break;
    case Ground:
        printf("Ground ");
        break;
    case Rock:
        printf("Rock ");
        break;
    case Bug:
        printf("Bug ");
        break;
    case Ghost:
        printf("Ghost ");
        break;
    case Steel:
        printf("Steel ");
        break;
    case Fire:
        printf("Fire ");
        break;
    case Water:
        printf("Water ");
        break;
    case Grass:
        printf("Grass ");
        break;
    case Eletric:
        printf("Electric ");
        break;
    case Psychic:
        printf("Psychic ");
        break;
    case Ice:
        printf("Ice ");
        break;
    case Dragon:
        printf("Dragon ");
        break;
    case Dark:
        printf("Dark ");
        break;
    case Fairy:
        printf("Fairy ");
        break;
    default:
        printf("Unknown ");
        break;
    }
    return 1;
}
int ReadTypeChart(int TypeChart[][NumofType]) {
    char s_filename[63]="typechart.txt";
    //printf("Please input the chart path:");
    //scanf("%s", s_filename);
    FILE*fp = fopen(s_filename, "r");
    for (int i = 0; i < NumofType; i++)
        for (int j = 0; j < NumofType; j++)
            fscanf(fp, "%d\n", &TypeChart[i][j]);
    fclose(fp);
    return 1;
}
int PrintTypeAndNumAll() {
    for (int i = 0; i < 17; i++) {
        printf("%d:", i);
        PrintTypeName((PokeType)i);
        if (i == 7)
            printf("\n");
        else
            printf("  ");
    }
    printf("\n");
    return 1;
}
int main() {
    int  TypeChart[NumofType][NumofType];
    ReadTypeChart(TypeChart);
    for (int i = 0; i < NumofType; i++) {
        for (int j = 0; j < NumofType; j++) {
            if (i>=j)continue;
            int Weak = 0;
            int Strong = 0;
            for (int k = 0; k < NumofType; k++) {
                int a;
                int b;
                a = TypeChart[k][i];
                b = TypeChart[k][j];
                a = a*b;
                switch (a) {
                case 64:
                case 0:
                case 8:
                    Strong++;
                    break;
                case 2:
                case 4:
                    Weak++;
                    break;
                default:
                    break;
                }
            }
            PrintTypeNameByNum(i);
            PrintTypeNameByNum(j);
            printf("%d %d\n", Weak, Strong);
        }
    }
    return 0;
}
