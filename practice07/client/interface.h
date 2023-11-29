#ifndef INTERFACE_H
#define INTERFACE_H


#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QRadioButton>

#include <vector>


class TInterface : public QWidget {
private:
    Q_OBJECT

    QLineEdit   *filename;
    QPushButton *btnDraw;

    QLabel *output;

public:
    explicit TInterface(QWidget *parent = nullptr);
    ~TInterface() override;

public slots:
    void answer(QString);

private slots:
    void formRequest();

signals:
    void request(QString);
};


#endif // INTERFACE_H
