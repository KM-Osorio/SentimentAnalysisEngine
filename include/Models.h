//
// Created by HP SUPPORT on 9/12/2025.
//

#ifndef HI_MODEL_H
#define HI_MODEL_H
#include "Utils.h"

// --- SENTIMENT MODULE ---
typedef struct Word {
    std::string text;
    int polarity;
}Word;
// --- PRODUCT MODULE ---
typedef struct Product{
    std::string code;
   std:: string name;
    double price;
    int quantity;
}Product;

typedef struct ProductNode {
    Product data;
    ProductNode *right;
    ProductNode *left;
    ProductNode():right(nullptr),left(nullptr){}
}ProductNode;

// --- REVIEW MODULE ---
typedef struct Review {
    std::string rawText;
    std::string processedText;
    std::vector <Word> words;
    int totalPolarity;
}Review;

// --- ORDER MODULE ---
typedef struct Order {
    int id;
    std::vector <Product> dishes;
    int dishCount;
    double totalRevenue;
    int timestamp;
    std::vector <Review> reviews;
}Order;


#endif //HI_MODEL_H