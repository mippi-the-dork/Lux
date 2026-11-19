# 01. Getting Started

Lux places a temporary **editor headlamp** next to Unreal's native viewport controls. You can illuminate a dark level for inspection without placing a light, changing the level's authored lights, or shipping an additional gameplay component.

## What happens when you enable Lux?

Click the toolbar icon: Lux creates one movable, transient point light in the shared Editor world and positions it at the active perspective Level Editor camera. Camera movement updates the light position; the light's orientation is irrelevant because it shines in all directions.

## Start using it

1. [Install Lux](install/DESIGN.md) for UE 5.8.x/Win64.
2. [Turn on Lux](first-use/DESIGN.md) from a perspective viewport.
3. Use the separate settings arrow to adjust reach, brightness and light color.
4. Turn it off to judge authored lighting again.

## Key distinctions

Lux's on/off state is **per Editor session** and begins disabled on startup; light property values are **per editor user**; project-wide bounds and reset defaults live under Project Settings. It creates no saved Light Actor.

## Getting Started topics

| Topic | Covers | Design | Technical |
| --- | --- | --- | --- |
| **What Lux Does** | Purpose, benefits, editor-only behavior and what the headlamp does not change | [Design](overview/DESIGN.md) | [Technical](overview/TECHNICAL.md) |
| **Installation and Compatibility** | Fab, GitHub releases and source installation for Unreal Engine 5.8 on Windows | [Design](install/DESIGN.md) | [Technical](install/TECHNICAL.md) |
| **First Use** | Turn on the headlamp, adjust the dropdown and return to authored lighting | [Design](first-use/DESIGN.md) | [Technical](first-use/TECHNICAL.md) |

**Next:** [Headlamp Controls](../02-headlamp-controls/README.md) explains every property in the toolbar menus.
