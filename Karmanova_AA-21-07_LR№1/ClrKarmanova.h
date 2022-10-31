#include <string>
#include "Check.h"
using namespace std;

class truba {
public:
    string Pname;
    bool condition;
    double diameter, length;
    int pId;
    static int maxPid;
    void Edit();
    truba();
    friend std::istream& operator>>(std::istream& in, truba& p);
    friend std::ostream& operator<<(std::ostream& out, truba& p);

};