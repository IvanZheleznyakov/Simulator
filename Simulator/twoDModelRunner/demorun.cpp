#include "demorun.h"
#include "myinterpreter.h"
#include <QEventLoop>

using namespace twoDModel;
using namespace kitBase::robotModel;

DemoRun::DemoRun(MyInterpreter * const interpreter)
    : mInterpreter(interpreter)
{

}

void DemoRun::Run()
{
//    const PortInfo *m3Port = new PortInfo("M3", output);
//    const PortInfo *m4Port = new PortInfo("M4", output);
    // Используем наш интерпретатор, чтобы включить моторы на портах по умолчанию (M3 и M4) на 100% мощности
    qDebug("demorun run");

    mInterpreter->motorsOn(100);


//    mInterpreter->motorsOn(*m4Port, 100);

    // Запускаем таймер, который по истечении 1000 миллисекунд включит моторы с мощностью -100 (то есть робот должен поехать обратно)
    QTimer::singleShot(1000, [this](){ mInterpreter->motorsOn(-100); });
//    QTimer::singleShot(1000, [this](){ mInterpreter->motorsOn(*m4Port, -100); });

    // Запускаем локальный цикл обработки событий, чтобы программа не закончилась раньше времени и, тем не менее, была способна обрабатывать события от таймеров. Запускаем таймер, который прибьёт цикл обработки событий через 2 секунды и тем закончит исполнение этой функции.
    QEventLoop loop;
    QTimer::singleShot(2000, &loop, SLOT(quit()));
    loop.exec();
}
