# First Use — Design

**Lux v2.0.10 · Unreal Engine 5.8.x · Win64 · Editor-only**

## Your first headlamp test

1. Open a dark test level in a **perspective Level Editor viewport**.
2. Find the Lux icon at the start of the right-side toolbar group.
3. Click the **icon** once. It changes from gray to Accent Blue.
4. Move the perspective camera closer to a dark wall or object. The temporary point light follows its position.
5. Click the **separate arrow** next to the icon to open the Lux settings menu without toggling the light.
6. Increase **Attenuation Radius** to reach farther, then adjust **Intensity** to control brightness. Drag the native numeric value to scrub or enter a number directly.
7. Click **Light Color** to open Unreal's color picker, or toggle **Cast Shadows**.
8. Click the Lux icon again to return to the level's authored illumination.

<figure class="doc-media" data-kind="gif" data-media-id="first-use-toggle">
<img src="../../../assets/media-placeholder.png" alt="Animated demonstration of Lux enabling and disabling." loading="lazy">
<figcaption>The Lux toolbar icon enables or disables a temporary editor headlamp without changing the level.<span class="media-capture-instructions"><strong>Capture instructions · GIF:</strong> Record a short loop in the same dark perspective viewport showing a gray Lux icon, click to Accent Blue with nearby geometry illuminated, move the camera a little, then click again to turn it gray and restore the original view.</span></figcaption>
</figure>

## Read the split control correctly

**Icon:** state and on/off toggle. **Arrow:** property menu. They are independent clickable targets with native Unreal tooltips. Lux starts **off** on each Editor launch even when it remembers your previous intensity and color.

## If you see no difference

Confirm you are in a perspective Level Editor viewport, the intensity is above zero, the radius reaches nearby surfaces, and exposure or rendering settings aren't masking the result. If you just switched viewports, click in the one you want Lux to track.

## Next

Read [Everyday Controls](../../02-headlamp-controls/everyday/DESIGN.md) for each menu value and [Viewport Following](../../04-workflows-and-implementation/viewports/DESIGN.md) for multi-viewport behavior.

---

For native implementation and constraints, [read Technical](TECHNICAL.md).
