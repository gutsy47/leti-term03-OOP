#include "interface.h"


/// Write to the QString operator
const QChar separator(';');
QString &operator>> (QString &str, const QString &other) {
    if (!str.isEmpty()) str.append(separator);
    str += other;
    return str;
}


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

    // Connects
    connect(btnState,      SIGNAL(pressed()),    this,    SLOT(onBtnState()));
    connect(btnAutonomous, SIGNAL(pressed()),    this,    SLOT(onRadioBtn()));
    connect(btnAutomatic,  SIGNAL(pressed()),    this,    SLOT(onRadioBtn()));
    connect(btnManual,     SIGNAL(pressed()),    this,    SLOT(onRadioBtn()));
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


void TDashboard::onBtnState() {
    isEnabled = !isEnabled;

    if (isEnabled) {
        btnState->setText("ВКЛ");
        btnState->setStyleSheet("background-color: green; color : white;");
    } else {
        btnState->setText("ВЫКЛ");
        btnState->setStyleSheet("background-color: red; color : white;");
    }

    emit dashEnable(isEnabled);
}


void TDashboard::onRadioBtn() {
    auto *btn = (QRadioButton*) sender();
    if (btn == btnAutonomous)     emit newMode(AUTONOMOUS);
    else if (btn == btnAutomatic) emit newMode(AUTOMATIC);
    else if (btn == btnManual)    emit newMode(MANUAL);
}




TDevice::TDevice(QWidget *parent) : QWidget(parent) {
    setFixedSize(100, 50);
    counterVal = 0;
    setState(OFF);
    mode = AUTOMATIC;

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
    btnState->setEnabled(false);

    // Counter text
    btnCounter = new QPushButton("0", this);
    btnCounter->setGeometry(60, 10, 30, 30);
    btnCounter->setFont(font);
    btnCounter->setEnabled(false);

    // Connects
    connect(btnState,   SIGNAL(pressed()), this, SLOT(onBtnState()));
    connect(btnCounter, SIGNAL(pressed()), this, SLOT(onBtnCounter()));
}


TDevice::~TDevice() {
    delete btnState;
    delete btnCounter;
}


void TDevice::setState(short newState) {
    state = newState;
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

    emit updState(state);
}


void TDevice::onBtnState() {
    isEnabled = !isEnabled;

    if (isEnabled) {
        btnState->setText("ВКЛ");
        btnState->setStyleSheet("background-color: green; color : white;");
        if (mode == MANUAL) btnCounter->setEnabled(true);
    } else {
        btnState->setText("ВЫКЛ");
        btnState->setStyleSheet("background-color: red; color : white;");
        if (mode == MANUAL) btnCounter->setEnabled(false);
    }

    emit enable(isEnabled);
}


void TDevice::onBtnCounter() {
    setState((++state) % 3);
}


void TDevice::onDashEnable(bool enabled) {
    if (!enabled && isEnabled) isEnabled = false;
    if (enabled && btnState->text() == "ВКЛ") isEnabled = true;
    btnState->setEnabled(enabled);
    btnCounter->setEnabled(isEnabled && mode == MANUAL);
    if (!enabled) setState(OFF);
}


void TDevice::onNewMode(short newMode) {
    mode = newMode;
    btnCounter->setEnabled(isEnabled && mode == MANUAL);
}


void TDevice::tact() {
    if (!isEnabled || mode == MANUAL) return;

    if (isEnabled) {
        counterVal += 1;
        counterVal %= 60;
    }

    btnCounter->setText(QString::number(counterVal));

    if (mode == AUTONOMOUS) {
        setState(state == YELLOW ? OFF : YELLOW);
        return;
    }

    if (mode == AUTOMATIC && counterVal % 3 == 0) {
        if (state == GREEN)       setState(YELLOW);
        else if (state == YELLOW) setState(RED);
        else if (state == RED)    setState(GREEN);
        else                      setState(RED);
    }
}




TInterface::TInterface(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Панель управления");
    setFixedSize(400, 300);

    timer = new QTimer();
    timer->setTimerType(Qt::PreciseTimer);
    timer->setInterval(1000);

    dashboard = new TDashboard(this);
    dashboard->show();

    int x = 220 + 40;
    int y = (300 - 70 * LIGHTS_COUNT + 20) / 2;
    for (int i = 0; i < LIGHTS_COUNT; ++i) {
        devices[i] = new TDevice(this);
        devices[i]->move(x, y + i*70);
        devices[i]->show();
        connect(dashboard,  &TDashboard::newMode,    devices[i], &TDevice::onNewMode);
        connect(dashboard,  &TDashboard::dashEnable, devices[i], &TDevice::onDashEnable);
        connect(timer,      &QTimer::timeout,        devices[i], &TDevice::tact);
        connect(devices[i], &TDevice::updState,      this,       &TInterface::onUpdState);
    }
    timer->start();
}


TInterface::~TInterface() {
    delete dashboard;
    for (auto &device : devices) delete device;
    timer->stop();
    delete timer;
}


void TInterface::onUpdState(short newState) {
    QString msg;
    for (int i = 0; i < LIGHTS_COUNT; ++i)
        if (devices[i] == sender())
            msg >> QString::number(i) >> QString::number(newState);
    emit request(msg);
}