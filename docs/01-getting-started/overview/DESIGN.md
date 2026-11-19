# What Lux Does — Design

**Lux v2.0.10 · Unreal Engine 5.8.x · Win64 · Editor-only**

Lux gives your Unreal Engine **Level Editor viewport a temporary headlamp**, making dark rooms easier to navigate and surfaces easier to inspect without placing or modifying scene lights.

## What problem does it solve?

When a level has little authored illumination, moving through it can be difficult. Adjusting its placed lights just to see the geometry risks altering the lighting you are actually building. Lux offers an independent inspection light that moves with your working perspective camera.

<figure class="doc-media" data-kind="image" data-media-id="overview-headlamp">
<img src="../../../assets/media-placeholder.png" alt="Lux enabled in a dark Level Editor interior." loading="lazy">
<figcaption>Lux illuminates nearby scene geometry for inspection while leaving placed level lighting alone.<span class="media-capture-instructions"><strong>Capture instructions · Image:</strong> Capture a dark interior in a perspective Level Editor viewport with Lux active. Show the Lux toolbar button and enough nearby geometry to reveal the headlamp's effect. Do not use a PIE or game camera.</span></figcaption>
</figure>

## What can it do?

- **Turn on instantly:** The Lux toolbar icon toggles the headlamp; gray means inactive and Accent Blue means active.
- **Follow your camera:** Navigate a perspective Level Editor viewport and the headlamp follows its position.
- **Adjust the light:** Set brightness, influence radius, color, shadows and advanced point-light settings from a native Slate dropdown.
- **Keep your scene intact:** Lux does not create an Outliner Light Actor or alter a placed light, and is absent from packaged gameplay.

## What Lux is not

Lux is **not** a gameplay flashlight, directional spotlight, per-viewport independent lighting pass or baked-lighting replacement. It uses one **omnidirectional point light** in the shared Editor world. As a result, that light can also illuminate content visible in another lit editor viewport.

## Where to start

[Install Lux](../install/DESIGN.md), then follow [First Use](../first-use/DESIGN.md). For fine adjustments, open the [Headlamp Controls](../../02-headlamp-controls/README.md) section.

---

For native implementation and constraints, [read Technical](TECHNICAL.md).
