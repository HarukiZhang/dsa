/*Grouping Methods Problem*/
/*Problem Description:
    If we have N elements, and maximally we could group them into M groups;
    Query: how many methods that we can group them;
    Notify: do not count different ordering;
*/
/*Solution Description:
    Using appropriate enumeration with recursive calling;
    Separate the problem into two conditions:
        1) if elemN < maxGrN:
            Under this condition, there have to be group(s) left empty;
            So, to simplify the problem, we could only count methods that grouping N elements
                into N groups;
        2) if elemN >= maxGrN;
    The Basic Counting Algo:
        After adjusting the above first condition, that is to let M = N, if N < M,
            so that eventually, N >= M;
        The total methods = 
            methods(N elem into at-most M-1 Gr) + methods(N-M elem into just M Gr);
        To continue: methods(N elem into at-most M-1 Gr) = 
            methods(N elem into at-most M-2 Gr) + methods(N-M+1 elem into M-1 Gr);
        To stop at: methods(N elem into at-most 1 Gr), which is only one method;

        The above process consists of a recursive looping solution;
        To optimize the above recurion, expand the loop, so that it becomes as following:
        The total methods = 
            method(N elem 1 Gr) +
            meth(N-2 elem 2 Gr) + ... + meth(N-M+1 elem M-1 Gr) + meth(N-M elem M Gr);
        And this is a well-structured for-loop;
*/
/*The Advantage:
    Comparing to the second algo, i.e., int groupingMethods_apple(int, int),
        the recursion times significantly declined;
    INPUT:7
    OUTPUT:
    The 1st method : 15, recursion times : 22
    The 2nd method : 15, recursion times : 43

    INPUT:10
    OUTPUT:
    The 1st method : 42, recursion times : 61
    The 2nd method : 42, recursion times : 124
*/

#include <iostream>
// counting recursion times;
int counter = 0;
/*My new algo*/
int groupMethod(int elemN, int maxGrN){
    // The Stop boundary of the recursion:
    // Due to that with each recursion, the maxGrN is increasing, no need to set stop fence
    // for maxGrN;
    if (elemN == 1 || elemN == 0){
        ++::counter;
        return 1;
    }
    // To simplify the problem when elemN < maxGrN;
    if (elemN < maxGrN) maxGrN = elemN;
    // For the method(N elem 1 Gr), there's only one possi.;
    int res = 1;
    // Loop counting methods;
    for (int grN = 2; grN <= maxGrN; ++grN){
        res += groupMethod(elemN - grN, grN);
        ++::counter;
    }
    return res;
}

/*Old algo*/
int groupMethod_apple(int n, int m){
    if (n == 1 || m == 1 || n == 0){
        ++::counter;
        return 1;
    }
    if (n < m) m = n;
    ::counter += 2;
    return groupMethod_apple(n, m - 1) + groupMethod_apple(n - m, m);
}

int main() {
    int a;
    std::cin >> a;
    std::cout << "The 1st method : " << groupMethod(a, a)
        << ", recursion times : " << ::counter << std::endl;
    ::counter = 0;
    std::cout << "The 2nd method : " << groupMethod_apple(a, a)
        << ", recursion times : " << ::counter << std::endl;
}