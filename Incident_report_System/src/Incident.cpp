
#include "Incident.h"
#include <sstream>
#include <vector>
#include <iostream>

#define COLOR_RESET  "\033[0m"
#define COLOR_RED    "\033[31m"
#define COLOR_GREEN  "\033[32m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_CYAN   "\033[36m"

static std::vector<std::string> split(const std::string& s, char delim) {
    std::vector<std::string> tokens;
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim))
        tokens.push_back(item);
    return tokens;
}

Incident::Incident(const std::string& _id, const std::string& _desc,
                   const std::string& _loc, int _sev, bool _res, const Date& _date)
        : id(_id), description(_desc), location(_loc),
          severity(_sev), resolved(_res), created(_date) {}

const std::string& Incident::getId()       const { return id;        }
const std::string& Incident::getDesc()     const { return description; }
const std::string& Incident::getLoc()      const { return location;  }
int                Incident::getSeverity() const { return severity;  }
bool               Incident::isResolved()  const { return resolved;  }
const Date&        Incident::getDate()     const { return created;   }

void Incident::setDesc(const std::string& d) { description = d; }
void Incident::setLoc(const std::string& l)  { location = l;    }
void Incident::setSeverity(int s)            { severity = s;    }
void Incident::setResolved(bool r)           { resolved = r;    }

std::string Incident::serialize(char delim) const {
    std::ostringstream oss;
    oss << id << delim
        << description << delim
        << location << delim
        << severity << delim
        << resolved << delim
        << created.day << delim << created.month << delim << created.year;
    return oss.str();
}

Incident Incident::deserialize(const std::string& line, char delim) {
    auto tokens = split(line, delim);
    if (tokens.size() < 8) throw std::runtime_error("Malformed incident line");
    Date d(std::stoi(tokens[5]), std::stoi(tokens[6]), std::stoi(tokens[7]));
    return Incident(tokens[0], tokens[1], tokens[2], std::stoi(tokens[3]), std::stoi(tokens[4]) != 0, d);
}

std::string Incident::toColoredString() const {
    std::ostringstream oss;
    std::string sevColor = (severity >= 4 ? COLOR_RED :
                            severity == 3 ? COLOR_YELLOW :
                            COLOR_GREEN);
    std::string statusColor = resolved ? COLOR_GREEN : COLOR_RED;

    oss << COLOR_CYAN << "[" << id << "]" << COLOR_RESET << " "
        << description << " @ " << location << " "
        << sevColor << "(severity " << severity << ")" << COLOR_RESET << " "
        << statusColor << (resolved ? "[RESOLVED]" : "[OPEN]") << COLOR_RESET
        << " [" << created.toString() << "]";
    return oss.str();
}
