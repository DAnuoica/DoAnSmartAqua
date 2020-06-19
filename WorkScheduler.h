#ifndef __DAIHUYNH_WORK_SCHEDULER__
#define __DAIHUYNH_WORK_SCHEDULER__
#include <inttypes.h>
class WorkScheduler
{
private:
	unsigned long _ellapsedTime;
	unsigned long _workTime;
	int _workPin;
	void (*func)(int);
	void (*func2)();
public:
	WorkScheduler(int workPin, unsigned long times, void (*func)(int));
	WorkScheduler(unsigned long times, void (*func)());

	~WorkScheduler();

	void update();
};
#endif
