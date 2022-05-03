#ifndef PATHCREATIONSTATEMANAGER_H
#define PATHCREATIONSTATEMANAGER_H

#include "IdleState.h"
#include "Path.h"
#include "PathCreationCommand.h"
#include "Subpath.h"

#include <memory>
#include <vector>

namespace PDFPathCreationAPI {
	class CreatingBezierCurve;
	class CreatingPathState;
	class CreatingRectangleState;
	class CreatingSubpathState;
	class CreationalState;

	class PathCreationStateManager {
		/* Add state classes as friends */
		friend class CreatingBezierCurve;
		friend class CreatingPathState;
		friend class CreatingRectangleState;
		friend class CreatingSubpathState;
		friend class CreationalState;
		friend class IdleState;

	public:
		enum class PathPaintingOptions {
			NO_FILL_NO_STROKE,
			STROKE, 
			FILL_NONZERO_WINDING_NUMBER,
			FILL_EVEN_ODD_RULE,
			FILL_STROKE_NONZERO_WINDING_NUMBER,
			FILL_STROKE_EVEN_ODD_RULE
		};

		enum class ClippingPathOptions {
			NO_CLIP,
			CLIP_NONZERO_WINDING_NUMBER,
			CLIP_EVEN_ODD_RULE
		};

		static PathCreationStateManager& getInstance() {
			static PathCreationStateManager instance;

			return instance;
		}

		/* Path */
		void beginPath();
		void endPath();

		/* Subpath */
		void beginSubpath(int x, int y);
		void endSubpath();
		void beginCubicBezierCurve(int x, int y);
		void appendCubicBezierCurvePoint(int x, int y);
		void appendStraightLinePoint(int x, int y);

		void beginRectangle(int x, int y);
		void endRectangle();

		void updateCurrentPoint(int x, int y);

		void dropCurrentSubpath();

		const std::vector<Path>& getPaths()const { return _paths; }
		void removeLastPath();
		
	private:
		/* Constructor */
		PathCreationStateManager() :
			_state(new IdleState(this)),
			_paths(),
			_currentPath(nullptr),
			_currentSubpath(nullptr),
			_pathPaintingOption(PathPaintingOptions::NO_FILL_NO_STROKE),
			_clippingPathOption(ClippingPathOptions::NO_CLIP),
			_closeSubpathOption(false) {

			resetCurrentPathSubpathAndOptions();
		}

		/* Member functions */

		/* Paths & Subpaths */
		Path* appendPath();

		Subpath* appendSubpath();
		
		/* Settings */
		PathPaintingOptions getPathPaintingOption() const { return _pathPaintingOption; }
		void setPathPaintingOption(PathPaintingOptions pathPaintingOption);

		ClippingPathOptions getClippingPathOption() const { return _clippingPathOption; }
		void setClippingPathOption(ClippingPathOptions clippingPathOption);

		bool getCloseSubpathOption() const { return _closeSubpathOption; }
		void setCloseSubpathOption(bool closeSubpathOption);

		/* Helpers */

		void resetCurrentPathSubpathAndOptions();

		PathCreationCommand getPathPaintingCommandBasedOnOption(PathPaintingOptions pathPaintingOption) const;
		PathCreationCommand getClippingPathCommandBasedOnOption(ClippingPathOptions clippingPathOption) const;
		PathCreationCommand getCloseSubpathCommandBasedOnOption(bool closeSubpathOption) const;

		/* Member variables */

		std::unique_ptr<CreationalState> _state;
		std::vector<Path> _paths;
		Path* _currentPath;
		Subpath* _currentSubpath;

		/* Settings */
		PathPaintingOptions _pathPaintingOption;
		ClippingPathOptions _clippingPathOption;
		bool _closeSubpathOption;

	};
}

#endif // !PATHCREATIONSTATEMANAGER_H
