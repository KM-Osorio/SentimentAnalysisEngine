#include "../include/Utils.h"

int main() {
    WordList lexicon;
    fillInLexicon(lexicon);
    ProductList dishList;
    fillInDishList(dishList);
    OrderList orderList;
    fillInOrderList(orderList,dishList);
    fillInReviews(orderList,lexicon);
    printReport(orderList);

    return 0;
}