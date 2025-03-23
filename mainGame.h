#pragma once
#include <time.h>
#include <iostream>
using namespace std;

struct Queue {
    int aq[10];
    int count;
    int front;
    int rear;
};


// Function is used to generate random (2 or 4) number
int generateRandNum() {
    int option = rand() % 2;
    if(option == 0) return 2;
    if(option == 1) return 4;
}

// Function to check if that index is empty
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

// Function to get new game
void inittialize (int arr[][10], int n, int& score) {
    score = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            arr[i][j] = 0;
        }
    }
    generateRandEmptyIndex(arr, n);
}

// Function to initialize queue
void initQueue(Queue& q) {
    q.count = 0;
    q.front = -1;
    q.rear = -1;
}

// Function to check is queue empty
bool isEmptyQueue(const Queue& q) {
    return q.front == -1;
}

// Function to add new value to rear
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

// Function to move up
void moveUp(int arr[][10], int n) {
    for(int col = 0; col < n; col++) {
        // Khai báo hai chỉ số ở đầu cột
        int i = 0;
        int j = i + 1;
        while(i < n - 1 && j < n) {
            // Bỏ qua các số khác 0 ở phía đầu cột
            while(i < n - 1 && j < n && arr[i][col] != 0) {
                i++;
                j = i + 1;
            }
            // Tìm các số có giá trị khác 0 ở phía sau
            while(i < n - 1 && j < n && arr[j][col] == 0) {
                j++;
            }

            // hoán đổi vị trí của i và j
            if(i < n - 1 && j < n) {
                swap(arr[j][col], arr[i][col]);
            }
        }
    }
}

// Function to merge up using queue
void mergeUp(int arr[][10], int n, Queue& q, int& count) {
    // Dồn lên phía trên
    moveUp(arr, n);
    for(int col = 0; col < n; col++) {
        // Mỗi cột sử dụng một queue mới
        initQueue(q);
        int i = 0;
        // Đẩy các giá trị khác 0 của cột vào queue
        for (int row = 0; row < n; row++) {
            if (arr[row][col] != 0) {
                enqueue(q, arr[row][col]);
            }
        }

        // Chạy cho đến khi queue rỗng
        while (!isEmptyQueue(q)) {
            // Lấy giá trị đầu tiên ra khỏi queue
            int value = dequeue(q);
            
            // Nếu như queue còn tồn tại giá trị và giá trị đầu bằng giá trị đã lấy ra
            if (!isEmptyQueue(q) && value == q.aq[q.front]) {
                // Lấy phần tử tiếp theo để hợp nhất
                dequeue(q); 
                // Gộp giá trị và cập nhật giá trị của mảng
                arr[i++][col] = 2 * value;
                // Tính điểm thưởng
                count += 2 * value;
            } 
            // Nếu queue rỗng hoặc hai giá trị không bằng nhau thì giữ nguyên giá trị và cập nhật lại vào mảng
            else {
                arr[i++][col] = value;
            }
        }
        
        // Nếu cập nhật xong mà vẫn còn chỗ trong mảng thì những chỗ trống đó bằng 0
        while(i < n) {
            arr[i++][col] = 0;
        }
        
    }
}

// Function to move down
void moveDown(int arr[][10], int n) {
    for(int col = 0; col < n; col++) {
        // Khai báo hai chỉ số chạy từ dưới lên
        int i = n - 1;
        int j = i - 1;
        while(i > 0 && j >= 0) {
            // Bỏ qua các số khác 0
            while(i > 0 && j >= 0 && arr[i][col] != 0) {
                i--;
                j = i - 1;
            }
            
            // Bỏ qua các số bằng 0 
            while(i > 0 && j >= 0 && arr[j][col] == 0) {
                j--;
            }

            // swap hai số có chỉ só i và j
            if(i > 0 && j >= 0) {
                swap(arr[j][col], arr[i][col]);

            }
        }
    }
}

// Function to merge down
void mergeDown(int arr[][10], int n, Queue& q, int &count) {
    // Dồn các số xuống dưới
    moveDown(arr, n);
    for(int col = 0; col < n; col++) {
        // Mỗi cột khởi tạo lại 1 queue
        initQueue(q);
        int i =  n - 1;
        
        for (int row = n - 1; row >= 0; row--) {
            // Bỏ vào queue các số khác 0
            if (arr[row][col] != 0) {
                enqueue(q, arr[row][col]);
            }
        }
        // Chạy tới hết queue
        while (!isEmptyQueue(q)) {
            // Lấy ra giá trị đầu tiên
            int value = dequeue(q);
            // Nếu queue còn giá trị và giá trị bằng giá trị đã lấy ra thì cập nhật lại cột và tăng điểm thưởng
            if (!isEmptyQueue(q) && value == q.aq[q.front]) {
                dequeue(q); // Lấy phần tử tiếp theo để hợp nhất
                arr[i--][col] = 2 * value;
                count += 2 * value;
                
            } 
            // Còn không thì trả lại giá trị đó vào cột
            else {
                arr[i--][col] = value;
            }
        }
        // Nếu chưa hết cột thì điền số 0 vào 
        while(i >= 0) {
            arr[i--][col] = 0;
        }
    }
}

