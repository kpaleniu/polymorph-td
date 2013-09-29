#include "pm_td/ModelAnimator.hpp"

namespace polymorph { namespace pm_td {

inline ModelAnimator::ModelAnimator()
:	_impl(nullptr)
{
}

template <typename AnimatorImpl>
ModelAnimator::ModelAnimator(AnimatorImpl&& animatorImpl)
:	_impl(std::unique_ptr<AnimatorBase>(new AnimatorDerived<AnimatorImpl>(std::move(animatorImpl))))
{
}

inline ModelAnimator::ModelAnimator(ModelAnimator&& other)
:	_impl(std::move(other._impl))
{
}

inline ModelAnimator& ModelAnimator::operator=(ModelAnimator&& other)
{
	_impl = std::move(other._impl);

	return *this;
}

inline void ModelAnimator::attach(gr::Model<gr::Transform2>& model)
{
	_impl->attach(model);
}

inline void ModelAnimator::update(TimeDuration dt, gr::Model<gr::Transform2>& model)
{
	_impl->update(dt, model);
}


template <typename AnimatorImpl>
ModelAnimator::AnimatorDerived<AnimatorImpl>::AnimatorDerived(AnimatorImpl&& animator)
:	impl(std::move(animator))
{
}

template <typename AnimatorImpl>
void ModelAnimator::AnimatorDerived<AnimatorImpl>::attach(gr::Model<gr::Transform2>& model)
{
	impl.attach(model);
}

template <typename AnimatorImpl>
void ModelAnimator::AnimatorDerived<AnimatorImpl>::update(TimeDuration dt,
														  gr::Model<gr::Transform2>& model)
{
	impl.update(dt, model);
}

} }