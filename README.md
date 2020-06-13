**DISCLAIMER: The source code and tools provided in this repository are entirely for EDUCATIONAL PURPOSES ONLY and shall not be used in any illicit activity or intent. You are entirely responsible for the actions, damages etc. caused. The code and tools come with no warranty!**

# 👻 blxr
blxr is a Spyware capable of spying on a client computer. blxr can read and extract data from the client computer, log it and then send it over to a server or the attacker.
This project is still in active development. Under here you can see which items are done, and which ones are WIP.

## Abilities
### Spying
- [x] Keylogger
- [x] Screenscraper

### Persistence
- [x] Startup Auto-Boot

### Defense Evasion
- [x] Anti-Malware Bypass
- [ ] Run as Windows Service
- [x] Encryption
- [ ] Spoof extension
- [ ] Kill switch & Data Wipe

## What happens when I run the process?
- Creates and drops hidden folders and files such as (*SystemService, winpst.jpeg, wnxshl2.log*)
- Hooks itself to intercept low-level keyboard events
- Creates an encryption key, encrypts the logs file with the key
- In certain intevals / commands the process sends over the data to the attacker
- Logs and spies on the user until terminated by a kill switch
