//
//  main.cpp
//  CIS 29 ASS-3
//
//  Created by zhaozeyu on 2019/10/24.
//  Copyright � 2019 zhaozeyu. All rights reserved.
//

#include <iostream>
#include <memory>
#include <vector>
#include <regex>
#include <fstream>
#include <algorithm>
#include <string>
#include <bitset>
#include <thread>
#include <mutex>
using namespace std;

vector<string> strvec;

mutex _mu;
mutex _mu1;
double totalprice = 0;
class Product//: public Node, public std::enable_shared_from_this<Product>
{
    string _key;
public:
    Product() = default;
    Product(string key) :_key(key) {}
    virtual string key() const { return _key; };
    void show() const { cout << "The Product is: " << _key << endl; }
    bool operator==(const Product& a) const {
        return _key == a._key;
    }
};

class Price//: public Node, public std::enable_shared_from_this<Price>
{
    double _key;
public:
    Price() = default;
    Price(double f) : _key(f) {};
    Price(const Price& a) : _key(a.key()) {};
    virtual double key() const { return _key; }
    void show() const { cout << "The Price is: " << _key << endl; }
};


class Node
{
    shared_ptr<Product> Pro;
    shared_ptr<Price> Pri;
public:
    Node() = default;
    Node(shared_ptr<Product> left) :Pro(left), Pri(NULL) {}
    Node(shared_ptr<Product> left, shared_ptr<Price> right) : Pro(left), Pri(right) {}
    bool operator==(const Node& a) const {
        return *Pro == *a.Pro;
    }
    void show() {
        Pro.get()->show();
        Pri.get()->show();
        cout << endl;
    }
    double returnint() {
        return Pri.get()->key();
    }
    string name() const
    {
        string quadname = typeid(*this).name();
#ifdef _MSC_VER       // for MS Visual Studio
        quadname = quadname.substr(6);
#elif __APPLE_CC__
        //cout<<quadname;
        quadname = quadname.substr(quadname.find_first_not_of("0123456789"));
#else                 // for other compilers
        quadname = quadname.substr(quadname.find_first_not_of("0123456789"));
#endif
        return quadname;
    }
    friend ostream& operator<<(ostream& out, const Node& a) {
        a.Pro.get()->show();
        a.Pri.get()->show();
        out << endl;
        return out;
    }
};

const size_t hash_table_size = 512;

template <class T>
class hashtable {
private:
    vector<T> hashobject;
    unsigned hashfun(string test) {
        //string binarystring;
        bitset<9> binarystring;
        unsigned long transfered = 0;
        for (int i = test.length() - 1; i >= 0; i--) {
            if (test[test.length() - 1 - i] == 'w') {
                binarystring[i] = 1;
            }
            else {
                binarystring[i] = 0;
            }
        }
        transfered = binarystring.to_ulong();
        return transfered;
    }
public:
    hashtable() {
        hashobject.resize(hash_table_size);
        for (auto i = 65; i < 91; i++) {
            char test = i;
            hashobject[hashfun(morseEncode(test))] = test;
        }
        for (auto i = 48; i < 58; i++) {
            char test = i;
            hashobject[hashfun(morseEncode(test))] = test;
        }
        char test = ' ';
        hashobject[hashfun(morseEncode(test))] = test;
        test = '.';
        hashobject[hashfun(morseEncode(test))] = test;
        test = '/';
        hashobject[hashfun(morseEncode(test))] = test;
        test = '*';
        hashobject[hashfun(morseEncode(test))] = test;
        test = '-';
        hashobject[hashfun(morseEncode(test))] = test;
        test = '+';
        hashobject[hashfun(morseEncode(test))] = test;
        test = '$';
        hashobject[hashfun(morseEncode(test))] = test;
        test = '%';
        hashobject[hashfun(morseEncode(test))] = test;
    }
    string morseEncode(char x) {
        switch (x) {
            case '*':
                return "nwnnwnwnn";
            case '-':
                return "nwnnnnwnw";
            case '+':
                return "nwnnnwnwn";
            case '$':
                return "nwnwnwnnn";
            case '%':
                return "nnnwnwnwn";
            case 'A':
                return "wnnnnwnnw";
            case 'B':
                return "nnwnnwnnw";
            case 'C':
                return "wnwnnwnnn";
            case 'D':
                return "nnnnwwnnw";
            case 'E':
                return "wnnnwwnnn";
            case 'F':
                return "nnwnwwnnn";
            case 'G':
                return "nnnnnwwnw";
            case 'H':
                return "wnnnnwwnn";
            case 'I':
                return "nnwnnwwnn";
            case 'J':
                return "nnnnwwwnn";
            case 'K':
                return "wnnnnnnww";
            case 'L':
                return "nnwnnnnww";
            case 'M':
                return "wnwnnnnwn";
            case 'N':
                return "nnnnwnnww";
            case 'O':
                return "wnnnwnnwn";
            case 'P':
                return "nnwnwnnwn";
            case 'Q':
                return "nnnnnnwww";
            case 'R':
                return "wnnnnnwwn";
            case 'S':
                return "nnwnnnwwn";
            case 'T':
                return "nnnnwnwwn";
            case 'U':
                return "wwnnnnnnw";
            case 'V':
                return "nwwnnnnnw";
            case 'W':
                return "wwwnnnnnn";
            case 'X':
                return "nwnnwnnnw";
            case 'Y':
                return "wwnnwnnnn";
            case 'Z':
                return "nwwnwnnnn";
            case ' ':
                return "nwwnnnwnn";
            case '.':
                return "wwnnnnwnn";
            case '/':
                return "nwnwnnnwn";
            case '0':
                return "nnnwwnwnn";
            case '1':
                return "wnnwnnnnw";
            case '2':
                return "nnwwnnnnw";
            case '3':
                return "wnwwnnnnn";
            case '4':
                return "nnnwwnnnw";
            case '5':
                return "wnnwwnnnn";
            case '6':
                return "nnwwwnnnn";
            case '7':
                return "nnnwnnwnw";
            case '8':
                return "wnnwnnwnn";
            case '9':
                return "nnwwnnwnn";
            default:
                cout << "There is something wrong with your conversion" << endl;
                exit(1);
        }
    }
    
