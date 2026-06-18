# Project MAGI: Embedded Linux Telemetry Daemon

## Architecture Overview
* **Core Engine:** Pure C headless daemon
* **Data Ingestion:** Direct parsing of Linux kernel `sysfs` and `procfs` nodes.
* **Data Processing:** Ring buffers, state-free math, dead-reckoning calibration.
* **IPC Protocol:** Standard output stream (JSON formatted) to a Wayland display server.
* **UI Layer:** Waybar (for the digital HUD) and Eww (for waveform/geometric rendering).

---

## Phase 1: The Battery Core (Completed)
*Goal: Establish the base C engine and raw UNIX system calls.*
* [x] Read raw hardware data from `/sys/class/power_supply/`.
* [x] Implement a circular buffer for a state-safe 10-second rolling average.
* [x] Build a "gatekeeper" calibration phase to prevent bad data reporting.
* [x] Convert raw microwatts into a stable `HH:MM:SS` format using pure integer math.
* [ ] Output state-dependent JSON formatting (`normal`, `warning`, `critical`).

## Phase 2: The UI Pipeline (Immediate Next Steps)
*Goal: Prove the Inter-Process Communication (IPC) by getting data on the screen.*
* [ ] Register the compiled C binary as a `custom` module in the `waybar` configuration file.
* [ ] Verify the C daemon wakes, prints JSON, and sleeps without causing the UI to hang.
* [ ] Download and install an Evangelion-accurate 7-segment font (e.g., `DSEG7`).
* [ ] Write GTK CSS in Waybar to map the JSON `class` outputs to the MAGI color palette (Neon Green, Alert Orange, Emergency Red).
* [ ] Implement CSS keyframe animations (e.g., blinking effect on critical battery).

## Phase 3: The Psychograph (CPU Telemetry & Harmonics)
*Goal: Map multi-core system load to Fourier waveform distortion.*
* [ ] **C Engine:** Parse `/proc/stat` to calculate actual CPU utilization per core (requires reading delta values over a sleep interval).
* [ ] **EE Math Logic:** Map the total package CPU load to the fundamental frequency/amplitude of a sine wave. Map individual core loads to the odd harmonic coefficients.
* [ ] **JSON Output:** Export the harmonic coefficients as a structured array.
* [ ] **UI Layer:** Use Eww to consume the JSON and render the dynamic wave (smooth sine for idle, jagged square-like distortion for heavy load).

## Phase 4: Phase-Locked Radio (WiFi/Bluetooth Double Helix)
*Goal: Visualize RF signal strength as a Phase-Locked Loop (PLL).*
* [ ] **C Engine:** Query `/proc/net/wireless` (or use `nl80211` sockets) to extract raw RSSI (dBm) and packet loss data.
* [ ] **EE Math Logic:** Map the RSSI dBm value to a phase shift variable. 
    * *High Signal:* Zero shift (perfect overlap).
    * *Low Signal/Packet Loss:* High phase shift (visibly decoupled helix).
* [ ] **JSON Output:** Export the calculated phase shift and frequency values.
* [ ] **UI Layer:** Render the two intertwined sine waves, applying the phase shift to visualize the connection stability dynamically.

## Phase 5: RAM Capacity & The AT-Field
*Goal: Memory tracking mapped to geometric UI elements.*
* [ ] **C Engine:** Parse `/proc/meminfo` to extract `MemTotal` and `MemAvailable`.
* [ ] **Math Logic:** Calculate the pure percentage of memory used without floating-point math.
* [ ] **UI Layer:** Map the percentage to the opacity, thickness, or layer count of an AT-Field hexagonal grid overlay.
