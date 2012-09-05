/**
 * @file Task.hpp
 *
 */

namespace sys {

template <typename T>
class Task : public Thread
{
public:
	Task();
	virtual ~Task();

	bool isDone() const;
	T getResult()
	{
		return _result;
	}

protected:
	void threadMain();

	virtual T taskMain() = 0;

private:
	T _result;
};

}

