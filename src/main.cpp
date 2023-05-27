#include "memory.hpp"
#include "offsets.hpp"
#include <iostream>
#include <thread>

int main(int, char**) {
	const Memory csgo = Memory("csgo.exe");
	std::cout << "CS:GO found, finding clinet.dll" << std::endl;

	const std::uintptr_t client = csgo.getAddress("client.dll");
	if (client == 0) {
		std::cout << "client.dll not found!" << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(2));
		return 1;
	}
	std::cout << "client.dll found: 0x" << std::hex << client << std::endl;

	constexpr std::ptrdiff_t localplayer = hazedumper::signatures::dwLocalPlayer;
	constexpr std::ptrdiff_t flags = hazedumper::netvars::m_fFlags;
	constexpr std::ptrdiff_t forcejump = hazedumper::signatures::dwForceJump;

	while (true) {
		std::uintptr_t player = csgo.read(client + localplayer);
		std::uintptr_t playerflags = csgo.read(player + flags);

		if (!player) {
			continue;
		}
		if (GetAsyncKeyState(VK_SPACE)) {
			if (playerflags & (1 << 0)) {
				csgo.write(client + forcejump, 6);
				std::cout << "hop\n";
			} else {
				csgo.write(client + forcejump, 4);
			}
		}
	}
	return 0;
}