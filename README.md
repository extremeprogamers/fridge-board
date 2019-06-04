# fridge-io


1. Install VSCode / Atom.
2. Install PlatformIO plugin for VSCode / Atom: https://platformio.org/platformio-ide
3. Clone repository.
4. Open VSCode / Atom, choose `Import Arduino Project` and board `Espressif GenericESP8266 ESP-01 1M`.
5. Verify `Build` task ends up with `SUCCESS`.

## Code rules:
- Używamy camel case
- Pliki *.h powinny być tylko szkieletem, cała implementacja w pliku *.cpp
- Nazwy klas i plików z wielkich liter
- Komentarze i kod po angielsku
- Klasy podzielone na pliki *.h i *.cpp
- Klasy testowe z postfixem *_test
- Staramy się unikać używania namespace
- Otwarcie klamry w tej samej linii. Przykład:
```
class Database {
};
```
- Przy stosowaniu namespace nie używamuy spacji. Przykład:
```
bool Database::add(string message) {
}
```
- Nie używamy domyślnych wartości typów prostych