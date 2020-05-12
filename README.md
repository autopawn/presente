# presente

Low budget game for LP

# features a programar

- Carga de niveles
  - Formato de archivo para cargar niveles (y enemigos)
  - Detectar argumento de la línea de comandos con nombre de archivo (sin argumento se genera random).

- Muros destruibles y teleports (entrada y salida)

- Generación procedimental de dungeons
  - Mandarle links

- Inteligencia de los enemigos
  - Caminar hacia el jugador una vez se alertan (el jugador se acerca a un cierto radio)
  - BRUTE va en linea recta
  - MINION acelera hacia el jugador (terminará orbitando)

- Daño de los enemigos
  - Daño de los enemigos y tiempo de inmunidad.

- Sistema de colisiones
  - Entidades colisionan con las paredes, componente perpendicular de la velocidad se pierde.
  - Mandar link.

- Diferentes tipos de armas
  - Botones para cambiar de arma.
  - Sea creativo (melé, más daño, spread shot, radio de explosión).

- Enemigo tipo BOSS
  - Con path finding: A*
  - https://github.com/felselva/uastar

- Enemigos que disparan
  - Balas que dañan al jugador y que no dañan a los enemigos.

- Enemigos que explotan al morir
  - Agregar enemigo que explota (daña jugador y otros enemigos).

- Tilesets para el nivel, inteligentes (comprueban tiles alrededor).

- Sprites para jugador y enemigos.
  - Mostrar la guía del disparo

- Arreglos dinámicos de state y hacer funciones para añadir enemigos.
  - Spawnear enemigos (lejos del jugador)

- Contador de puntaje
  - Guardar Hi-score en game over (crear archivo)
  - Agregar música del DOOM y de game over.

- Power-ups
  - En su lista a parte, sólo interactuan con el jugador.
  - Vida adicional

- GUI
  - Añadir barra de vida del jugador y de los enemigos

 /\_/\
( o.o )
 > ^ <
