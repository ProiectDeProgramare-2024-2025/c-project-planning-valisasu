
#include "Date.h"
#include <ctime>
#include <iomanip>
#include <sstream>

Date::Date() : day(1), month(1), year(1970) {}

Date::Date(int d, int m, int y) : day(d), month(m), year(y) {}

std::string Date::toString() const {
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << day << "/"
        << std::setw(2) << month << "/"
        << year;
    return oss.str();
}

Date Date::today() {
    std::time_t t = std::time(nullptr);
    std::tm*    tm = std::localtime(&t);
    return Date(tm->tm_mday, tm->tm_mon + 1, tm->tm_year + 1900);
}
