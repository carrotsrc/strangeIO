#include "system/units/RuFlacLoad.h"
#include "system/units/RuAlsa.h"
#include "framework/threads/RackQueue.h"
#include <chrono>

void RackoonCycle() {
	RackoonIO::RackQueue pool(6);
	pool.init();

	RuFlacLoad f;
	RuAlsa a;
	f.setRackQueue(&pool);
	a.setRackQueue(&pool);

	f.setConnection("audio_out", "audio", &a);
	f.setConfig("filename", "/home/charlie/Brain in a Fish Tank.flac");
	do { 
	f.getJack("power")->rackFeed(RackoonIO::RackState::RACK_AC);
	pool.cycle();
	std::this_thread::sleep_for(std::chrono::microseconds(200));
	} while(1);
}
int main(void)
{
	std::thread t(RackoonCycle);
	int x;
	cin >> x;
}




