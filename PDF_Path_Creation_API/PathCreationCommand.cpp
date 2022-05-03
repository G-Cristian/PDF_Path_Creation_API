#include "PathCreationCommand.h"

#include <stdexcept>

namespace PDFPathCreationAPI {
	const PathCreationCommand EmptyCommand;

	bool operator==(const PathCreationCommand& lhs, const PathCreationCommand& rhs) {
		return (lhs.command() == rhs.command() &&
			lhs.points() == rhs.points());
	}

	bool operator!=(const PathCreationCommand& lhs, const PathCreationCommand& rhs) {
		return !(lhs == rhs);
	}

	const PathCreationCommand::Point& PathCreationCommand::updatePoint(size_t index, int x, int y) {
		if (index < 0 || index >= _points.size()) {
			throw std::out_of_range("index must be in range");
		}

		_points[index].first = x;
		_points[index].second = y;

		return _points[index];
	}
}