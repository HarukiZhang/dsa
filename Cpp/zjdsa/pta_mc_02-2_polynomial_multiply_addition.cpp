#include<cstdio>

using namespace std;

constexpr int kMaxHeapSize = 64;
constexpr int kMaxExponent = 100000;

class PLNode {
    friend class Polynomial;
    friend class MaxHeap;
public:
    using Term = PLNode*;
    PLNode(){}
    PLNode(int c, int e)
        :coef(c), expo(e)
    {}
    PLNode(Term pn)
        : coef(pn->coef), expo(pn->expo)
    {}
    ~PLNode(){}
private:
    int coef = -1, expo = -1;
    Term next = nullptr;
};

class MaxHeap {
public:
    using Term = typename PLNode::Term;
    MaxHeap()
        : arr(new Term [kMaxHeapSize + 2])
    {
        arr[0] = new PLNode { 0, kMaxExponent };//lookout;
    }
    ~MaxHeap(){
        delete arr[0];
        delete[] arr;
    }
    bool empty(){ return size == 0; }
    bool push(Term x);
    Term pop();
    void percolate(int idx);
private:
    int size = 0;
    int cap = kMaxHeapSize;
    Term *arr;
};

class Polynomial {
public:
    using Term = typename PLNode::Term;
    Polynomial(){}
    Polynomial(Polynomial&& pn)
        : size(pn.size), firstItem(pn.firstItem), lastItem(pn.lastItem)
    {
        pn.size = 0;
        pn.firstItem = nullptr;
        pn.lastItem = nullptr;
    }
    ~Polynomial(){
        if (firstItem){
            Term tmp = firstItem, last;
            while (tmp->next){
                last = tmp;
                tmp = tmp->next;
                delete last;
            }
        }
    }
    void newItem(int c, int e){
        if (firstItem){
            lastItem->next = new PLNode {c, e};
            lastItem = lastItem->next;
        }
        else {
            firstItem = new PLNode {c, e};
            lastItem = firstItem;
        }
        ++size;
        return;
    }
    void sort();
    void mergeItem();
    Polynomial& operator=(Polynomial&& pn);
    Polynomial operator+(const Polynomial& pn);
    Polynomial operator*(const Polynomial& pn);
    void print();

    //try;
    // Polynomial addition(const Polynomial& pn);

private:
    int size = 0;
    Term firstItem = nullptr;
    Term lastItem = nullptr;
};


int main(){
    freopen("E:\\in.txt", "r", stdin);
    int n1, n2, coef, expo;
    scanf("%d ", &n1);
    Polynomial poly1;
    if (n1){
        for (int i = 0; i < n1; ++i){
            scanf("%d %d ", &coef, &expo);
            poly1.newItem(coef, expo);
        }
    }
    scanf("%d ", &n2);
    Polynomial poly2;
    if (n2){
        for (int i = 0; i < n2; ++i){
            scanf("%d %d ", &coef, &expo);
            poly2.newItem(coef, expo);
        }
    }
    poly1.operator*(poly2).print();
    printf("\n");
    poly1.operator+(poly2).print();
    return 0;
}

bool MaxHeap::push(Term x){
    if (size == cap) return false;
    int crt = ++size;
    for (; arr[crt / 2]->expo < x->expo; crt /= 2)
        arr[crt] = arr[crt / 2];
    arr[crt] = x;
    return true;
}

MaxHeap::Term MaxHeap::pop(){
    if (size == 0) return nullptr;
    Term ret = arr[1];
    arr[1] = arr[size--];
    percolate(1);
    return ret;
}

void MaxHeap::percolate(int ptr){
    int parent, child;
    Term x = arr[ptr];
    for (parent = ptr; (child = parent * 2) <= size; parent = child){
        if (child != size && arr[child]->expo < arr[child + 1]->expo)
            ++child;
        if (x->expo < arr[child]->expo) arr[parent] = arr[child];
        else break;
    }
    arr[parent] = x;
    return;
}

void Polynomial::sort(){
    MaxHeap myHeap;
    Term crt;
    for (crt = firstItem; crt; crt = crt->next){
        myHeap.push(crt);
    }
    PLNode tmp;
    crt = &tmp;
    while (!myHeap.empty()){
        crt->next = myHeap.pop();
        crt = crt->next;
    }
    firstItem = tmp.next;
    lastItem = crt;
    return;
}


