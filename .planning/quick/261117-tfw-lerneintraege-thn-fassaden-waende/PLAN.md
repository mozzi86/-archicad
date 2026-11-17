---
quick_id: 261117-tfw
slug: lerneintraege-thn-fassaden-waende
date: 2026-11-17
status: planned
---

Lerneinträge aus THN (live verifiziert 2026-11-17) in den Skill eintragen. Nur Markdown, Marker `<!-- 2026-11-17 -->`.

## Aufgaben

1. `recipes/curtain-walls.md` und `reference/mcp-extension.md`: „kein ModifyCurtainWall / Rasteränderung = neu bauen“ als überholt kennzeichnen (nicht löschen); `ELM_SAB.SetCurtainWallSegmentELM` (nur lokaler Stand 0.11.12.1, 4010 in 0.11.12/0.11.12.2), Einzelwert vs. volle Feldliste mit Nachregeln, `GetCurtainWallPlaneELM` ohne planeMatrix, Glasebene = Querlage der langen Feld-Polygone, Querschieben per `MoveElements` in 6er-Paketen, Nachmess-Skripte.
2. `recipes/wall-operations.md`: Gotchas 12–15 (ModifyWalls-Form ohne `details`, Referenzlinie auf Wandseite mit Kantenmessung, Stärke mit fester Seite, „Failed to modify wall“ = Ebene gesperrt).
3. `reference/ui-aufgaben.md`: Get2DGeometryOfElements braucht Grundriss, ChangeSelectionOfElements-Felder, AXMinimized, Port→PID per lsof.

Keine anderen Dateien ändern. Doku-Commit + Abschluss-Commit, nicht pushen.
