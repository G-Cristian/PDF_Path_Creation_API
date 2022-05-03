#include "Subpath.h"

#include "PathCreationCommand.h"

#include <sstream>
#include <string>

namespace PDFPathCreationAPI {
	PathCreationCommand* Subpath::addCreationCommand(const PathCreationCommand& command) {
		_creationCommands.push_back(command);
		return &(_creationCommands[_creationCommands.size() - 1]);
	}

	const PathCreationCommand* Subpath::getLastCreationCommand() const {
		if (_creationCommands.empty()) {
			return nullptr;
		}
		return &(_creationCommands[_creationCommands.size() - 1]);
	}

	PathCreationCommand* Subpath::getLastCreationCommand() {
		if (_creationCommands.empty()) {
			return nullptr;
		}
		return &(_creationCommands[_creationCommands.size() - 1]);
	}

	const PathCreationCommand* Subpath::setClosingSubpathCommand(const PathCreationCommand& closingCommand) {
		_closingSubpathCommand = closingCommand;
		return &_closingSubpathCommand;
	}

	std::string Subpath::toString() const {
		std::stringstream ss;
		for (size_t i = 0; i != _creationCommands.size(); i++) {
			const PathCreationCommand& command = _creationCommands[i];

			if (i != 0) {
				ss << " ";
			}

			for (const auto& point : command.points()) {
				ss << point.first << " " << point.second << " ";
			}

			ss << command.command();
		}

		if (!_creationCommands.empty()) {
			ss << " ";
		}

		ss << _closingSubpathCommand.command();

		return ss.str();
	}
}