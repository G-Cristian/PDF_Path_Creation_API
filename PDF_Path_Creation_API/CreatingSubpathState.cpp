#include "CreatingSubpathState.h"

#include "PathCreationCommandFactory.h"
#include "PathCreationStateManager.h"
#include "Subpath.h"

namespace PDFPathCreationAPI {
	void CreatingSubpathState::endSubpath(bool closeSubpath) {
		if (_stateManager->_currentSubpath) {
			_stateManager->_currentSubpath->setClosingSubpathCommand(_stateManager->getCloseSubpathCommandBasedOnOption(closeSubpath));
		}

		_stateManager->_currentSubpath = nullptr;
	}

	void CreatingSubpathState::beginCubicBezierCurve(int x, int y) {
		if (_stateManager->_currentSubpath) {
			_stateManager->_currentSubpath->addCreationCommand(PathCreationCommandFactory::getInstance().appendBezierCurve(x, y));
		}
	}

	void CreatingSubpathState::appendStraightLinePoint(int x, int y) {
		if (_stateManager->_currentSubpath) {
			_stateManager->_currentSubpath->addCreationCommand(PathCreationCommandFactory::getInstance().appendLine(x, y));
		}
	}

	void CreatingSubpathState::updateCurrentPoint(int x, int y) {
		if (_stateManager->_currentSubpath) {
			PathCreationCommand* lastCreationCommand = _stateManager->_currentSubpath->getLastCreationCommand();
			if (lastCreationCommand) {
				lastCreationCommand->updatePoint(lastCreationCommand->points().size() - 1, x, y);
			}
		}
	}
}
