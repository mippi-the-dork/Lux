# Per-User Preferences and Session State — Design

**Lux v2.0.10 · User guide**

## Three different kinds of state

| State | Stored where | What happens on restart? |
| --- | --- | --- |
| Project default values and allowed ranges | Shared Project Settings | Continue as shared config |
| Your intensity, radius, color and advanced choices | Editor-per-project user preferences | Remembered in the same project |
| Headlamp enabled / disabled | Current editor session only | **Always starts off** |

Lux's actual point light is a **transient Editor component**, not a Light Actor or saved scene object. Saving a level doesn't bake in Lux's inspection light.

## Example

Turn on Lux and adjust intensity to suit a dim environment. Close Unreal normally. Reopen your project: **Lux is off**, but when you turn it on again it uses your saved intensity instead of necessarily reverting to the original project default.

<figure class="doc-media" data-kind="image" data-media-id="preferences-session">
<img src="../../../assets/media-placeholder.png" alt="Lux enabled-state reset and persistent user intensity comparison." loading="lazy">
<figcaption>Lux remembers personal light properties independently from the temporary on/off state.<span class="media-capture-instructions"><strong>Capture instructions · Image:</strong> Create a two-panel before-and-after Unreal Editor capture: the first shows Lux enabled with customized intensity; after restarting, show the icon gray and the dropdown still holding the customized intensity.</span></figcaption>
</figure>

## What changes across a team?

Shared project defaults can be checked into source control, while developer-specific values remain personal. When a project's minimum or maximum changes, Lux may clamp an existing personal Intensity/Radius to fit the new allowed range.

## Avoid two common assumptions

A setting that persists is **not** proof that the light is a level Actor. And changing shared project defaults does **not** automatically overwrite personal choices—use Reset to Project Defaults if you want to adopt the new values.

---

For configuration classes and native save behavior, [read Technical](TECHNICAL.md).
