#include "CreatingPathState.h"

#include "PathCreationCommandFactory.h"
#include "PathCreationStateManager.h"
#include "Subpath.h"

namespace PDFPathCreationAPI {

	CreatingPathState::~CreatingPathState() {}

	void CreatingPathState::endPath() {
		_stateManager->resetCurrentPathSubpathAndOptions();
	}

	void CreatingPathState::beginSubpath(int x, int y) {
		Subpath *subpath = _stateManager->appendSubpath();
		if (subpath) {
			subpath->addCreationCommand(PathCreationCommandFactory::getInstance().beginSubpath(x, y));
		}
	}

	void CreatingPathState::beginRectangle(int x, int y) {
		Subpath* subpath = _stateManager->appendSubpath();
		if (subpath) {
			subpath->addCreationCommand(PathCreationCommandFactory::getInstance().appendRectangle(x, y));
		}
	}
}