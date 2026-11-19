# Installation and Compatibility — Design

**Lux v2.0.10 · Unreal Engine 5.8.x · Win64 · Editor-only**

## Compatibility first

Lux v2.0.10 targets **Unreal Engine 5.8.x on Windows 64-bit** and works in the Unreal Editor. It does not install a runtime lighting feature. Use a package built for your engine version; other platforms or engine releases are not assumed compatible.

## Install through Fab

If Lux is available in your Fab library for your installed engine, install it through Epic Games Launcher, open the project and enable Lux in **Edit → Plugins** when required. Restart if prompted.

## Install a GitHub release

1. Close the Unreal Editor.
2. Download a matching ZIP from [Lux Releases](https://github.com/mippi-the-dork/Lux/releases).
3. Extract the **entire Lux folder** into `YourProject/Plugins/Lux/`.
4. Check that `Lux.uplugin` sits directly inside that directory, not under `Lux/Lux/`.
5. Enable the plugin and restart the Editor if prompted.

<figure class="doc-media" data-kind="image" data-media-id="install-plugin-folder">
<img src="../../../assets/media-placeholder.png" alt="File Explorer showing the installed Lux plugin directory." loading="lazy">
<figcaption>A project installation places the complete Lux plugin inside the project's Plugins folder.<span class="media-capture-instructions"><strong>Capture instructions · Image:</strong> Capture Windows File Explorer at YourProject/Plugins/Lux, with Lux.uplugin, Source, Resources and Content visible, plus the full parent path in the address bar.</span></figcaption>
</figure>

## Install from source

Clone [the public Lux repository](https://github.com/mippi-the-dork/Lux) into the project's Plugins folder. Generate IDE project files if needed, then compile a matching **Win64 Development Editor** target using the Unreal C++ toolchain.

## Verify the installation

Open a perspective Level Editor viewport and look at the **first control in the right-anchored viewport toolbar group**. Lux has a separate icon button and neighboring dropdown arrow. If absent, see [Troubleshooting](../../05-support-and-troubleshooting/troubleshooting/DESIGN.md).

For updates, replace the whole old plugin folder while the Editor is closed; avoid mixing files from different versions.

---

For native implementation and constraints, [read Technical](TECHNICAL.md).
