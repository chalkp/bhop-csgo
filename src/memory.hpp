#pragma once
#define WIN32_LEAN_AND_MEAN
#include <cstdint>
#include <string_view>
#include <Windows.h>
#include <TlHelp32.h>

class Memory {
private:
	std::uintptr_t processId = 0;
	void* handle = nullptr;

public:
	Memory(const std::string_view process) noexcept;
	~Memory();

	const std::uintptr_t getAddress(const std::string_view module) const noexcept;

	const std::uintptr_t read(const std::uintptr_t& address) const noexcept;
	void write(const std::uintptr_t& address, const std::uintptr_t value) const noexcept;
};