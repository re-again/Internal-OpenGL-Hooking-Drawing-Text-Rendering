#include "pch.h"
#include "mem.h"

void mem::Patch(BYTE* dst, BYTE* src, unsigned int size)
{
	//±£¥Êæ… Ù–‘
	DWORD oldProperties;
	VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldProperties);
	memcpy(dst, src, size);
	VirtualProtect(dst, size, oldProperties, &oldProperties);
}

void mem::Nop(BYTE* dst, unsigned int size)
{
	DWORD oldProperties;
	VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldProperties);
	memset(dst, 0x90, size);
	VirtualProtect(dst, size, oldProperties, &oldProperties);
}

uintptr_t mem::FindDMAAddy(uintptr_t ptr, std::vector<unsigned int> offsets)
{
	uintptr_t addr = ptr;
	for (unsigned int i = 0; i < offsets.size(); ++i)
	{
		addr = *(uintptr_t*)addr;
		addr += offsets[i];
	}
	return addr;
}