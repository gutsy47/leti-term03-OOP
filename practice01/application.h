#ifndef OOP_APPLICATION_H
#define OOP_APPLICATION_H

class Application {
public:
    Application();
    static int execute();
private:
    static bool menu(char&);
};


#endif //OOP_APPLICATION_H
