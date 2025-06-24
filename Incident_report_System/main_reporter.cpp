
#include <iostream>
#include "Report.h"

static void usage() {
    std::cerr << "Reporter usage:\n"
              << "  reporter.exe report_incident <id> <description> <location> <severity>\n"
              << "  reporter.exe view_unresolved\n"
              << "  reporter.exe filter_incidents by_location <location>\n"
              << "  reporter.exe filter_incidents by_severity <severity>\n";
}

int main(int argc, char* argv[]) {
    try {
        Report rpt(Report::loadIncidents("incidents.txt"));

        if (argc < 2) { usage(); return 1; }
        std::string cmd = argv[1];

        if (cmd == "report_incident") {
            if (argc < 6) { usage(); return 1; }
            std::string id  = argv[2];
            std::string desc= argv[3];
            std::string loc = argv[4];
            int sev = std::stoi(argv[5]);
            rpt.addIncident(Incident(id, desc, loc, sev, false, Date::today()));
        }
        else if (cmd == "view_unresolved") {
            for (const auto& in : rpt.getUnresolved())
                std::cout << in.toColoredString() << '\n';
        }
        else if (cmd == "filter_incidents") {
            if (argc < 4) { usage(); return 1; }
            std::string sub = argv[2];
            if (sub == "by_location") {
                auto res = rpt.filterByLocation(argv[3]);
                for (const auto& in : res)
                    std::cout << in.toColoredString() << '\n';
            } else if (sub == "by_severity") {
                int sev = std::stoi(argv[3]);
                auto res = rpt.filterBySeverity(sev);
                for (const auto& in : res)
                    std::cout << in.toColoredString() << '\n';
            } else usage();
        }
        else {
            usage(); return 1;
        }

        Report::saveIncidents(rpt.getAll(), "incidents.txt");
        Report::saveUnresolved(rpt.getUnresolved(), "unresolved.txt");
    }
    catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << '\n';
        return 1;
    }
    return 0;
}
