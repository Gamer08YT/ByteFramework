#
# Script by JetBrains AI Assistant.
# (I hate Python 😈)
#

import os
import shutil
from pathlib import Path


def kopiere_dateien(quell_pfad, ziel_pfad):
    try:
        # Erstelle den Zielordner, falls er nicht existiert
        Path(ziel_pfad).mkdir(parents=True, exist_ok=True)

        # Hole den absoluten Pfad für das Quellverzeichnis
        quell_pfad = os.path.abspath(os.path.join(os.getcwd(), quell_pfad))

        # Überprüfe, ob das Quellverzeichnis existiert
        if not os.path.exists(quell_pfad):
            raise FileNotFoundError(f"Quellverzeichnis nicht gefunden: {quell_pfad}")

        # Kopiere alle Dateien aus dem Quellverzeichnis
        for item in os.listdir(quell_pfad):
            quell_item = os.path.join(quell_pfad, item)
            ziel_item = os.path.join(ziel_pfad, item)

            if os.path.isfile(quell_item):
                shutil.copy2(quell_item, ziel_item)
                print(f"Kopiert: {item}")
            elif os.path.isdir(quell_item):
                shutil.copytree(quell_item, ziel_item, dirs_exist_ok=True)
                print(f"Kopiert Verzeichnis: {item}")

        print(f"\nAlle Dateien wurden erfolgreich kopiert nach: {ziel_pfad}")

    except Exception as e:
        print(f"Fehler beim Kopieren: {str(e)}")


if __name__ == "__main__":
    # Definiere Quell- und Zielpfade
    quell_pfad = "./data"

    # I know it's dirty but Import("env") is not working for me ;/
    ziel_pfad = os.path.abspath(os.path.join(os.getcwd(), "../../../../data"))



    # Führe das Kopieren aus
    kopiere_dateien(quell_pfad, ziel_pfad)
