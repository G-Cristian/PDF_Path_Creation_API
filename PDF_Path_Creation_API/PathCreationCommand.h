#ifndef PATHCREATIONCOMMAND_H
#define PATHCREATIONCOMMAND_H

#include <utility>
#include <string>
#include <vector>

namespace PDFPathCreationAPI {

	class PathCreationCommand;
	bool operator==(const PathCreationCommand&, const PathCreationCommand&);
	bool operator!=(const PathCreationCommand&, const PathCreationCommand&);

	class PathCreationCommand {
		using Point = std::pair<int, int>;
		friend class PathCreationCommandFactory;
	public:
		PathCreationCommand() = default;

		/* Getters */
		const std::vector<Point>& points() const { return _points; }
		const std::string& command() const { return _command; }

		/* Other methods */
		const Point& updatePoint(size_t index, int x, int y);

	private:
		PathCreationCommand(const std::vector<Point>& points, const std::string& command) :
			_points(points),
			_command(command) {
		}

		std::vector<Point> _points;
		std::string _command;
	};

	extern const PathCreationCommand EmptyCommand;
}

#endif // !PATHCREATIONCOMMAND_H
