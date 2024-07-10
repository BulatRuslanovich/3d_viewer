#ifndef INC_3D_VIEWER_SET_CENTER_H
#define INC_3D_VIEWER_SET_CENTER_H

#include "model_data.h"

namespace s21 {

///@brief Main interface implemented by the "Chain of Responsibility" pattern
	class Event {
	public:
		Event() = default;

		virtual ~Event() = default;

		enum class Command {
			findMinMax, findMax, findCentre
		};

		struct MinMax {
			MinMax() : x(0), y(0), z(0) {}

			double x, y, z;
		};

		/// Passes responsibilities to the next in the chain
		virtual Event *setNextEvent(Event *event) = 0;

		/// Receives command for execution
		virtual void execute(s21::ModelData *data, Command command) = 0;

		double scaleForCentre = 0.0;
		MinMax centre = MinMax();
		MinMax min = MinMax();
		MinMax max = MinMax();
	};

	class AbstractEvent : public Event {
	public:
		AbstractEvent() = default;

		Event *setNextEvent(Event *event) override;

	private:
		Event *nextEvent = nullptr;
	};

	class FindMinMax : public AbstractEvent {
	public:
		void execute(s21::ModelData *data, Command command) override;

		void initMinMax(const s21::ModelData::Coordinate &vertex);

		void update(Event *e);
	};

	class FindMax : public AbstractEvent {
	public:
		void execute(s21::ModelData *data, Command command) override;

		void update(Event *e);
	};

	class FindCentre : public AbstractEvent {
	public:
		void execute(s21::ModelData *data, Command command) override;

		void update(Event *e);
	};

} // s21

#endif //INC_3D_VIEWER_SET_CENTER_H
