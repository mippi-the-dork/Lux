# 03. Settings and Preferences

Lux separates **project-wide limits and defaults**, **individual editor-user light properties**, and the **session-only enabled state**. This prevents an inspection light from becoming authored level content while still giving every developer convenient personal adjustments.

## Where to change settings

Open **Edit → Project Settings → Plugins → Lux** to define shared limits and reset values. The Lux dropdown also provides a direct **Lux Project Settings** command. For personal adjustments, use the normal Lux toolbar menu instead.

## Which values survive a restart?

Shared project config and personal property selections are retained according to their config storage. Lux's on/off state always starts off on editor launch. No point light is saved into the level.

## A typical team example

A lead sets a maximum Lux radius that fits the project scale. Each developer can still choose their own intensity and light color for inspection. If the allowed radius decreases, Lux constrains the saved personal radius accordingly. **Reset to Project Defaults** restores shared reset values without toggling Lux.

## Settings topics

| Topic | Explains | Design | Technical |
| --- | --- | --- | --- |
| **Project Defaults and Limits** | Shared minimums, maximums and reset values under Plugins → Lux | [Design](project-defaults/DESIGN.md) | [Technical](project-defaults/TECHNICAL.md) |
| **Per-User Preferences and Session State** | Which values persist, which reset, and why the level stays unchanged | [Design](user-preferences/DESIGN.md) | [Technical](user-preferences/TECHNICAL.md) |
| **Reset to Project Defaults** | Restore all headlamp values without changing the on/off state | [Design](reset/DESIGN.md) | [Technical](reset/TECHNICAL.md) |

**Next:** [Workflows and Implementation](../04-workflows-and-implementation/README.md) covers viewport tracking and troubleshooting unusual scene behavior.
