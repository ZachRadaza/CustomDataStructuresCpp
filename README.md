# Custom Data Structures in C++

Making custom data structures in C++ to better understand memory management, pointers, and templates. I plan to create these data structures as practice.
 - ArrayList
 - LinkedList
 - Stack
 - Queue
 - HashSet
 - TreeSet
 - Map

 Important Takeaways from project
 - Use of Templates, and a DEEEEEEEEPER understanding of memory and pointers
 - transfer of ownership
 - Difference of using const in function headers (for const return type and const not modifying object -> "const Type foo() const{}")
 - Using "->" for object pointers as to using "."
 - Use of struct in classes
 - No automatic garbage collection, always delete
 - using array of pointers
 - Template pointers

 ## To Run

Run these commands from the root of the project folder

```bash
 cmake -S . -B build
 cmake --build build    
 ./build/DataStructures
 ```