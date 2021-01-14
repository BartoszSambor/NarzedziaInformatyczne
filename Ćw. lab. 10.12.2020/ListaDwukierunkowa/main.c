#include <stdio.h>
#include <stdlib.h>
#include "list.c"


void duplicate(T* elem){
    *elem *= 2;
}

int main()
{
    T k[] = {10,11,12,13,14,15,16,17};
    T* l = (T*)&k;
    T* o = &k[5];
    List *list = constructListN(8, 99);
    assign(list, l, o);

    printList(list);

    ListIterator  *LI = end(list);
    previous(LI);
    erase(list, LI);

    printList(list);

    for_each(list, &duplicate);

    printList(list);

    return 0;
}
