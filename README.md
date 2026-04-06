# ProjektPP_METAR

Projekt szkolny służący do automatycznego odczytu i dekodowania lotniczych raportów pogodowych METAR dla lotniska w Gdańsku (EPGD). Program przetwarza surowe depesze tekstowe na sformatowany, czytelny dla użytkownika raport.

### Główne Funkcje
* **Analiza depesz:** Wyodrębnianie daty, czasu UTC oraz ciśnienia QNH.
* **Warunki wiatrowe:** Odczyt kierunku, prędkości (kts) oraz zmienności wiatru.
* **Zjawiska pogodowe:** Identyfikacja opadów (deszcz, śnieg, grad) i ograniczeń widzialności (mgła, zamglenie).
* **Zachmurzenie:** Określenie stopnia pokrycia nieba oraz wysokości podstawy chmur w stopach (ft).
* **Widzialność:** Obsługa widzialności poziomej, w tym komunikatów CAVOK.
* **Archiwizacja:** Automatyczny zapis zdekodowanych danych do pliku wynikowego `pogoda_gd.txt`.

### Obsługa Programu
1. Program wymaga pliku wejściowego `Metar_Gdansk1.txt` umieszczonego w ścieżce zdefiniowanej w kodzie.
2. Po uruchomieniu dostępne są dwie opcje:
    * `o` – Rozpoczęcie analizy i zapisu danych.
    * `q` – Zakończenie pracy programu.
