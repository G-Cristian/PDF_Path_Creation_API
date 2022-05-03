#include "IdleState.h"

#include "PathCreationStateManager.h"

namespace PDFPathCreationAPI {
	void IdleState::beginPath() {
		_stateManager->appendPath();
	}
}