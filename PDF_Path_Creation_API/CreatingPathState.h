#ifndef CREATINGPATHSTATE_H
#define CREATINGPATHSTATE_H

#include "CreationalState.h"

#include <stdexcept>

namespace PDFPathCreationAPI {
	class PathCreationStateManager;

	class CreatingPathState : public CreationalState {
	public:
		CreatingPathState(PathCreationStateManager* stateManager) :
			CreationalState(stateManager) {
		}

		/* Path */
		virtual void beginPath() final override { throw std::logic_error("Cannot begin path before ending current one."); }
		virtual void endPath() final override;

		/* Subpath */
		virtual void beginSubpath(int x, int y) final override;
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

		virtual void beginRectangle(int x, int y) final override;
		virtual void endRectangle() final override { throw std::logic_error("Cannot end rectangle before begining one rectangle."); }

		virtual void updateCurrentPoint(int x, int y) final override { throw std::logic_error("Cannot update current point before begining one subpath or renctangle."); }
	private:
	};
}

#endif // !CREATINGPATHSTATE_H
