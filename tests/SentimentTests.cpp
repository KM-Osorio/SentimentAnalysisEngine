//
// Created by HP SUPPORT on 16/12/2025.
//
#include <gtest/gtest.h>
#include "../include/Utils.h"
#include "../include/Functions.h"

using namespace std;

// --- TEST 1: Verify text cleaning ---
TEST(SentimentLogic, LimpiaLosSignos) {
    EXPECT_EQ(SentimentLogic::cleanRawText("HOLA!!"), "hola");
    EXPECT_EQ(SentimentLogic::cleanRawText("Mundo..."), "mundo");
    EXPECT_EQ(SentimentLogic::cleanRawText("Que Tal?"), "que tal");
}

// --- TEST 2: Verify word separation ---
TEST(SentimentLogic, SplitIntoWords) {
    string input = "hello world";
    vector<string> result = SentimentLogic::splitIntoWords(input);

    EXPECT_EQ(result.size(), 2);
    EXPECT_EQ(result[0], "hello");
    EXPECT_EQ(result[1], "world");
}

// --- TEST 3: Verify sentiment logic ---
TEST(SentimentLogic,BasicSentimentAnalysis) {
    int totalPolarity = 0;
    string input = "this is great but bad";

    map<string, Word> lexicon;
    lexicon["bad"] = addNewWord(-5, "bad");
    lexicon["great"] = addNewWord(3, "great");

    vector<string> tokenList = SentimentLogic::splitIntoWords(input);
    vector<Word> result = SentimentLogic::analyzeSentiment(tokenList,totalPolarity,lexicon);
    EXPECT_EQ(result.size(), 2);
    EXPECT_EQ(result[0].polarity,3);
    EXPECT_EQ(result[1].polarity,-5);
    EXPECT_EQ(totalPolarity,-2);
}



