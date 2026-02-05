#include "ArrayList.h"
#include "LinkedList.h"
#include "Stack.h"
#include "Queue.h"
#include "HashSet.h"
#include "Map.h"

#include <iostream>
#include <string>

void testMap(){
    Map<int, std::string> map;

    std::string two = "two";

    map.insert(1, "one");
    map.insert(2, two);

    std::cout << "Contains key 1: " << map.contains(1) << "\n";
    std::cout << "Contains key 2: " << map.contains(2) << "\n";

    map.erase(1);

    std::cout << "Contains key 1 (should return false): " << map.contains(1) << "\n";
    std::cout << "Contains key 2: " << map.contains(2) << "\n";
    std::cout << "IsEmpty (should be false): " << map.isEmpty() << "\n";

    std::cout << "Find(2): " << map.find(2) << "\n";
    std::cout << "Size of Map (should be 1): " << map.size() << "\n";
}

void testHashSet(){
    HashSet<int> set;

    set.add(5);

    std::cout << "Contains 5: " << set.contains(5) << "\n";

    set.remove(5);
    
    std::cout << "Removed 5: " << set.contains(5) << "\n";

    int a = 10;
    int b = 4;

    set.add(a);
    set.add(b);
    set.add(7);

    std::cout << "Size: " << set.size() << "\n";
    std::cout << "Contains a = 10, passing a: " << set.contains(a) << "\n";
    std::cout << "Contains b = 4, passing 4: " << set.contains(4) << "\n";
    std::cout << "Contains 8 (should be false): " << set.contains(8) << "\n";
}

void testQueue(){
    Queue<int> q;

    int a = 5;
    q.enqueue(a);
    q.enqueue(10);

    std::cout << "First: " << q.front() << "\n";

    q.dequeue();

    std::cout << "First: " << q.front() << "\n";
}

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
    //testArrayList();

    //testLinkedList();

    //testStack();

    //testQueue();

    //testHashSet();

    testMap();

    return 0;
}