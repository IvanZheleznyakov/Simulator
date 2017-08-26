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

#pragma once

#include <QtCore/QObject>
#include <QtWidgets/QAction>

#include <qrgui/plugins/toolPluginInterface/usedInterfaces/projectManagementInterface.h>
#include <qrgui/plugins/toolPluginInterface/usedInterfaces/graphicalModelAssistInterface.h>
#include <qrgui/plugins/toolPluginInterface/usedInterfaces/logicalModelAssistInterface.h>
#include <qrutils/interpreter/thread.h>
#include <qrtext/languageToolboxInterface.h>

#include <kitBase/interpreterInterface.h>
#include <kitBase/robotModel/robotModelManagerInterface.h>
#include <kitBase/devicesConfigurationProvider.h>
#include <kitBase/robotModel/robotModelInterface.h>

#include "interpreterCore/interpreter/details/blocksTable.h"
#include "interpreterCore/interpreter/details/sensorVariablesUpdater.h"
#include "interpreterCore/interpreter/details/autoconfigurer.h"
#include <twoDModel/engine/model/model.h>
#include <kitBase/robotModel/portInfo.h>
#include <kitBase/robotModel/robotParts/motor.h>



namespace twoDModel {


class MyInterpreter : public kitBase::InterpreterInterface
{
    Q_OBJECT

public:
    MyInterpreter(const qReal::GraphicalModelAssistInterface &graphicalModelApi
                  , qReal::LogicalModelAssistInterface &logicalModelApi
                  , qReal::gui::MainWindowInterpretersInterface &interpretersInterface
                  , const qReal::ProjectManagementInterface &projectManager
                  );

    ~MyInterpreter() override;

    bool isRunning() const;

    void motorsOn(int speed);

    void setModel(twoDModel::model::RobotModel * const robotModel);

public slots:
    void connectToRobot() override;
    void interpret() override;
    void stopRobot(qReal::interpretation::StopReason reason = qReal::interpretation::StopReason::userStop) override;
    int timeElapsed() const override;
    qReal::IdList supportedDiagrams() const override;

private slots:


private:
    enum InterpreterState {
        interpreting
        , waitingForDevicesConfiguredToLaunch
        , idle
    }; //из blockinterpreter отсюда

    const qReal::GraphicalModelAssistInterface &mGraphicalModelApi;
    qReal::LogicalModelAssistInterface &mLogicalModelApi;
    qReal::gui::MainWindowInterpretersInterface &mInterpretersInterface;

    InterpreterState mState;
    quint64 mInterpretationStartedTimestamp;
    QHash<QString, qReal::interpretation::Thread *> mThreads;  //из blockinterpreter досюда

 //   interpreterCore::interpreter::details::SensorVariablesUpdater mSensorVariablesUpdater;

    const twoDModel::model::RobotModel *mRobotModel; //todo мб сделать лист robotmodel
};

}
