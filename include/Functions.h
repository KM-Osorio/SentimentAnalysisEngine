//
// Created by HP SUPPORT on 8/12/2025.
//

#ifndef HI_FUNCTIONS_H
#define HI_FUNCTIONS_H
#include "Utils.h"

namespace SentimentLogic {
 std::string cleanRawText(std::string rawReview);
 std::vector <std::string>splitIntoWords(std::string cleaned);
 std::vector<Word>analyzeSentiment(std::vector <std::string>tokenList,int &totalPolarity,std::map<std::string,Word>lexicon);
}
void lines(std::ofstream &out,int n,char c);
std::ifstream input(const char*name);
std::ofstream output(const char*name);
int cinInt(std::ifstream &in);
std::string cinString(std::ifstream &in,int n,char c);
std::string asing(char*chain);


void fillInLexicon(std::map <std::string,Word>&lexicon);
Word addNewWord(int polarity,std::string word);

void fillInDishList( ProductNode* &Menu);
ProductNode* insertNewProduct(ProductNode*Menu,ProductNode*newDish);
ProductNode *addNewDish(std::ifstream &in,std::string dishCode);

void  fillInOrderList(std:: vector <Order>&orders, ProductNode* Menu);
Order addNewOrder(std::ifstream &in,int orderCode,  ProductNode* Menu);
int cinTime(std::ifstream &in);
 ProductNode *lookUpDish( ProductNode* Menu,std::string dishCode);

void fillInReviews(std::vector <Order>&orders,std::map<std::string,Word> &lexicon);
Order* lookUpOrder( std::vector<Order>&orders,int orderCode);
Review addNewReview(std::string rawReview,std::map<std::string,Word> &lexicon);
const Word*findWordInLexicon(std::string word,std::map<std::string,Word> &lexicon);


void printReport(std:: vector <Order>&orderList);
void title(std::ofstream &out) ;
void reviewHeader(std::ofstream &out, Order order);
void printTime(std::ofstream &out,int timestamp);
void printDish(std::ofstream &out,int i, Product dish);
#endif //HI_FUNCTIONS_H