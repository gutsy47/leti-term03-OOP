#ifndef OOP_PARSER_H
#define OOP_PARSER_H

#include <QWidget>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>

#include <vector>
#include <fstream>


class TParser : public QWidget {
private:
    Q_OBJECT

    std::vector<std::vector<int>> values;

    std::string getPath();
    short parseFile(const std::string&);
    void showError(const short&);

public:
    explicit TParser(QWidget *parent = nullptr);
    std::vector<std::vector<int>> getValues();
};


#endif //OOP_PARSER_H