# 02. Headlamp Controls

Lux is operated from the **native Level Editor viewport toolbar**. The icon enables/disables the headlamp; the independent arrow opens properties. All properties control **one temporary movable point light**, not existing lights in the level.

## Which control should I use?

| Goal | Where to look |
| --- | --- |
| Turn the headlamp on/off | Lux icon in the viewport toolbar |
| Make nearby surfaces brighter | Intensity |
| Reach farther or nearer | Attenuation Radius |
| Tint inspection light or disable shadows | Light Color and Cast Shadows |
| Inspect reflections, fog, indirect light and translucency | Advanced → Lighting |
| Make light warmer or cooler | Advanced → Temperature |

## Defaults and persistence

Intensity starts at 5,000 and Attenuation Radius at 1,000 cm. Color is white and Cast Shadows is on. The headlamp's **on/off** state resets off at editor launch; individual property adjustments persist for the editor user and are independent of that toggle. Project Settings control starting/reset values and intensity/radius limits.

## Controls by topic

| Topic | Explains | Design | Technical |
| --- | --- | --- | --- |
| **Toolbar and Headlamp Toggle** | Toolbar location, blue/gray state and the independent settings arrow | [Design](toolbar/DESIGN.md) | [Technical](toolbar/TECHNICAL.md) |
| **Everyday Light Controls** | Intensity, Attenuation Radius, Light Color and Cast Shadows | [Design](everyday/DESIGN.md) | [Technical](everyday/TECHNICAL.md) |
| **Advanced Lighting Controls** | Source Radius, volumetrics, indirect lighting, specular and translucency | [Design](advanced-lighting/DESIGN.md) | [Technical](advanced-lighting/TECHNICAL.md) |
| **Color Temperature** | Use Temperature and Kelvin controls working together with Light Color | [Design](temperature/DESIGN.md) | [Technical](temperature/TECHNICAL.md) |

**Next:** [Settings and Preferences](../03-settings-and-preferences/README.md) covers shared project defaults, user values, and Reset.
