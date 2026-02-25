// By: Gonçalo Leão
// With contributions by Eduardo Almeida

int maxSubsequence(int A[], unsigned int n, unsigned int &i, unsigned int &j) {
    int maxSum=A[0];
    int curSum=A[0];
    i=0;
    j=0;
    unsigned int start=0;
    for (unsigned int k=1; k<n; k++) {
        if (curSum+A[k]<A[k]) {
            curSum=A[k];
            start=k;
        } else {
            curSum+=A[k];
        }
        if (curSum>maxSum){
            maxSum=curSum;
            i=start;
            j=k;
        }
    }
    return maxSum;
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP2_Ex1, maxSubsequence) {
    int A[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    unsigned int n = 9;
    unsigned int i, j;
    EXPECT_EQ(maxSubsequence(A,n,i,j), 6);
    EXPECT_EQ(i, 3);
    EXPECT_EQ(j, 6);
}