    void printdata() {//debug use
        for (auto i = 0; i < hashobject.size(); i++) {
            cout << hashobject[i] << endl;
        }
    }
    char find(string test) {
        return hashobject[hashfun(test)];
    }
};

string HexToBin(string hexdec)
{
    long int i = 0;
    string stuff;
    while (hexdec[i]) {
        switch (hexdec[i]) {
            case '0':
                stuff.append("0000");
                break;
            case '1':
                stuff.append("0001");
                break;
            case '2':
                stuff.append("0010");
                break;
            case '3':
                stuff.append("0011");
                break;
            case '4':
                stuff.append("0100");
                break;
            case '5':
                stuff.append("0101");
                break;
            case '6':
                stuff.append("0110");
                break;
            case '7':
                stuff.append("0111");
                break;
            case '8':
                stuff.append("1000");
                break;
            case '9':
                stuff.append("1001");
                break;
            case 'A':
            case 'a':
                stuff.append("1010");
                break;
            case 'B':
            case 'b':
                stuff.append("1011");
                break;
            case 'C':
            case 'c':
                stuff.append("1100");
                break;
            case 'D':
            case 'd':
                stuff.append("1101");
                break;
            case 'E':
            case 'e':
                stuff.append("1110");
                break;
            case 'F':
            case 'f':
                stuff.append("1111");
                break;
            default:
                cout << "\nInvalid hexadecimal digit "
                << hexdec[i];
        }
        i++;
    }
    return stuff;
}

vector<Node> VecNo;

void matchmaker(regex token, string str) {
    hashtable<char> myhash;
    smatch match;
    int count = 0;
    vector<shared_ptr<Product>> vecpro;
    vector<shared_ptr<Price>> vecpri;
    while (regex_search(str, match, token)) {
        string product(5, ' ');
        if (count == 0) {
            int countpro = 0;
            string thing = match.str();
            string binaryin;
            binaryin.clear();
            binaryin.resize(9);
            auto pos = thing.find('.');
            if (pos == -1) {
                for (int i = 0; i < 46; i++) {
                    if (i % 9 == 0 && i != 0) {
                        for_each(binaryin.begin(), binaryin.end(), [](char& i) {if (i == '1') i = 'w'; else i = 'n'; });
                        product[countpro] = myhash.find(binaryin);
                        binaryin.clear();
                        binaryin.resize(9);
                        countpro++;
                    }
                    binaryin[i % 9] = thing[i];
                }
                shared_ptr<Product> Pto = make_shared<Product>(product);
                vecpro.push_back(Pto);
                str = match.suffix().str();
                count = 1;
            }
            else {
                shared_ptr<Product> Pto = make_shared<Product>(product);
                shared_ptr<Price> Ptp = make_shared<Price>(stod(match.str()));
                vecpro.push_back(Pto);
                vecpri.push_back(Ptp);
                str = match.suffix().str();
            }
        }
        else {
            shared_ptr<Price> Pto = make_shared<Price>(stod(match.str()));
            vecpri.push_back(Pto);
            str = match.suffix().str();
            count = 0;
        }
    }
    for (int i = 0; i < vecpro.size(); i++) {
        Node stuff(vecpro[i], vecpri[i]);
        VecNo.push_back(stuff);
    }
}

