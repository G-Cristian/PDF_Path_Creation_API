#include "PathCreationStateManager.h"

#include "CreatingBezierCurve.h"
#include "CreatingPathState.h"
#include "CreatingRectangleState.h"
#include "CreatingSubpathState.h"
#include "Path.h"
#include "PathCreationCommandFactory.h"

namespace PDFPathCreationAPI {
	void PathCreationStateManager::beginPath() {
		_state->beginPath();
		_state.reset(new CreatingPathState(this));
	}

	void PathCreationStateManager::endPath() {
		_state->endPath();
		_state.reset(new IdleState(this));
	}

	void PathCreationStateManager::beginSubpath(int x, int y) {
		_state->beginSubpath(x, y);
		_state.reset(new CreatingSubpathState(this));
	}

	void PathCreationStateManager::endSubpath() {
		_state->endSubpath(_closeSubpathOption);
		_state.reset(new CreatingPathState(this));
	}

	void PathCreationStateManager::beginCubicBezierCurve(int x, int y) {
		_state->beginCubicBezierCurve(x, y);
		_state.reset(new CreatingBezierCurve(this));
	}

	void PathCreationStateManager::appendCubicBezierCurvePoint(int x, int y) {
		if (_state->appendCubicBezierCurvePoint(x, y)) {
			_state.reset(new CreatingSubpathState(this));
		}
	}

	void PathCreationStateManager::appendStraightLinePoint(int x, int y) {
		_state->appendStraightLinePoint(x, y);
	}

	void PathCreationStateManager::beginRectangle(int x, int y) {
		_state->beginRectangle(x, y);
		_state.reset(new CreatingRectangleState(this));
	}

	void PathCreationStateManager::endRectangle() {
		_state->endRectangle();
		_state.reset(new CreatingPathState(this));
	}

	void PathCreationStateManager::updateCurrentPoint(int x, int y) {
		_state->updateCurrentPoint(x, y);
	}

	void PathCreationStateManager::dropCurrentSubpath() {
		if (_currentPath && _currentSubpath) {
			_currentPath->removeLastSubpath();
			_currentSubpath = nullptr;
			_closeSubpathOption = false;
			_state.reset(new CreatingPathState(this));
		}
	}

	void PathCreationStateManager::removeLastPath() {
		if (!_paths.empty()) {
			_paths.pop_back();
		}
		resetCurrentPathSubpathAndOptions();
		_state.reset(new IdleState(this));
	}

	Path* PathCreationStateManager::appendPath() {
		_paths.push_back(Path());
		_currentPath = &(_paths[_paths.size() - 1]);
		_currentPath->setClippingPathCommand(getClippingPathCommandBasedOnOption(_clippingPathOption));
		_currentPath->setPathPaintinghCommand(getPathPaintingCommandBasedOnOption(_pathPaintingOption));

		return _currentPath;
	}

	Subpath* PathCreationStateManager::appendSubpath() {
		if (!_currentPath) {
			return nullptr;
		}

		_currentPath->addSubpath(Subpath());
		_currentSubpath = _currentPath->getLastSubpath();
		if (_currentSubpath) {
			_currentSubpath->setClosingSubpathCommand(getCloseSubpathCommandBasedOnOption(_closeSubpathOption));
		}

		return _currentSubpath;
	}

	void PathCreationStateManager::setPathPaintingOption(PathPaintingOptions pathPaintingOption) {
		_pathPaintingOption = pathPaintingOption;
		if (_currentPath) {
			_currentPath->setPathPaintinghCommand(getPathPaintingCommandBasedOnOption(pathPaintingOption));
		}
	}

	void PathCreationStateManager::setClippingPathOption(ClippingPathOptions clippingPathOption) {
		_clippingPathOption = clippingPathOption;
		if (_currentPath) {
			_currentPath->setClippingPathCommand(getClippingPathCommandBasedOnOption(clippingPathOption));
		}
	}

	void PathCreationStateManager::setCloseSubpathOption(bool closeSubpathOption) {
		_closeSubpathOption = closeSubpathOption;
		if (_currentSubpath) {
			_currentSubpath->setClosingSubpathCommand(getCloseSubpathCommandBasedOnOption(closeSubpathOption));
		}
	}

	void PathCreationStateManager::resetCurrentPathSubpathAndOptions() {
		_currentPath = nullptr;
		_currentSubpath = nullptr;

		_pathPaintingOption = PathPaintingOptions::NO_FILL_NO_STROKE;
		_clippingPathOption = ClippingPathOptions::NO_CLIP;
		_closeSubpathOption = false;
	}

	PathCreationCommand PathCreationStateManager::getPathPaintingCommandBasedOnOption(PathPaintingOptions pathPaintingOption) const {
		switch (pathPaintingOption)
		{
		case PathPaintingOptions::NO_FILL_NO_STROKE:
			return PathCreationCommandFactory::getInstance().noFillNoStrokePath();
			break;
		case PDFPathCreationAPI::PathCreationStateManager::PathPaintingOptions::STROKE:
			return PathCreationCommandFactory::getInstance().strokePath();
			break;
		case PDFPathCreationAPI::PathCreationStateManager::PathPaintingOptions::FILL_NONZERO_WINDING_NUMBER:
			return PathCreationCommandFactory::getInstance().fillPathNonZeroWindingNumber();
			break;
		case PDFPathCreationAPI::PathCreationStateManager::PathPaintingOptions::FILL_EVEN_ODD_RULE:
			return PathCreationCommandFactory::getInstance().fillPathEvenOdd();
			break;
		case PDFPathCreationAPI::PathCreationStateManager::PathPaintingOptions::FILL_STROKE_NONZERO_WINDING_NUMBER:
			return PathCreationCommandFactory::getInstance().fillStrokePathNonZeroWindingNumber();
			break;
		case PDFPathCreationAPI::PathCreationStateManager::PathPaintingOptions::FILL_STROKE_EVEN_ODD_RULE:
			return PathCreationCommandFactory::getInstance().fillStrokePathEvenOdd();
			break;
		default:
			return PathCreationCommandFactory::getInstance().emptyCommand();
			break;
		}
	}

	PathCreationCommand PathCreationStateManager::getClippingPathCommandBasedOnOption(ClippingPathOptions clippingPathOption) const {
		if (clippingPathOption == ClippingPathOptions::NO_CLIP) {
			return PathCreationCommandFactory::getInstance().noClippingPath();
		}
		else if (clippingPathOption == ClippingPathOptions::CLIP_NONZERO_WINDING_NUMBER) {
			return PathCreationCommandFactory::getInstance().clippingPathNonZeroWindingNumber();
		}
		else if (clippingPathOption == ClippingPathOptions::CLIP_EVEN_ODD_RULE) {
			PathCreationCommandFactory::getInstance().clippingPathEvenOdd();
		}

		return PathCreationCommandFactory::getInstance().emptyCommand();
	}

	PathCreationCommand PathCreationStateManager::getCloseSubpathCommandBasedOnOption(bool closeSubpathOption) const {
		if (closeSubpathOption) {
			return PathCreationCommandFactory::getInstance().closeSubpath();
		}
		else {
			return PathCreationCommandFactory::getInstance().emptyCommand();
		}
	}
}