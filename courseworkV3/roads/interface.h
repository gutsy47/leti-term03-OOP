#ifndef OOP_INTERFACE_H
#define OOP_INTERFACE_H


#include "sample-light.h"
#include "sample-road.h"
#include "../config.h"

#include <QWidget>


class TInterface : public QWidget {
private:
    Q_OBJECT
    TLight *lights[LIGHTS_COUNT]; // Светофоры
    TRoad  *road;                 // Рисунок перекрестка

public:
    explicit TInterface(QWidget* = nullptr); // Создаёт интерфейс
    ~TInterface() override;                  // Удаляет интерфейс, чистит память

protected:
    void paintEvent(QPaintEvent*) override;  // Отрисовка интерфейса

private:
    // TODO: Здесь будет переключение светофоров

public slots:
    void answer(QString);  // Слот ответа на сообщение

signals:
    void request(QString); // Сигнал отправки сообщения
};


#endif //OOP_INTERFACE_H
