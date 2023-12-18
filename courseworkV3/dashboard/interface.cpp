#include "interface.h"


TDashboard::TDashboard(QWidget *parent) : QWidget(parent) {
    setFixedSize(220, 300);

    // Change background color
    QPalette pal = palette();
    pal.setColor(QPalette::Window, QColor("#505050"));
    pal.setColor(QPalette::WindowText, QColor("#FFFFFF"));
    setAutoFillBackground(true);
    setPalette(pal);

    // Font
    QFont font;
    font.setBold(true);
    font.setPointSize(12);

    // Надпись Панель управления
    title = new QLabel("ПАНЕЛЬ УПРАВЛЕНИЯ", this);
    title->setGeometry(0, 10, 220, 20);
    title->setFont(font);
    title->setAlignment(Qt::AlignCenter);

    // Надпись Режим
    mode = new QLabel("Режим", this);
    mode->setGeometry(20, 50, 200, 20);
    mode->setFont(font);

    // Переключатели
    btnAutonomous = new QRadioButton("Автономный", this);
    btnAutonomous->setGeometry(20, 80, 200, 20);
    btnAutomatic = new QRadioButton("Автоматический", this);
    btnAutomatic->setGeometry(20, 110, 200, 20);
    btnAutomatic->setChecked(true);
    btnManual = new QRadioButton("Ручной", this);
    btnManual->setGeometry(20, 140, 200, 20);

    // Надпись Состояние
    state = new QLabel("Состояние", this);
    state->setGeometry(20, 170, 200, 20);
    state->setFont(font);

    // Кнопка состояние
    isEnabled = false;
    btnState = new QPushButton("ВЫКЛ", this);
    btnState->setGeometry(20, 200, 60, 60);
    btnState->setFont(font);
    btnState->setStyleSheet("background-color: red; color : white;");
}


TDashboard::~TDashboard() {
    delete title;
    delete mode;
    delete state;
    delete btnAutonomous;
    delete btnAutomatic;
    delete btnManual;
    delete btnState;
}




TDevice::TDevice(QWidget *parent) : QWidget(parent) {
    setFixedSize(100, 50);

    // Change background color
    state = OFF;
    QPalette pal = palette();
    QColor color;
    switch (state) {
        case OFF:    color = "#D9D9D9";  break;
        case RED:    color = Qt::red;    break;
        case YELLOW: color = Qt::yellow; break;
        case GREEN:  color = Qt::green;  break;
        default:     color = "#505050";  break;
    }
    pal.setColor(QPalette::Window, color);
    setAutoFillBackground(true);
    setPalette(pal);

    // Font
    QFont font;
    font.setBold(true);
    font.setPointSize(12);

    // Button
    isEnabled = false;
    btnState = new QPushButton("ВЫКЛ", this);
    btnState->setGeometry(0, 0, 50, 50);
    btnState->setFont(font);
    btnState->setStyleSheet("background-color: red; color : white;");

    // Counter text
    counter = new QLabel("0", this);
    counter->setGeometry(50, 0, 50, 50);
    counter->setFont(font);
    counter->setAlignment(Qt::AlignCenter);
}


TDevice::~TDevice() {
    delete btnState;
    delete counter;
}




TInterface::TInterface(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Панель управления");
    setFixedSize(400, 300);

    dashboard = new TDashboard(this);
    dashboard->show();

    int x = 220 + 40;
    int y = (300 - 70 * LIGHTS_COUNT + 20) / 2;
    for (int i = 0; i < LIGHTS_COUNT; ++i) {
        devices[i] = new TDevice(this);
        devices[i]->move(x, y + i*70);
        devices[i]->show();
    }
}


TInterface::~TInterface() {
    delete dashboard;
    for (auto &device : devices) delete device;
}