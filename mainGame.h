#pragma once
#include <time.h>
#include <iostream>
using namespace std;

struct Queue {
    int aq[10];
    int count;
    // Đầu
    int front;
    // Đuôi
    int rear;
};


// Function is used to generate random (2 or 4) number
int generateRandNum() {
    int option = rand() % 2;
    if(option == 0) return 2;
    if(option == 1) return 4;
}

bool isEmpty(int arr[][10], int i, int j) {
    if(arr[i][j] == 0) return true;
    return false;
}

// Function is used to generate random index if that index is empty fill number 2 or 4 into that index
void generateRandEmptyIndex(int arr[][10], int n) {
    // Generate random row index
    int i;
    int j;
    do {
        i = rand() % n;
        j = rand() % n;
    }
    arr[i][j] = generateRandNum();
}

void inittialize (int arr[][10], int n, int& score) {
    score = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            arr[i][j] = 0;
        }
    }
    generateRandEmptyIndex(arr, n);
}

/*
FUNCTION moveTiles(direction)
{
    FOR each row/column based on direction
    {
        SLIDE all tiles in the chosen direction
        MERGE adjacent tiles with the same value
        UPDATE score when merging occurs
        STORAGE State
    }
}

FUNCTION addRandomTile() 
{
    FIND all empty tiles
    IF empty tiles exist THEN
    {
        PLACE a random tile (2 or 4) at a random empty position
        STORAGE State
    }
}
*/


void initQueue(Queue& q) {
    q.count = 0;
    q.front = -1;
    q.rear = -1;
}

bool isEmptyQueue(const Queue& q) {
    return q.front == -1;
}

void enqueue(Queue& q, int number) {
    if(isEmptyQueue(q)) {
        q.front = 0;
        q.aq[q.front] = number;
        q.rear = 0;
        q.count++;
    } else {
        q.rear++;
        q.aq[q.rear] = number;
        q.count++;
    }
}

// Xóa giá trị front và trả về giá trị đã xóa

int dequeue(Queue& q) {
    if (isEmptyQueue(q)) return -1;
    int value = q.aq[q.front];
    q.front++;
    if (q.front > q.rear) {
        q.front = -1;
        q.rear = -1;
    }
    return value;
}

void moveUp(int arr[][10], int n) {
    for(int col = 0; col < n; col++) {
        int i = 0;
        int j = i + 1;
        while(i < n - 1 && j < n) {
            
            while(i < n - 1 && j < n && arr[i][col] != 0) {
                i++;
                j = i + 1;
            }
  
            while(i < n - 1 && j < n && arr[j][col] == 0) {
                j++;
            }
            
            if(i < n - 1 && j < n) {
                swap(arr[j][col], arr[i][col]);

            }
        }
    }
}


void mergeUp(int arr[][10], int n, Queue& q, int& count) {
    moveUp(arr, n);
    for(int col = 0; col < n; col++) {
        initQueue(q);
        int i = 0;
        for (int row = 0; row < n; row++) {
            if (arr[row][col] != 0) {
                enqueue(q, arr[row][col]);
            }
        }

        while (!isEmptyQueue(q)) {
            int value = dequeue(q);
            if (!isEmptyQueue(q) && value == q.aq[q.front]) {
                dequeue(q); // Lấy phần tử tiếp theo để hợp nhất
                arr[i++][col] = 2 * value;
                count += 2 * value;
            } else {
                arr[i++][col] = value;
            }
        }

        while( i < n) {
            arr[i++][col] = 0;
        }
        
    }
}

void moveDown(int arr[][10], int n) {
    for(int col = 0; col < n; col++) {
        int i = n - 1;
        int j = i - 1;
        while(i > 0 && j >= 0) {
            
            while(i > 0 && j >= 0 && arr[i][col] != 0) {
                i--;
                j = i - 1;
            }
            
            // đi từ cuối hàng
            while(i > 0 && j >= 0 && arr[j][col] == 0) {
                j--;
            }
            
            if(i > 0 && j >= 0) {
                swap(arr[j][col], arr[i][col]);

            }
        }
    }
}


