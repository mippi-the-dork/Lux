# Lux Roadmap

**Current documented version:** Lux **v2.0.10**, Unreal Engine 5.8.x on Win64.  
**Status:** Public documentation baseline, not a release promise.  
**History limit:** Earlier Lux version-by-version milestones have not been independently reconstructed from tagged source/release notes. We will not assign past features to versions without that evidence.

## At a glance

<figure class="doc-media" data-kind="image" data-media-id="roadmap-timeline">
<img src="assets/media-placeholder.png" alt="Lux current release and proposed future roadmap timeline" loading="lazy">
<figcaption>Lux's roadmap distinguishes the current documented release from uncommitted future opportunities.<span class="media-capture-instructions"><strong>Capture instructions · Image:</strong> Create a clean timeline with Lux v2.0.10 marked Released, historical milestones explicitly marked Unverified, and future directions marked Not Scheduled. Do not assign unsupported v1/v2 release claims or dates.</span></figcaption>
</figure>


| Milestone | Status | Scope |
| --- | --- | --- |
| **Lux v2.0.10** | Released · current documented version | Native Level Editor headlamp, camera following, everyday/Advanced properties, project defaults, personal preferences |
| **Past Lux releases** | Historical · details awaiting verification | Release-by-release history can be added from actual tags and changelogs |
| **Future Lux updates** | Not scheduled | No specific new Lux feature, version number or date has been approved for this roadmap |

## Current capability — v2.0.10

Lux already provides a native viewport toolbar icon and settings arrow, one temporary movable point light in the Editor world, tracking of the active eligible perspective Level Editor viewport, an everyday settings menu, an Advanced Lighting/Temperature menu, and project/user settings separation.

[Explore current controls](02-headlamp-controls/README.md) or [read how it works](04-workflows-and-implementation/architecture/TECHNICAL.md).

## Opportunities to evaluate, not committed features

The following are **research directions**, not approved roadmap deliverables:

- **Inspection workflow improvements:** Research where users still need to alter authored scene lights to inspect materials or geometry, and whether a small Lux control could remove that friction.
- **Viewport clarity:** Evaluate whether the interface can communicate the current perspective viewport target more clearly in multi-viewport layouts without adding UI clutter.
- **Rendering guidance:** Improve descriptions and diagnostics for shadows, volumetrics, translucency and indirect contribution under varying Unreal render configurations.
- **Performance:** Measure the effect of large attenuation radii and supported dynamic shadows on representative projects before changing their UI or default policies.

Any selected feature should preserve Lux's editor-only, native Slate, minimal-footprint design, and avoid editing Unreal Engine source.

<figure class="doc-media" data-kind="image" data-media-id="roadmap-future">
<img src="assets/media-placeholder.png" alt="Conceptual examples of future Lux inspection workflow areas" loading="lazy">
<figcaption>Future Lux research may focus on faster inspection workflows, clearer viewport targeting and more predictable rendering feedback.<span class="media-capture-instructions"><strong>Capture instructions · Image:</strong> Make a labeled three-column concept diagram for Inspection Workflows, Viewport Clarity and Rendering Guidance. Use conceptual icons or neutral diagrams only, not fabricated screenshots or a mockup implying these features ship today.</span></figcaption>
</figure>

## Acceptance criteria for future changes

A future feature should have a clear user problem, a behavior specification, no unintended saved Light Actor or packaged-game consequence, predictable viewport ownership, documented supported render paths, and repeatable native Unreal Editor tests. New controls also need Design/Technical documentation and genuine screenshots/GIF examples.

## Documentation status

The initial website is based on v2.0.10 source. The [Verification Matrix](VERIFICATION_MATRIX.md) separates checks still to be run from source-grounded findings; the [Media Inventory](MEDIA_INVENTORY.md) identifies visual examples needing new captures.

A future historical section should quote actual release notes or tags rather than infer what happened in v1.0 or v2.0 from the current implementation.
