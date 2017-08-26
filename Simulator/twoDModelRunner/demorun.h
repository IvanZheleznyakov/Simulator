#pragma once

#include "myinterpreter.h"

namespace twoDModel {

class DemoRun : public QObject
{
    Q_OBJECT

public:
    DemoRun(MyInterpreter * const interpreter);

public slots:
    void Run();

private:
    MyInterpreter *mInterpreter;
};
}
