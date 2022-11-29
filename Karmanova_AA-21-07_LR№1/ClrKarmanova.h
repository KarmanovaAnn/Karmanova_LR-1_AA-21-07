#pragma once

#include <string>
#include "Check.h"

class truba {
public:
    std::string Pname;
    bool condition;
    double diameter, length;
    int pId;
    int IdInput, IdExit;
    static int maxPid;
    void Edit();
  
    bool IsAvailable();
    void Connect(int in, int out);
    void PrintConnection();
    truba();
    friend std::istream& operator>>(std::istream& in,  truba& p);
    friend std::ostream& operator<<(std::ostream& out, const truba& p);

};