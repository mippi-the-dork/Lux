# 04. Workflows and Implementation

Lux is designed for ordinary level-editing work: brightening an unlit corridor, checking a material, confirming shadows, or comparing effects in a shared Editor world. This section explains the practical methods and the engine architecture behind them.

## Understand the fundamental limitation

There is **one transient movable point light** in the editor world, not one per viewport. Lux follows the most recently interacted **perspective** Level Editor camera, but its illumination may appear from another editor viewport looking at the same world.

## Choose by goal

| What you need | Suggested approach |
| --- | --- |
| Navigate a dark room | Turn on Lux; adjust Intensity and Attenuation Radius separately |
| Understand an odd shadow | Hold the camera fixed, compare Cast Shadows on/off |
| Inspect specular response | Try neutral Light Color and adjust Specular Scale/Source Radius |
| Inspect fog or translucency | Use Advanced Lighting in a compatible renderer setup |
| Switch between editor viewports | Interact with the perspective viewport you want Lux to track |
| Compare final authored lighting | Turn Lux off before evaluating the scene |

## Topics

| Topic | Explains | Design | Technical |
| --- | --- | --- | --- |
| **Viewport Following and Multi-Viewport Behavior** | Which perspective camera Lux follows and why other views may also show its light | [Design](viewports/DESIGN.md) | [Technical](viewports/TECHNICAL.md) |
| **Practical Lighting Inspection Workflows** | Dark interiors, material inspection, shadows, fog and level lighting comparison | [Design](inspection-workflows/DESIGN.md) | [Technical](inspection-workflows/TECHNICAL.md) |
| **Editor Architecture and Lifecycle** | Subsystem, transient component, toolbar and personal configuration ownership | [Design](architecture/DESIGN.md) | [Technical](architecture/TECHNICAL.md) |

**Next:** [Support and Troubleshooting](../05-support-and-troubleshooting/README.md) helps diagnose unusual toolbar, viewport, render and preference behavior.
