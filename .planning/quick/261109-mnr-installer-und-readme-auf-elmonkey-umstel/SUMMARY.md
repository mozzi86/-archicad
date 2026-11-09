---
slug: 261109-mnr
status: complete
---
# Zusammenfassung: Installer und README auf ELMonkey umstellen

Anlass 09.11.2026: Kollegin sah nur 0.10.x — Installer, README-Links und Update-Prüfung zeigten auf das Release von -archicad (Stand 0.10.3), das Add-On wird seit 0.11 in mozzi86/ELMonkey gebaut.

1. installer/*: Release-Adresse → github.com/mozzi86/ELMonkey/releases/download/elm-sab-tapir-latest (sonst identisch mit ELMonkey/archicad-addon/installer).
2. README: Download-Links, curl-Einzeiler, MCP-Installation → ELMonkey; Status 0.11.12; Zeile `ExportSurfaces`.
3. Übergang: Release `elm-sab-tapir-latest` in -archicad mit 0.11.12 gespiegelt (für ältere Add-Ons, deren Update-Prüfung noch hierher fragt).
