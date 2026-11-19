# Troubleshooting — Design

**Lux v2.0.10 · User guide**

## Lux doesn't appear in the viewport toolbar

Check **Edit → Plugins**, confirm Lux is enabled, restart if prompted, and use the standard **Level Editor viewport**, not a separate asset-editor tab or PIE window. Verify UE 5.8.x and Win64, and look at the beginning of the right-anchored viewport toolbar group.

## Icon is blue but the environment is not illuminated

1. Click into a **perspective Level Editor viewport**.
2. Open Lux's arrow menu and check **Intensity** is above zero.
3. Ensure **Attenuation Radius** reaches nearby geometry.
4. Move close to a surface to make the effect easier to judge.
5. Check exposure, renderer, light visibility and the project's relevant lighting settings.
6. If you changed maps or viewport layout, interact with the intended perspective viewport again.

<figure class="doc-media" data-kind="image" data-media-id="troubleshoot-dark-scene">
<img src="../../../assets/media-placeholder.png" alt="Lux active but dim versus correctly configured light." loading="lazy">
<figcaption>Lux can be active while brightness, light radius or viewport conditions prevent an obvious visible result.<span class="media-capture-instructions"><strong>Capture instructions · Image:</strong> Capture two screenshots of the same perspective viewport with the Lux icon blue: one with near-zero Intensity or tiny radius leaving the scene dark, another with a useful value lighting nearby surfaces. Show the relevant dropdown controls and labels.</span></figcaption>
</figure>

## Lux follows the wrong camera

In a multi-viewport Level Editor layout, click the desired **perspective** viewport, then move its camera. Orthographic viewports cannot take control; PIE and asset editor cameras also aren't eligible.

## I cannot enter a higher numeric value

**Intensity** and **Attenuation Radius** are bounded by **Project Settings → Plugins → Lux**. Advanced properties have their own fixed bounds. This is expected clamping, not necessarily a broken numeric widget.

## Advanced controls appear to have no effect

For temperature, enable **Use Temperature** and try white Light Color. For volumetrics, inspect the fog setup; for translucent lighting, inspect material and render support; for indirect lighting, inspect the renderer. Dynamic shadow and source-radius effects may also depend on the project.

## Settings didn't survive restart

Check you reopened the same project and understand that the **enabled state always resets off**. Light properties are personal editor config and usually save shortly after adjustment. Changed project ranges may clamp a saved value.

## Lux Project Settings opens an unexpected page

Confirm the expected **Project → Plugins → Lux** section and avoid duplicate Lux installations in Engine and Project plugin folders. Report reproducible routing issues with the exact plugin/Unreal versions.

## What to include in a report

Record UE version, Lux version, Windows version, installation method, exact viewport arrangement, renderer/fog/shadow setup, involved property, reproducible steps, and relevant Output Log lines. [Open a Lux issue](https://github.com/mippi-the-dork/Lux/issues).

---

For the underlying editor implementation and diagnostic paths, [read Technical](TECHNICAL.md).
