#ifndef FUNCTION_H
#define FUNCTION_H

#include "function_global.h"

class FUNCTIONSHARED_EXPORT Function
{

public:
    Function();

    int add(int a, int b);
    int sub(int a, int b);
    int mul(int a, int b);
    int div(int a, int b);
};

#endif // FUNCTION_H
