//
// Created by HP SUPPORT on 9/12/2025.
//

#ifndef HI_MODEL_H
#define HI_MODEL_H
#include "Utils.h"

// --- SENTIMENT MODULE ---
typedef struct Word {
    string text;
    int polarity;
}Word;

typedef struct WordNode {
    Word word;
    WordNode* next;
}WordNode;

typedef struct WordList {
    WordNode* head;
    WordNode* tail;
}WordList;

// --- PRODUCT MODULE ---
typedef struct Product{
    string code;
    string name;
    double price;
    int quantity;
}Product;

typedef struct ProductNode {
    Product data;
    ProductNode *next;
}ProductNode;

typedef struct ProductList {
    ProductNode *head;
    ProductNode *tail;
}ProductList;

// --- REVIEW MODULE ---
typedef struct Review {
    string rawText;
    string processedText;
    vector <Word> words;
    int totalPolarity;
}Review;

// --- ORDER MODULE ---
typedef struct Order {
    int id;
    vector <Product> dishes;
    int dishCount;
    double totalRevenue;
    int timestamp;
    vector <Review> reviews;
}Order;

typedef struct OrderNode {
    Order order;
    OrderNode *next;
}OrderNode;

typedef struct OrderList {
    OrderNode *head;
    OrderNode *tail;
}OrderList;

#endif //HI_MODEL_H