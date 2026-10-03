#include <iostream>
#include <fstream>
#include <iomanip> 

using namespace std;

const int MAX = 10;
int A[MAX][MAX], B[MAX][MAX], C[MAX][MAX], N;

// Print matrix with alignment
void printMat(int mat[MAX][MAX]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << setw(4) << mat[i][j] << " ";
        }
        cout << "\n";
    }
}

// 1. Read input file
bool readMatrices(const char* filename) {
    ifstream file(filename);
    if (!file) {
        cout << "Error opening file: " << filename << "\n";
        return false;
    }

    file >> N;
    if (N <= 0 || N > MAX) {
        cout << "Invalid N\n";
        return false;
    }

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) file >> A[i][j];

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) file >> B[i][j];

    file.close();
    return true;
}

// 2. Add matrices
void addMatrices() {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) C[i][j] = A[i][j] + B[i][j];
}

// 3. Multiply matrices
void multiplyMatrices() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++) C[i][j] += A[i][k] * B[k][j];
        }
    }
}

// 4. Diagonal sums
void printDiagonalSums() {
    int mainDiag = 0, secDiag = 0;
    for (int i = 0; i < N; i++) {
        mainDiag += A[i][i];
        secDiag += A[i][N - 1 - i];
    }
    cout << "Main Diagonal: " << mainDiag << "\nSecondary Diagonal: " << secDiag << "\n";
}

// 5. Swap rows
void swapRows(int r1, int r2) {
    if (r1 < 0 || r1 >= N || r2 < 0 || r2 >= N) {
        cout << "Invalid row index\n";
        return;
    }
    
    for (int j = 0; j < N; j++) {
        int t = A[r1][j];
        A[r1][j] = A[r2][j];
        A[r2][j] = t;
    }
    printMat(A);
}

// 6. Swap columns
void swapColumns(int c1, int c2) {
    if (c1 < 0 || c1 >= N || c2 < 0 || c2 >= N) {
        cout << "Invalid column index\n";
        return;
    }
    
    for (int i = 0; i < N; i++) {
        int t = A[i][c1];
        A[i][c1] = A[i][c2];
        A[i][c2] = t;
    }
    printMat(A);
}

// 7. Update element
void updateElement(int row, int col, int newVal) {
    if (row < 0 || row >= N || col < 0 || col >= N) {
        cout << "Invalid position\n";
        return;
    }
    
    A[row][col] = newVal;
    printMat(A);
}

int main(int argc, char* argv[]) {
    const char* inputFileName = "input.txt";
    if (argc > 1){
        inputFileName = argv[1];
    }

    if (!readMatrices(inputFileName)) return 1;

    ofstream outFile("output.txt");
    if (!outFile){
        cout << "Error creating output file \n";
        return 1;
    }
    streambuf* coutbuf = cout.rdbuf();
    cout.rdbuf(outFile.rdbuf());

    cout << "=== Matrix A ===\n"; printMat(A);
    cout << "\n=== Matrix B ===\n"; printMat(B);

    cout << "\n=== Addition (A + B) ===\n";
    addMatrices();
    printMat(C);

    cout << "\n=== Multiplication (A * B) ===\n";
    multiplyMatrices();
    printMat(C);

    cout << "\n=== Diagonal Sums (A) ===\n";
    printDiagonalSums();

    int r1 = 0, r2 = 2;
    cout << "\n=== Swap Rows " << r1 << " and " << r2 << " (A) ===\n";
    swapRows(r1, r2);

    int c1 = 1, c2 = 3;
    cout << "\n=== Swap Columns " << c1 << " and " << c2 << " (A) ===\n";
    swapColumns(c1, c2);

    int row = 1, col = 1, newVal = 99;
    cout << "\n=== Update Position (" << row << ", " << col << ") to " << newVal << " (A) ===\n";
    updateElement(row, col, newVal);

    cout.rdbuf(coutbuf);
    outFile.close();

    return 0;
}