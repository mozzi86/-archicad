---
quick_id: 261116-osp
slug: holen-aus-archicad-volles-paket
date: 2026-11-16
status: planned
---

Regel „Holen aus Archicad = volles Paket“ (Weisung Mudi, 16.11.2026) und live verifiziertes Rezept Archicad → Schwarz Platform in den Skill eintragen.

## Aufgaben

1. `SKILL.md`: neuer kurzer Abschnitt „Holen aus Archicad = volles Paket <!-- 2026-11-16 -->“ direkt vor „## Wo welches Wissen liegt“. Inhalt: „hol es aus Archicad / schau es dir in Archicad an und bau es nach“ heißt immer (a) richtige Objekte + Geometrien aus dem richtigen IFC, (b) richtige Baustoffe, (c) richtige Oberflächen (`ELM_SAB.ExportSurfaces` → `archicad_oberflaechen_hochladen` → `archicad_oberflaechen_einpflegen`); nie grafische Überschreibungen als Material; Umbau-Farben (Neubau rot, Abbruch gelb) sind ein Schalter in der Plattform (PR SchwarzArchitekturbuero/SchwarzPlatform#345), kein Material. Verweis auf das Rezept.
2. Neues Rezept `recipes/archicad-nach-plattform.md` (Stil und Ton wie `recipes/plattform-bauteile-uebernehmen.md`, Datums-Marker `<!-- 2026-11-16 -->`, „live BSZ 10659 2026-11-16“). Quelle: `~/.scratch/10659/handoff_10659_plattform-modell_2026-11-16.md` — generalisiert, ohne projektspezifische GUIDs. Pflichtinhalte:
   - Aktives Fenster nur lesen (`TapirCommand.GetCurrentWindowType` = FloorPlan/3D); NIE per `ChangeWindow` wechseln (zwei Abstürze am BSZ) — der Nutzer holt den Grundriss selbst nach vorn; Ansicht ohne Umbau-/Grafik-Überschreibung.
   - Export: `TapirCommand.IFCFileOperation` `method: save`, `translatorName`, `elementsToExport: "EntireProject"` (ab ELMonkey 0.11.12).
   - Prüfen vor dem Hochladen: Soll-Ist per GlobalId (`GetIFCIdsOfElements`; leere Öffnungen = IfcOpeningElement mit eigener Kennung, Gelände im IfcSite); Surface-Styles auszählen — ein Stil über 50 % wie „Farbe rot“ = Überschreibung eingebacken, nicht hochladen (BSZ: 61 Stile/92,5 % rot gegen 117 echte Stile).
   - Plattform: 400-MB-Grenze des Konnektors (curl-Link und `sharepoint`-Pfad); Weg über SharePoint-Projektablage, ~15–20 min bis die Datei als Dokument erscheint, dann `modell_hochladen` mit `document_id`; `modell_import_freigeben`; alte Stände mit `modell_version_entfernen` (weich).
   - Oberflächen: `ELM_SAB.ExportSurfaces` (`targetFolder`), ZIP mit NFC-Dateinamen (Python `zipfile` + `unicodedata.normalize`), sonst „Bild fehlt“ bei Umlauten; Prüfplan lesen, dann einpflegen.
   - Falle: Elemente ohne gültigen 3D-Körper (entartete Bounding-Box, Höhe 0, hauchdünne Reststücke) fehlen im Export, unabhängig vom Umbaufilter; aktiver Umbaufilter ist per API nicht lesbar.
3. `SKILL.md`: Rezept in der Recipes-Liste verlinken (bei `plattform-bauteile-uebernehmen.md`).

Keine anderen Dateien ändern. Ein atomarer Commit (Deutsch).
