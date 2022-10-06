#include<SDL.h>
#include<iostream>
#include<limits>
#include<time.h>
#include<string>
using namespace std;

const int SCREEN_WIDTH = 910;
const int SCREEN_HEIGHT = 750;

const int arrSize = 130;
const int rectSize = 7;

int arr[arrSize];
int Barr[arrSize];

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

bool complete = false;

bool init()
{
    bool success = true;
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cout << "Couldn't initialize SDL. SDL_Error: " << SDL_GetError();
        success = false;
    }
    else
    {
        if (!(SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")))
        {
            cout << "Warning: Linear Texture Filtering not enabled.\n";
        }

        window = SDL_CreateWindow("Sorting Visualizer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL)
        {
            cout << "Couldn't create window. SDL_Error: " << SDL_GetError();
            success = false;
        }
        else
        {
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if (renderer == NULL)
            {
                cout << "Couldn't create renderer. SDL_Error: " << SDL_GetError();
                success = false;
            }
        }
    }

    return success;
}

void close()
{
    SDL_DestroyRenderer(renderer);
    renderer = NULL;

    SDL_DestroyWindow(window);
    window = NULL;

    SDL_Quit();
}

void visualize(int x = -1, int y = -1, int z = -1)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0); // set color for drawing window.
    SDL_RenderClear(renderer); //clear entire screen to our display colour.

    int j = 0;
    for (int i = 0; i <= SCREEN_WIDTH - rectSize; i += rectSize)
    {
        //SDL_PumpEvents() gathers all the pending input information from devices and places it in the event queue. 
        SDL_PumpEvents();

        SDL_Rect rect = { i, 0, rectSize, arr[j] }; // x, y, width, height
        if (complete)
        {
            SDL_SetRenderDrawColor(renderer, 100, 300, 100, 0);
            SDL_RenderDrawRect(renderer, &rect); //Draw a rectangle on the current rendering target.
        }
        else if (j == x)
        {
            SDL_SetRenderDrawColor(renderer, 100, 250, 100, 0);
            SDL_RenderFillRect(renderer, &rect);
        }
        else if (j == y)
        {
            SDL_SetRenderDrawColor(renderer, 250, 100, 100, 0);
            SDL_RenderFillRect(renderer, &rect);
        }
        else if (j == z)
        {
            SDL_SetRenderDrawColor(renderer, 100, 100, 250, 0);
            SDL_RenderFillRect(renderer, &rect);

        }
        else
        {
            SDL_SetRenderDrawColor(renderer, 170, 183, 184, 0);
            SDL_RenderDrawRect(renderer, &rect);
        }
        j++;
    }
    SDL_RenderPresent(renderer);//Update the screen with any rendering performed since the previous call.
}

void inplaceHeapSort(int* input, int n)
{
    for (int i = 1; i < n; i++)
    {
        int childIndex = i;
        int parentIndex = (childIndex - 1) / 2;

        while (childIndex > 0)
        {
            if (input[childIndex] > input[parentIndex])
            {
                int temp = input[parentIndex];
                input[parentIndex] = input[childIndex];
                input[childIndex] = temp;

            }
            else
            {
                break;
            }

            visualize(parentIndex, childIndex);
            SDL_Delay(40);

            childIndex = parentIndex;
            parentIndex = (childIndex - 1) / 2;
        }
    }

    for (int idx = n - 1; idx >= 0; idx--)
    {
        int temp = input[0];
        input[0] = input[idx];
        input[idx] = temp;

        int parentIndex = 0;
        int leftChildIndex = 2 * parentIndex + 1;
        int rightChildIndex = 2 * parentIndex + 2;

        while (leftChildIndex < idx)
        {
            int mx = parentIndex;

            if (input[leftChildIndex] > input[mx])
            {
                mx = leftChildIndex;
            }
            if (rightChildIndex<idx && input[rightChildIndex]>input[mx])
            {
                mx = rightChildIndex;
            }
            if (mx == parentIndex)
            {
                break;
            }

            int temp = input[parentIndex];
            input[parentIndex] = input[mx];
            input[mx] = temp;

            visualize(mx, parentIndex, idx);
            SDL_Delay(40);

            parentIndex = mx;
            leftChildIndex = 2 * parentIndex + 1;
            rightChildIndex = 2 * parentIndex + 2;
        }
    }
}

