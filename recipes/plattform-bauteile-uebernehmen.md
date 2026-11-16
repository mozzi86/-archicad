# Rezept: Bauteile aus der Schwarz Platform nach Archicad übernehmen <!-- 2026-11-16 -->

Live durchlaufen an AFWC (WC-Sanierung Amtsgericht Fürth, AC29 Teamwork, ELMonkey mit Tapir 1.7.2):
20 Tragtraversen (Ebene „Traversen Sanitär (LV 002)“, 2. OG + DG), die Claude in der Plattform
gezeichnet hatte, als Träger ins Archicad-Modell übernommen. Das Muster gilt für alles, was in der
Plattform mit `modell_bauen` entsteht (Duofix-Elemente, Kernbohrungen, Stahlteile …).

## Ablauf

1. **Projekt und Instanz:** `projekte_suchen` (Projektnummer, hier „AFWC“) und
   `discovery_list_active_archicads` (Projektname → Port; Ports wechseln bei jedem Neustart).
2. **Bauteile finden:** `modell_lesen` (Ebenen mit Zählung) → `modell_register_lesen` mit
   `modellart:"plattform"`. Die Ebene selbst (`modell_ebenen`) zeigt bei gebauten Bauteilen **keine
   Objekte** (`objekte: []`). Die Bauteile stehen nur im Register (`herkunft.ebene`). Große
   Antworten landen in einer Datei; dort mit Python filtern.
3. **Exakte Geometrie in Archicad-Koordinaten:** `modell_exportieren` mit
   `modellarten:["plattform"]`, `mit_ebenen:["<Ebene>"]`, `mit_bezuegen:false`. Das IFC liegt
   **in Archicad-Koordinaten** (Meter, z = absolute Archicad-Höhe), GUIDs wie in der Plattform.
   Download per `curl` in einen eigenen Ordner. `ifcopenshell` ist nicht installiert; das STEP
   reicht mit Regex: `IFCMEMBER` → Shape → `IFCTRIANGULATEDFACESET` → `IFCCARTESIANPOINTLIST3D`.
   Die Pset `SAB_Plattform` trägt `Skizzen-ID`, `Profil`, `Werkstoff`; `Qto_SAB_Plattform` die Länge.
   Achse und Dicke je Bauteil per Hauptachse (PCA) der xy-Punkte.
   Achtung: Das Export enthält **alle** Plattform-Bauteile (auch Traversen *innerhalb* der
   Duofix-Elemente); nach `Skizzen-ID`/Herkunft filtern.
4. **Gegenprobe:** Grundmodell-GUIDs der Plattform sind die Archicad-GUIDs. Eine Wand per
   `GetDetailsOfElements` lesen und mit `bauteil_geometrie` vergleichen.
5. **Anlegen** (hier `CreateBeams`, Breite = Blechdicke + Schenkel, Höhe 0,302, `anchorPoint
   BottomCenter`, `zCoordinate` = Unterkante, `floorIndex` explizit, Baustoff „Stahl verzinkt_760“).
   Bei Tapir 1.7.2: ohne `id`/`layerIndex` anlegen, danach Ebene und Element-ID setzen (siehe
   [`../reference/mcp-conventions.md`](../reference/mcp-conventions.md), „MCP-Schema ≠ installiertes Add-on“).
6. **Rücklesen:** `GetDetailsOfElements` + `Get3DBoundingBoxes` gegen die IFC-Box (hier mm-genau).
7. **KI-Stempel** setzen; fehlt die Property im Projekt (AFWC am 16.11.), der Nutzerin melden.
8. **Zeigen:** Grundriss per `ChangeWindow` öffnen, Bild speichern, Bauteile darüberzeichnen.

## Koordinaten, falls kein Export möglich ist

- `bauteil_geometrie` liefert **Projekt-Meter** (x Ost, y Nord ab Modelladresse) und Höhen **über
  Nullniveau**. `modell_register_lesen` liefert Unter-/Oberkante dagegen in **Archicad-Höhe**.
  Unterschied = `georeferenz_archicad.hoeheNN − nullniveauNN` (AFWC 12,52 m).
- Lage: Archicad hat oft keine Nordrichtung gesetzt (`project_get_geo_location` → north π/2,
  Survey Point 0), die Plattform aber eine eingepasste (`nordrichtungGrad`, AFWC 308,26°).
  Archicad → Projekt-Meter: `P = O + x·(cos θ, sin θ) + y·(−sin θ, cos θ)`, θ = nordrichtungGrad,
  O = Archicad-Ursprung (lat/lon aus `georeferenz_archicad` gegen `ursprung_wgs84`, m/° nach
  Breite). Damit lagen die Traversen auf ~1 cm. Ein Ausgleich über Wand-Hüllen der Plattform war
  ungenauer (±10 cm), weil die Hüllen Anschlusspunkte mitnehmen.

## Fallen

1. **Fast-achsparallel:** In der Plattform im gedrehten System gezeichnete Bauteile kommen um
   0,1–0,8° schief an (Rundung der Hüllen). Bei < 1,5° auf die Archicad-Achse einrasten (Mittel der
   Querkoordinate). Echte Schrägen stehen lassen und melden (AFWC: TRAV-OG2-04, 14 cm, 15°).
2. **Bauteile in Vorwänden** sind im gespeicherten Grundriss kaum zu sehen (Schnitthöhe, 22 mm).
   Das ist kein Fehler; zum Zeigen überzeichnen.
3. **Ebene:** Der Werkzeug-Standard kann eine fremde Ebene sein (AFWC Träger → „A_80_MASKENBLOCK“).
   Immer bewusst setzen und vorher prüfen, dass die Zielebene sichtbar und nicht gesperrt ist.

## Was der Nutzer entscheidet

- Werkzeug (Träger, Objekt, Morph), Ebene und Baustoff, wenn es keinen passenden Favoriten gibt.
  AFWC: Träger auf „A_28_EINBAU_SANIT“, Element-ID = Skizzen-ID in Großbuchstaben.
- Ob eingebettete Teile (Traversen in Duofix-Elementen) mitkommen.
- Senden in Teamwork.
