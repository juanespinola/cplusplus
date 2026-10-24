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
- `menu_scene.h/.cpp` — menú JUGAR / SALIR, ENTER en JUGAR → `PlayingScene`.
- `playing_scene.h/.cpp` — el juego. Miembros: snake, food, direction, eat, elapsedTime,
  intervalMovement (0.15f s), grid, `static const int cellSize = 10`.
  Movimiento con **acumulador**: `elapsedTime += deltaTime; if (>= interval) { mover; -= interval; }`.
- `timer.h/.cpp` — clase `Timer` (tick / getDeltaTime / restart), delta en **segundos** (float),
  usa `SDL_GetTicks64()`. El constructor llama a `restart()`.
- `char_letras.h/.cpp` — `drawText` / `drawChar` con fuente propia (solo MAYÚSCULAS, espacio y punto).
- `types.h` (Position, Delta), `globals.h` (SCREEN_WIDTH/HEIGHT).
- Loop en `main.cpp`: applyPendingScene → eventos/handleInput → timer.tick → update(deltaTime) →
  clear → render → present.

## Conceptos que ya vimos (no re-explicar desde cero, sí repasar si hace falta)
headers y `#pragma once`; cada archivo incluye lo que usa; declaración (.h) vs definición (.cpp);
stack vs heap; `new`/`delete`, fugas de memoria; punteros (`*`, `&var`) vs referencias (`&` en firma);
`.` vs `->`; shadowing; miembros vs variables locales; inicializar todo (basura en int/float/punteros);
`static const` (solo enteros en el .h; para float → `constexpr`); lista de inicialización (mencionada);
herencia "es un" vs composición "tiene un"; `virtual`/`override`/polimorfismo, `= 0`;
división entera; unidades (ms vs s); deltaTime y acumulador (como Unity / FixedUpdate);
`srand(time(nullptr))`; cambio diferido y transferencia de propiedad (mencioné `unique_ptr`/`std::move` como próximo paso).

## Hecho recientemente
- `collision.h/.cpp`: `pointVsPoint`, `pointInRect` (tablero en **celdas**: columns/rows = grid px / CELL_SIZE).
- En `playing_scene.cpp`: `isHittingWall`, `isHittingSelf` (for desde i=1, early return), `checkFood`.
  `update`: mover → `if (wall || self) { changeScene(new GameOverScene); return; }` → checkFood.
- `gameover_scene.h/.cpp`: "PERDISTE..." + JUGAR / SALIR (JUGAR vuelve a PlayingScene).
- Serpiente arranca con cabeza en {3,3} mirando a la derecha, `direction = {1,0}` (con {0,0} chocaba consigo misma).
- Regla vista: forward declaration en el `.h` solo si el `.h` nombra el tipo; `#include` real en el `.cpp` que lo usa.
- `snake/todo.txt`: lista de **bugs a revisar** con forma de probarlos.

## Pendientes (en orden sugerido)
1. **SIGUIENTE: opción SALIR** (en MenuScene y GameOverScene). Idea guiada: el SceneManager ("recepcionista")
   tiene una "libreta" (bool) — la escena pide salir con un método, `main` la lee en el loop y pone
   `running = false`. Mismo patrón que changeScene (uno pide, otro ejecuta). Alternativa SDL: SDL_PushEvent(SDL_QUIT).
   Le hice 3 preguntas guía (tipo de la libreta, método para anotar, método para leer y dónde) — sin responder aún.
2. Bug en `todo.txt`: giro de 180° con dos teclas rápidas (separar dirección pedida vs. dirección real).
3. Limpieza: `moveSnake`, `generateFood`, `isHitting*`, `checkFood` siguen siendo funciones sueltas;
   `drawSnake`/`drawFood` reciben parámetros que sobran (shadowing con los miembros);
   comentarios viejos ("assuming...") y bloque comentado de `collisionDetection`; código comentado viejo en `main.cpp`;
   `<iostream>` y `collision.h` en `playing_scene.h` (deberían ir en el .cpp);
   `MENU_OPTIONS` duplicado en `globals.h` y `MenuScene`; `;` suelto después de `pointInRect` en collision.cpp;
   couts/destructores de prueba ("Se destruyo ..."); GameOverScene usa `std::cout` sin incluir `<iostream>`.
4. Colisiones a futuro: AABB rect-rect (dejarme deducir: "¿cuándo NO se tocan?"), círculo-círculo.
5. A futuro: puntaje, `unique_ptr`, AddressSanitizer (`-fsanitize=address`), vsync, clase `Snake` propia.
   Después: Pong / Breakout / Tetris.
