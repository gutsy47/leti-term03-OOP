#include "parser.h"


TParser::TParser(QWidget *parent) : QWidget(parent) {
    short response = 0;
    while (response != 1 && response != -1) {
        std::string path = getPath();
        graph = new Graph();
        response = parseFile(path);
        if (response != 1) showError(response);
    }
}


/// Get path from user
std::string TParser::getPath() {
    QFile file = QFileDialog::getOpenFileName(
            nullptr, tr("Open input file"), "../../practice07", tr("Text (*.txt)")
    );

    return file.fileName().toStdString();
}


/// Update <this.names> & <this.values> by data from <path>. Return 1 on success
/** Return values
 *  1 Success
 * -1 File Not Found
 * -2 Invalid Input
 * -3 Invalid Size
 * -4 Non-Zero Diagonals
 */
short TParser::parseFile(const std::string &path) {
    // Open file. Return -1 if not found
    std::ifstream iFile(path);
    if (!iFile.is_open()) return -1;
    std::string line;

    // Get names
    std::getline(iFile, line);
    std::string name;
    std::vector<char> names;
    for (auto &c : line) {
        if (c == ' ') {
            if (!name.empty()) names.push_back(name[0]);
            name.clear();
        } else {
            name += c;
            if (name.length() > 1) return -2;
        }
    }
    names.push_back(name[0]);

    // Get values
    std::vector<std::vector<int>> values;
    while (std::getline(iFile, line)) {
        std::vector<int> row;
        for (int i = 0; i < line.length(); ++i) {
            if (line[i] == '0' || line[i] == '1') {
                if (i != line.length() - 1 && line[i+1] != ' ') return -2; // Not '0' or '1' value error
                row.push_back(line[i] - '0');
            } else if (line[i] != ' ') return -2; // Invalid char error
        }
        if (!values.empty() && row.size() != values[0].size()) return -3; // Invalid row size
        values.push_back(row);
    }
    if (values.size() != values[0].size()) return -3; // Invalid matrix size
    for (int i = 0; i < values.size(); ++i) if (values[i][i] != 0) return -4; // Invalid diagonals

    graph->setVertices(names, values);
    iFile.close();
    return 1;
}


/// Show error message
void TParser::showError(const short &response) {
    if (response == -1)      QMessageBox::information(nullptr, "Cancelled", "File wasn't selected\nPress OK to exit");
    else if (response == -2) QMessageBox::critical(nullptr, "Error #2", "Invalid Input error");
    else if (response == -3) QMessageBox::critical(nullptr, "Error #3", "Invalid Size error");
    else if (response == -4) QMessageBox::critical(nullptr, "Error #4", "Non-Zero Diagonals error");
    else                     QMessageBox::critical(nullptr, "Error #5", "Unknown error");
}