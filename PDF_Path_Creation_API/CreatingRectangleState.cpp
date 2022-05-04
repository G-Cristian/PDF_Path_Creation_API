#include "CreatingRectangleState.h"

#include "PathCreationCommand.h"
#include "PathCreationCommandFactory.h"
#include "PathCreationStateManager.h"
#include "Subpath.h"

namespace PDFPathCreationAPI {
	CreatingRectangleState::~CreatingRectangleState() {}

	void CreatingRectangleState::endRectangle() {
		_stateManager->_currentSubpath = nullptr;
	}

	void CreatingRectangleState::updateCurrentPoint(int x, int y) {
		if(_stateManager->_currentSubpath){
			PathCreationCommand* lastCreationCommand = _stateManager->_currentSubpath->getLastCreationCommand();
			if (lastCreationCommand) {
				lastCreationCommand->updatePoint(1, x, y);
			}
		}
	}
}