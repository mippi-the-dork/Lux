# Viewport Following and Multi-Viewport Behavior — Design

**Lux v2.0.10 · User guide**

## Which viewport gets the headlamp?

Lux tracks the **most recently interacted perspective Level Editor viewport**. With multiple perspective views, click or navigate inside the view you want to inspect. Its camera position becomes the light's location.

<figure class="doc-media" data-kind="gif" data-media-id="viewport-switching">
<img src="../../../assets/media-placeholder.png" alt="Animation transferring Lux tracking between perspective editor viewports." loading="lazy">
<figcaption>A single Lux headlamp moves between perspective Level Editor cameras as the user changes the active editing viewport.<span class="media-capture-instructions"><strong>Capture instructions · GIF:</strong> Record a two-perspective-viewport Unreal layout with both viewports visible. Click and move camera A, then click and move camera B, showing which view is receiving the tracking light. Use a modest attenuation radius and an overlay label to make the current target unmistakable.</span></figcaption>
</figure>

## What orthographic views do

An **orthographic** viewport does not become a headlamp target. Interacting with an ortho view doesn't move the point light to its camera. Lux is intended for perspective Level Editor navigation, not top/front/side orthographic inspection.

**PIE and game cameras** are also excluded. Lux does not become a gameplay flashlight or follow the active player's camera.

## Why can another viewport still look illuminated?

Lux creates **one point light in the shared Editor world**. When two editor viewports look into the same world, the light can affect both views' scene rendering even if it's following only one camera. This is not a separate headlamp per viewport.

## After changing layouts or maps

Lux can fall back to an available perspective viewport when the prior tracked viewport is no longer valid. After a layout change, click in the perspective view you want to use. During map changes, the old transient component is destroyed and recreated for the new valid Editor world as appropriate, while the enabled state may remain true.

## If it follows the wrong camera

Click directly in the intended **perspective** Level Editor viewport, then move that camera. Do not use a game or asset editor viewport as the selection mechanism.

---

For source implementation details, [read Technical](TECHNICAL.md).
