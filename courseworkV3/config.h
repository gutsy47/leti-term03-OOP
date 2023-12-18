#ifndef OOP_CONFIG_H
#define OOP_CONFIG_H


// Константы. Установлены рекомендуемые значения
const int WINDOW_SIZE_X = 500;                   // Ширина окна. Не меньше 300.
const int WINDOW_SIZE_Y = 500;                   // Высота окна. Не меньше 300.
const int LIGHTS_COUNT  = 4;                     // Количество светофоров
const int LIGHTS_COORDS[LIGHTS_COUNT][2] = {     // Координаты [x, y] каждого светофора
    {144, 100}, {320, 100}, {144, 310}, {320, 310}
};


#endif //OOP_CONFIG_H
