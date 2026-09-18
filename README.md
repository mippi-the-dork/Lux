# Lux

**Lux** is a lightweight C++ editor plugin for Unreal Engine that adds a toggleable headlamp to the editor viewport, making dark levels easier to navigate and inspect.

By integrating a custom User Interface widget directly into the level editor viewport, Lux allows you to adjust your lighting on the fly without ever losing focus on your scene. Stop dropping temporary point lights into your outliner or fighting auto-exposure—just toggle Lux and keep building.

---

## Features

* **Instant Illumination:** A dynamic, camera-attached light source that follows your viewport movement.
* **In-Viewport UI:** Adjust settings natively within the editor viewport overlay—no floating windows or hunting through obscure engine menus.
* **Real-Time Parameter Control:** Instantly tweak the light's **Intensity**, **Attenuation Radius**, and **Color** to suit the scale and mood of your environment.
* **Editor-Only Footprint:** Cleanly implemented via Editor Subsystems. Lux leaves zero footprint in your packaged game and does not bloat your world outliner.
* **Memory-Safe:** Carefully architected to prevent world memory leaks and widget duplication across level transitions or Play-In-Editor (PIE) sessions.

## Installation

### Via Fab (Marketplace)

1. Download **Lux - Editor Camera Light** from your Fab library.
2. Install it to your engine version.
3. Open your project and ensure the plugin is enabled via `Edit > Plugins > Installed > Editor`.

### Via GitHub (Source)

1. Close your Unreal Engine project.
2. Create a `Plugins` folder in the root of your project directory (if one doesn't already exist).
3. Clone this repository into the `Plugins` folder:
```bash
cd YourProject/Plugins
git clone https://github.com/mippi-the-dork/Lux.git

```


4. Right-click your `.uproject` file and select **Generate Visual Studio project files**.
5. Compile your project from your IDE (Visual Studio / Rider).
6. Open your project. The plugin will be enabled automatically.

## Quick Start

1. Open any level in the Unreal Engine Editor.
2. Locate the **Lux UI Widget** in the active viewport overlay.
3. Click the toggle switch to activate the camera light.
4. Expand the panel to customize the light properties (Intensity, Radius, Color) to your exact preference.

## Technical Details

* **Plugin Module:** `Lux` (Editor)
* **Architecture:** Built on `UEditorSubsystem` for safe, persistent editor-wide state management.
* **Platform Support:** Windows, macOS.
* **Codebase:** Fully C++, leveraging modern UE slate and widget integration techniques to bind UI elements securely to the active level editor viewport.

## Issues & Contributions

If you run into any widget compilation issues, discover a bug, or have a feature request, please [open an issue](https://www.google.com/search?q=https://github.com/mippi-the-dork/Lux/issues&utm_source=gemini) on GitHub. Pull requests are always welcome!