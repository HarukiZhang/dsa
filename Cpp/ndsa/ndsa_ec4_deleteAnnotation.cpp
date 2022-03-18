#include<cstdio>

using namespace std;

int main(){
    // freopen("E:\\Downloads\\in.txt", "r", stdin);

    int x, y;
    while ((x = getchar()) != EOF){
        if (x == '/'){
            y = getchar();
            if (y == '*'){
                x = getchar();
                while (true){
                    if (x == '*'){
                        y = getchar();
                        if (y == '/') break;
                        else x = y;
                    }
                    else x = getchar();
                }
            }
            else if (y == '/'){
                x = getchar();
                while (true){
                    if (x == '\n'){
                        putchar(x);
                        break;
                    }
                    else x = getchar();
                }
            }
            else printf("%c%c", (char)x, (char)y);
        }
        else if (x == '\"' || x == '\''){
            putchar(x);
            do {
                putchar(y = getchar());
                while (y == '\\'){
                    putchar(getchar());
                    putchar(y = getchar());
                }
            } while (y != x);
        }
        else putchar(x);
    }
}