# Updating, Support and Compatibility — Design

**Lux v2.0.10 · User guide**

## Current compatibility

| Item | Declared support |
| --- | --- |
| Lux release | **v2.0.10** |
| Unreal Engine | **5.8.x** (descriptor `5.8.0`) |
| Platform | **Win64** |
| Plugin type | **Editor-only** |
| Game build dependency | None |

Support for other engines and platforms should not be assumed without tests.

## Update a downloaded package

1. Close the Unreal Editor.
2. Choose the [Lux Release](https://github.com/mippi-the-dork/Lux/releases) compatible with your engine.
3. Remove the previous `YourProject/Plugins/Lux` folder and replace it with the full new Lux folder.
4. Confirm `Lux.uplugin` is directly inside the folder.
5. Start the editor, check plugin status and verify the toolbar icon and menu.

Avoid layering a new ZIP over an older source checkout. If you use Git source, pull the intended version, regenerate project files if appropriate, and rebuild the Editor target.

<figure class="doc-media" data-kind="image" data-media-id="update-plugin-directory">
<img src="../../../assets/media-placeholder.png" alt="Lux project plugin folder ready for a complete update." loading="lazy">
<figcaption>A safe manual Lux update replaces the entire plugin folder rather than mixing files from multiple versions.<span class="media-capture-instructions"><strong>Capture instructions · Image:</strong> Capture File Explorer showing YourProject/Plugins/Lux with Lux.uplugin, Source, Resources and Content. Include a simple note that the Unreal Editor is closed and the full folder is replaced.</span></figcaption>
</figure>

## Reporting issues and requesting features

Use [Lux Issues](https://github.com/mippi-the-dork/Lux/issues) for bug reports and requests. Include the exact Unreal/Lux version, viewport scenario, project rendering conditions and expected versus observed result. For feature requests, explain the editing task you want to make easier.

## Where to find source and releases

[Lux repository](https://github.com/mippi-the-dork/Lux) · [Release downloads](https://github.com/mippi-the-dork/Lux/releases) · [MIT License](https://github.com/mippi-the-dork/Lux/blob/main/LICENSE).

---

For the underlying editor implementation and diagnostic paths, [read Technical](TECHNICAL.md).
