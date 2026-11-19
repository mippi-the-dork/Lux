# 05. Support and Troubleshooting

Lux's most common support questions concern **where its toolbar control appears**, **which viewport it follows**, **why an active light produces little illumination**, and **which values persist across editor sessions**. You can usually isolate these without altering level content.

## Diagnose the symptom

| Symptom | First check |
| --- | --- |
| Missing Lux icon | Plugin enabled and proper Level Editor viewport toolbar |
| Blue icon, dark scene | Valid perspective viewport, Intensity, Attenuation Radius, renderer/exposure |
| Wrong camera followed | Click in intended perspective Level Editor viewport |
| Temperature disabled | Enable Advanced → Temperature → Use Temperature |
| Cannot exceed number | Project's Intensity/Radius bounds or fixed advanced-property range |
| Settings changed on restart | Headlamp activation always resets off; property values use per-user config |
| Another viewport appears lit | One shared-world light rather than per-viewport isolation |

## Troubleshooting without changing the level

Create a disposable test level with simple geometry, neutral material and a perspective camera. Enable Lux with known nonzero intensity and radius. Once the basic effect works, reintroduce the project's exposure, fog, material and multi-viewport setup one factor at a time.

## Support topics

| Topic | Covers | Design | Technical |
| --- | --- | --- | --- |
| **Frequently Asked Questions** | Quick explanations of activation, persistence, viewport choice and renderer limitations | [Design](faq/DESIGN.md) | [Technical](faq/TECHNICAL.md) |
| **Troubleshooting** | Find a missing control, invisible light, wrong viewport or settings problem | [Design](troubleshooting/DESIGN.md) | [Technical](troubleshooting/TECHNICAL.md) |
| **Updating, Support and Compatibility** | Safe updates, reported compatibility and useful bug reports | [Design](updates/DESIGN.md) | [Technical](updates/TECHNICAL.md) |

**Source and support:** [Lux GitHub repository](https://github.com/mippi-the-dork/Lux) and [Issue tracker](https://github.com/mippi-the-dork/Lux/issues).
