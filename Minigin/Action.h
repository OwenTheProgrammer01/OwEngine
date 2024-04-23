#pragma once
namespace dae
{
	class Action abstract
	{
	public:
		virtual ~Action() = default;
		virtual void Execute() = 0;
	};
}