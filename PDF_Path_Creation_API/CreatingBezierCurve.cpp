#include "CreatingBezierCurve.h"


#include "PathCreationCommandFactory.h"
#include "PathCreationStateManager.h"
#include "Subpath.h"

namespace PDFPathCreationAPI {

	CreatingBezierCurve::~CreatingBezierCurve() {}

	bool CreatingBezierCurve::appendCubicBezierCurvePoint(int x, int y) {
		updateCurrentPoint(x, y);

		switch (_innerState)
		{
		case InnerState::FIRST_POINT:
			_innerState = InnerState::SECOND_POINT;
			break;
		case InnerState::SECOND_POINT:
			_innerState = InnerState::THIRD_POINT;
			break;
		case InnerState::THIRD_POINT:
			return true;
			break;
		default:
			break;
		}

		return false;
	}

	void CreatingBezierCurve::updateCurrentPoint(int x, int y) {
		if (_stateManager->_currentSubpath) {
			PathCreationCommand* lastCreationCommand = _stateManager->_currentSubpath->getLastCreationCommand();
			if (lastCreationCommand) {
				switch (_innerState)
				{
				case InnerState::FIRST_POINT:
					lastCreationCommand->updatePoint(0, x, y);
					lastCreationCommand->updatePoint(1, x, y);
					lastCreationCommand->updatePoint(2, x, y);
					break;
				case InnerState::SECOND_POINT:
					lastCreationCommand->updatePoint(1, x, y);
					lastCreationCommand->updatePoint(2, x, y);
					break;
				case InnerState::THIRD_POINT:
					lastCreationCommand->updatePoint(2, x, y);
					break;
				default:
					break;
				}
			}
		}
	}
}
