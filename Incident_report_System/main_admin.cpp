
#include <iostream>
#include "Report.h"

static void usage() {
    std::cerr << "Admin usage:\n"
              << "  admin.exe view_incidents\n"
              << "  admin.exe add_incident <id> <description> <location> <severity>\n"
              << "  admin.exe delete_incident <id>\n"
              << "  admin.exe modify_incident <id> <description|location|severity> <new_value>\n"
              << "  admin.exe resolve_incident <id>\n"
              << "  admin.exe export_reports\n";
}

int main(int argc, char* argv[]) {
    try {
        Report rpt(Report::loadIncidents("incidents.txt"));

        if (argc < 2) { usage(); return 1; }
        std::string cmd = argv[1];

        if (cmd == "view_incidents") {
            for (const auto& in : rpt.getAll())
                std::cout << in.toColoredString() << '\n';
        }
        else if (cmd == "add_incident") {
            if (argc < 6) { usage(); return 1; }
            std::string id  = argv[2];
            std::string desc= argv[3];
            std::string loc = argv[4];
            int sev = std::stoi(argv[5]);
            rpt.addIncident(Incident(id, desc, loc, sev, false, Date::today()));
        }
        else if (cmd == "delete_incident") {
            if (argc < 3) { usage(); return 1; }
            bool ok = rpt.deleteIncident(argv[2]);
            if (!ok) std::cerr << "Incident not found.\n";
        }
        else if (cmd == "modify_incident") {
            if (argc < 5) { usage(); return 1; }
            bool ok = rpt.modifyIncident(argv[2], argv[3], argv[4]);
            if (!ok) std::cerr << "Incident not found or field invalid.\n";
        }
        else if (cmd == "resolve_incident") {
            if (argc < 3) { usage(); return 1; }
            bool ok = rpt.resolveIncident(argv[2]);
            if (!ok) std::cerr << "Incident not found.\n";
        }
        else if (cmd == "export_reports") {
            rpt.exportSnapshot("report_log.txt");
            std::cout << "Snapshot exported.\n";
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
