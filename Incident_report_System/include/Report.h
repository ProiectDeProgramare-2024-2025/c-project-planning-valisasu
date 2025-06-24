
#ifndef REPORT_H
#define REPORT_H

#include <vector>
#include <string>
#include "Incident.h"
#include "Date.h"

class Report {
private:
    std::vector<Incident> incidents;
    Date reportDate;

public:
    Report()  = default;
    explicit Report(const std::vector<Incident>& inc);

    void addIncident(const Incident& in);
    bool deleteIncident(const std::string& id);
    bool modifyIncident(const std::string& id, const std::string& field, const std::string& value);
    bool resolveIncident(const std::string& id);

    std::vector<Incident> filterByLocation(const std::string& loc) const;
    std::vector<Incident> filterBySeverity(int sev) const;
    std::vector<Incident> getUnresolved() const;
    const std::vector<Incident>& getAll() const;

    // File helpers
    static std::vector<Incident> loadIncidents(const std::string& file);
    static void saveIncidents(const std::vector<Incident>& inc, const std::string& file);
    static void saveUnresolved(const std::vector<Incident>& inc, const std::string& file);

    void exportSnapshot(const std::string& logFile) const;
};

#endif // REPORT_H
