# Lux 2.0.5

Lux is a lightweight, Editor-only Unreal Engine viewport headlamp. It makes dark levels easier to inspect without placing lights in your map or modifying your level assets.

## Requirements

- Unreal Engine 5.8.x (built against the 5.8 editor API; validation required in your local 5.8.3 project)
- Windows 64-bit
- Editor only

## Viewport Toolbar

Lux adds a sun-shaped icon with a small native dropdown at the **left edge of the right-aligned viewport toolbar group**, before the other right-side controls. It does not depend on the Link plugin.

- **Click the icon** to toggle the headlamp. Unreal's normal foreground tint indicates off; Accent Blue indicates on. A native simple button supplies hover and pressed feedback without a blue checked background.
- **Click the dropdown arrow** to edit the light properties.
- **Point light follows the most recently interacted perspective Level Editor viewport.** Clicking or interacting with a different viewport transfers the light to that viewport's camera. Orthographic cameras do not move the light.
- Lux uses one global light, not one per viewport. Other viewports may also see its contribution because editor viewports share the editor world.

Lux uses a native editor menu with Headlamp and Additional Properties sections, plus a collapsible Advanced group. Property fields follow Unreal's Details-style alignment. Standard menu actions sit below the property controls. The menu provides these controls:

| Property | Behavior |
|---|---|
| Intensity | Numeric scrub control, constrained by project Min/Max |
| Attenuation Radius | Numeric scrub with a centimeters unit label, constrained by project Min/Max |
| Light Color | Opens Unreal Engine's built-in color picker |
| Cast Shadows | Toggles dynamic point-light shadows |
| Source Radius | Light source radius in centimeters |
| Volumetric Scattering Intensity | Amount of volumetric lighting |
| Use Temperature | Advanced toggle for blackbody temperature |
| Temperature | Advanced Kelvin value, enabled only when temperature is in use |
| Specular Scale | Advanced value from 0 to 1 |
| Reset to Project Defaults | Restores all light parameters to the project's configured defaults |
| Lux Project Settings | Opens Project Settings directly to Plugins > Lux using Lux's registered section identifier |

There is no Apply button: settings update the light immediately.

## Project Settings

Go to **Edit > Project Settings > Plugins > Lux**, or choose **Lux Project Settings** from the viewport dropdown. Both target the same native settings section.

Project Settings define the project-wide minimum, maximum, and default values for **Intensity** and **Attenuation Radius**. They also define default Light Color, Cast Shadows, Source Radius, Volumetric Scattering, Use Temperature, Temperature, and Specular Scale.

Project defaults are stored using Unreal's standard editor configuration system. Changes to the intensity and radius limits clamp current user values if necessary. The Reset command uses the current project defaults.

### User preferences

Lux remembers the most recently used light properties in each user's editor-per-project settings and batches disk writes to avoid saving every numerical scrub step. **The enabled/disabled state is session-only**, so Lux begins off each time you open the editor. Each user's properties are independent from the project's default values.

## Installation

1. Close Unreal Editor.
2. Remove the existing `Plugins/Lux` directory, including the old Lux Blueprint Content folder. Do not merge v2's files into a v1 installation.
3. Copy the `Lux` directory from the release ZIP to `<YourProject>/Plugins/Lux`.
4. Regenerate project files when required by your source-plugin workflow, then build and launch the Unreal Editor.
5. Enable Lux under **Edit > Plugins** if it is not enabled already.

This version is source-only with a Slate-based toolbar. It does not contain or require Editor Utility Widgets, UMG, or Blueprint assets.

## Behavior & Limitations

- Lux uses a transient movable point-light component in the Editor world. It is not saved into the level, is not an actor, and does not operate in cooked builds.
- The light remains enabled across editor-world/map replacement, but the old light is destroyed before world cleanup and recreated in the new Editor world.
- The light does not follow PIE/Game viewports. On returning to the editor, it resumes tracking the Level Editor's active perspective viewport.
- Selecting an orthographic viewport holds the last perspective lighting position until a perspective viewport is selected again.
- Because the light belongs to the shared Editor world, multiple simultaneously displayed viewports may see its contribution. True per-viewport render isolation is not provided.
- Lighting impact depends on renderer, project lighting configuration, and viewport show flags. Shadow casting can be comparatively expensive.

## Source layout

- `Lux.cpp`: native Level Editor toolbar registration at the leading edge of the right-aligned toolbar section and input processor lifecycle.
- `SLuxViewportControl.cpp`: native Slate icon toggle and property flyout.
- `LuxViewportTracker.cpp`: interaction-based camera selection adapted from the approach used in Metric.
- `LuxEditorSubsystem.cpp`: transient headlamp management and live settings.
- `LuxProjectSettings.cpp`: native project-level settings, defaults and limits.
- `LuxUserSettings.h`: per-user persisted light properties.
- `LuxStyle.cpp`: SVG vector brush registered in Unreal's Slate style registry.

Copyright Mippithedork 2026, Inc. All Rights Reserved.

## Toolbar placement correction in 2.0.5

- Places Lux at the **start** of the native `Right` section using `EToolMenuInsertType::First`. The entire group stays right-aligned, with Lux on its leftmost edge.
- Does not anchor to Camera or Link. Its position is independent of either plugin registration order or an entry name.
- Corrects the 2.0.4 regression that placed Lux in the native left-side viewport controls.
- Preserves the 2.0.3 icon colors, light settings menu, project settings, and viewport-follow behavior without changes.

## UI polish in 2.0.3

- Positions Lux immediately before Link's registered `LinkViewportControls` toolbar entry when Link is enabled. Without Link, the anchor remains Unreal's native `Camera` entry. The plugins do not depend on each other's modules.
- Switches the icon toggle to Unreal's `SimpleButton` style so the icon alone conveys state: standard gray when off, Accent Blue when on. Retains native hover, focus and keyboard interaction.
- Widens the property rows slightly to fit the full `Volumetric Scattering Intensity` label without truncation.
- Matches the Light Color swatch width to the value column and adds a native separator before the bottom commands.
- Preserves the native full-range spinbox appearance of Specular Scale. At its maximum of 1.0, Unreal fills the slider track; this matches the corresponding generated Project Settings property control.
- Verified the original Project Settings already declare `Units="cm"` for all three attenuation-radius properties. No unnecessary metadata change.

## UI polish in 2.0.2

- Replaces the dimmed inactive icon with normal editor foreground tint; the enabled icon remains the native Accent Blue.
- Uses Unreal's built-in toggle-button checked and hover appearances and a compact combo arrow.
- Uses `FMenuBuilder` section headings, separators and menu actions instead of a custom form header and two full-width buttons.
- Aligns numeric fields, the color swatch and both boolean properties on the value column.
- Displays centimeters and Kelvin alongside the applicable numeric controls and removes forced trailing `.0` for whole values.
- Corrects Project Settings navigation by registering the actual settings section as `Project / Plugins / Lux`, not the default `LuxProjectSettings` identifier.
- Preserves all lighting behavior and the per-user preferences from 2.0.1.
