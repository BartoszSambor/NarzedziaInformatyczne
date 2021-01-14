#include "list.h"


struct List{
    struct Node *first;
    struct Node *last;
    T size;
};
typedef struct List List;

struct Node{
    struct Node *next;
    struct Node *previous;
    T value;
};
typedef struct Node Node;

struct ListIterator{
    struct Node *elem;
};
typedef struct ListIterator ListIterator;


/// Construct and destruct functions:
void printList(List *list){
    Node *node = list->first;
    while(node){
        printf("%d ", node->value);
        node = node->next;
    }
    printf("\n");
}

Node* constructNode(T value){
    Node *elem = malloc(sizeof(Node));
    elem->next = NULL;
    elem->previous = NULL;
    elem->value = value;
    return elem;
}

List* constructList(T element){
    List *newlist = malloc(sizeof(List));
    newlist->first = constructNode(element);
    newlist->last = newlist->first;
    newlist->size = 1;
    return newlist;
}

List* constructListN(size_t elements, T value){
    List *newlist = constructList(value);
    Node *st = newlist->first;
    Node *nd = NULL;
    for(int i = 0; i < elements - 1; ++i){
        nd = constructNode(value);
        st->next = nd;
        nd->previous = st;
        st = nd;
    }
    newlist->last = st;
    newlist->size = elements;
    return newlist;
}

List* constructListFromRange(const T* from, const T* to){
    T listSize = to - from + 1;
    List *newlist = constructList(*from);
    from++;
    Node *st = newlist->first;
    Node *nd = NULL;
    while(from != to + 1){
        nd = constructNode(*from);
        st->next = nd;
        nd->previous = st;
        st = nd;
        from++;
    }
    newlist->last = st;
    newlist->size = listSize;
    return newlist;
}

void destruct(List* l){
    Node* node = l->first;
    while(node->next){
        node = node->next;
        free(node->previous);
    }
    free(node);
    free(l);
}

List* cloneList(const List* l){ // do poprawy
    Node* node = l->first;
    List* newlist = constructList(node->value);
    node = node->next;
    while(node){
        push_back(newlist, node->value);
        node = node->next;
    }
    return newlist;
}


/// Iterator functions:
ListIterator* begin(List* l){
    ListIterator* lit = malloc(sizeof(ListIterator));
    lit->elem = l->first;
    return lit;
}

ListIterator* end(List* l){
    ListIterator* lit = malloc(sizeof(ListIterator));
    lit->elem = l->last;
    return lit;
}


/// Functions of ListIterator
bool hasNext(const ListIterator* li){
    return (bool)li->elem->next;
}

bool hasPrevious(const ListIterator* li){
    return (bool)li->elem->previous;
}

void next(ListIterator* li){   // nie jestem pewny co powinno sie dziac jesli nie ma nastepnego elementu
    if(li->elem->next){
        li->elem = li->elem->next;
    }
}

void previous(ListIterator* li){    // tak jak wyzej
    if(li->elem->previous){
        li->elem = li->elem->previous;
    }
}

T* current(ListIterator* li){
    return &li->elem->value;
}


/// Capasity functions:
size_t size(const List* l){
    return l->size;
}

bool empty(const List* l){
    return (bool) l->first;
}


/// Element access:
T* front(List* l){
    return &l->first->value;
}

T* back(List* l){
    return &l->last->value;
}


///  Modifiers:
void push_front(List* l, T element){
    Node* node = malloc(sizeof(Node));
    node->value = element;
    node->previous = NULL;
    node->next = l->first;
    l->first->previous = node;
    l->first = node;
    l->size++;
}

void pop_front(List* l){
    l->first = l->first->next;
    l->size--;
    free(l->first->previous);
    l->first->previous = NULL;
}

void push_back(List* l, T element){
    Node* node = malloc(sizeof(Node));
    node->value = element;
    node->next = NULL;
    node->previous = l->last;
    l->last->next = node;
    l->last = node;
    l->size++;
}

void pop_back(List* l){
    l->last = l->last->previous;
    l->size--;
    free(l->last->next);
    l->last->next = NULL;
}

void assign(List* l, const T* from, const T* to){  // nie obsługuje przypadku gdy lista ma za mało elementów
    Node* node = l->first;
    while(from != to + 1)
    {
        node->value = *from;
        node = node->next;
        from++;
    }
}

ListIterator* insert(List* l, ListIterator* position, T element){
    Node* newnode = malloc(sizeof(Node));
    newnode->value = element;

    if(!hasPrevious(position)){
        newnode->next = position->elem;
        position->elem->previous = newnode;
        l->size++;
        previous(position);
        l->first = position->elem;
        return position;
    }

    position->elem->previous->next = newnode;
    newnode->previous =  position->elem->previous;
    newnode->next = position->elem;
    position->elem->previous = newnode;
    l->size++;
    previous(position);
    return position;
}

ListIterator* erase(List* l, ListIterator* position){
    if(!hasPrevious(position)){
        next(position);
        free(position->elem->previous);
        position->elem->previous = NULL;
        l->first = position->elem;
        l->size--;
        return position;
    }
    if(!hasNext(position)){
        previous(position);
        free(position->elem->next);
        position->elem->next = NULL;
        l->last = position->elem;
        l->size--;
        return position;
    }
    //w przypadku usuwania elementu ze środka:
    Node* node = position->elem;
    position->elem->previous->next = position->elem->next;
    position->elem->next->previous = position->elem->previous;
    next(position);
    free(node);
    l->size--;
    return position;
}

void swap(List* l1, List* l2){
    List* tmp = malloc(sizeof(List));
    tmp->size = l2->size;
    tmp->first = l2->first;
    tmp->last = l2->last;

    l2->size = l1->size;
    l2->first = l1->first;
    l2->last = l1->last;

    l1->size = tmp->size;
    l1->first = tmp->first;
    l1->last = tmp->last;
}

void resize(List *l, size_t newSize){
    if(l->size == newSize){
        return;
    }else if(size == 0){
        destruct(l);
    }else{
        l->size = newSize;
        newSize--;
        Node* node = l->first;
        while(newSize){
            if(node->next == NULL)
            {
                List* list = constructListN(newSize, 0);
                l->last->next = list->first;
                list->first->previous = l->last;
                l->last = list->last;
                return;
            }
            node = node->next;
            newSize--;
        }
        l->last = node;
        List* listtodelete = malloc(sizeof(List));
        listtodelete->first = node->next;
        destruct(listtodelete);
        l->last->next = NULL;
    }
}

void clear(List* l){
    l->size = 1;
    l->last = l->first;
    List* list = malloc(sizeof(List));
    list->first = l->first->next;
    destruct(list);
    l->first->next = NULL;
}


/// Operations:
///TODO


/// Functions to cooperate with function pointers:
void for_each(List* l, void(*f)(T* current)){
    ListIterator *iterator = begin(l);
    while(hasNext(iterator)){
        f(current(iterator));
        next(iterator);
    }
    f(current(iterator));
}





