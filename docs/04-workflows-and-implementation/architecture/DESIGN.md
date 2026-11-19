# Editor Architecture and Lifecycle — Design

**Lux v2.0.10 · User guide**

## What Lux adds to the Editor

Lux integrates directly with the normal Unreal Level Editor. It does **not** require a placed Lux Actor or new project data asset. Its responsibilities are split so UI, viewport tracking, light lifetime and preferences are distinct.

| Part | What it does for users |
| --- | --- |
| Toolbar icon + arrow | Toggle the headlamp or access settings |
| Viewport tracker | Choose which perspective editor camera to follow |
| Editor subsystem | Create/remove the point light and apply values |
| Project Settings | Supply shared defaults and intensity/radius bounds |
| User preferences | Remember personal light values between editor sessions |

## The lifecycle in everyday language

When enabled in a valid perspective editor view, Lux creates a **single movable point light component** and places it at the camera. Moving the camera moves the light. Disabling Lux removes it. During a map change, the old component is destroyed and can be recreated for the next suitable Editor world.

<figure class="doc-media" data-kind="image" data-media-id="architecture-lifecycle">
<img src="../../../assets/media-placeholder.png" alt="Lux temporary headlamp lifecycle architecture." loading="lazy">
<figcaption>The Lux headlamp exists only while enabled in a compatible Editor world and follows the working camera.<span class="media-capture-instructions"><strong>Capture instructions · Image:</strong> Draw a lifecycle diagram: Disabled → toolbar click → Enabled/valid editor camera → Create transient point light → camera movement updates position → Disable or world cleanup destroys component. Show map-change recreation as a separate arrow.</span></figcaption>
</figure>

## What cannot be concluded from seeing the light

It isn't a saved level Actor, doesn't create runtime content, and doesn't become per-viewport lighting. Renderer features still decide what the transient component can illuminate.

For deeper source responsibilities, use the companion Technical page.

---

For source implementation details, [read Technical](TECHNICAL.md).
