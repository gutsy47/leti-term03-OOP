#ifndef OOP_DASHBOARD_H
#define OOP_DASHBOARD_H


#include "../config.h"

#include <QWidget>
#include <QPushButton>
#include <QRadioButton>
#include <QLabel>
#include <QTimer>


enum { OFF = -1, RED = 0, YELLOW = 1, GREEN = 2 };
enum { MANUAL = 0, AUTOMATIC = 1, AUTONOMOUS = 2};


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

private slots:
    void onBtnState();
    void onRadioBtn();

signals:
    void dashEnable(bool);
    void newMode(short);
};




class TDevice : public QWidget {
private:
    Q_OBJECT
    short       mode;
    short       state;
    short       counterVal;
    bool        isEnabled;
    QPushButton *btnState;
    QPushButton *btnCounter;

public:
    explicit TDevice(QWidget* = nullptr);
    ~TDevice() override;

private:
    void setState(short);

private slots:
    void onBtnState();
    void onBtnCounter();

public slots:
    void onDashEnable(bool);
    void onNewMode(short);
    void tact();

signals:
    void enable(bool);
    void updState(short);
};




class TInterface : public QWidget {
private:
    Q_OBJECT
    TDashboard *dashboard;
    TDevice    *devices[LIGHTS_COUNT];
    QTimer     *timer;

public:
    explicit TInterface(QWidget* = nullptr);
    ~TInterface() override;

public slots:
    void onUpdState(short);

signals:
    void request(QString);
};


#endif //OOP_DASHBOARD_H
