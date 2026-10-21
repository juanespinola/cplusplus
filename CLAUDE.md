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

## Pendientes (en orden sugerido)
1. **EN CURSO: archivo de colisiones genérico** `collision.h/.cpp`: funciones puras (sin clase,
   opcional `namespace`), parámetros `const &`, devuelven `bool`.
   Orden: (a) punto-punto (misma celda) → (b) punto dentro de rectángulo (paredes) → (c) AABB rect-rect
   (dejarme deducir la lógica: "¿cuándo NO se tocan?"). Recordar agregar al `CMakeLists.txt`.
   Ojo: el grid está en **píxeles** y la serpiente en **celdas** → hoy la colisión con paredes compara
   unidades mezcladas.
2. Reemplazar `exit(0)` de `collisionDetection` (playing_scene.cpp): al perder mostrar "GAME OVER".
   Opciones discutidas: (A) nueva `GameOverScene` (recomendada) o (B) `bool gameOver` en PlayingScene.
   Separar *detectar* (bool) de *decidir* (la escena en `update`).
3. Agregar choque de la serpiente consigo misma (empezar el for desde el segmento 1, no la cabeza).
4. Opción SALIR del menú (cómo se entera `main` para poner `running = false`).
5. Limpieza: `moveSnake`, `generateFood`, `collisionDetection` siguen siendo funciones sueltas;
   `drawSnake`/`drawFood` reciben parámetros que sobran (shadowing con los miembros);
   `generateFood` tiene números mágicos `% 80` / `% 60`; código comentado viejo en `main.cpp`;
   `<iostream>` está en `playing_scene.h` (debería ir en los .cpp que lo usan);
   `MENU_OPTIONS` duplicado en `globals.h` y `MenuScene`; `class PlayingScene;` sobra en `menu_scene.h`.
6. A futuro: `unique_ptr`, AddressSanitizer (`-fsanitize=address`), vsync, clase `Snake` propia.
