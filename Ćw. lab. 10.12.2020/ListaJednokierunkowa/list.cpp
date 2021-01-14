 #include "list.h"

 typedef int_fast32_t T;

 struct ForwardList{
     T value;
     struct ForwardList *next;
 };
typedef struct ForwardList ForwardList;

///Utilities:

void printList(ForwardList* l){
    while(l){
        printf("%d ", l->value);
        l = l->next;
        if(!l){
            printf(" NULLPOINTER");
        }
    }
    printf("\n");
}

void printElem(ForwardList* l){
    printf("%d\n", l->value);
}

/// Construct and destruct functions:

ForwardList* constructList(T element){
    struct ForwardList *newelem = malloc(sizeof(struct ForwardList));
    newelem->value = element;
    newelem->next = 0;
    return newelem;
}

ForwardList* constructListN(size_t elements, T nvalue){

    struct ForwardList *firstelem = malloc(sizeof(struct ForwardList));
    firstelem->next = 0;
    firstelem->value = nvalue;
    struct ForwardList *elemtoreturn = firstelem;

    for(int i = 1; i < elements; ++i){
        firstelem->next =  malloc(sizeof(struct ForwardList));
        firstelem->next->value = nvalue;
        firstelem->next->next = 0;
        firstelem = firstelem->next;
    }

    return elemtoreturn;
}

void destruct(ForwardList* l){
    struct ForwardList* current = l;
    struct ForwardList* next = l;
    while(current){
        next = current->next;
        free(current);
        current = next;
    }
}

ForwardList* cloneList(const ForwardList* l){
    struct ForwardList *firstelem = malloc(sizeof(struct ForwardList));
    firstelem->next = 0;
    firstelem->value = l->value;
    struct ForwardList *elemtoreturn = firstelem;

    while(l->next){
        firstelem->next =  malloc(sizeof(struct ForwardList));
        firstelem->next->value = l->next->value;
        firstelem->next->next = 0;
        firstelem = firstelem->next;
        l = l->next;
    }

    return elemtoreturn;
}


void clear(ForwardList* l){
    struct ForwardList *secondelem = l->next;
    destruct(secondelem);
    l->value = 0;
    l->next = 0;
}

/// Comfort functions:

ForwardList* getNode(ForwardList* l, size_t index){
    while(l->next != NULL && index){
        l = l->next;
        index--;
    }
    return index >= 1 ? NULL : l;
}

T get(const ForwardList* l){
    return l->value;
}

void setNodeValue(ForwardList* l, T value){
    l->value = value;
}

ForwardList* nextNode(const ForwardList* l){
    return l->next;
}

/// Capacity functions:

size_t size(const ForwardList* l){
    int siz = 1;
    while(l->next){
        siz++;
        l = l->next;
    }
    return siz;
}

void resize(ForwardList* l, size_t newSize){
    if(newSize == 0){
        destruct(l);
        return;
    }

    newSize--;
    while(newSize){
        if(l->next == NULL){
            struct ForwardList *lis = constructListN(newSize, 0);
            l->next = lis;
            return;
        }
        l = l->next;
        newSize--;
    }
    int val = l->value;
    clear(l);
    l->value = val;
}

///  Element access function:

T* at(ForwardList* l, size_t index){
    return &getNode(l, index)->value;
}

T* front(ForwardList* l){
    return &l->value;
}

T* back(ForwardList* l){
    while(l->next != NULL){
        l = l->next;
    }
    return &l->value;
}

///  Modifiers:

ForwardList* push_front(ForwardList* l, T element){
    struct ForwardList *newelem = malloc(sizeof(struct ForwardList));
    newelem->value = element;
    newelem->next = l;
    return newelem;
}

ForwardList* pop_front(ForwardList* l){
    struct ForwardList *second = l->next;
    free(l);
    return second;
 }

void assign(ForwardList* l, size_t elementCount, const T elements[]){
    for(int i = 0; i < elementCount; ++i){
        l->value = elements[i];
        l = l->next;
    }
}

ForwardList* insert_after(ForwardList* l, size_t index, T element){
    for(int i = 0; i < index-1; ++i){
        l = l->next;
    }
    struct ForwardList *newelem = malloc(sizeof(struct ForwardList));
    newelem->value = element;
    newelem->next = l->next;
    l->next = newelem;
    return newelem;
}

ForwardList* erase_after(ForwardList* l, size_t index){
    for(int i = 0; i < index-1; ++i){
        l = l->next;
    }
    struct ForwardList *todelete = l->next;
    l->next = l->next->next;
    free(todelete);
    return(l->next);
}

/// Operations:

ForwardList* reverse(ForwardList* l){
    struct ForwardList *first = l;
    struct ForwardList *second = l->next;
    struct ForwardList *third = l->next->next;
    first->next = NULL;

    while(third->next != NULL){
        second->next = first;
        first = second;
        second = third;
        third = third->next;
    }

   second->next = first;
   third->next = second;
   return third;
}

ForwardList* sort(ForwardList* l){
    int length = size(l);
    struct ForwardList *first = l;
    for(int i = 0; i < length-2; ++i){
        l = first;
        for(int j = 0; j < length-1; ++j){
            if(l->value > l->next->value){
                T tmp = l->value;
                l->value = l->next->value;
                l->next->value = tmp;
            }
            l = l->next;
        }
    }
    return first;
}

ForwardList* unique(ForwardList* l){
    struct ForwardList *first = l;
    while(l->next != NULL){
        if(l->value == l->next->value){
            erase_after(l, 1);
        }
        else{
            l = l->next;
        }
    }
    return first;
}

/// Functions to cooperate with function pointers:

void for_each(ForwardList* l, void(*f)(ForwardList* current)){
    while(l){
        f(l);
        l = l->next;
    }
}

ForwardList* remove_if(ForwardList* l, bool(*predicate)(T nodeValue)){
    struct ForwardList *first = l;
    while(l->next){
        if(predicate(l->next->value)){
            erase_after(l, 1);
        }
        else{
        l = l->next;
        }
    }
    if(predicate(first->value)){
        first = pop_front(first);
    }
    return first;
}




