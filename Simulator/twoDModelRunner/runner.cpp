/* Copyright 2007-2015 QReal Research Group
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

#include "runner.h"

#include <QtCore/QFile>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonValue>
#include <QtWidgets/QApplication>

#include <twoDModel/engine/view/twoDModelWidget.h>
#include <twoDModel/engine/model/model.h>
#include "myinterpreter.h"
#include "demorun.h"

using namespace twoDModel;

Runner::Runner(const QString &report, const QString &trajectory)
	: mProjectManager(mQRealFacade.models())
	, mMainWindow(mErrorReporter, mQRealFacade.events()
			, mProjectManager, mQRealFacade.models().graphicalModelAssistApi())
	, mConfigurator(mQRealFacade.models().repoControlApi()
			, mQRealFacade.models().graphicalModelAssistApi()
			, mQRealFacade.models().logicalModelAssistApi()
			, mController
			, mMainWindow
			, mMainWindow
			, mProjectManager
			, mSceneCustomizer
			, mQRealFacade.events()
			, mTextManager)
	, mReporter(report, trajectory)
{
	mPluginFacade.init(mConfigurator);

    //достаем robotModel
    QList<view::TwoDModelWidget *> twoDModelWindows;
    for (QWidget * const widget : QApplication::allWidgets()) {
        if (view::TwoDModelWidget * const twoDModelWindow = dynamic_cast<view::TwoDModelWidget *>(widget)) {
            twoDModelWindows << twoDModelWindow;
        }
    }

    model::RobotModel * myRobotModel = twoDModelWindows[0]->model().robotModels()[0];
    for (view::TwoDModelWidget * const twoDModelWindow : twoDModelWindows) {
        if (twoDModelWindow->model().robotModels()[0]) {
            myRobotModel = twoDModelWindow->model().robotModels()[0];
        }
    }
//    const auto myRobotModel = twoDModelWindows[0]->model().robotModels()[0];
//4 twodmodelwindow, в каждой по robotmodel

    MyInterpreter *myInterpreter = new MyInterpreter(
                mConfigurator.graphicalModelApi()
                , mConfigurator.logicalModelApi()
                , mConfigurator.mainWindowInterpretersInterface()
                , mConfigurator.projectManager());
    myInterpreter->setModel(myRobotModel);
    mPluginFacade.registerInterpreter(myInterpreter);
	for (const QString &defaultSettingsFile : mPluginFacade.defaultSettingsFiles()) {
		qReal::SettingsManager::loadDefaultSettings(defaultSettingsFile);
	}

    qDebug("runner");

    DemoRun const *demoRun = new DemoRun(myInterpreter);
  //  connect(this, Runner::readyToRun, demoRun, DemoRun::Run);
    QObject::connect(this, &Runner::readyToRun, demoRun, &DemoRun::Run);

    connect(&mErrorReporter, &qReal::ConsoleErrorReporter::informationAdded, &mReporter, &Reporter::addInformation);
	connect(&mErrorReporter, &qReal::ConsoleErrorReporter::errorAdded, &mReporter, &Reporter::addError);
	connect(&mErrorReporter, &qReal::ConsoleErrorReporter::criticalAdded, &mReporter, &Reporter::addError);
}

Runner::Runner(const QString &report, const QString &trajectory, const QString &input, const QString &mode)
	: Runner(report, trajectory)

{
	mInputsFile = input;
	mMode = mode;
}

Runner::~Runner()
{
	mReporter.onInterpretationEnd();
	mReporter.reportMessages();
}

bool Runner::interpret(const QString &saveFile, bool background)
{
/*    if (!mProjectManager.open(saveFile)) {
        return false;
    }*/

	/// @todo: A bit hacky way to get 2D model window. Actually we must not have need in this.
	/// GUI must be separated from logic and not appear here at all.
	QList<view::TwoDModelWidget *> twoDModelWindows;
	for (QWidget * const widget : QApplication::allWidgets()) {
		if (view::TwoDModelWidget * const twoDModelWindow = dynamic_cast<view::TwoDModelWidget *>(widget)) {
            twoDModelWindows << twoDModelWindow;
		}
	}

	if (background) {
		connect(&mPluginFacade.eventsForKitPlugins
				(), &kitBase::EventsForKitPluginInterface::interpretationStopped, [&]() {
				QTimer::singleShot(0, this, SLOT(close()));
		});
	}

	for (view::TwoDModelWidget * const twoDModelWindow : twoDModelWindows) {
		connect(twoDModelWindow, &view::TwoDModelWidget::widgetClosed, [=]() { mMainWindow.emulateClose(); });
		twoDModelWindow->model().timeline().setImmediateMode(background);
        qDebug("window");
		for (const model::RobotModel *robotModel : twoDModelWindow->model().robotModels()) {
            qDebug("robotmodel");
			connectRobotModel(robotModel);
		}
	}
    qReal::Id *myId = new qReal::Id("1", "2", "3");
    qReal::TabInfo *myTab = new qReal::TabInfo(*myId, nullptr);
    emit mConfigurator.systemEvents().activeTabChanged(*myTab);
	mReporter.onInterpretationStart();
/*    if (mMode == "js") {
        return mPluginFacade.interpretCode(mInputsFile);
    } else if (mMode == "diagram") {
        mPluginFacade.actionsManager().runAction().trigger();
    }*/ // эту вещь меняем на посылку сигнала "все готово"
    qDebug("interpret раннера и эмитим readytorun");
    emit this->readyToRun();

	return true;
}

void Runner::connectRobotModel(const model::RobotModel *robotModel)
{
	connect(robotModel, &model::RobotModel::positionRecalculated
			, this, &Runner::onRobotRided, Qt::UniqueConnection);

	connect(&robotModel->info().configuration(), &kitBase::robotModel::ConfigurationInterface::deviceConfigured
			, this, [=](const kitBase::robotModel::robotParts::Device *device) {
		connect(device, &kitBase::robotModel::robotParts::Device::propertyChanged, this
				, [=](const QString &property, const QVariant &value) {
			onDeviceStateChanged(robotModel->info().robotId(), device, property, value);
		});
	});
}

void Runner::onRobotRided(const QPointF &newPosition, const qreal newRotation)
{
	mReporter.newTrajectoryPoint(
			static_cast<model::RobotModel *>(sender())->info().robotId()
			, mPluginFacade.interpreter().timeElapsed()
			, newPosition
			, newRotation
			);
}

void Runner::onDeviceStateChanged(const QString &robotId
		, const kitBase::robotModel::robotParts::Device *device
		, const QString &property
		, const QVariant &value)
{
	mReporter.newDeviceState(robotId
			, mPluginFacade.interpreter().timeElapsed()
			, device->deviceInfo().name()
			, device->port().name()
			, property
			, value
			);
}

void Runner::close()
{
	mMainWindow.emulateClose(mReporter.lastMessageIsError() ? 1 : 0);
}
