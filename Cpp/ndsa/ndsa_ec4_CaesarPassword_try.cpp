#include<cstdio>
using namespace std;

int main(){
    // freopen("E:\\Downloads\\in.txt", "r", stdin);
    char buf[210];
    while (true){
        fgets(buf, 205, stdin);//read "START";
        if (buf[0] == 'E')//if "ENDOFINPUT";
            return 0;
        fgets(buf, 205, stdin);//read password;
        int idx = 0;
        while (buf[idx]){
            if (buf[idx] >= 'A' && buf[idx] <= 'Z'){
                printf("%c", ((buf[idx] - 44) % 26) + 65);
            }
            else
                printf("%c", buf[idx]);
            ++idx;
        }
        fgets(buf, 205, stdin);//read "END";
    }
    fclose(stdin);
    return 0;
}

/*
IN WAR, EVENTS OF IMPORTANCE ARE THE RESULT OF TRIVIAL CAUSES
I WOULD RATHER BE FIRST IN A LITTLE IBERIAN VILLAGE THAN SECOND IN ROME
DANGER KNOWS FULL WELL THAT CAESAR IS MORE DANGEROUS THAN HE


IN WAR, EVENTS OF IMPORTANCE ARE THE RESULT OF TRIVIAL CAUSES

I WOULD RATHER BE FIRST IN A LITTLE IBERIAN VILLAGE THAN SECOND IN ROME

DANGER KNOWS FULL WELL THAT CAESAR IS MORE DANGEROUS THAN HE
*/