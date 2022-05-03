#include "Path.h"

#include "Subpath.h"
#include "PathCreationCommand.h"

#include <sstream>
#include <string>

namespace PDFPathCreationAPI {
	Subpath* Path::addSubpath(const Subpath& subpath) {
		_subpaths.push_back(subpath);

		return &(_subpaths[_subpaths.size() - 1]);
	}

	void Path::removeLastSubpath() {
		if (!_subpaths.empty()) {
			_subpaths.pop_back();
		}
	}

	const Subpath* Path::getLastSubpath() const {
		if (_subpaths.empty()) {
			return nullptr;
		}

		return &(_subpaths[_subpaths.size() - 1]);
	}

	Subpath* Path::getLastSubpath() {
		if (_subpaths.empty()) {
			return nullptr;
		}

		return &(_subpaths[_subpaths.size() - 1]);
	}

	const PathCreationCommand* Path::setClippingPathCommand(const PathCreationCommand& clippingPathCommand) {
		_clippingPathCommand = clippingPathCommand;
		return &_clippingPathCommand;
	}

	const PathCreationCommand* Path::setPathPaintinghCommand(const PathCreationCommand& pathPaintingCommand) {
		_pathPaintingCommand = pathPaintingCommand;
		return &_pathPaintingCommand;
	}

	std::string Path::toString() const {
		std::stringstream ss;

		for (size_t i = 0; i != _subpaths.size(); i++) {
			const Subpath& subpath = _subpaths[i];

			if (i != 0) {
				ss << " ";
			}

			ss << subpath.toString();
		}

		if (!_subpaths.empty()) {
			ss << " ";
		}

		ss << _clippingPathCommand.command();
		if (_clippingPathCommand != EmptyCommand) {
			ss << " ";
		}

		ss << _pathPaintingCommand.command();

		return ss.str();
	}
}