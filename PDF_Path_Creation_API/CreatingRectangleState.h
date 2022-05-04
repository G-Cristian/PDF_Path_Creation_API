#ifndef CREATINGRECTANGLESTATE_H
#define CREATINGRECTANGLESTATE_H

#include "CreationalState.h"

#include <stdexcept>

namespace PDFPathCreationAPI {
	class PathCreationStateManager;

	class CreatingRectangleState :public CreationalState {
	public:
		CreatingRectangleState(PathCreationStateManager* stateManager) :
			CreationalState(stateManager) {
		}

		virtual ~CreatingRectangleState();

		/* Path */
		virtual void beginPath() final override { throw std::logic_error("Cannot begin path before ending current one."); }
		virtual void endPath() final override { throw std::logic_error("Cannot end path while creating rectangle."); }

		/* Subpath */
		virtual void beginSubpath(int x, int y) final override { throw std::logic_error("Cannot begin subpath while creating rectangle."); }
		virtual void endSubpath(bool closeSubpath) final override { throw std::logic_error("Cannot end subpath while creating rectangle."); }
		virtual void beginCubicBezierCurve(int x, int y) final override { throw std::logic_error("Cannot begin bezier before begining one subpath."); }

		/// <summary>
		/// 
		/// </summary>
		/// <param name="x"></param>
		/// <param name="y"></param>
		/// <returns>True if state must change.</returns>
		virtual bool appendCubicBezierCurvePoint(int x, int y) final override { throw std::logic_error("Cannot append bezier before begining one."); }
		virtual void appendStraightLinePoint(int x, int y) final override { throw std::logic_error("Cannot append line before begining one subpath."); }

		virtual void beginRectangle(int x, int y) final override { throw std::logic_error("Cannot begin rectangle while creating another rectangle."); }
		virtual void endRectangle() final override;

		virtual void updateCurrentPoint(int x, int y) final override;
	private:
	};
}

#endif // !CREATINGRECTANGLESTATE_H
