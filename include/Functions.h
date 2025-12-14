//
// Created by HP SUPPORT on 8/12/2025.
//

#ifndef HI_FUNCTIONS_H
#define HI_FUNCTIONS_H
#include "Utils.h"
void lines(ofstream &out,int n,char c);
ifstream input(const char*name);
ofstream output(const char*name);
int cinInt(ifstream &in);
double cinDouble(ifstream &in);
string cinString(ifstream &in,char c) ;
string asing(char*chain);


void fillInLexicon(map <string,Word>&lexicon);
Word addNewWord(ifstream &in,string word);

void fillInDishList(ProductList &dishList);
void setUpDishList(ProductList &dishList);
ProductNode *addNewDish(ifstream &in,string dishCode);

void  fillInOrderList( vector <Order>&orders,ProductList dishesList);
Order addNewOrder(ifstream &in,int orderCode, ProductList dishesList);
int cinTime(ifstream &in);
 ProductNode *lookUpDish( ProductList dishesList,string dishCode);

void fillInReviews( vector <Order>&orders,map<string,Word> &lexicon);
Order* lookUpOrder( vector<Order>&orders,int orderCode);
Review addNewReview(string rawReview,map<string,Word> &lexicon);

bool verifyChar(char c);
void deleteChar(int pos,string &rawReview,int max);
void cleanRawText(string &rawReview) ;
void myMinus(string &rawReview) ;

string extractWord(int &begin,string rawReview) ;
const Word*findWordInLexicon(string word,map<string,Word> &lexicon);


void printReport( vector <Order>&orderList);
void title(ofstream &out) ;
void reviewHeader(ofstream &out, Order order);
void printTime(ofstream &out,int timestamp);
void printDish(ofstream &out,int i, Product dish);
#endif //HI_FUNCTIONS_H