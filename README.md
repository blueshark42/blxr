**DISCLAIMER: The source code and tools provided in this repository are entirely for EDUCATIONAL PURPOSES ONLY and shall not be used in any illicit activity or intent. You are entirely responsible for the actions, damages etc. caused. The code and tools come with no warranty!**

# 👻 blxr
blxr is a Windows spyware capable of logging keystrokes and taking screenshots while sending them to an attacker's server. The project is WIP so here you can see what is done and what is WIP / planned:

## Abilities
### Spying
- [x] Keylogger
- [x] Screenscraper
- [ ] Communication with attacker

### Persistence
- [x] Startup Auto-Boot

### Defense Evasion
- [x] Anti-Malware Bypass
- [ ] Run as Windows Service
- [x] Encryption
- [x] Spoof extension
- [x] Check for Virtual Machine Environment
- [ ] Kill switch & Data Wipe

## What happens when I run the process?
- Checks if the client is running on a VM
- Creates and drops hidden folders and files such as (*SystemService, winpst.jpeg, wnxshl2.log*)
- Hooks itself to intercept low-level keyboard events
- Creates an encryption key, encrypts the logs file with the key
- Creates registry keys, sets registry values to start on boot
- In certain intevals / commands the process sends over the data to the attacker (WIP)
- Logs and spies on the user until terminated by a kill switch (WIP)
