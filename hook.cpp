#include "pch.h"
#include "hook.h"

bool Detour32(BYTE* src, BYTE* dst, const uintptr_t len)
{
    if (len<5)
      return false;
    DWORD oldProperties;
    VirtualProtect(src, len, PAGE_EXECUTE_READWRITE, &oldProperties);
    uintptr_t relativeAddress = dst - src - 5;
    *src = 0xE9;
    *(uintptr_t*)(src + 1) = relativeAddress;
    VirtualProtect(src, len, oldProperties, &oldProperties);
}

BYTE* TrampHook32(BYTE* src, BYTE* dst, const uintptr_t len)
{
    if (len < 5)
        return nullptr;
    //·ÖÅäÄÚ´æ¡£
    BYTE* gateway = (BYTE*)VirtualAlloc(0, len, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    memcpy_s(gateway, len, src, len);
    uintptr_t gatewayRelativeAddr = src - gateway - 5;
    *(gateway + len) = 0xE9;
    *(uintptr_t*)((uintptr_t)gateway + len + 1) = gatewayRelativeAddr;
    Detour32(src, dst, len);
    return gateway;
}

Hook::Hook(BYTE* src, BYTE* dst, BYTE* PtrToGatewayFnPtr, uintptr_t len)
{
    this->src = src;
    this->dst = dst;
    this->len = len;
    this->PtrToGatewayFnPtr = PtrToGatewayFnPtr;
}

Hook::Hook(const char* exportName, const char* modName, BYTE* dst, BYTE* PtrToGatewayFnPtr, uintptr_t len)
{
    HMODULE hMod = GetModuleHandleA(modName);
    if(hMod)
       this->src = (BYTE*)GetProcAddress(hMod, exportName);
    this->dst = dst;
    this->len = len;
    this->PtrToGatewayFnPtr = PtrToGatewayFnPtr;
}

void Hook::Enable()
{
    memcpy(originalBytes, src, len);
    *(uintptr_t*)PtrToGatewayFnPtr = (uintptr_t)TrampHook32(src, dst, len);
}


void Hook::Disable()
{
    mem::Patch(src, originalBytes, len);
    bStatus = false;
}

void Hook::Toggle()
{
    if (!bStatus)
        Enable();
    else
        Disable();
}
