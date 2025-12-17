//
// Created by HP SUPPORT on 8/12/2025.
//
#include "../include/Utils.h"
#include "../include/Functions.h"
using namespace std;

namespace SentimentLogic{
    string cleanRawText(string rawReview){
        string cleaned;
        for (char c: rawReview) {
            if (isalnum(c)or c==' ')cleaned.push_back(tolower(c));
        }
        return cleaned;
    }
    vector <string>splitIntoWords(string cleaned) {
        vector <string>tokenList;
        stringstream ss(cleaned);
        string word;
        while (ss>>word) tokenList.push_back(word);
        return tokenList;
    }

    vector<Word>analyzeSentiment(vector <string>tokenList,int &totalPolarity,map<string,Word>lexicon) {
        totalPolarity=0;
        vector<Word>words;
        for (auto& token:tokenList) {
            const Word*ptr=findWordInLexicon(token,lexicon);
            if (ptr!=nullptr) {
                words.push_back(*ptr);
                totalPolarity+=ptr->polarity;
            }
        }
        return words;
    }
}
void lines(ofstream &out,int n,char c) {
    for(int i=0;i<n;i++) out<<c;
    out<<endl;
}
ifstream input(const char*name) {
    ifstream file(name,ios::in);
    if(!file.is_open()) {
        cout<<"File Not Found"<<name<<endl;
        exit(1);
    }
    return file;
}
ofstream output(const char*name){
    ofstream file(name,ios::out);
    if(!file.is_open()) {
        cout<<"File Not Found"<<endl;
        exit(1);
    }
    return file;
}
int cinInt(ifstream &in) {
    int i;
    in>>i;
    in.get();
    return i;
}
double cinDouble(ifstream &in){
    double i;
    in>>i;
    in.get();
    return i;
}
string cinString(ifstream &in,int n,char c) {
    char chain[n]{};
    string i;
    in.getline(chain,n,c);
    i=chain;
    return i;
}
string asing(char*chain) {
    return string (chain);
}

void fillInLexicon( map<string,Word> &lexicon) {
    ifstream in=input("../data/lexicon.csv");
    string word;
    int polarity;
    while(true) {
        word=cinString(in,20,',');
        polarity=cinInt(in);
        if (in.eof())break;
        lexicon[word]=addNewWord(polarity,word);
    }
}
Word addNewWord(int polarity,string word) {
    struct Word newWord;
    newWord.text=word;
    newWord.polarity=polarity;
    return newWord;
}

void fillInDishList( ProductNode* &Menu) {
    ifstream in=input("../data/platos.csv");
    string dishCode;
    while(true) {
        dishCode=cinString(in,50,',');
        if (in.eof())break;
         ProductNode *newNode =addNewDish(in,dishCode);
        Menu=insertNewProduct(Menu,newNode);
    }
}
ProductNode *addNewDish(ifstream &in,string dishCode) {
    ProductNode *newNode =new ProductNode;
    newNode->data.code=dishCode;
    newNode->data.name=cinString(in,100,',');
    newNode->data.price=cinDouble(in);
    return newNode;
}
ProductNode* insertNewProduct(ProductNode*Menu,ProductNode*newDish) {
    if (Menu==nullptr)return newDish;
    if (newDish->data.code>Menu->data.code) Menu->right=insertNewProduct(Menu->right,newDish);
    else Menu->left= insertNewProduct(Menu->left,newDish);
    return Menu;
}
void  fillInOrderList( vector <Order>&orders,ProductNode*Menu) {
    ifstream in=input("../data/atenciones.txt");
    int orderCode;
    while (true) {
        in>>orderCode;
        if (in.eof())break;
        orders.push_back(addNewOrder(in,orderCode,Menu));
    }
}

 Order addNewOrder(ifstream &in,int orderCode,  ProductNode* Menu) {
    Order newOrder;
    newOrder.id=orderCode;
    newOrder.timestamp=cinTime(in);
    newOrder.totalRevenue=0;
    int cant,i=0;
    string dishCode;
    while (in.peek()!='\n') {
        in>>dishCode>>cant;
        struct ProductNode *dish=lookUpDish(Menu,dishCode);
        newOrder.dishes.push_back(dish->data);
        newOrder.dishes[i].quantity=cant;
        newOrder.totalRevenue+=cant*dish->data.price;
        i++;
    }
    newOrder.dishCount=i;
    return newOrder;
}
int cinTime(ifstream &in) {
    int h,m;
    char c;
    in>>h>>c>>m;
    return h*60+m;
}
ProductNode *lookUpDish( ProductNode* Menu,string dishCode) {
    if (Menu==nullptr)return nullptr;
    if (Menu->data.code==dishCode)return Menu;
    if (Menu->data.code>dishCode) return lookUpDish(Menu->left,dishCode);
    else return (lookUpDish(Menu->right,dishCode));
}

