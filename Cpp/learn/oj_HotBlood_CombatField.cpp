#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <cstring>
#include <iostream>

#include <map>
#include <cstdlib>

inline void printPerfCounter(LARGE_INTEGER&, LARGE_INTEGER&, const char*);

void verifyAnwser(const char*, const char*);

int main() {
    freopen("E:\\Downloads\\in (3).txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    LARGE_INTEGER t0, t1;
    QueryPerformanceCounter(&t0);
    //-----------------------------main codes below-----------------------------------
    
    std::map<int, int> memsht; //first:attack; second:memID;
    memsht.insert(std::make_pair(1000000000, 1));
    int nMem;
    scanf("%d", &nMem);
    for (int i = 0; i < nMem; i++) {
        int memId, memAtt;
        scanf("%d %d", &memId, &memAtt);
        int idApprop; //firstly search for appropriate member ID in the map;
        auto itLowB = memsht.lower_bound(memAtt);
        if (itLowB == memsht.begin()) idApprop = itLowB->second;
        else if (itLowB == memsht.end()) idApprop = (--itLowB)->second;
        else {
            auto itAft = itLowB;
            auto itBef = --itLowB;
            int distA = abs(itAft->first - memAtt);
            int distB = abs(itBef->first - memAtt);
            if (distA != distB)
                idApprop = (distA < distB) ? itAft->second : itBef->second;
            else idApprop = itBef->second;
        }
        printf("%d %d\n", memId, idApprop);
        //then consider insert the present member;
        memsht.insert(std::make_pair(memAtt, memId));
    }

    //-----------------------------main codes above-----------------------------------
    QueryPerformanceCounter(&t1);

    freopen("CON", "a", stdout);

    printf("\n--------------- Main complete. ---------------\n");
    printPerfCounter(t0, t1, "Total  ");

    verifyAnwser("E:\\Downloads\\out (3).txt", "out.txt");
    
    fclose(stdin);
    fclose(stdout);
    return 0;
}

/*
Ϊ��ӭ��08��İ��˻ᣬ�ô�Ҹ����˽���ָ��˶���facer�¿���һ����Ѫ�񶷳���
�񶷳�ʵ�л�Ա�ƣ����������Ļ�Ա����Ҫ�����ѣ���ֻҪͬһ���ϻ�Ա��һ����������֤���Լ���ʵ����

���Ǽ���񶷵�ʵ��������һ����������ʾ����Ϊʵ��ֵ�����⣬ÿ���˶���һ��Ψһ��id��Ҳ��һ����������
Ϊ��ʹ�ñ������ÿ���ÿһ���¶�Ա����ѡ������ʵ����Ϊ�ӽ����˱�����������˫����ʵ��ֵ֮��ľ���ֵԽСԽ�ã�
����������˵�ʵ��ֵ���������ͬ��������ѡ����������Ǹ�����Ȼ��Ű�˱ر�Ű�ã���

���ҵ��ǣ�Facerһ��С�İѱ�����¼Ū���ˣ��������������Ż�Ա��ע���¼��
���������facer�ָ�������¼������ʱ��˳���������ÿ������˫����id��

����
��һ��һ����n(0 < n <=100000)����ʾ�񶷳������Ļ�Ա����������facer����
�Ժ�n��ÿһ������������������ʱ�������Ա��id��ʵ��ֵ��
һ��ʼ��facer�����ǻ�Ա��idΪ1��ʵ��ֵ1000000000��
���뱣֤���˵�ʵ��ֵ��ͬ��

���
N�У�ÿ����������Ϊÿ������˫����id�����ֵ�idд��ǰ�档

��������
3
2 1
3 3
4 2
�������
2 1
3 2
4 2
*/

inline void printPerfCounter(LARGE_INTEGER& t0, LARGE_INTEGER& t1, const char* tag_name) {
    static double freq = -1;
    if (freq == -1) {
        LARGE_INTEGER fq;
        QueryPerformanceFrequency(&fq);
        freq = (double)fq.QuadPart;
        printf("\n\n-----------------------------\n");
    }
    double ts = (double)(t1.QuadPart - t0.QuadPart) / freq;
    if (ts < 1) {
        ts *= 1000;
        printf("%s: %.3f ms\n-----------------------------\n", tag_name, ts);
    }
    else printf("%s: %.3f s\n-----------------------------\n", tag_name, ts);
}

constexpr unsigned short kArrSize_vfAws = 20;
void verifyAnwser(const char* dir1, const char* dir2) {
    FILE* f1 = fopen(dir1, "r");
    FILE* f2 = fopen(dir2, "r");
    char line1[kArrSize_vfAws], line2[kArrSize_vfAws];
    for (int i = 0; fgets(line2, kArrSize_vfAws, f2) != NULL; i++) {
        fgets(line1, kArrSize_vfAws, f1);
        if (strcmp(line1, line2) != 0) {
            printf("\n-----------------------------------------------------");
            printf("\nWrong in line %d. Please try again, Master Haruki.", i);
            printf("\n-----------------------------------------------------");
            fclose(f1);
            fclose(f2);
            return;
        }
    }
    printf("\n---------------------------------------------");
    printf("\nAll correct! Congradulations, master Haruki~!");
    printf("\n---------------------------------------------");
    fclose(f1);
    fclose(f2);
    return;
}