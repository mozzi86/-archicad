---
quick_id: 261120-bwe
type: quick
autonomous: true
files_modified: [scripts/_kern/**, scripts/plattform_abgleich/plattform_abgleich.py, recipes/plattform-abgleich.md, .planning/STATE.md]
---
# Quick 261120-bwe: Spiegel 04459bd (ELMonkey PR #3, Kern unter scripts/_kern) in den installierten Skill mergen

Zweig elm-0.10.4-fixes bleibt. 1. `git merge --no-ff origin/main` (Mail lokal mozzi666@gmail.com).
2. Prüfen ohne ELMonkey-Pfad: `env -u PYTHONPATH python3 -I scripts/plattform_abgleich/plattform_abgleich.py bauen --help` → `--verbund` sichtbar.
3. SUMMARY + STATE, Doku-Commit. Nicht pushen.
