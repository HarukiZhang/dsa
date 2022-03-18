#include <iostream>

using namespace std;

class LNode {
friend class LinkList;
private:
    int data;
    typedef LNode *Position;
    LNode::Position next;
public:
    LNode(){}
    LNode(int d, LNode::Position n)
        : data(d), next(n)
    {}
    ~LNode(){}
};

class LinkList {
public:
    LinkList()
        : length(0), head(new LNode)
    {
        head->next = nullptr;
    }
    ~LinkList(){
        LNode::Position crt, last;
        crt = head;
        while (crt != nullptr){
           last = crt;
           crt = crt->next;
           delete last; 
        }
    }
    LNode::Position find(int loc){
        if (loc > length) return nullptr;
        LNode::Position res = head;
        int i = 0;
        while (res->next && i++ < loc) res = res->next;
        return res;
    }
    bool insert(int x, int loc){
        LNode::Position crt = find(loc);
        if (crt == nullptr) return false;
        LNode::Position newNode = new LNode {x, crt->next };
        crt->next = newNode;
        ++length;
        return true;
    }
    bool erase_after(int loc){
        LNode::Position ptr = find(loc);
        if (ptr == nullptr || ptr->next == nullptr) return false;
        LNode::Position tmp = ptr->next;
        ptr->next = tmp->next;
        delete tmp;
        --length;
        return true;
    }
    void traversal(){
        LNode::Position crt = head;
        while (crt->next){
            crt = crt->next;
            cout << crt->data << endl;
        }
        return;
    }
private:
    int length;
    LNode::Position head;
};

int main(){
    freopen("E:\\in.txt", "r", stdin);
    LinkList myList;
    int N, tmp;
    cin >> N;
    for (int i = 0; i < N; ++i){
        cin >> tmp;
        myList.insert(tmp, i);
    }
    myList.erase_after(1);
    myList.traversal();
}