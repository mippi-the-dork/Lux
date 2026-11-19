# Toolbar and Headlamp Toggle — Design

**Lux v2.0.10 · User guide**

## Find the Lux control

Lux is the **first item in the right-anchored group** of Level Editor viewport toolbar controls. Its icon and neighboring arrow are two distinct click targets.

| Click | Result |
| --- | --- |
| **Lux icon** | Toggles the editor headlamp on/off; Accent Blue indicates active, gray indicates inactive |
| **Dropdown arrow** | Opens the native Lux settings menu without changing on/off state |
| **Hover** | Shows a native tooltip explaining the targeted button |

<figure class="doc-media" data-kind="image" data-media-id="toolbar-button">
<img src="../../../assets/media-placeholder.png" alt="Lux toolbar icon and separate settings dropdown arrow." loading="lazy">
<figcaption>The Lux icon and settings arrow occupy a compact native viewport toolbar control.<span class="media-capture-instructions"><strong>Capture instructions · Image:</strong> Capture a perspective Level Editor viewport toolbar including the Lux icon and adjacent menu arrow, with enough surrounding controls to establish its position. Show the icon in its active Accent Blue state.</span></figcaption>
</figure>

## Toggle without affecting authored lighting

Open a dark level and click Lux's icon. The light appears at your perspective camera, illuminating nearby surfaces. Move the camera and Lux follows. Click again to disable it and assess the level's authored lighting without the temporary inspection light.

## Expected behavior after restart

Lux always starts **off** on a new Editor session. Your last intensity, radius, color, shadows and advanced light settings are stored separately and reused on next activation.

## Typical mistakes

Clicking the arrow doesn't toggle Lux; it opens the property menu. The icon may be active while illumination is hard to see due to exposure, small radius, near-zero intensity, a non-perspective viewport or rendering conditions.

---

For specific Unreal properties and implementation paths, [read Technical](TECHNICAL.md).
