#ifndef PATHCREATIONCOMMANDFACTORY_H
#define PATHCREATIONCOMMANDFACTORY_H

#include "PathCreationCommand.h"

#include <utility>
#include <string>
#include <vector>

namespace PDFPathCreationAPI {
	class PathCreationCommandFactory {
	public:
		static const PathCreationCommandFactory& getInstance() {
			static PathCreationCommandFactory instance;
			return instance;
		}

		/* Empty command */
		PathCreationCommand emptyCommand() const {
			return EmptyCommand;
		}

		/* Creation subpath commands */
		PathCreationCommand beginSubpath(int x, int y) const {
			return { {{x, y}}, "m" };
		}

		PathCreationCommand appendLine(int x, int y) const {
			return { {{x, y}}, "l" };
		}

		PathCreationCommand appendBezierCurve(int x, int y) const {
			return { {{x, y}, {x, y}, {x, y}}, "c" };
		}

		PathCreationCommand appendRectangle(int x, int y) const {
			return { {{x, y}, {1, 1}}, "re" };
		}

		PathCreationCommand closeSubpath() const {
			return { {}, "h" };
		}

		/* Painting commands */
		PathCreationCommand strokePath() const {
			return { {}, "S" };
		}

		PathCreationCommand fillPathNonZeroWindingNumber() const {
			return { {}, "f" };
		}

		PathCreationCommand fillPathEvenOdd() const {
			return { {}, "f*" };
		}

		PathCreationCommand fillStrokePathNonZeroWindingNumber() const {
			return { {}, "B" };
		}

		PathCreationCommand fillStrokePathEvenOdd() const {
			return { {}, "B*" };
		}

		PathCreationCommand noFillNoStrokePath() const {
			return { {}, "n" };
		}

		/* Clipping commands */
		PathCreationCommand clippingPathNonZeroWindingNumber() const {
			return { {}, "W" };
		}

		PathCreationCommand clippingPathEvenOdd() const {
			return { {}, "W*" };
		}

		PathCreationCommand noClippingPath() const {
			return EmptyCommand;
		}

	private:
		using Point = std::pair<int, int>;

		PathCreationCommandFactory() = default;
	};
}
#endif // !PATHCREATIONCOMMANDFACTORY_H

