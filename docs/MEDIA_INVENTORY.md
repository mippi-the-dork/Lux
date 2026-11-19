# Lux Documentation Media Inventory

The Lux manual reuses genuine images and animations already provided with the plugin. It also contains **34 planned media placements** (**29 still images and 5 GIFs**) that currently display the same neutral placeholder image.

Each placeholder includes two lines below it: a **reader-facing caption** describing the eventual result, followed by **Capture instructions · Image** or **Capture instructions · GIF** explaining exactly what should be shown. Full descriptions, expected filenames and alt text live in [media-slots.json](assets/media-slots.json).

## Planned media

| Documentation page | Type | Expected final asset |
| --- | --- | --- |
| [01-getting-started/first-use/TECHNICAL.md](01-getting-started/first-use/TECHNICAL.md) | IMAGE | `assets/media/first-use-state-flow.png` |
| [01-getting-started/install/DESIGN.md](01-getting-started/install/DESIGN.md) | IMAGE | `assets/media/install-plugin-folder.png` |
| [01-getting-started/install/TECHNICAL.md](01-getting-started/install/TECHNICAL.md) | IMAGE | `assets/media/install-toolbar-location.png` |
| [01-getting-started/overview/DESIGN.md](01-getting-started/overview/DESIGN.md) | IMAGE | `assets/media/overview-headlamp.png` |
| [01-getting-started/overview/TECHNICAL.md](01-getting-started/overview/TECHNICAL.md) | IMAGE | `assets/media/overview-light-lifecycle.png` |
| [02-headlamp-controls/advanced-lighting/DESIGN.md](02-headlamp-controls/advanced-lighting/DESIGN.md) | IMAGE | `assets/media/advanced-menu.png` |
| [02-headlamp-controls/advanced-lighting/DESIGN.md](02-headlamp-controls/advanced-lighting/DESIGN.md) | GIF | `assets/media/advanced-render-effects.gif` |
| [02-headlamp-controls/advanced-lighting/TECHNICAL.md](02-headlamp-controls/advanced-lighting/TECHNICAL.md) | IMAGE | `assets/media/advanced-property-routing.png` |
| [02-headlamp-controls/everyday/DESIGN.md](02-headlamp-controls/everyday/DESIGN.md) | GIF | `assets/media/everyday-scrubbing.gif` |
| [02-headlamp-controls/everyday/TECHNICAL.md](02-headlamp-controls/everyday/TECHNICAL.md) | IMAGE | `assets/media/everyday-value-flow.png` |
| [02-headlamp-controls/temperature/DESIGN.md](02-headlamp-controls/temperature/DESIGN.md) | GIF | `assets/media/temperature-comparison.gif` |
| [02-headlamp-controls/temperature/TECHNICAL.md](02-headlamp-controls/temperature/TECHNICAL.md) | IMAGE | `assets/media/temperature-color-flow.png` |
| [02-headlamp-controls/toolbar/DESIGN.md](02-headlamp-controls/toolbar/DESIGN.md) | IMAGE | `assets/media/toolbar-button.png` |
| [02-headlamp-controls/toolbar/TECHNICAL.md](02-headlamp-controls/toolbar/TECHNICAL.md) | IMAGE | `assets/media/toolbar-slate-composition.png` |
| [03-settings-and-preferences/project-defaults/DESIGN.md](03-settings-and-preferences/project-defaults/DESIGN.md) | IMAGE | `assets/media/project-defaults-screen.png` |
| [03-settings-and-preferences/project-defaults/TECHNICAL.md](03-settings-and-preferences/project-defaults/TECHNICAL.md) | IMAGE | `assets/media/project-config-flow.png` |
| [03-settings-and-preferences/reset/DESIGN.md](03-settings-and-preferences/reset/DESIGN.md) | GIF | `assets/media/reset-menu.gif` |
| [03-settings-and-preferences/reset/TECHNICAL.md](03-settings-and-preferences/reset/TECHNICAL.md) | IMAGE | `assets/media/reset-state-update.png` |
| [03-settings-and-preferences/user-preferences/DESIGN.md](03-settings-and-preferences/user-preferences/DESIGN.md) | IMAGE | `assets/media/preferences-session.png` |
| [03-settings-and-preferences/user-preferences/TECHNICAL.md](03-settings-and-preferences/user-preferences/TECHNICAL.md) | IMAGE | `assets/media/preferences-storage.png` |
| [04-workflows-and-implementation/architecture/DESIGN.md](04-workflows-and-implementation/architecture/DESIGN.md) | IMAGE | `assets/media/architecture-lifecycle.png` |
| [04-workflows-and-implementation/architecture/TECHNICAL.md](04-workflows-and-implementation/architecture/TECHNICAL.md) | IMAGE | `assets/media/architecture-source-map.png` |
| [04-workflows-and-implementation/inspection-workflows/DESIGN.md](04-workflows-and-implementation/inspection-workflows/DESIGN.md) | IMAGE | `assets/media/material-comparison.png` |
| [04-workflows-and-implementation/inspection-workflows/TECHNICAL.md](04-workflows-and-implementation/inspection-workflows/TECHNICAL.md) | IMAGE | `assets/media/inspection-performance.png` |
| [04-workflows-and-implementation/viewports/DESIGN.md](04-workflows-and-implementation/viewports/DESIGN.md) | GIF | `assets/media/viewport-switching.gif` |
| [04-workflows-and-implementation/viewports/TECHNICAL.md](04-workflows-and-implementation/viewports/TECHNICAL.md) | IMAGE | `assets/media/viewport-tracker-policy.png` |
| [05-support-and-troubleshooting/faq/DESIGN.md](05-support-and-troubleshooting/faq/DESIGN.md) | IMAGE | `assets/media/faq-compare-states.png` |
| [05-support-and-troubleshooting/faq/TECHNICAL.md](05-support-and-troubleshooting/faq/TECHNICAL.md) | IMAGE | `assets/media/faq-diagnostic-branches.png` |
| [05-support-and-troubleshooting/troubleshooting/DESIGN.md](05-support-and-troubleshooting/troubleshooting/DESIGN.md) | IMAGE | `assets/media/troubleshoot-dark-scene.png` |
| [05-support-and-troubleshooting/troubleshooting/TECHNICAL.md](05-support-and-troubleshooting/troubleshooting/TECHNICAL.md) | IMAGE | `assets/media/troubleshoot-light-lifecycle.png` |
| [05-support-and-troubleshooting/updates/DESIGN.md](05-support-and-troubleshooting/updates/DESIGN.md) | IMAGE | `assets/media/update-plugin-directory.png` |
| [05-support-and-troubleshooting/updates/TECHNICAL.md](05-support-and-troubleshooting/updates/TECHNICAL.md) | IMAGE | `assets/media/update-source-ownership.png` |
| [ROADMAP.md](ROADMAP.md) | IMAGE | `assets/media/roadmap-timeline.png` |
| [ROADMAP.md](ROADMAP.md) | IMAGE | `assets/media/roadmap-future.png` |

## Replacing a placeholder

1. Capture the actual **running Lux Editor plugin** or create a clearly labeled, accurate technical diagram. For GIFs, show the stated gesture/sequence with the viewport and menu states readable.
2. Place the completed image or GIF under `docs/assets/media/` with the exact filename listed in the inventory.
3. Change the relevant figure's relative `<img src>` to the new file, retaining and refining the reader-facing caption and alt text. Remove the capture-instruction line only after that slot is finished, if desired.
4. Check desktop/mobile article widths and GIF file sizes. Avoid fabricated Lux UI or unrelated screenshots.

## Existing genuine assets

The site already uses the repository's real `Lux-Hero.png`, `Lux-Headlamp-Comparison.png`, `Lux-Controls.png`, `Lux-Settings.png`, `Lux-Off.png`, `Lux-On.png` and `Lux-Toggle.gif`. These are complete media assets rather than neutral placeholders and should not be recaptured without a reason.
