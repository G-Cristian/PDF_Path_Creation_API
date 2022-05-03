#ifndef PATH_H
#define PATH_H

#include "PathCreationCommand.h"
#include "Subpath.h"

#include <string>
#include <vector>

namespace PDFPathCreationAPI {
	class Path {
	public:
		/* Subpath */
		Subpath* addSubpath(const Subpath&);
		void removeLastSubpath();
		const Subpath* getLastSubpath() const;
		Subpath* getLastSubpath();

		/* Clipping Path */
		const PathCreationCommand* getClippingPathCommand() const { return &_clippingPathCommand; }
		const PathCreationCommand* setClippingPathCommand(const PathCreationCommand&);

		/* Path Painting */
		const PathCreationCommand* getPathPaintinghCommand() const { return &_pathPaintingCommand; }
		const PathCreationCommand* setPathPaintinghCommand(const PathCreationCommand&);

		/* Other methods */
		std::string toString() const;
	private:
		std::vector<Subpath> _subpaths;
		PathCreationCommand _clippingPathCommand;
		PathCreationCommand _pathPaintingCommand;
	};
}

#endif // !PATH_H
