# Reset to Project Defaults — Design

**Lux v2.0.10 · User guide**

## What Reset does

The **Reset to Project Defaults** command is near the bottom of the Lux settings dropdown, below the property menus. It restores **Intensity, Attenuation Radius, Light Color, Cast Shadows and every Advanced property** to the values configured under Project Settings → Plugins → Lux.

Reset does **not** enable or disable Lux, remove project settings, alter authored level lights or change existing light Actors.

## Reset safely

1. Open the Lux menu with its settings arrow.
2. If you want to inspect the current configuration, choose **Lux Project Settings** first.
3. Return to the Lux menu and click **Reset to Project Defaults**.
4. Observe that your Intensity/Radius, color, shadows and Advanced values now match the project defaults.
5. Lux's icon remains on or off according to its previous state.

<figure class="doc-media" data-kind="gif" data-media-id="reset-menu">
<img src="../../../assets/media-placeholder.png" alt="Lux Reset to Project Defaults command restoring edited properties." loading="lazy">
<figcaption>Reset restores Lux's personal headlamp adjustments without changing whether the headlamp is enabled.<span class="media-capture-instructions"><strong>Capture instructions · GIF:</strong> Record changing Intensity, Light Color and one Advanced property, then selecting Reset to Project Defaults from the native Lux menu. Reopen the menu to show the restored values and unchanged toolbar icon state.</span></figcaption>
</figure>

## Why the result may differ from earlier sessions

The reset target is the **current project's configuration**, not necessarily Lux's original built-in defaults. If teammates changed the shared defaults, Reset deliberately adopts those values.

---

For configuration classes and native save behavior, [read Technical](TECHNICAL.md).
