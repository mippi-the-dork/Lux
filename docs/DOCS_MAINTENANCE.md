# Maintaining Lux Documentation

## Source of truth

Inspect the current Lux C++ source, plugin descriptor and relevant native Unreal behavior whenever documenting a changed capability. The README is a helpful introduction but not a substitute for inspecting the actual implementation.

## Site organization

The site uses the same visual language and Markdown navigation architecture as the Focus documentation, adapted for Lux rather than copying Focus's categories. Every feature topic has:

- **DESIGN.md:** User-facing purpose, exact controls, workflows, examples, expected results and troubleshooting.
- **TECHNICAL.md:** C++ ownership, native Unreal integration, state handling, target limits, constraints and source references.

Avoid duplicating entire paragraphs across the pair. Keep category overviews informative, not just lists of links.

## Media and capture instructions

[Media Inventory](MEDIA_INVENTORY.md) and the JSON registry under `assets/media-slots.json` identify the expected static images and GIFs. Each placeholder figure has a **reader-facing caption** and a second clearly labeled capture-instruction line. Replace placeholders with genuine screenshots/animations from the active Lux plugin, keeping captions accurate. The provided real Lux marketing hero and existing screenshots/GIF are preserved where useful.

## QA and version accuracy

[Verification Matrix](VERIFICATION_MATRIX.md) distinguishes source review from actual Unreal Editor and browser tests; never mark a test as passed without observing it. When Lux releases, update `site-manifest.json`, the homepage and relevant topic references together. Pin C++ source links to a verified release commit/tag when possible.

## Publishing

Deploy from **main → /docs** under repository Settings → Pages. The intended site URL is `https://mippi-the-dork.github.io/Lux/`. Validate the actual deployment separately from the existence of merged docs.

Only change plugin source when a separate explicit implementation task requires it.
