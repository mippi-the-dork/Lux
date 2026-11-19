# Advanced Lighting Controls — Design

**Lux v2.0.10 · User guide**

## Open the Advanced submenu

Click the settings arrow, then hover or open **Advanced → Lighting**. These settings affect secondary properties of the same temporary point light; they are not a second light.

| Control | Initial value | Purpose |
| --- | --- | --- |
| **Source Radius** | 0 cm | Apparent source radius for supported highlights and soft shadows |
| **Volumetric Scattering Intensity** | 0 | Contribution to supported volumetric fog |
| **Indirect Lighting Intensity** | 1 | Multiplier of supported indirect-light contribution |
| **Specular Scale** | 1 | Specular contribution multiplier, from 0 to 1 |
| **Affect Translucent Lighting** | On | Contribution to supported translucent materials |

<figure class="doc-media" data-kind="image" data-media-id="advanced-menu">
<img src="../../../assets/media-placeholder.png" alt="Lux Advanced Lighting submenu displaying five native properties." loading="lazy">
<figcaption>The Advanced → Lighting submenu contains the less frequently changed light properties.<span class="media-capture-instructions"><strong>Capture instructions · Image:</strong> Capture the Lux dropdown with the Advanced submenu open and the Lighting section fully visible. Ensure all five labels and the numeric or checkbox controls are readable.</span></figcaption>
</figure>

## Use the correct control for the problem

- Want softer supported shadows or different highlights? Try **Source Radius**. For a light reaching farther, use **Attenuation Radius** instead.
- Want light interacting with fog? Adjust **Volumetric Scattering Intensity**, with appropriate volumetric fog enabled in the project.
- Want to reduce distracting reflections while inspecting surface colors? Lower **Specular Scale**.
- Want to inspect translucent materials? Turn **Affect Translucent Lighting** on, but confirm your material/render path responds.
- Want to vary supported indirect contribution? Adjust **Indirect Lighting Intensity**; this is not a global illumination replacement.

<figure class="doc-media" data-kind="gif" data-media-id="advanced-render-effects">
<img src="../../../assets/media-placeholder.png" alt="Advanced Lux lighting effects demonstrated in a fixed test scene." loading="lazy">
<figcaption>Advanced Lux settings may alter supported shadows, specular highlights, fog and translucency without changing the level's lights.<span class="media-capture-instructions"><strong>Capture instructions · GIF:</strong> Record a controlled scene with fog, a reflective object and a translucent material. Keep camera and primary light controls fixed while adjusting Source Radius, Volumetric Scattering Intensity and Specular Scale separately. Clearly label each adjustment.</span></figcaption>
</figure>

## Why an option can seem ineffective

The renderer, project configuration, material model, and whether fog or supported shadows are present determine visible effects. The setting can be stored and sent to the light correctly even when the scene has nothing that responds to it.

---

For specific Unreal properties and implementation paths, [read Technical](TECHNICAL.md).
