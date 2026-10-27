# Lux 2.0.7

Lux is a lightweight, native Unreal Engine 5.8 Level Editor headlamp. It temporarily illuminates dark areas without creating an actor or changing level content.

## Supported environment

- Unreal Engine 5.8.x, Windows 64-bit, Editor only
- Native C++ Slate controls, no Editor Utility Widgets or UMG assets
- Source distribution; compile in a matching UE 5.8 installation

## Viewport toolbar

Lux appears at the **left edge of the right-anchored** Level Editor viewport control group. It is independent of other viewport plugins, including Link and Metric.

- Click the Lux SVG icon to toggle the headlamp. Grey is off, Unreal's Accent Blue is on.
- Click the adjacent arrow for the native viewport settings menu.
- The single transient point light follows the most recently interacted **perspective Level Editor viewport**. Orthographic, PIE and game viewports do not take ownership of the headlamp.
- Other editor viewports may also see the light because the Editor world is shared. Lux does not provide per-viewport rendering isolation.

## Headlamp menu

The main menu deliberately holds just four common adjustments:

| Property | Function |
| --- | --- |
| Intensity | Scrubbable numeric value; minimum and maximum set in Project Settings |
| Attenuation Radius | Scrubbable radius in centimeters; minimum and maximum set in Project Settings |
| Light Color | Opens Unreal's native color picker |
| Cast Shadows | Toggles dynamic shadows on the movable point light |

**Advanced** is a native hover/click submenu containing the less frequently adjusted properties:

| Property | Function | Default |
| --- | --- | --- |
| Source Radius | Radius of the apparent light source in cm | 0 cm |
| Volumetric Scattering Intensity | Amount of light contributed to supported volumetric fog | 0 |
| Indirect Lighting Intensity | Multiplier for indirect contribution where supported | 1 |
| Specular Scale | Strength of specular contribution (0–1) | 1 |
| Affect Translucent Lighting | Whether Lux contributes to supported translucent material lighting | Enabled |
| Use Temperature | Enables physically inspired temperature tint, combined with Light Color | Disabled |
| Temperature | Color temperature in Kelvin, editable only with Use Temperature enabled | 6500 K |

The submenu uses native **Lighting** and **Temperature** sections without a redundant additional "Advanced" heading. Values update immediately; no Apply button is required. The **Reset to Project Defaults** and **Lux Project Settings** actions remain in the main menu.

A light's indirect and translucent contributions may differ by renderer, project settings, scene content, and shading path. Some lighting methods may not produce an obvious visual difference.

## Project Settings

Go to **Edit > Project Settings > Plugins > Lux**, or use **Lux Project Settings** in the menu. The command selects the Lux section directly.

Project-wide configuration contains:

- Intensity: minimum, maximum, default.
- Attenuation Radius: minimum, maximum, default (cm).
- Light Defaults: color and cast-shadows state.
- Advanced Defaults: source radius, volumetric scattering intensity, indirect lighting intensity, specular scale, affect translucent lighting, use temperature, and temperature.

The project settings provide bounds for Intensity and Radius. Reset restores **all** properties to the project defaults.

### User preferences

Every user can adjust Lux without changing the project's shared default values. Preferences use `EditorPerProjectUserSettings`, are saved in batches to avoid disk writes during each scrub, and survive editor restarts. The **enabled state deliberately resets to Off** when the editor opens.

Upgrading from 2.0.6 preserves prior user preferences. The newly added indirect and translucent properties are initialized once from the project's settings.

## Installation

1. Close Unreal Editor.
2. Replace the entire `<Project>/Plugins/Lux` directory with this release's `Lux` directory. Do not merge with the old Blueprint-based Lux.
3. Regenerate project files if needed and build the Editor target for UE 5.8.
4. Enable Lux in the Plugin Browser if it isn't already enabled.
5. Refer to `Doc/TESTING.md` for functional and UX validation.

## Limitations

- The headlamp is a transient movable point light in the Editor world; it isn't saved to levels or included in cooked builds.
- It follows the last interacted perspective viewport rather than providing independent lights in every viewport.
- Its source is at the camera location, not a separate beam or spotlight.
- Shadow casting may be expensive, especially at large attenuation radii.
- Results for volumetric, indirect and translucent settings depend on the project renderer and content.

## Source files

- `Lux.cpp`: native toolbar registration at the start of the right-aligned group.
- `SLuxViewportControl.cpp`: Slate icon, native menus and controls.
- `LuxViewportTracker.cpp`: interaction-based active viewport detection.
- `LuxEditorSubsystem.cpp`: transient point-light lifetime, settings, and persistence.
- `LuxProjectSettings.cpp`: project settings validation.
- `LuxUserSettings.h`: per-user persisted values.
- `LuxStyle.cpp`: Unreal vector-image icon style.

Copyright Mippithedork 2026, Inc. All Rights Reserved.
