#pragma once
namespace dae
{
	class Action abstract
	{
	public:
		virtual ~Action() = default;
		virtual void Execute() = 0;

		//Action(const Action& other) = delete;
		//Action(Action&& other) = delete;
		//Action& operator=(const Action& other) = delete;
		//Action& operator=(Action&& other) = delete;
	//protected:
		//Action() = default;
	};
}