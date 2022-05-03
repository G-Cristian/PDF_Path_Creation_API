#ifndef CREATINGBEZIERCURVE_H
#define CREATINGBEZIERCURVE_H


#include "CreationalState.h"

#include <stdexcept>

namespace PDFPathCreationAPI {
	class PathCreationStateManager;

	class CreatingBezierCurve :public CreationalState {
		enum class InnerState { FIRST_POINT = 0, SECOND_POINT = 1, THIRD_POINT = 2 };
	public:
		CreatingBezierCurve(PathCreationStateManager* stateManager) :
			CreationalState(stateManager),
		    _innerState(InnerState::FIRST_POINT){
		}

		/* Path */
		virtual void beginPath() final override { throw std::logic_error("Cannot begin path while creating bezier."); }
		virtual void endPath() final override { throw std::logic_error("Cannot end path while creating bezier."); }

		/* Subpath */
		virtual void beginSubpath(int x, int y) final override { throw std::logic_error("Cannot begin subpath while creating bezier."); }
		virtual void endSubpath(bool closeSubpath) final override { throw std::logic_error("Cannot end subpath while creating bezier."); }
		virtual void beginCubicBezierCurve(int x, int y) final override { throw std::logic_error("Cannot begin bezier while creating bezier."); }

		/// <summary>
		/// 
		/// </summary>
		/// <param name="x"></param>
		/// <param name="y"></param>
		/// <returns>True if state must change.</returns>
		virtual bool appendCubicBezierCurvePoint(int x, int y) final override;
		virtual void appendStraightLinePoint(int x, int y) final override { throw std::logic_error("Cannot append line while creating bezier."); }

		virtual void beginRectangle(int x, int y) final override { throw std::logic_error("Cannot begin rectangle while creating a bezier."); }
		virtual void endRectangle() final override { throw std::logic_error("Cannot end rectangle before begining one rectangle."); }

		virtual void updateCurrentPoint(int x, int y) final override;
	private:
		InnerState _innerState;
	};
}

#endif // !CREATINGBEZIERCURVE_H
