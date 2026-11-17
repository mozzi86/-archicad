---
status: complete
date: 2026-11-17
---
# Fassaden-Rasterursprung live berichtigt

Live (AC29 Mac, ELMonkey 0.11.16): `SetCurtainWallSegmentELM` mit `gridOriginAtStart`/`gridOrigin` meldet `success`, erreicht den Ursprung aber nicht (`gridOriginReached: false`, Rücklese (0,0,0), Pfosten unverändert), weder per Memo noch per Segment-Element. Rasterlage bestehender Fassaden per API (DevKit 29) nicht verschiebbar; ungleiche Bestandsteilungen nur per Neubau. `GetCurtainWallFramesELM` funktioniert; der feste Pfosten war ein normaler Rasterpfosten.

Geändert: `recipes/curtain-walls.md` (Abschnitt Rasterursprung). Nur Doku.
