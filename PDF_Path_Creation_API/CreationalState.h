#ifndef CREATIONALSTATE_H
#define CREATIONALSTATE_H

namespace PDFPathCreationAPI {
	class PathCreationStateManager;

	class CreationalState {
	public:
		CreationalState(PathCreationStateManager* stateManager):
			_stateManager(stateManager) {
		}

		/* Path */
		virtual void beginPath() = 0;
		virtual void endPath() = 0;

		/* Subpath */
		virtual void beginSubpath(int x, int y) = 0;
		virtual void endSubpath(bool closeSubpath) = 0;
		virtual void beginCubicBezierCurve(int x, int y) = 0;
		/// <summary>
		/// 
		/// </summary>
		/// <param name="x"></param>
		/// <param name="y"></param>
		/// <returns>True if state must change.</returns>
		virtual bool appendCubicBezierCurvePoint(int x, int y) = 0;
		virtual void appendStraightLinePoint(int x, int y) = 0;

		virtual void beginRectangle(int x, int y) = 0;
		virtual void endRectangle() = 0;
		
		virtual void updateCurrentPoint(int x, int y) = 0;

	protected:
		PathCreationStateManager* _stateManager;
	};
}

#endif // !CREATIONALSTATE_H