void fillInReviews( vector <Order>&orders,map<string,Word> &lexicon) {
    ifstream in=input("../data/comentarios.csv");
    int orderCode;
    string rawReview;
    while (true) {
        orderCode=cinInt(in);
        if (in.eof())break;
        getline(in,rawReview,'\n');
        Order*ptr=lookUpOrder(orders,orderCode);
        if (ptr!=nullptr){
            ptr->reviews.push_back(addNewReview(rawReview,lexicon));
        }
    }
}
Order* lookUpOrder(vector<Order>&orders,int orderCode) {
    for (auto &order:orders) {
        if (order.id==orderCode)return &order;
    }
    return nullptr;
}
 Review addNewReview(string rawReview,map<string,Word> &lexicon) {
    Review newReview;
    newReview.rawText=rawReview;

    string cleaned=SentimentLogic::cleanRawText(rawReview);
    newReview.processedText=cleaned;

    vector <string> tokenList=SentimentLogic::splitIntoWords(cleaned);
    newReview.words=SentimentLogic::analyzeSentiment(tokenList,newReview.totalPolarity,lexicon);
    return newReview;
}


const Word*findWordInLexicon(string word,map<string,Word> &lexicon) {
    map<string,Word>::iterator it=lexicon.find(word);
    if (it!=lexicon.end()) return &it->second;
    return nullptr;
}



void printReport( vector<Order>&orders) {
    ofstream out=output("outputFiles/SentimentAnalysisReport.txt");
    double score=0;
    title(out);
    for (const auto&order:orders) {
        reviewHeader(out,order);
        int i=1;
        for (const auto&dish: order.dishes) {
            printDish(out,i,dish);
            i++;
        }
        out<<"Total Revenue: "<<order.totalRevenue<<endl;
        lines(out,130,'-');
        out<<"Costumer Reviews: "<<endl;
        int k=0;
        for (const auto& review:order.reviews) {
            out<<" - "<<order.reviews[k].rawText<<endl;
            score+=order.reviews[k].totalPolarity;
            k++;
        }
        out<<"TotalSentiment Score: "<<score<<endl;

    }
}
void reviewHeader(ofstream &out, Order order) {
    lines(out,130,'=');
    out<<"ID TRANSACTION  "<<order.id<<setw(52)<<"Time: ";
    printTime(out,order.timestamp);
    lines(out,130,'-');
}
void printTime(ofstream &out,int timestamp) {
   int h=timestamp/60;
   int m=timestamp%60;
    out.fill('0');
    out<<right<<setw(2)<<h<<":"<<setw(2)<<m;
    out.fill(' ');
    if (h<=12)out<<" AM"<<endl;
    else out<<" PM"<<endl;

}
void printDish(ofstream &out,int i,Product dish) {
    out<<setprecision(2)<<fixed<<right;
    out<<setw(5)<<i<<")  "<<left<<setw(10)<<dish.code<<setw(50)<<dish.name<<setw(12)<<dish.price<<setw(10)<<dish.quantity<<dish.price*dish.quantity<<right<<endl;
}
void title(ofstream &out) {
    out<<setw(70)<<"TP DELIVERY SERVICES INC."<<endl;
    out<<setw(64)<<"TRANSACTION LOG"<<endl;
}