int partition_array(int a[], int si, int ei)
{
    int c = 0;

    for (int i = (si + 1); i <= ei; i++)
    {
        if (a[i] <= a[si])
        {
            c++;
        }
    }
    c += si;
    int temp = a[c];
    a[c] = a[si];
    a[si] = temp;
    visualize(c, si);
    SDL_Delay(1);
    int i = si, j = ei;

    while (i<c && j>c)
    {
        if (a[i] <= a[c])
        {
            i++;
        }
        else if (a[j] > a[c])
        {
            j--;
        }
        else
        {
            int temp_1 = a[j];
            a[j] = a[i];
            a[i] = temp_1;

            visualize(i, j);
            SDL_Delay(70);

            i++;
            j--;
        }
    }
    return c;
}

void quickSort(int a[], int si, int ei)
{
    if (si >= ei)
    {
        return;
    }

    int c = partition_array(a, si, ei);
    quickSort(a, si, c - 1);
    quickSort(a, c + 1, ei);

}

void merge(int a[], int si, int ei)
{
    int size_output = (ei - si) + 1;
    int* output = new int[size_output];

    int mid = (si + ei) / 2;
    int i = si, j = mid + 1, k = 0;
    while (i <= mid && j <= ei)
    {
        if (a[i] <= a[j])
        {
            output[k] = a[i];
            visualize(i,j,k);
            SDL_Delay(10);
            i++;
            k++;
        }
        else
        {
            output[k] = a[j];
            visualize(i, j,k);
            SDL_Delay(10);
            j++;
            k++;
        }

    }
    while (i <= mid)
    {
        output[k] = a[i];
        visualize(i,-1,k);
        SDL_Delay(10);
        i++;
        k++;
    }
    while (j <= ei)
    {
        output[k] = a[j];
        visualize(-1, j,k);
        SDL_Delay(10);
        j++;
        k++;
    }
    int x = 0;
    for (int l = si; l <= ei; l++)
    {
        a[l] = output[x];
        visualize(l);
        SDL_Delay(10);
        x++;
    }
    delete[]output;
}

void mergeSort(int a[], int si, int ei)
{
    if (si >= ei)
    {
        return;
    }
    int mid = (si + ei) / 2;

    mergeSort(a, si, mid);
    mergeSort(a, mid + 1, ei);

    merge(a, si, ei);
}

void bubbleSort()
{
    for (int i = 0; i < arrSize - 1; i++)
    {
        bool f = false;
        for (int j = 0; j < arrSize - 1 - i; j++)
        {
            if (arr[j + 1] < arr[j])
            {
                f = true;
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;

                visualize(j,j+1,i);
            }
            SDL_Delay(1);
        }
        if (!f)
            break;
    }
}

void insertionSort()
{


    for (int i = 0; i < arrSize; i++)
    {
        for (int j = i - 1; j >= 0; j--)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
                visualize(j,j+1,i);
               
            }
            else
                break;
            SDL_Delay(1);
        }
    }
    
}

void selectionSort()
{


    for (int i = 0; i < arrSize; i++)
    {
        int mn = arr[i], idx = i;
        for (int j = i + 1; j < arrSize; j++)
        {
            if (arr[j] < mn)
            {
                mn = arr[j];
                idx = j;
                visualize(-1, idx,i);
            }
         
            SDL_Delay(1);
        }
        visualize(i,idx);
        SDL_Delay(1);
        swap(arr[idx], arr[i]);

    }
}

void loadArray()
{
    memcpy(arr, Barr, sizeof(int) * arrSize);
}

void randomizeAndSaveArray()
{
    unsigned int seed = (unsigned)time(NULL);
    srand(seed);
    for (int i = 0; i < arrSize; i++)
    {
        int random = rand() % (SCREEN_HEIGHT);
        Barr[i] = random;
    }
}

