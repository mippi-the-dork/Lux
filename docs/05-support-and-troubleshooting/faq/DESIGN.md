# Frequently Asked Questions — Design

**Lux v2.0.10 · User guide**

## Does Lux modify my level?

**No.** The headlamp is a temporary movable Point Light Component in the Editor world, not a placed Light Actor. It is not saved into the map or packaged gameplay.

## Why is the icon blue but my scene still dark?

The headlamp may be active while the light has too little Intensity, too small an Attenuation Radius, no valid perspective camera, or a rendering/exposure configuration that obscures the result. Use [Troubleshooting](../troubleshooting/DESIGN.md) to isolate the cause.

## Does the arrow also turn Lux on?

No. The toolbar **icon toggles Lux**; the adjacent **arrow opens settings**. Both have independent hit areas.

## Can I use Lux in orthographic or Play mode?

No. Lux follows perspective **Level Editor** cameras and doesn't target orthographic or PIE/game cameras.

## Why does the other perspective viewport look lit?

There is **one shared-world point light**, not independent illumination for each editor viewport. Both may render light from the same component.

## Why is Temperature grayed out?

Open **Advanced → Temperature → Use Temperature** and enable it. The Kelvin field is conditional. Temperature also multiplies with Light Color; use white when comparing temperature alone.

## Why won't Intensity or Radius exceed a value?

The project's [Intensity and Attenuation Radius limits](../../03-settings-and-preferences/project-defaults/DESIGN.md) constrain these properties. Other advanced properties have their own fixed setter bounds.

## Does Lux remember what I used yesterday?

**Light properties yes; enabled state no.** Your personal values remain in editor-per-project settings, but Lux always starts off after an Editor restart.

## How can I return to the team's chosen light?

Choose **Reset to Project Defaults** from the Lux menu. It restores the project values but keeps Lux's current on/off state.

<figure class="doc-media" data-kind="image" data-media-id="faq-compare-states">
<img src="../../../assets/media-placeholder.png" alt="Lux activation, preferences and transient component comparison." loading="lazy">
<figcaption>Lux's toolbar state, saved preferences and the temporary light are separate concepts.<span class="media-capture-instructions"><strong>Capture instructions · Image:</strong> Create a three-column annotated still: Lux icon off/on, dropdown settings showing a saved intensity, and the same scene without a placed Light Actor in the Outliner. Keep the purpose of each state distinct.</span></figcaption>
</figure>

---

For the underlying editor implementation and diagnostic paths, [read Technical](TECHNICAL.md).
