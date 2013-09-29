#pragma once

#include "pm_td/Polygon.hpp"

#include <Time.hpp>
#include <NonCopyable.hpp>

#include <memory>

namespace polymorph { namespace pm_td {

class ModelAnimator : NonCopyable
{
public:
	ModelAnimator();

	template <typename AnimatorImpl>
	ModelAnimator(AnimatorImpl&& animatorImpl);

	ModelAnimator(ModelAnimator&& other);

	ModelAnimator& operator=(ModelAnimator && other);
	
	void attach(gr::Model<gr::Transform2>& model);
	void update(TimeDuration dt, gr::Model<gr::Transform2>& model);

private:

	struct AnimatorBase
	{
		virtual ~AnimatorBase() {};

		virtual void attach(gr::Model<gr::Transform2>& model) = 0;
		virtual void update(TimeDuration dt, gr::Model<gr::Transform2>& model) = 0;
	};

	template <typename AnimatorImpl>
	struct AnimatorDerived : ::NonCopyable, AnimatorBase
	{
		AnimatorDerived(AnimatorImpl&& animator);

		void attach(gr::Model<gr::Transform2>& model) override;
		void update(TimeDuration dt, gr::Model<gr::Transform2>& model) override;

		AnimatorImpl impl;
	};

	std::unique_ptr<AnimatorBase> _impl;
};

} }

#include "pm_td/ModelAnimator.inl"