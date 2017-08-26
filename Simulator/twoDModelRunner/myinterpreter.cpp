/* Copyright 2012-2016 CyberTech Labs Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License. */

#include "myinterpreter.h"

#include <QtCore/QCoreApplication>
#include <QtWidgets/QAction>

#include <qrtext/languageToolboxInterface.h>

#include <utils/timelineInterface.h>
#include <kitBase/robotModel/robotModelInterface.h>
#include <kitBase/robotModel/robotModelUtils.h>
#include <twoDModel/robotModel/parts/motor.h>
#include "kitBase/robotModel/robotParts/device.h"


using namespace qReal;
using namespace interpreterCore::interpreter;
using namespace kitBase::robotModel;
using namespace twoDModel;
using namespace kitBase;
using namespace twoDModel::robotModel::parts;

const IdList supportedDiagramTypes = {
        Id("1", "2", "3")
};

MyInterpreter::MyInterpreter(const GraphicalModelAssistInterface &graphicalModelApi
                             , LogicalModelAssistInterface &logicalModelApi
                             , qReal::gui::MainWindowInterpretersInterface &interpretersInterface
                             , const qReal::ProjectManagementInterface &projectManager
                             )
                         : mGraphicalModelApi(graphicalModelApi)
                         , mLogicalModelApi(logicalModelApi)
                         , mInterpretersInterface(interpretersInterface)
                         , mState(idle)

{
    qDebug("конструктор интерпретатора");
}

MyInterpreter::~MyInterpreter()
{

}

bool MyInterpreter::isRunning() const
{
    return true;
}

void MyInterpreter::motorsOn(int speed)
{
    qDebug("motorsOn");
//    Motor * motor = kitBase::robotModel::RobotModelUtils::findDevice<Motor>(*mRobotModel, port);
    const PortInfo *m3Port = new PortInfo("M3", output);
 //   const PortInfo *m4Port = new PortInfo("M4", output);
    kitBase::robotModel::robotParts::Motor * motor = dynamic_cast<robotParts::Motor *>(mRobotModel->info().configuration().device(*m3Port));
    if (motor)
    {
        motor->on(speed);
    }
    qDebug("установили скорость");
}

void MyInterpreter::setModel(twoDModel::model::RobotModel * const robotModel)
{
    mRobotModel = robotModel;
}

void MyInterpreter::connectToRobot()
{
    //mRobotModelManager.model().connectToRobot();
}

void MyInterpreter::interpret()
{
/*    const QString modelName = mRobotModelManager.model().robotId();
    for (const PortInfo &port : mRobotModelManager.model().configurablePorts()) {
        const DeviceInfo deviceInfo = currentConfiguration(modelName, port);
        mRobotModelManager.model().configureDevice(port, deviceInfo);
    }

    mRobotModelManager.model().applyConfiguration();*/
    // если достаем как-то robotmodelmanager
    // todo конфигурация девайсов, надо ли?
}

void MyInterpreter::stopRobot(qReal::interpretation::StopReason reason)
{
    //?
}

int MyInterpreter::timeElapsed() const
{
    return 0;
}

IdList MyInterpreter::supportedDiagrams() const
{
    return supportedDiagramTypes;
}