void searchfun(string find) {
    shared_ptr<Product> tryfind = make_shared<Product>(find);
    Node stu(tryfind);
    auto it = std::find(VecNo.begin(), VecNo.end(), stu);
    if (it != VecNo.end()) {
        totalprice = it->returnint() + totalprice;
        cout << *it;
    }
    else {
        cout << "There is no such thing" << endl;
        cout << endl;
    }
}

void processingcsv(regex token, string stuff) {
    lock_guard<mutex> locker(_mu1);
    hashtable<char> myhash;
    smatch match;
    int count = 1;
    while (regex_search(stuff, match, token)) {
        string str = match.str();
        if (str.substr(0, 4) == "Cart") {
            if (count != 1) { cout << "The total price for this cart is $" << totalprice << endl << endl; }
            cout << str << ": " << endl;
            stuff = match.suffix().str();
            totalprice = 0;
            count++;
        }
        else {
            string binaystring = HexToBin(str);
            int countpro = 0;
            string binaryin;
            binaryin.clear();
            binaryin.resize(9);
            string product(5, ' ');
            for (int i = 0; i < 46; i++) {
                if (i % 9 == 0 && i != 0) {
                    for_each(binaryin.begin(), binaryin.end(), [](char& i) {if (i == '1') i = 'w'; else i = 'n'; });
                    product[countpro] = myhash.find(binaryin);
                    binaryin.clear();
                    binaryin.resize(9);
                    countpro++;
                }
                binaryin[i % 9] = binaystring[i];
            }
            stuff = match.suffix().str();
            searchfun(product);
        }
    }
    cout << endl << "The total price for this cart is $" << totalprice << endl << endl;
}

int strvec_count = -1;

bool judgerange = true;

string filereading(int& i) {
    lock_guard<mutex> locker(_mu);
    i++;
    if (i < strvec.size()) {
        return strvec[i];
    }
    else {
        judgerange = false;
    }
    return " ";
}

void fileprocessor(regex token) {
    while (strvec_count != strvec.size() && judgerange) {
        string stuff = filereading(strvec_count);
        processingcsv(token, stuff);
    }
}

int main() {
    vector<Node> myNodes;
    string stuff, content;
    ifstream fin;
    fin.open("ProductPrice.xml");
    if (!fin.is_open()) {//quit if there is no problem finding the file
        cout << "There is something wrong with the file" << endl;
        exit(2);
    }
    while (fin >> content) {
        stuff = stuff + content;
    }
    regex token("[0-9]+.[0-9]+");
    matchmaker(token, stuff);
    fin.close();
    fin.open("Carts.csv");
    if (!fin.is_open()) {//quit if there is no problem finding the file
        cout << "There is something wrong with the file" << endl;
        exit(3);
    }
    bool count = true;
    stuff.clear();
    while (fin >> content) {
        if (content.substr(0, 4) == "Cart" && count) {
            content.append(".");
            content.insert(0, ".");
            count = false;
        }
        else if (content.substr(0, 4) == "Cart") {
            content.append(".");
            content.insert(0, ".");
            strvec.push_back(stuff);
            stuff.clear();
        }
        stuff = stuff + content;
    }
    vector<thread> vecthr;
    regex newtoken("[a-zA-Z0-9]+");
    //for_each(vecthr.begin(), vecthr.end(), [](thread& i){i(fileprocessor, ref(newtoken));});
    thread th1(fileprocessor, ref(newtoken));
    thread th2(fileprocessor, ref(newtoken));
    thread th3(fileprocessor, ref(newtoken));
    thread th4(fileprocessor, ref(newtoken));
    thread th5(fileprocessor, ref(newtoken));
    thread th6(fileprocessor, ref(newtoken));
    thread th7(fileprocessor, ref(newtoken));
    thread th8(fileprocessor, ref(newtoken));
    thread th9(fileprocessor, ref(newtoken));
    thread th10(fileprocessor, ref(newtoken));
    th1.join();
    th2.join();
    th3.join();
    th4.join();
    th5.join();
    th6.join();
    th7.join();
    th8.join();
    th9.join();
    th10.join();
    return 0;
}
