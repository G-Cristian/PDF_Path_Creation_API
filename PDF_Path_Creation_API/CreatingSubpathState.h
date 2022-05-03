#ifndef CREATINGSUBPATHSTATE_H
#define CREATINGSUBPATHSTATE_H

#include "CreationalState.h"

#include <stdexcept>

namespace PDFPathCreationAPI {
	class PathCreationStateManager;

	class CreatingSubpathState:public CreationalState {
	public:
		CreatingSubpathState(PathCreationStateManager* stateManager) :
			CreationalState(stateManager) {
		}

		/* Path */
		virtual void beginPath() final override { throw std::logic_error("Cannot begin path while creating subpath."); }
		virtual void endPath() final override { throw std::logic_error("Cannot end path while creating subpath."); }

		/* Subpath */
		virtual void beginSubpath(int x, int y) final override { throw std::logic_error("Cannot begin subpath while creating subpath."); }
		virtual void endSubpath(bool closeSubpath) final override;
		virtual void beginCubicBezierCurve(int x, int y) final override;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="x"></param>
		/// <param name="y"></param>
		/// <returns>True if state must change.</returns>
		virtual bool appendCubicBezierCurvePoint(int x, int y) final override { throw std::logic_error("Cannot append bezier before begining one."); }
		virtual void appendStraightLinePoint(int x, int y) final override;

		virtual void beginRectangle(int x, int y) final override { throw std::logic_error("Cannot begin rectangle while creating a subpath."); }
		virtual void endRectangle() final override { throw std::logic_error("Cannot end rectangle before begining one rectangle."); }

		virtual void updateCurrentPoint(int x, int y) final override;
	private:
	};
}

#endif // !CREATINGSUBPATHSTATE_H
