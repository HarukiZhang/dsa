#include<iostream>

constexpr int kMaxNodeNum = 30;
int totalStack[kMaxNodeNum + 2]{}, tTop = -1;
int rightStack[kMaxNodeNum + 2]{}, rTop = -1;

int main(){
    freopen("E:\\in.txt", "r", stdin);
    int N;
    std::cin >> N >> std::ws;
    int lines = 2 * N;
    char cmd[5]{ 0, 'u' }, lastCmd;
    int crtN, lastPop;
    for (int i = 0; i < lines; ++i){
        lastCmd = cmd[1];
        std::cin >> cmd >> std::ws;
        if (cmd[1] == 'u'){
            std::cin >> crtN >> std::ws;
            if (lastCmd == 'u'){// push -> push
                totalStack[++tTop] = crtN;
            }
            else {//pop -> push
                rightStack[++rTop] = lastPop;
                totalStack[++tTop] = crtN;
            }
        }
        else {
            if (lastCmd == 'u'){//push -> pop
                lastPop = totalStack[tTop--];
            }
            else {//pop -> pop
                std::cout << lastPop << " ";
                lastPop = totalStack[tTop--];
                if (i + 1 == lines) std::cout << lastPop << " ";
                while (rTop >= 0)
                    std::cout << rightStack[rTop--] << " ";
            }
        }
    }
    return 0;
}