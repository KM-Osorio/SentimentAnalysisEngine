#include "../include/Utils.h"
#include "../include/Functions.h"
using namespace std;
using namespace SentimentLogic;
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