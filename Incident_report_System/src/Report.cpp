
#include "Report.h"
#include <fstream>
#include <iostream>
#include <algorithm>

Report::Report(const std::vector<Incident>& inc)
        : incidents(inc), reportDate(Date::today()) {}

void Report::addIncident(const Incident& in) {
    incidents.push_back(in);
}

bool Report::deleteIncident(const std::string& id) {
    auto it = std::remove_if(incidents.begin(), incidents.end(),
                             [&](const Incident& i){ return i.getId() == id; });
    if (it == incidents.end()) return false;
    incidents.erase(it, incidents.end());
    return true;
}

bool Report::modifyIncident(const std::string& id, const std::string& field, const std::string& value) {
    for (auto& inc : incidents) {
        if (inc.getId() == id) {
            if (field == "description") inc.setDesc(value);
            else if (field == "location") inc.setLoc(value);
            else if (field == "severity") inc.setSeverity(std::stoi(value));
            else return false;
            return true;
        }
    }
    return false;
}

bool Report::resolveIncident(const std::string& id) {
    for (auto& inc : incidents) {
        if (inc.getId() == id) {
            inc.setResolved(true);
            return true;
        }
    }
    return false;
}

std::vector<Incident> Report::filterByLocation(const std::string& loc) const {
    std::vector<Incident> res;
    std::copy_if(incidents.begin(), incidents.end(), std::back_inserter(res),
                 [&](const Incident& i){ return i.getLoc() == loc; });
    return res;
}

std::vector<Incident> Report::filterBySeverity(int sev) const {
    std::vector<Incident> res;
    std::copy_if(incidents.begin(), incidents.end(), std::back_inserter(res),
                 [&](const Incident& i){ return i.getSeverity() == sev; });
    return res;
}

std::vector<Incident> Report::getUnresolved() const {
    std::vector<Incident> res;
    std::copy_if(incidents.begin(), incidents.end(), std::back_inserter(res),
                 [&](const Incident& i){ return !i.isResolved(); });
    return res;
}

const std::vector<Incident>& Report::getAll() const {
    return incidents;
}

static void ensureFile(const std::string& file) {
    std::ofstream ofs(file, std::ios::app);
}

std::vector<Incident> Report::loadIncidents(const std::string& file) {
    ensureFile(file);
    std::ifstream ifs(file);
    std::string line;
    std::vector<Incident> res;
    while (std::getline(ifs, line)) {
        if (line.empty()) continue;
        try {
            res.push_back(Incident::deserialize(line));
        } catch (...) {
            std::cerr << "Skipping malformed line: " << line << '\n';
        }
    }
    return res;
}

void Report::saveIncidents(const std::vector<Incident>& inc, const std::string& file) {
    std::ofstream ofs(file);
    for (const auto& in : inc)
        ofs << in.serialize() << '\n';
}

void Report::saveUnresolved(const std::vector<Incident>& inc, const std::string& file) {
    std::ofstream ofs(file);
    for (const auto& in : inc)
        if (!in.isResolved())
            ofs << in.serialize() << '\n';
}

void Report::exportSnapshot(const std::string& logFile) const {
    std::ofstream ofs(logFile, std::ios::app);
    ofs << "=== " << reportDate.toString() << " ===\n";
    for (const auto& in : incidents)
        ofs << in.serialize() << '\n';
}
