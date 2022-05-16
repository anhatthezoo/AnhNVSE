#pragma once

#define IS_TYPE(form, type) (*(UInt32*)form == kVtbl_##type)
#define GameHeapAlloc(size) ThisStdCall<void*>(0xAA3E40, (void*)0x11F6238, size)

template <typename T_Ret = void, typename ...Args>
__forceinline T_Ret ThisCall(UInt32 _addr, void* _this, Args ...args)
{
	return ((T_Ret(__thiscall*)(void*, Args...))_addr)(_this, std::forward<Args>(args)...);
}

#define GameHeapFree(ptr) ThisCall<void, void*>(0xAA4060, (void*)0x11F6238, ptr)

