//
// Created by HP SUPPORT on 8/12/2025.
//
#include "../include/Utils.h"
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
string cinString(ifstream &in,char c) {
    char chain[300];
    in.getline(chain,300,c);
    return string (chain);
}
string asing(char*chain) {
    return string (chain);
}

void fillInLexicon( map<string,Word> &lexicon) {
    ifstream in=input("../data/lexicon.csv");
    string word;
    while(true) {
        word=cinString(in,',');
        if (in.eof())break;
        lexicon[word]=addNewWord(in,word);
    }
}
Word addNewWord(ifstream &in,string word) {
    struct Word newWord;
    newWord.text=word;
    newWord.polarity=cinInt(in);
    return newWord;
}

void fillInDishList( ProductList &dishList) {
    ifstream in=input("../data/platos.csv");
    setUpDishList(dishList);
    char dishCode[7]{};
    while(true) {
        in.getline(dishCode,7,',');
        if (in.eof())break;
         ProductNode *newNode =addNewDish(in,dishCode);
        if (dishList.head==nullptr)dishList.head=newNode;
        else dishList.tail->next=newNode;
        dishList.tail=newNode;
    }

}
void setUpDishList(ProductList &dishList) {
    dishList.head=nullptr;
    dishList.tail=nullptr;
}
ProductNode *addNewDish(ifstream &in,string dishCode) {
    ProductNode *newNode =new ProductNode;
    newNode->data.code=dishCode;
    newNode->data.name=cinString(in,',');
    newNode->data.price=cinDouble(in);
    newNode->next=nullptr;
    return newNode;
}

void  fillInOrderList( vector <Order>&orders,ProductList dishesList) {
    ifstream in=input("../data/atenciones.txt");
    int orderCode;
    while (true) {
        in>>orderCode;
        if (in.eof())break;
        orders.push_back(addNewOrder(in,orderCode,dishesList));
    }
}

 Order addNewOrder(ifstream &in,int orderCode, ProductList dishesList) {
    Order newOrder;
    newOrder.id=orderCode;
    newOrder.timestamp=cinTime(in);
    newOrder.totalRevenue=0;
    int cant,i=0;
    string dishCode;
    while (in.peek()!='\n') {
        in>>dishCode>>cant;
        struct ProductNode *dish=lookUpDish(dishesList,dishCode);
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
ProductNode *lookUpDish( ProductList dishesList,string dishCode) {
    ProductNode *trail=dishesList.head;
    while (true) {
        if (trail->data.code==dishCode)return trail;
        trail=trail->next;
    }
    return nullptr;
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
 Review addNewReview(string rawReview,map<string,Word> &lexicon) {
    Review newReview;
    newReview.rawText=rawReview;
    cleanRawText(rawReview);
    newReview.processedText=rawReview;
    newReview.totalPolarity=0;
    int begin=0;
    while (rawReview[begin]) {
       string word=extractWord(begin,rawReview);
        const Word*ptr=findWordInLexicon(word,lexicon);
        if (ptr!=nullptr) {
            newReview.words.push_back(*ptr);
            newReview.totalPolarity+=ptr->polarity;
        }
    }
    return newReview;
}
string extractWord(int &begin,string rawReview) {
    string word;
    while(rawReview[begin]) {
        if (rawReview[begin]==' ')break;
        word.push_back(rawReview[begin]);
        begin++;
    }
    begin++;
    return word;
}
const Word*findWordInLexicon(string word,map<string,Word> &lexicon) {
    map<string,Word>::iterator it=lexicon.find(word);
    if (it!=lexicon.end()) return &it->second;
    return nullptr;
}
Order* lookUpOrder(vector<Order>&orders,int orderCode) {
    for (auto &order:orders) {
        if (order.id==orderCode)return &order;
    }
    return nullptr;
}
void cleanRawText(string &rawReview) {
    bool okChar;
    for (int i=rawReview.length()-1;i>=0;i--) {
        okChar=verifyChar(rawReview[i]);
        if (okChar==false)deleteChar(i,rawReview,rawReview.length());
    }
    myMinus(rawReview);
}
void myMinus(string &rawReview) {
    for (int i=0;rawReview[i];i++) {
        if (rawReview[i]>='A' && rawReview[i]<='Z'&& rawReview[i]!=' ' ) rawReview[i]+=32;
    }
}
bool verifyChar(char c) {
    if ((c>='A' && c<='z') or (c==' '))return true;
    return false;
}
void deleteChar(int pos,string &rawReview,int max) {
    for (int i=pos;i<max;i++) {
        rawReview[i]=rawReview[i+1];
    }
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