void execute()
{
    if (!init()) // window initialisation
    {
        cout << "SDL Initialization Failed.\n";
    }
    else
    {
        randomizeAndSaveArray(); 
        loadArray();

        SDL_Event e;
        bool quit = false;
        while (!quit)
        {
            while (SDL_PollEvent(&e) != 0) //poll until all events are handled!
            {
                if (e.type == SDL_QUIT) // quit 
                {
                    quit = true;
                    complete = false;
                }
                else if (e.type == SDL_KEYDOWN) // press keyboard key
                {
                    switch (e.key.keysym.sym)
                    {
                    case(SDLK_q):
                        quit = true;
                        complete = false;
                        cout << "\nEXITING SORTING VISUALIZER.\n";
                        break;
                    case(SDLK_0):
                        randomizeAndSaveArray();
                        complete = false;
                        loadArray();
                        cout << "\nNEW RANDOM LIST GENERATED.\n";
                        break;
                    case(SDLK_1):
                        loadArray();
                        cout << "\nSELECTION SORT STARTED.\n";
                        complete = false;
                        selectionSort();
                        complete = true;
                        cout << "\nSELECTION SORT COMPLETE.\n";
                        break;
                    case(SDLK_2):
                        loadArray();
                        cout << "\nINSERTION SORT STARTED.\n";
                        complete = false;
                        insertionSort();
                        complete = true;
                        cout << "\nINSERTION SORT COMPLETE.\n";
                        break;
                    case(SDLK_3):
                        loadArray();
                        cout << "\nBUBBLE SORT STARTED.\n";
                        complete = false;
                        bubbleSort();
                        complete = true;
                        cout << "\nBUBBLE SORT COMPLETE.\n";
                        break;
                    case(SDLK_4):
                        loadArray();
                        cout << "\nMERGE SORT STARTED.\n";
                        complete = false;
                        mergeSort(arr, 0, arrSize - 1);
                        complete = true;
                        cout << "\nMERGE SORT COMPLETE.\n";
                        break;
                    case(SDLK_5):
                        loadArray();
                        cout << "\nQUICK SORT STARTED.\n";
                        complete = false;
                        quickSort(arr, 0, arrSize - 1);
                        complete = true;
                        cout << "\nQUICK SORT COMPLETE.\n";
                        break;
                    case(SDLK_6):
                        loadArray();
                        cout << "\nHEAP SORT STARTED.\n";
                        complete = false;
                        inplaceHeapSort(arr, arrSize);
                        complete = true;
                        cout << "\nHEAP SORT COMPLETE.\n";
                        break;
                    }
                }
            }
            visualize(-1,-1,-1);
        }
        close();
    }
}

bool controls()
{
    cout << "WARNING: Giving repetitive commands may cause latency and the visualizer may give unexpected results. Please give a new command only after the current command's execution is done.\n\n"
        << "Basic Controls inside the Sorting Visualizer:-\n" << endl;

        cout<< "    Use 0 to Generate a different randomized list.\n"
        << "    Use 1 to start Selection Sort Algorithm.\n"
        << "    Use 2 to start Insertion Sort Algorithm.\n"
        << "    Use 3 to start Bubble Sort Algorithm.\n"
        << "    Use 4 to start Merge Sort Algorithm.\n"
        << "    Use 5 to start Quick Sort Algorithm.\n"
        << "    Use 6 to start Heap Sort Algorithm.\n"
        << "    Use 'q' to exit out of Sorting Visualizer\n\n"
        << "PRESS \"ENTER\" TO START SORTING VISUALIZER...\n\n"
        << "Or type -1 and press ENTER to quit the program.";

    string s;
    getline(cin, s);
    if (s == "-1")
    {
        return false;
    }
    return true;
}

void entry()
{
    cout << "                                  SORTING VISUALIZER                       " << endl;

        cout << " Few points to be Noted:" << endl;
        cout << endl;
        cout << "1. Visualisation of different sorting algorithms in c++ with C++ SDL library. A sorting Algorithm is the one which put the list / array in an Ascending or Descending order. We know a lot of sorting algorithms , while prefer a few in practice  based on their implementations." << endl;
        cout << endl;
        cout << "2. In this sorting visualizer , we will be looking at some of the well known sorting algorithms and visually compare their working. " << endl;
        cout << endl;
        cout << "3. We pick the following sorting algorithms : Insertion sort , Selection sort , Bubble sort , Merge sort , Quick sort and  Heap sort. " << endl;
        cout << endl;
        cout << "4. We have made a predefined list/array  of elements in the code as 130 and we have the functionality to randomise the     elements in the list." << endl;
        cout << endl;
        cout << "5. Kindly Press \"Enter\" for knowing the controls." << endl;

    string s;
    getline(cin, s);
    if (s == "\n")
    {
        return;
    }
}

int main(int argc, char* args[])
{
    entry();

    while (1)
    {
        cout << endl;
        if (controls())
            execute();
        else
        {
            cout<<endl;
            cout << " Exiting program."<<endl;
            break;
        }
    }

    return 0;
}
