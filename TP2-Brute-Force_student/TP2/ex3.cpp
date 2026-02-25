// By: Gonçalo Leão

unsigned int integerKnapsack(unsigned int values[], unsigned int weights[], unsigned int n, unsigned int maxWeight, bool usedItems[]) {
    int total=1,res,max=0;
    for (unsigned int i = 0; i < n; i++) {
        total*=2;
    }
    for (unsigned int i = 0; i < total; i++) {
        int m=i,w=0,sum=0;
        for (unsigned int j = 0; j < n; j++) {
            usedItems[j]=false;
        }
        for (unsigned int j = 0; j < n; j++) {
            if (m%2==1) {
                w+=weights[j];
                sum+=values[j];
                usedItems[j]=true;
            }
            m/=2;
        }
        if (sum>max && w<=maxWeight) {
            max=sum;
            res=i;
        }
    }
    for (unsigned int j = 0; j < n; j++) {
        if (res%2==1) {
            usedItems[j]=true;
        }
        else {
            usedItems[j]=false;
        }
        res/=2;
    }
    return max;
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP2_Ex3, testKnapsack_4items) {
    const unsigned int n = 4;
    {
        unsigned int values[n] = {10, 7, 11, 15};
        unsigned int weights[n] = {1, 2, 1, 3};
        bool usedItems[n];

        EXPECT_EQ(integerKnapsack(values, weights, n, 5, usedItems), 36);
        EXPECT_EQ(usedItems[0], true);
        EXPECT_EQ(usedItems[1], false);
        EXPECT_EQ(usedItems[2], true);
        EXPECT_EQ(usedItems[3], true);
    }

    {
        unsigned int values[n] = {3, 4, 5, 6};
        unsigned int weights[n] = {2, 3, 4, 5};
        bool usedItems[n];

        EXPECT_EQ(integerKnapsack(values, weights, n, 5, usedItems), 7);
        EXPECT_EQ(usedItems[0], true);
        EXPECT_EQ(usedItems[1], true);
        EXPECT_EQ(usedItems[2], false);
        EXPECT_EQ(usedItems[3], false);
    }
}

TEST(TP2_Ex3, testKnapsack_5items) {
    const unsigned int n = 5;
    {
        unsigned int values[n] = {1, 2, 5, 9, 4};
        unsigned int weights[n] = {2, 3, 3, 4, 6};
        bool usedItems[n];

        EXPECT_EQ(integerKnapsack(values, weights, n, 10, usedItems), 16);
        EXPECT_EQ(usedItems[0], false);
        EXPECT_EQ(usedItems[1], true);
        EXPECT_EQ(usedItems[2], true);
        EXPECT_EQ(usedItems[3], true);
        EXPECT_EQ(usedItems[4], false);
    }
}