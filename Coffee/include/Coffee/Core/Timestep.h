#pragma once

namespace Coffee {

	class Timestep {
	public:

		Timestep(float time = 0.0f);

		operator float() const;
		
		float getSeconds() const;
		float getMilliseconds() const;

	private:

		float _time;
		
	};
	
}