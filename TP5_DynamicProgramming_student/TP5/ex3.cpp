#include "exercises.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include <vector>
#include <algorithm>
using namespace std;

int editDistance(string pattern, string text) {
    int n = pattern.size();
    int m = text.size();
    vector<vector<int>> dp(n+1, vector<int>(m+1, 0));
    for (int i = 0; i <= n; i++) dp[i][0] = i;
    for (int j = 0; j <= m; j++) dp[0][j] = j;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int cost = (pattern[i-1] == text[j-1]) ? 0 : 1;
            dp[i][j] = min({
                dp[i-1][j] + 1,
                dp[i][j-1] + 1,
                dp[i-1][j-1] + cost
            });
        }
    }
    return dp[n][m];
}

float numApproximateStringMatching(string filename, string toSearch) {
    ifstream file(filename);
    if (!file.is_open()) return 0;
    string word;
    int totalDistance = 0;
    int count = 0;
    while (file >> word) {
        totalDistance += editDistance(word, toSearch);
        count++;
    }
    file.close();
    if (count == 0) return 0;
    return (float) totalDistance / count;
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP5_Ex3, testEditDistance) {
    EXPECT_EQ(3, editDistance("abcdefghijkl", "bcdeffghixkl"));
    EXPECT_EQ(3, editDistance("bcdeffghixkl", "abcdefghijkl"));

    EXPECT_EQ(1, editDistance("", "b"));
    EXPECT_EQ(1, editDistance("a", ""));
    EXPECT_EQ(1, editDistance("a", "b"));
    EXPECT_EQ(0, editDistance("", ""));
    EXPECT_EQ(0, editDistance("a", "a"));
}



#define REL_PATH std::string("../TP5/testsEx3/") // relative path to the tests

TEST(TP5_Ex3, testNumApproximateStringMatching) {
    const float delta = 0.01;

    const float expected1 = 7.76;
    float dist1 = numApproximateStringMatching(REL_PATH + "text1.txt", "estrutur");
    ASSERT_LE(expected1-delta, dist1);
    ASSERT_GE(expected1+delta, dist1);

    const float expected2 = 7.49;
    float dist2 = numApproximateStringMatching(REL_PATH + "text2.txt", "estrutur");
    ASSERT_LE(expected2-delta, dist2);
    ASSERT_GE(expected2+delta, dist2);
}