void Polynomial::mergeItem(){
    if (size < 2) return;

    this->sort();//heap sort;
    PLNode tmpHead;
    tmpHead.next = firstItem;
    Term crt = firstItem, last = &tmpHead, spare = last;
    while (crt){
        if (crt->expo == last->expo || crt->coef == 0){
            last->coef += crt->coef;
            last->next = crt->next;
            delete crt;//both expo-equal and coef-0 delete here;
            crt = last;
            --size;
        }
        if (crt->coef == 0){//only if offsetting after merge;
            spare->next = crt->next;
            delete crt;
            last = spare;
            crt = last->next;
        }
        else {
            spare = last;
            last = crt;
            crt = crt->next;
        }
    }
    firstItem = tmpHead.next;
    lastItem = firstItem ? last : nullptr;
    return;
}

Polynomial& Polynomial::operator=(Polynomial&& pn){
    size = pn.size;
    firstItem = pn.firstItem;
    lastItem = pn.lastItem;
    pn.size = 0;
    pn.firstItem = nullptr;
    pn.lastItem = nullptr;
    return *this;
}

// Polynomial Polynomial::addition(const Polynomial& pn){
//     Polynomial newPoly;
//     MaxHeap heap;
//     PLNode tmpHead;
//     Term ptr = firstItem;
//     while (ptr){
//         heap.push(ptr);
//         ptr = ptr->next;
//     }
//     ptr = pn.firstItem;
//     while (ptr){
//         heap.push(ptr);
//         ptr = ptr->next;
//     }
//     ptr = &tmpHead;
//     Term tmp, crt;
//     const PLNode kDiff { -1, -1 };
//     tmp = new PLNode { heap.pop() };
//     while (!heap.empty() || tmp != nullptr){
//         while (!heap.empty() && (crt = heap.pop()).expo == tmp.expo){
//             tmp->coef += crt.coef;
//             crt = nullptr;
//         }
//         if (crt->expo != tmp->expo){
//             ptr->next = tmp;
//             tmp = crt;
//             crt = kDiff;
//         }
//         if (tmp->coef == 0){
//             delete tmp;
//             tmp = crt;
//             crt = kDiff;
//         }
//         /*Uncomplete!*/
//     }
//     return newPoly;
// }

Polynomial Polynomial::operator+(const Polynomial& pn){
    Polynomial newPoly;
    PLNode newNode;
    Term crt = &newNode, p1 = firstItem, p2 = pn.firstItem;
    while (p1 && p2){
        if (p1->expo > p2->expo){
            crt->next = new PLNode {p1};
            p1 = p1->next;
            crt = crt->next;
            ++newPoly.size;
        }
        else if (p1->expo < p2->expo){
            crt->next = new PLNode {p2};
            p2 = p2->next;
            crt = crt->next;
            ++newPoly.size;
        }
        else {
            int tmpCf = p1->coef + p2->coef;
            if (tmpCf != 0){
                crt->next = new PLNode { tmpCf, p1->expo };
                crt = crt->next;
                ++newPoly.size;
            }
            p1 = p1->next;
            p2 = p2->next;
        }
    }
    while (p1){
        crt->next = new PLNode {p1};
        p1 = p1->next;
        crt = crt->next;
        ++newPoly.size;
    }
    while (p2){
        crt->next = new PLNode {p2};
        p2 = p2->next;
        crt = crt->next;
        ++newPoly.size;
    }
    newPoly.firstItem = newNode.next;
    newPoly.lastItem = crt;
    // newPoly.mergeItem();//no need;
    return newPoly;
}

Polynomial Polynomial::operator*(const Polynomial& pn){
    Polynomial newPoly;
    if (size == 0 || pn.size == 0) return newPoly;
    PLNode newNode;
    Term crt = &newNode, p1, p2;
    for (p1 = firstItem; p1; p1 = p1->next){
        for (p2 = pn.firstItem; p2; p2 = p2->next){
            crt->next = new PLNode { p1->coef * p2->coef, p1->expo + p2->expo };
            ++newPoly.size;
            crt = crt->next;
        }
    }
    newPoly.firstItem = newNode.next;
    newPoly.lastItem = crt;
    newPoly.mergeItem();
    return newPoly;
}

void Polynomial::print(){
    if (size == 0){
        printf("0 0");
        return;
    }
    Term crt = firstItem;
    while(true) {
        if (crt->coef != 0)
            printf("%d %d", crt->coef, crt->expo);
        crt = crt->next;
        if (!crt) break;
        printf(" ");
    }
    return;
}