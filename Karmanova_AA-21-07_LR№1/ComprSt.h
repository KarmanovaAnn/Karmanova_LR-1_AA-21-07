#pragma once
#include <string>
#include "Check.h"
using namespace std;

class compress_station {
public:
    string Pname;
    static int maxCSid;
    double amount_shop, amount_Wshop, indicator, k;
    int csId;
    void Edit();
    compress_station();
    
    
    friend std::istream& operator>>(std::istream& in, compress_station & cs);
    friend std::ostream& operator<<(std::ostream& out, const compress_station & cs);

};