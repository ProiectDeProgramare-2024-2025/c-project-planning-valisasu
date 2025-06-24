
#ifndef DATE_H
#define DATE_H

#include <string>

class Date {
public:
    int day;
    int month;
    int year;

    Date();
    Date(int d, int m, int y);

    std::string toString() const;
    static Date today();
};

#endif // DATE_H
