#include "../include/Utils.h"

int main() {
    map <string,Word>lexicon;
    fillInLexicon(lexicon);
    ProductList dishList;
    fillInDishList(dishList);
    vector <Order>orders;
    fillInOrderList(orders,dishList);
    fillInReviews(orders,lexicon);
    printReport(orders);

    return 0;
}