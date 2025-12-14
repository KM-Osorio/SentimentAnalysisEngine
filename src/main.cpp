#include "../include/Utils.h"

int main() {
    map <string,Word>lexicon;
    fillInLexicon(lexicon);
    ProductNode* Menu=nullptr;
    fillInDishList(Menu);
    vector <Order>orders;
    fillInOrderList(orders,Menu);
    fillInReviews(orders,lexicon);
    printReport(orders);
    return 0;
}