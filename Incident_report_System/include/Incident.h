
#ifndef INCIDENT_H
#define INCIDENT_H

#include <string>
#include "Date.h"

class Incident {
private:
    std::string id;
    std::string description;
    std::string location;
    int severity;      // 1–5
    bool resolved;
    Date created;

public:
    Incident() = default;
    Incident(const std::string& _id,
             const std::string& _desc,
             const std::string& _loc,
             int _sev,
             bool _res,
             const Date& _date);

    // Getters
    const std::string& getId()       const;
    const std::string& getDesc()     const;
    const std::string& getLoc()      const;
    int                getSeverity() const;
    bool               isResolved()  const;
    const Date&        getDate()     const;

    // Setters / modifiers
    void setDesc(const std::string& d);
    void setLoc(const std::string& l);
    void setSeverity(int s);
    void setResolved(bool r);

    std::string serialize(char delim='|') const;
    static Incident deserialize(const std::string& line, char delim='|');

    std::string toColoredString() const;
};

#endif // INCIDENT_H
