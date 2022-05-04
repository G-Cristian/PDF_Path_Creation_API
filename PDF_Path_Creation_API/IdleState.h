#ifndef IDLESTATE_H
#define IDLESTATE_H

#include "CreationalState.h"

#include <stdexcept>

namespace PDFPathCreationAPI {
	class PathCreationStateManager;

	class IdleState : public CreationalState {
	public:
		IdleState(PathCreationStateManager* stateManager) :
			CreationalState(stateManager) {
		}

		virtual ~IdleState();

		/* Path */
		virtual void beginPath() final override;
		virtual void endPath() final override { throw std::logic_error("Cannot end path before begining one."); }

		/* Subpath */
		virtual void beginSubpath(int x, int y) final override { throw std::logic_error("Cannot begin subpath before begining one path."); }
		virtual void endSubpath(bool closeSubpath) final override { throw std::logic_error("Cannot end subpath before begining one."); }
		virtual void beginCubicBezierCurve(int x, int y) final override { throw std::logic_error("Cannot begin bezier before begining one subpath."); }

		/// <summary>
		/// 
		/// </summary>
		/// <param name="x"></param>
		/// <param name="y"></param>
		/// <returns>True if state must change.</returns>
		virtual bool appendCubicBezierCurvePoint(int x, int y) final override { throw std::logic_error("Cannot append bezier before begining one."); }
		virtual void appendStraightLinePoint(int x, int y) final override { throw std::logic_error("Cannot append line before begining one subpath."); }

		virtual void beginRectangle(int x, int y) final override { throw std::logic_error("Cannot create rectangle before begining one path."); }
		virtual void endRectangle() final override { throw std::logic_error("Cannot end rectangle before begining one rectangle."); }

		virtual void updateCurrentPoint(int x, int y) final override { throw std::logic_error("Cannot update current point before begining one subpath or renctangle."); }
	private:
	};
}

#endif // !IDLESTATE_H
