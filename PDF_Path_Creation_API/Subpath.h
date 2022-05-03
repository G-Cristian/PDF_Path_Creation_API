#ifndef SUBPATH_H
#define SUBPATH_H

#include "PathCreationCommand.h"

#include <string>
#include <vector>

namespace PDFPathCreationAPI {
	class Subpath {
	public:
		/* Creation Comands */
		PathCreationCommand* addCreationCommand(const PathCreationCommand&);

		const PathCreationCommand* getLastCreationCommand() const;
		PathCreationCommand* getLastCreationCommand();

		/* Closing Subpath Command */
		const PathCreationCommand* getClosingSubpathCommand() const { return &_closingSubpathCommand; }
		const PathCreationCommand* setClosingSubpathCommand(const PathCreationCommand&);

		/* Other methods */
		std::string toString() const;
	private:
		std::vector<PathCreationCommand> _creationCommands;
		PathCreationCommand _closingSubpathCommand;
	};
}

#endif // !SUBPATH_H
