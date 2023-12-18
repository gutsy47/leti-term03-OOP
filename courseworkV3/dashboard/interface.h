#ifndef OOP_DASHBOARD_H
#define OOP_DASHBOARD_H


#include "../config.h"

#include <QWidget>
#include <QPushButton>
#include <QRadioButton>
#include <QLabel>


class TDashboard : public QWidget {
private:
    Q_OBJECT

    // Labels
    QLabel *title;
    QLabel *mode;
    QLabel *state;

    // Buttons
    QRadioButton *btnAutonomous;
    QRadioButton *btnAutomatic;
    QRadioButton *btnManual;

    bool         isEnabled;
    QPushButton  *btnState;

public:
    explicit TDashboard(QWidget* = nullptr);
    ~TDashboard() override;
};




class TDevice : public QWidget {
private:
    Q_OBJECT
    enum { OFF = -1, RED = 0, YELLOW = 1, GREEN = 2 } state;
    bool        isEnabled;
    QPushButton *btnState;
    QLabel      *counter;

public:
    explicit TDevice(QWidget* = nullptr);
    ~TDevice() override;
};




class TInterface : public QWidget {
private:
    Q_OBJECT
    TDashboard *dashboard;
    TDevice    *devices[LIGHTS_COUNT];

public:
    explicit TInterface(QWidget* = nullptr);
    ~TInterface() override;
};


#endif //OOP_DASHBOARD_H
