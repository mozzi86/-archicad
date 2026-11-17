---
status: complete
date: 2026-11-17
---

# Lerneinträge THN Fassaden + Wände (17.11.)

Live-Fall THN 17.11.: 206 von 255 Fassaden per `ELM_SAB.SetCurtainWallSegmentELM` auf 1,20 m gestellt (Befehl nur im lokalen Stand 0.11.12.1, in 0.11.12/0.11.12.2 Fehler 4010); Wand-Referenzlinie/Stärke per `ModifyWalls` (201 + 757 Wände, 3 zurückgesetzt); gesperrte Ebene als Ursache von „Failed to modify wall“.

Geändert: `recipes/curtain-walls.md` (neuer Abschnitt, „kein ModifyCurtainWall“ als überholt), `reference/mcp-extension.md` (gleiche Aussage überholt + Kurzfassung), `recipes/wall-operations.md` (Gotchas 12–15), `reference/ui-aufgaben.md` (Abschnitt „Fenster- und API-Kleinigkeiten“).

Alles aus dem Auftrag untergebracht. Doku-Commit `be2d99c`, nicht gepusht.
