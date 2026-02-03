#include "ArrayList.h"
#include "LinkedList.h"
#include "Stack.h"

#include <iostream>

void testStack(){
    Stack<int> stack;
    int a = 5;
    stack.push(2);
    stack.push(a);

    std::cout << "Peek: " << stack.peek() << "\n";

    std::cout << "Pop: " << stack.pop() << "\n";

    std::cout << "Peek: " << stack.peek() << "\n";
}

void printLinkedListContent(LinkedList<int> &list){
    std::cout << "Printing LinkedList Content: \n";
    for(int i = 0; i < list.size(); i++){
        std::cout << i << ". " << list.get(i) << "\n";
    }
}

void testLinkedList(){
    LinkedList<int> list;

    printLinkedListContent(list);

    list.add(2);

    printLinkedListContent(list);

    int a = 90;
    list.add(a);

    printLinkedListContent(list);

    list.remove(0);

    printLinkedListContent(list);

    list.add(10);
    std::cout << "Containts 10: " << list.contains(10) << "\n";

    std::cout << "Is list empty: " << list.isEmpty() << "\n";

    printLinkedListContent(list);
}

void printArrayListContent(ArrayList<int> &list){
    std::cout << "Printing ArrayList Content: \n";
    for(int i = 0; i < list.size(); i++){
        std::cout << i << ". " << list.get(i) << "\n";
    }
}

void testArrayList(){
    ArrayList<int> list;

    printArrayListContent(list);

    list.add(2);

    printArrayListContent(list);

    int a = 90;
    list.add(a);

    printArrayListContent(list);

    list.remove(0);

    printArrayListContent(list);

    list.add(10);
    std::cout << "Containts 10: " << list.contains(10) << "\n";

    std::cout << "Index of 10: " << list.find(10) << "\n";

    std::cout << "Is list empty: " << list.isEmpty() << "\n";

    printArrayListContent(list);
}

int main(){
    testStack();

    return 0;
}