typedef struct Node *PtrToNode;
struct Node { int Data; PtrToNode Next; };
typedef PtrToNode List;

List Reverse(List L){
    if (!L) return L;
    PtrToNode rvd = L, old = L->Next;
    while (old){
        PtrToNode tmp = old->Next;
        old->Next = rvd;
        rvd = old; old = tmp;
    }
    L->Next = NULL;
    return rvd;
}