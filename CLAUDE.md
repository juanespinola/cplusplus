# Contexto para la IA (leer primero)

## Cómo trabajar conmigo — REGLA PRINCIPAL
- **NO escribas ni edites código del proyecto.** Soy quien implementa. Tu rol es de **tutor**:
  ayudarme a razonar, hacer preguntas guía, explicar conceptos y revisar lo que escribo.
- Sí podés: leer mis archivos, compilar para ver errores, señalar bugs explicando el *porqué*,
  dar pistas, pseudocódigo o ideas de diseño. Si me trabo mucho y pido "la respuesta", dámela en
  **pseudocódigo casi-C++** para que yo la pase a código.
- Respondé en **español**. Ir **de a un paso por vez**; si te tiro muchas cosas juntas me mareo.
- Usá analogías (me sirvieron: "casa vs dirección" para punteros, "alcancía" para el acumulador,
  "pintor" para el orden clear→render→present, "recepcionista" para el SceneManager).
- Vengo de C#/Unity: compararlo con Unity me ayuda.

## Proyecto actual: `snake/` (C++17 + SDL2 + CMake)
Arquitectura de escenas ya funcionando:
- `scene.h` — clase base abstracta `Scene` (handleInput / update / render, `virtual` + destructor virtual).
- `scene_manager.h/.cpp` — dueño de las escenas. **Cambio diferido**: `changeScene()` solo anota en
  `pendingScene`; `applyPendingScene()` (llamado al **inicio** de cada vuelta del loop en `main`) hace
  `delete currentScene; currentScene = pendingScene; pendingScene = nullptr;`. Destructor borra ambas.
  Punteros inicializados en `nullptr` en el `.h`.
  **Salir**: `requestQuit()` / `isQuitRequested()` (bool `requestedQuit`); `main` hace
  `while (!sceneManager.isQuitRequested())` y `SDL_QUIT` también llama a `requestQuit()`.
- `menu_scene.h/.cpp` — menú JUGAR / SALIR (SALIR → `requestQuit()`).
- `playing_scene.h/.cpp` — el juego. Miembros: snake, food, direction, eat, elapsedTime,
  intervalMovement (0.15f s), points, grid (derecha), panel (izquierda, muestra "SNAKE" y "POINT" + puntaje),
  `CELL_SIZE = 10`, `COLUMNS`/`ROWS` (celdas), `MARGIN`.
  Movimiento con **acumulador**: `elapsedTime += deltaTime; if (>= interval) { mover; -= interval; }`.
- `timer.h/.cpp` — clase `Timer` (tick / getDeltaTime / getFPS / restart), delta en **segundos** (float),
  usa `SDL_GetTicks64()`. El constructor llama a `restart()`. **FPS** con alcancía en `tick()`:
  `frames++; alcanciaFps += deltaTime; if (>= 1.0) { fps = frames; frames = 0; alcanciaFps -= 1.0; }`.
- `char_letras.h/.cpp` — `drawText` / `drawChar` con fuente propia: MAYÚSCULAS, espacio, punto y
  dígitos 0–9 (tabla `numero[10]`, índice `c - '0'`). Falta un fallback para caracteres desconocidos.
- `types.h` (Position, Delta), `globals.h` (SCREEN_WIDTH/HEIGHT).
- Loop en `main.cpp`: applyPendingScene → eventos/handleInput → timer.tick → update(deltaTime) →
  clear → render → **dibuja "FPS N" abajo a la izquierda** (overlay, todas las escenas) → present.
  **VSync** activado con `SDL_RenderSetVSync(renderer, 1)` (0 = éxito): bajó de ~1000 FPS a 60, la CPU ya no se calienta.

## Conceptos que ya vimos (no re-explicar desde cero, sí repasar si hace falta)
headers y `#pragma once`; cada archivo incluye lo que usa; declaración (.h) vs definición (.cpp);
stack vs heap; `new`/`delete`, fugas de memoria; punteros (`*`, `&var`) vs referencias (`&` en firma);
`.` vs `->`; shadowing; miembros vs variables locales; inicializar todo (basura en int/float/punteros);
`static const` (solo enteros en el .h; para float → `constexpr`); lista de inicialización (mencionada);
herencia "es un" vs composición "tiene un"; `virtual`/`override`/polimorfismo, `= 0`;
división entera; unidades (ms vs s); deltaTime y acumulador (como Unity / FixedUpdate);
`srand(time(nullptr))`; cambio diferido y transferencia de propiedad (mencioné `unique_ptr`/`std::move` como próximo paso);
`char` es un número (ASCII): `c - '0'` / `'0' + n`; `std::to_string` + `.c_str()`; `<string>` vs `<string.h>` (C);
`x++` (suma 1) vs `x += v` (acumula) vs `x = v` (pisa); `frames = frames++` no suma;
VSync / FPS como dato del motor (no de la escena); convención SDL "0 = éxito" y `if(int)`;
paso por valor (copia) vs por referencia (bug real: `int points` sin `&` no sumaba); includes "de regalo"
(sacar `<iostream>` de `playing_scene.h` rompió Menu/GameOver que usaban `cout` sin incluirlo).

## Hecho recientemente
- **VSync + contador de FPS** en `Timer`, dibujado desde `main` (ver arriba).
- **SALIR** funcionando (patrón "libreta" del SceneManager, ver arriba).
- **Panel** lateral izquierdo + **puntaje**: `points` (miembro, = 0 en el constructor), `checkFood(..., int &points)`
  hace `points++`, `drawPanel` lo dibuja con `std::to_string(points).c_str()`.
- `collision.h/.cpp`: `pointVsPoint`, `pointInRect` (tablero en **celdas**).
- `update`: mover → `if (wall || self) { changeScene(new GameOverScene); return; }` → checkFood.
- `gameover_scene.h/.cpp`: "PERDISTE..." + JUGAR / SALIR.
- Regla vista: forward declaration en el `.h` solo si el `.h` nombra el tipo; `#include` real en el `.cpp` que lo usa.
- `snake/todo.txt`: lista de **bugs a revisar** con forma de probarlos.

## Pendientes (en orden sugerido)
1. Detalles del FPS: `main.cpp` usa `std::string` sin `#include <string>`; spacing 0 en `drawText` (letras pegadas);
   fallback en `getLetraMayuscula` para caracteres fuera de la fuente (minúsculas, ':' → índice fuera del array).
2. **SIGUIENTE:** Bug en `todo.txt`: giro de 180° con dos teclas rápidas (separar dirección pedida vs. dirección real).
3. Limpieza: `moveSnake`, `generateFood`, `isHitting*`, `checkFood` siguen siendo funciones sueltas;
   `drawSnake`/`drawFood` reciben parámetros que sobran (shadowing con los miembros);
   comentarios viejos ("assuming...") y bloque comentado de `collisionDetection`; código comentado viejo en `main.cpp`;
   `<iostream>` (marcado "sacar más adelante") y `collision.h` en `playing_scene.h` — al sacarlo, Menu/GameOver
   necesitan su propio `<iostream>` o borrar sus couts de prueba; `MENU_OPTIONS` duplicado en `globals.h` y `MenuScene`;
   `;` suelto después de funciones en collision.cpp / char_letras.cpp; `c >= 48 && c <= 57` → `'0'..'9'`;
   `Untitled-1.cpp` suelto en `snake/`.
4. Colisiones a futuro: AABB rect-rect (dejarme deducir: "¿cuándo NO se tocan?"), círculo-círculo.
5. A futuro: guardar récord, `unique_ptr`, AddressSanitizer (`-fsanitize=address`), clase `Snake` propia.
   Después: Pong / Breakout / Tetris.
