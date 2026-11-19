# Color Temperature — Design

**Lux v2.0.10 · User guide**

## Two controls under Advanced → Temperature

**Use Temperature** enables Lux's blackbody temperature tint. **Temperature** supplies the Kelvin value, and becomes editable only after Use Temperature is checked.

- **Warm values** toward the lower end of the range produce warmer-looking illumination.
- **Cool values** toward the upper end generally produce cooler-looking illumination.
- Initial Temperature is **6,500 K**; the supported range is **1,000–20,000 K**.
- Temperature tint is **combined with Light Color** rather than replacing it.

## A clean comparison workflow

1. In Lux's primary menu, set **Light Color to white**.
2. Open **Advanced → Temperature** and enable **Use Temperature**.
3. Adjust Temperature from a warm value to a cooler one, observing the same neutral material or surface without moving the camera.
4. Disable Use Temperature to return to the Light Color result without the temperature tint.

<figure class="doc-media" data-kind="gif" data-media-id="temperature-comparison">
<img src="../../../assets/media-placeholder.png" alt="Lux color temperature changing from warm to cool in the same scene." loading="lazy">
<figcaption>Lux's temperature tint changes the character of the inspection light when Use Temperature is enabled.<span class="media-capture-instructions"><strong>Capture instructions · GIF:</strong> Record the Lux Temperature submenu with Use Temperature checked; hold the viewport camera and material constant while scrubbing Kelvin from a warm value through 6500 K to a cooler value. Then disable Use Temperature to show the distinction.</span></figcaption>
</figure>

## If nothing happens

The Temperature field is disabled until Use Temperature is enabled. A strongly tinted Light Color can mask what you expect from Kelvin; set it to white when comparing. Exposure and color grading can also change the perceived result.

---

For specific Unreal properties and implementation paths, [read Technical](TECHNICAL.md).
