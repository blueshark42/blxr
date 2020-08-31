**DISCLAIMER: The source code and tools provided in this repository are entirely for EDUCATIONAL PURPOSES ONLY and shall not be used in any illicit activity or intent. You are entirely responsible for the actions, damages etc. caused. The code and tools come with no warranty!**

# 👻 blxr
blxr is a Windows spyware capable of logging keystrokes, taking screenshots and then encrypting and logging them into hidden files and folders. The project is **WIP**.

## Info
### Folders Created
- SystemService
- BootSetup

### Files Created
- wnxshl2.sys
- boothandler.sys
- winpst(idx).png

### Hook Injection
**Hooking** is a technique used to intercept function calls. Malware can leverage hooking functionality to have their malicious DLL loaded upon an event getting triggered in a specific thread. This is usually done by calling **SetWindowsHookEx** to install a hook routine into the hook chain. The **SetWindowsHookEx** function takes four arguments. The first argument is the type of **event**. The events reflect the range of hook types, and vary from pressing keys on the keyboard (WH_KEYBOARD) to inputs to the mouse (WH_MOUSE), CBT, etc. The second argument is a **pointer to the function** the malware wants to invoke upon the event execution.The third argument is a **module** that contains the function. Thus, it is very common to see calls to **LoadLibrary** and GetProcAddress before calling **SetWindowsHookEx**. The last argument to this function is the thread with which the hook procedure is to be associated. If this value is set to zero all threads perform the action when the event is triggered. However, malware usually targets one thread for less noise, thus it is also possible to see calls **CreateToolhelp32Snapshot** and **Thread32Next** before **SetWindowsHookEx** to find and target a single thread. Once the DLL is injected, the malware executes its malicious code on behalf of the process that its threadId was passed to **SetWindowsHookEx** function. (more at elastic.co)
