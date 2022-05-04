#include "IdleState.h"

#include "PathCreationStateManager.h"

namespace PDFPathCreationAPI {
	IdleState::~IdleState() {}

	void IdleState::beginPath() {
		_stateManager->appendPath();
	}
}