// Function to move left
void moveLeft(int arr[][10], int n) {
    for(int row = 0; row < n; row++) {
        // Khai báo hai chỉ số chạy từ đầu hàng i trước j sau
        int i = 0;
        int j = i + 1;
        while(i < n - 1 && j < n) {
            // Bỏ qua các số khác 0 
            while(i < n - 1 && j < n && arr[row][i] != 0) {
                i++;
                j = i + 1;
            }
            // Bỏ qua các số bằng 0
            while(i < n - 1 && j < n && arr[row][j] == 0) {
                j++;
            }
            // Hoán đổi giá trị của hai chỉ số i và j
            if(i < n - 1 && j < n) {
                swap(arr[row][j], arr[row][i]);

            }
        }
    }
}

// Function to merge left
void mergeLeft(int arr[][10], int n, Queue& q, int & count) {
    // Dồn các số về phía bên trái
    moveLeft(arr, n);
    for (int row = 0; row < n; row++) {
        // Khởi tạo lại queue cho mỗi hàng
        initQueue(q);
        int i = 0;

        // Dồn các giá trị khác 0 vào queue
        for(int col = 0; col < n; col++) {
            if (arr[row][col] != 0) {
                enqueue(q, arr[row][col]);
            }
        }

        while (!isEmptyQueue(q)) {
            // Lấy ra giá trị đầu tiên của queue
            int value = dequeue(q);
            // Nếu như queue vẫn còn giá trị và giá trị tiếp theo bằng giá trị đã lấy ra thì lấy phần tử tiếp theo để hợp nhất và cập nhật lại giá trị của hàng và tăng điểm thưởng
            if (!isEmptyQueue(q) && value == q.aq[q.front]) {
                dequeue(q);
                arr[row][i++] = 2 * value;
                count += 2 * value;
            } 
            // Nếu không thì chỉ cập nhật lại hàng bằng giá trị vừa được lấy ra khỏi queue
            else {
                arr[row][i++] = value;
            }
        }

        // Nếu còn thiếu giá trị của hàng thì điền số 0 vào cuối
        while( i < n) {
            arr[row][i++] = 0;
        }
        
    }
}

// Function to move right
void moveRight(int arr[][10], int n) {
    for(int row = 0; row < n; row++) {
        // Khởi tạo hai giá trị ở đầu cuối mỗi hàng 
        int i = n - 1;
        int j = i - 1;
        while(i > 0 && j >= 0) {
            // Bỏ qua các số có giá trị khác 0
            while(i > 0 && j >= 0 && arr[row][i] != 0) {
                i--;
                j = i - 1;
            }
            
            // Bỏ qua các số có giá trị bằng 0
            while(i > 0 && j >= 0 && arr[row][j] == 0) {
                j--;
            }

            // Hoán đổi giá trị của hai vị trí i và j
            if(i > 0 && j >= 0) {
                swap(arr[row][j], arr[row][i]);

            }
        }
    }
}

// Function to merge right
void mergeRight(int arr[][10], int n, Queue& q, int& count) {
    // Dồn các số về bên phải
    moveRight(arr, n);
    for (int row = 0; row < n; row++) {
        // Mỗi hàng khởi tạo lại queue
        initQueue(q);
        int i =  n - 1;

        // Dồn các số khác 0 vào queue
        for (int col = n - 1; col >= 0; col--) {
            if (arr[row][col] != 0) {
                enqueue(q, arr[row][col]);
            }
        }

        while (!isEmptyQueue(q)) {
            // Lấy ra giá trị đầu tiên của queue
            int value = dequeue(q);

            // Nếu như queue còn giá trị và giá trị tiếp theo bằng giá trị đã lấy ra  thì lấy phần tử tiếp theo đó ra khỏi queue và hợp nhật rồi cập nhật lại vào hàng
            if (!isEmptyQueue(q) && value == q.aq[q.front]) {
                dequeue(q); // Lấy phần tử tiếp theo để hợp nhất
                arr[row][i--] = 2 * value;
                count += 2 * value;
            }
            // Nếu không thì cập nhật lại giá trị của hàng bằng giá trị đã lấy ra
            else {
                arr[row][i--] = value;
            }
        }
        // Nếu sau khi cập nhật lại mà mảng còn trống thì fill bằng số 0
        while(i >= 0) {
            arr[row][i--] = 0;
        }
        
    }
}

// Function to move depending on direction
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
}


// Function to print the board
void printBoard(int arr[][10], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << arr[i][j] << "\t";
        }
        cout << endl;
    }
}