void mergeDown(int arr[][10], int n, Queue& q, int &count) {
    moveDown(arr, n);
    for(int col = 0; col < n; col++) {
        initQueue(q);
        int i =  n - 1;
        for (int row = n - 1; row >= 0; row--) {
            if (arr[row][col] != 0) {
                enqueue(q, arr[row][col]);
            }
        }

        while (!isEmptyQueue(q)) {
            int value = dequeue(q);
            if (!isEmptyQueue(q) && value == q.aq[q.front]) {
                dequeue(q); // Lấy phần tử tiếp theo để hợp nhất
                arr[i--][col] = 2 * value;
                count += 2 * value;
                
            } else {
                arr[i--][col] = value;
            }
        }

        while( i >= 0) {
            arr[i--][col] = 0;
        }
        
    }
}
void moveLeft(int arr[][10], int n) {
    for(int row = 0; row < n; row++) {
        int i = 0;
        int j = i + 1;
        while(i < n - 1 && j < n) {
            
            while(i < n - 1 && j < n && arr[row][i] != 0) {
                i++;
                j = i + 1;
            }
            
  
            while(i < n - 1 && j < n && arr[row][j] == 0) {
                j++;
            }
            
            if(i < n - 1 && j < n) {
                swap(arr[row][j], arr[row][i]);

            }
        }
    }
}


void mergeLeft(int arr[][10], int n, Queue& q, int & count) {
    moveLeft(arr, n);
    for (int row = 0; row < n; row++) {
        initQueue(q);
        int i = 0;
        for(int col = 0; col < n; col++) {
            if (arr[row][col] != 0) {
                enqueue(q, arr[row][col]);
            }
        }

        while (!isEmptyQueue(q)) {
            int value = dequeue(q);
            if (!isEmptyQueue(q) && value == q.aq[q.front]) {
                dequeue(q); // Lấy phần tử tiếp theo để hợp nhất
                arr[row][i++] = 2 * value;
                count += 2 * value;
            } else {
                arr[row][i++] = value;
            }
        }

        while( i < n) {
            arr[row][i++] = 0;
        }
        
    }
}


void moveRight(int arr[][10], int n) {
    for(int row = 0; row < n; row++) {
        int i = n - 1;
        int j = i - 1;
        while(i > 0 && j >= 0) {
            
            while(i > 0 && j >= 0 && arr[row][i] != 0) {
                i--;
                j = i - 1;
            }
            
            // đi từ cuối hàng
            while(i > 0 && j >= 0 && arr[row][j] == 0) {
                j--;
            }
            
            if(i > 0 && j >= 0) {
                swap(arr[row][j], arr[row][i]);

            }
        }
    }
}

void mergeRight(int arr[][10], int n, Queue& q, int& count) {
    moveRight(arr, n);
    for (int row = 0; row < n; row++) {
        initQueue(q);
        int i =  n - 1;
        for (int col = n - 1; col >= 0; col--) {
            if (arr[row][col] != 0) {
                enqueue(q, arr[row][col]);
            }
        }

        while (!isEmptyQueue(q)) {
            int value = dequeue(q);
            if (!isEmptyQueue(q) && value == q.aq[q.front]) {
                dequeue(q); // Lấy phần tử tiếp theo để hợp nhất
                arr[row][i--] = 2 * value;
                count += 2 * value;
            } else {
                arr[row][i--] = value;
            }
        }

        while(i >= 0) {
            arr[row][i--] = 0;
        }
        
    }
}

void moveTiles(char direction, int arr[][10], int n, Queue& q,  int & score) {
    switch (direction)
    {
    case 'w':
        mergeUp(arr, n, q, score);
        break;
    
    case 's':
        mergeDown(arr, n, q, score);
        break;

    case 'a':
        mergeLeft(arr, n, q, score);
        break;

    case 'd':
        mergeRight(arr, n, q,  score);
        break;
    }

    generateRandEmptyIndex(arr, n);
}

void printBoard(int arr[][10], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << arr[i][j] << "\t";
        }
        cout << endl;
    }
}
