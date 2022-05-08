#include <stdio.h>
#include <vector>
using namespace std;
void classicView(int m, int n, vector <vector<int>> mx, char mxname){
    printf("Classic matrix %c view: \n", mxname);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%2d ", mx[i][j]);
        }
        printf("\n");
    }
}
vector <vector<int>> expander(int m, int n, vector <int> M, vector <int> A){
    vector <vector<int>> mx(m, vector<int> (n, 0));
    int pos = 0; // triplet column position in vector A
    for (int k = 0; k < M.size(); k++){
        mx[k].resize(n);
        for (int j = 0; j < n; j++){
            if (M[k] == 0){break;}
            if (j == A[pos] - 1){
                mx[k][A[pos]-1] = A[pos+1];
                if(A[pos+2] == 0){ // if there is no non-zero after element, go next line
                    pos+=3;
                    break;
                }
                pos+=3;
            }
        }
    }
    return mx;
}
void shortener(int m, int n, vector <vector<int>> mx, char mxname){
    vector <int> M, A;
    for (int k = 0; k < m; k++) {
        bool startFound = false;
        for (int j = 0; j < n; j++) {
            if (mx[k][j] != 0) {
                if (startFound == false) {
                    M.push_back(j + 1); // found first non-zero element
                    startFound = true; // flag to prevent re-writing MA[k]
                } else {
                    A.push_back(j + 1); // add the "next non-zero element", but 1st found element protected from that by the flag
                }
                A.push_back(j + 1); // add column number
                A.push_back(mx[k][j]); // add value of non-zero element
            }
        }
        if(startFound == false){
            M.push_back(0);
            continue;
        }
        A.push_back(0); // processing of any line will give zero at end because there are no elements after last element
    }
    printf("\nM of matrix %c: ", mxname);
    for (int i = 0; i < m; i++){
        printf("%d",M[i]);
    }
    printf("\nA of matrix %c: ", mxname);
    for (int i = 0; i < A.size(); i++){
        printf("%d ", A[i]);
    }
    printf("\n");
}
int main() {
    int mA, nA, mB, nB;
    int lAA, lAB;
    vector<int> MA, MB, AA, AB;
    //
    // Matrix A inputs
    //
    printf("Enter number of lines of matrix A: ");
    scanf("%d", &mA);
    MA.resize(mA);
    printf("\nEnter number of columns of matrix A: ");
    scanf("%d", &nA);
    printf("\nEnter M array for matrix A:\n");
    for(int i = 0; i < mA; i++){
        scanf("%d", &MA[i]);
    }
    A:
    printf("Enter length of array A for matrix A:");
    scanf("%d", &lAA);
    if(lAA %3 != 0){
        printf("Error. Your array should contain triplets of numbers.\n");
        goto A;
    }
    AA.resize(lAA);
    printf("\nEnter A array for matrix A\n");
    for(int i = 0; i < lAA; i++){
        scanf("%d", &AA[i]);
    }
    //
    // Matrix B inputs
    //
    printf("Enter number of lines of matrix B: ");
    scanf("%d", &mB);
    MB.resize(mB);
    if (nA != mB){
        printf("Warning! Can't perform multiply: matrix sizes doesn't match.\n");
    }
    printf("\nEnter number of columns of matrix B: ");
    scanf("%d", &nB);
    printf("\nEnter M array for matrix B:\n");
    for(int i = 0; i < mB; i++){
        scanf("%d", &MB[i]);
    }
    B:
    printf("Enter length of array A for matrix B:");
    scanf("%d", &lAB);
    if(lAB %3 != 0){
        printf("Error. Your array should contain triplets of numbers.\n");
        goto B;
    }
    AB.resize(lAB);
    printf("\nEnter A array for matrix B\n");
    for(int i = 0; i < lAB; i++){
        scanf("%d", &AB[i]);
    }
    //
    // Matrix A expanding
    //
    vector <vector<int>> mxA = expander(mA, nA, MA, AA);
    classicView(mA, nA, mxA, 'A');
    //
    // Matrix B expanding
    //
    vector <vector<int>> mxB = expander(mB, nB, MB, AB);
    classicView(mB, nB, mxB, 'A');

    //
    // Multiplying
    //

    vector <vector<int>> mxD(mA, vector<int> (nB, 0));
    if (nA == mB){
        for (int line = 0; line < nA; line++){
            for (int column = 0; column < nB; column++){
                for(int i = 0; i < mA; i++){
                    mxD[line][column] += mxA[line][i]*mxB[i][column];
                }
            }
        }
    }
    printf("Result of multiplying: \n");
    classicView(mA, nB, mxD, 'C');

    //full A to short
    shortener(mA, nA, mxA, 'A');

    // full B to short
    shortener(mB, nB, mxB, 'B');

    return 0;
}
