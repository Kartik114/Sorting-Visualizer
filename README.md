# Sorting-Visualizer

Visualization of different sorting algorithms in C++ with SDL2 library.

A sorting Algorithm is an algorithm which puts the elements of a list in a certain order. There are a large no of sorting algorithms today,
but a few dominate as they are optimal then others and faster in implementation. In this implementation of sorting visualizer we will be
looking at some of these popularly used sorting algorithms and see visually their working. So the sorting algorithms picked by me are 
Selection sort , Insertion sort , Bubble sort , Heap sort , Merge sort and Quick sort. We have fixed the size of list as 130 but alloted 
the elements randomly to array. The sorting algorithms will sort in Ascending order of array. I have delayed faster algoriths like Merge
sort , Heap sort to get proper visuals.




## How to Run:
You can run the cpp file available here in a code editor like Microsoft Visual studio one you download the project.
Though you need special library called SDL for the code to function properly.
I recommend you follow Lazy Foo' Productions' tutorial to setup SDL2 Library. PLEASE NOTE THAT the tutorial follows 
to setup SDL2 32-bit library but to run Sorting Visualizer, you have to use the 64-bit library. Just use x86_64-w64-mingw32 
folder instead of i686-w64-mingw32 to setup the SDL2 files. After setting up the  SDL2 library, just include the Sorting Visualizer.cpp 
file from the repository in your project with the build options as mentioned in the tutorial and build and run the project.


## How to Input :
Available keys to control the input are :

1. Press "0" for generating different random list of elements than the one mentioned.
2. Press "1" to start Selection Sort Algorithm.
3. Press "2" to start Insertion Sort Algorithm.
4. Press "3" to start Bubble Sort Algorithm.
5. Press "4" to start Merge Sort Algorithm.
6. Press "5" to start Quick Sort Algorithm.
7. Press "6" to start Heap Sort Algorithm.
8. Press "q" to exit out of Visualizer.
