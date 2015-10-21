//-----------------------------LICENSE NOTICE------------------------------------
//  This file is part of TopTop: An Amstrad CPC Game
//  Copyright (C) 2015 Rantan (@RantanGames)
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.
//------------------------------------------------------------------------------

#include <cpctelera.h>
#include "game.h"
#include "../sprites/sprites.h"
#include "../sprites/animation.h"
#include "../entities/shot.h"
#include "../entities/heroe.h"
#include "../constants.h"
#include "../maps/maps.h"
#include "../audio/audio.h"

#define G_NUM_REDRAW 32
#define G_DONT_REDRAW 255

struct Heroe heroe1;
struct Heroe heroe2;

struct Shot shots1[G_maxShots];
struct Shot shots2[G_maxShots];

u8 map1[G_mapHTiles][G_mapWTiles];
u8 map2[G_mapHTiles][G_mapWTiles];

u8 mapRedraw1[G_NUM_REDRAW];
u8 mapRedraw2[G_NUM_REDRAW];

u8 doorLevel1;
u8 doorLevel2;

u8 blueDoor[G_maxButtons][2];
u8 redDoor[G_maxButtons][2];

u8 blueButton[G_maxButtons][2];
u8 redButton[G_maxButtons][2];

extern u8* const G_SCR_VMEM = (u8*)0xC000; 

u8* const g_scrbuffers[2] = { (u8*)0xC000, (u8*)0x8000 }; // Direccion de los dos buffers

u8 level;

u8 redrawHearts;

// Inicializa el menu
void initGame() {
   u8 x, y, i;

   level = 0;
   redrawHearts = 0;
   doorLevel1 = 0;
   doorLevel2 = 0;

   for(i=0; i<G_maxButtons; i++) {
      blueButton[i][0] = G_outsideMap;    // Coordenada del boton, en principio no estan en el mapa
      blueButton[i][1] = 0;               // Estado del boton -> 0 = Desactivado, 1 = Activado

      redButton[i][0] = G_outsideMap;
      redButton[i][1] = 0;
   }

   // Inicializamos el audio
   cpct_akp_musicInit(G_toptop_effects); 

   //cpct_akp_musicInit(G_toptop_effects); 
   cpct_akp_SFXInit(G_toptop_effects);

   // Lee y prepara los mapas
   for(y=0; y<G_mapHTiles; y++) {
      for(x=0; x<G_mapWTiles; x++) {
         // Obtenemos los datos de nuestros mapas
         //map1[y][x] = G_map01[y*G_mapWTiles+x];
         map1[y][x] = G_map07[y*G_mapWTiles+x];
         map2[y][x] = G_map08[y*G_mapWTiles+x];

         // Guardamos coordenadas de distintos elementos del mapa
         switch(map1[y][x]) {
            case 0x1A: doorLevel1 = tile2tile1(x, y); break;               // << Puertas fin de nivel

            case 0x2A: redDoor[0][0] = tile2tile1(x, y); break;            // << Puertas intermedias
            case 0x32: redDoor[0][1] = tile2tile1(x, y); break;            // |
            case 0x3C: redDoor[1][0] = tile2tile1(x, y); break;            // |
            case 0x44: redDoor[1][1] = tile2tile1(x, y); break;            // |
            case 0x4E: redDoor[2][0] = tile2tile1(x, y); break;            // |
            case 0x56: redDoor[2][1] = tile2tile1(x, y); break;            // |

            case 0x5E: blueButton[0][0] = tile2tile1(x, y); break;         // << Botones
            case 0x70: blueButton[1][0] = tile2tile1(x, y); break;         // |
            case 0x82: blueButton[2][0] = tile2tile1(x, y); break;         // |
         }

         // Guardamos coordenadas de distintos elementos del mapa
         switch(map2[y][x]) {
            case 0x1E: doorLevel2 = tile2tile1(x, y); break;               // << Puertas fin de nivel

            case 0x60: blueDoor[0][0] = tile2tile1(x, y); break;           // << Puertas intermedias
            case 0x68: blueDoor[0][1] = tile2tile1(x, y); break;           // |
            case 0x72: blueDoor[1][0] = tile2tile1(x, y); break;           // |
            case 0x7A: blueDoor[1][1] = tile2tile1(x, y); break;           // |
            case 0x84: blueDoor[2][0] = tile2tile1(x, y); break;           // |
            case 0x8C: blueDoor[2][1] = tile2tile1(x, y); break;           // |

            case 0x28: redButton[0][0] = tile2tile1(x, y); break;          // << Botones
            case 0x3A: redButton[1][0] = tile2tile1(x, y); break;          // |
            case 0x4C: redButton[2][0] = tile2tile1(x, y); break;          // |
         }
      }
   }

   for(x=0; x<G_NUM_REDRAW; x++) {
      mapRedraw1[x] = G_DONT_REDRAW;
      mapRedraw2[x] = G_DONT_REDRAW;
   }

	drawGameBorder();

   // Inicializamos todas las entidades...
   initHeroes(&heroe1, &heroe2);
   initShots(shots1);
   initShots(shots2);

   // Preparamos el double buffer y dibujamos...
   cpct_memset_f64(g_scrbuffers[1], 0x00, 0x4000); // Limpiamos el segundo buffer (contiene valores aleatorios)
   cpct_waitVSYNC();                               // Esperamos al VSYNC para esperar a dibujar
   firstDraw();                                    // Dibujamos en el buffer actual
   cpct_waitVSYNC();                               // Volvemos a esperar al VSYNC
   swapBuffers(g_scrbuffers);                      // Cambiamos de buffer
   firstDraw();                                    // Dibujamos en este buffer
}

// Dibuja todo lo que habra en pantalla al comenzar la partida
void firstDraw() {
   drawGameBorder();
   drawMap();
   drawHeroes();
   drawHUD();
}

// Update del menu
u8 updateGame() {
   // ---------------------------------------------------------------------------------------------------
   cpct_waitVSYNC(); //---------- Comienza Primer Frame (para actualizar entidades, 1 vez cada 2 frames)

   // Reproduce musica (1 vez cada frame)
   cpct_akp_musicPlay(); 

   // Actualiza entidades
   updateHeroe(&heroe1);
   updateHeroe(&heroe2);
   updateShots(&heroe1, shots1);
   updateShots(&heroe2, shots2);

   checkNextLevel();
   
   // ---------------------------------------------------------------------------------------------------
   cpct_waitVSYNC(); // ---------- Comienza Segundo Frame (para redibujar elementos, 1 vez cada 2 frames)
   
   // Reproduce musica (1 vez cada frame)
   cpct_akp_musicPlay(); // La musica se reproduce cada frame

   // Redibuja tiles ocupados por Heroes
   repaintBackgroundOverSprite(heroe1.preX[0], heroe1.preY[0], G_left);
   repaintBackgroundOverSprite(heroe2.preX[0], heroe2.preY[0], G_right);

   // Redibuja tiles ocupados por Disparos
   repaintBackgroundOverShot(shots1, G_left);
   repaintBackgroundOverShot(shots2, G_right);
   
   // Dibuja entidades
   drawHeroes();
   drawShots();

   // Intercambia buffer de dibujado
   swapBuffers(g_scrbuffers);
   
   // Redibuja tiles que han cambiado
   redrawTiles(G_left);
   redrawTiles(G_right);

   redrawHUD();
   
	return G_sceneGame;
}

void updateHeroe(struct Heroe *heroe) {
   // Cambiamos la variable en la que guardamos la posicion previa.
   // Usamos dos variables para saber donde limpiar el rastro en cada buffer
   swapPrePos(heroe);
   heroe->preX[1] = heroe->x;
   heroe->preY[1] = heroe->y;

   // Scan Keyboard
   cpct_scanKeyboard_f();

   // Correr
   if (((cpct_isKeyPressed(Key_A) && heroe->id == G_heroe1) || (cpct_isKeyPressed(Key_CursorLeft) && heroe->id == G_heroe2)) && heroe->x > 0) {
      // Izquierda
      heroe->x--;
      heroe->side = G_left;
      if(heroe->stateY == sy_land) {
         // Ani Run
         setAniHeroe(heroe, 1); 
      }
      else if(heroe->stateY == sy_duck)  {
         // Ani Duck Run
         setAniHeroe(heroe, 5);
      }
      heroe->readyNextLevel = 0;
   }
   else if (((cpct_isKeyPressed(Key_D) && heroe->id == G_heroe1) || (cpct_isKeyPressed(Key_CursorRight) && heroe->id == G_heroe2)) && heroe->x < G_mapWBytes - G_heroeW) {
      // Derecha
      level++;
      heroe->x++;
      heroe->side = G_right;
      if(heroe->stateY == sy_land) {
         // Ani Run
         setAniHeroe(heroe, 1);
      }
      else if(heroe->stateY == sy_duck)  {
         // Ani Duck Run
         setAniHeroe(heroe, 5);
      }
      heroe->readyNextLevel = 0;
   }
   else {
      if(heroe->stateY == sy_land) {
         // Ani Idle
         setAniHeroe(heroe, 0);
      }
      else if(heroe->stateY == sy_duck)  {
         // Ani Duck
         setAniHeroe(heroe, 4);
      }
   }

   // Agachar
   if ((cpct_isKeyPressed(Key_S) && heroe->id == G_heroe1) || (cpct_isKeyPressed(Key_CursorDown) && heroe->id == G_heroe2)) {
      heroe->duckPressed = 1;
      // Si esta en el suelo, se puede agachar
      if(heroe->stateY == sy_land) {
         heroe->stateY = sy_duck;
      }
      heroe->readyNextLevel = 0;
   }
   else {
      heroe->duckPressed = 0;
   }

   // Saltar
   if ((cpct_isKeyPressed(Key_F) && heroe->id == G_heroe1) || (cpct_isKeyPressed(Key_O) && heroe->id == G_heroe2)) {
      if(heroe->stateY != sy_duck) {
         if(heroe->jumpPressed == 0) {
            heroe->jumpPressed = 1;
            // Si estaba en el suelo, salta
            if(heroe->stateY == sy_land) {
               // Reproducimos el efecto de sonido SALTAR
               cpct_akp_SFXPlay(1, 15, 50, 0, 0, AY_CHANNEL_B);  //parametros: numero del instrumento, volumen [0-15], nota tocada, velocidad (0=original), inverted pitch (0=no pitch), numero del canal (0, 1, 2)
               heroe->stateY = sy_jump;
               heroe->jumpFactor = 0;
            }
         }
      }
      heroe->readyNextLevel = 0;
   }
   else {
      heroe->jumpPressed = 0;
      // Si estaba saltando, cae
      if(heroe->stateY == sy_jump && heroe->jumpFactor < 5) {
         heroe->jumpFactor = 5;
      }
   } 

   updateJump(heroe);

   if(heroe->stateY == sy_jump) {
      // Ani Jump
      setAniHeroe(heroe, 2);
   }
   else if(heroe->stateY == sy_fall) {
      // Ani Fall
      setAniHeroe(heroe, 3);
   }

   if(heroe->id == G_heroe1) {
      checkHeroeCollision(heroe, &map1[0][0]);
      interactWithItems(heroe, &map1[0][0], heroe->sensorCT);
      interactWithItems(heroe, &map1[0][0], heroe->sensorCC);
      interactWithDoors(heroe, &map1[0][0]);

      //Disparar
      if(cpct_isKeyPressed(Key_G)) {
         if(heroe->shotPressed == 0) {
            heroe->shotPressed = 1;
            createShot(heroe, shots1);
         }
         heroe->readyNextLevel = 0;
      }
      else {
         heroe->shotPressed = 0;
      }   
   }
   else {
      checkHeroeCollision(heroe, &map2[0][0]);
      interactWithItems(heroe, &map2[0][0], heroe->sensorCT);
      interactWithItems(heroe, &map2[0][0], heroe->sensorCC);
      interactWithDoors(heroe, &map2[0][0]);

      //Disparar
      if(cpct_isKeyPressed(Key_P)) {
         if(heroe->shotPressed == 0) {
            heroe->shotPressed = 1;
            createShot(heroe, shots2);
         }
         heroe->readyNextLevel = 0;
      }
      else {
         heroe->shotPressed = 0;
      }  
   }

   updateCooldown(heroe);

   updateAnimation(&heroe->anim, heroe->nextAnim, 0);
}

// Comprueba las colisiones entre un heroe y tiles
void checkHeroeCollision(struct Heroe *heroe, u8 *map) {
   u8 isColliding;

   // -- Colisiones Verticales
   // Se comprueban hasta que deje de colisionar
   do {
      isColliding = 0;
      updateSensorHeroe(heroe);
      // Colisiones con tiles superiores
      if(map[heroe->sensorTL] == 0x00 || map[heroe->sensorTR] == 0x00 ||
         map[heroe->sensorTL] == 0x05 || map[heroe->sensorTR] == 0x05 ||
         map[heroe->sensorTL] == 0x06 || map[heroe->sensorTR] == 0x06 ||
         map[heroe->sensorTL] == 0x07 || map[heroe->sensorTR] == 0x07) {
         if(heroe->stateY == sy_jump || heroe->stateY == sy_fall) { 
            isColliding = 1;
            heroe->y = (heroe->sensorTL / G_mapWTiles) * G_tileSizeH + G_tileSizeH-1;
            heroe->jumpFactor = G_jumpSize-1;
            heroe->stateY = sy_fall;
         }
      }

      // Colision con el limite superior del mapa
      if(heroe->y > 200) {
         isColliding = 1;
         heroe->y = 0;
         heroe->jumpFactor = G_jumpSize-1;
         heroe->stateY = sy_fall;
      }

      // Colisiones con tiles inferiores
      if(map[heroe->sensorDL] == 0x00 || map[heroe->sensorDR] == 0x00 ||
         map[heroe->sensorDL] == 0x05 || map[heroe->sensorDR] == 0x05 ||
         map[heroe->sensorDL] == 0x06 || map[heroe->sensorDR] == 0x06 ||
         map[heroe->sensorDL] == 0x07 || map[heroe->sensorDR] == 0x07) {
         if(heroe->stateY != sy_jump) {
            isColliding = 1;
            heroe->y = (heroe->sensorDL / G_mapWTiles) * G_tileSizeH - G_heroeH;
            heroe->stateY = sy_land;
         }
      }

      // Colisiones con el limite inferior del mapa
      if(heroe->y > G_mapHTiles * G_tileSizeH - G_heroeH) {
         isColliding = 1;
         heroe->y = G_mapHTiles * G_tileSizeH - G_heroeH;
         if(heroe->stateY == sy_fall) {
            heroe->stateY = sy_land;
         }
      }
   } while(isColliding != 0);

   // Detectamos si hay suelo debajo nuestra para caer o no
   if(map[heroe->sensorDL+8] != 0x00 && map[heroe->sensorDR+8] != 0x00 &&
      map[heroe->sensorDL+8] != 0x05 && map[heroe->sensorDR+8] != 0x05 &&
      map[heroe->sensorDL+8] != 0x06 && map[heroe->sensorDR+8] != 0x06 &&
      map[heroe->sensorDL+8] != 0x07 && map[heroe->sensorDR+8] != 0x07) {
      if(heroe->y < G_mapHTiles * G_tileSizeH - G_heroeH) {
         if(heroe->stateY != sy_jump && heroe->stateY != sy_fall) {
            heroe->stateY = sy_fall;
            heroe->jumpFactor = G_jumpSize - 2;
            updateSensorHeroe(heroe);
            // Colisiones con tiles superiores
            if(map[heroe->sensorTL] == 0x00 || map[heroe->sensorTR] == 0x00 ||
               map[heroe->sensorTL] == 0x05 || map[heroe->sensorTR] == 0x05 ||
               map[heroe->sensorTL] == 0x06 || map[heroe->sensorTR] == 0x06 ||
               map[heroe->sensorTL] == 0x07 || map[heroe->sensorTR] == 0x07) {
               if(heroe->stateY == sy_jump || heroe->stateY == sy_fall) { 
                  heroe->y = (heroe->sensorTL / G_mapWTiles) * G_tileSizeH + G_tileSizeH-1;
                  updateSensorHeroe(heroe);
               }
            }
         }
      }
   }

   // Detectamos si podemos dejar de estar agachados (si queremos)
   if(heroe->stateY == sy_duck) {
      // Si hemos soltado la tecla de agachar y no colisionamos con nada al levantarnos...
      if(heroe->duckPressed == 0) {
         if(map[heroe->sensorTL] != 0x00 && map[heroe->sensorTR] != 0x00 &&
            map[heroe->sensorTL] != 0x05 && map[heroe->sensorTR] != 0x05 &&
            map[heroe->sensorTL] != 0x06 && map[heroe->sensorTR] != 0x06 &&
            map[heroe->sensorTL] != 0x07 && map[heroe->sensorTR] != 0x07) {
            heroe->stateY = sy_land;
            // Ani Idle
            setAniHeroe(heroe, 0);
         }
      }
   }

   // -- Colisiones Horizontales
   // Colisiones con tiles a la izquierda
   if((heroe->stateY != sy_duck && (map[heroe->sensorLT] == 0x00 || map[heroe->sensorLT] == 0x05 || map[heroe->sensorLT] == 0x06 || map[heroe->sensorLT] == 0x07)) ||
      map[heroe->sensorLC] == 0x00 || map[heroe->sensorLC] == 0x05 || map[heroe->sensorLC] == 0x06 || map[heroe->sensorLC] == 0x07 ||
      map[heroe->sensorLD] == 0x00 || map[heroe->sensorLD] == 0x05 || map[heroe->sensorLD] == 0x06 || map[heroe->sensorLD] == 0x07) {
      heroe->x = ((heroe->sensorLC - ((heroe->sensorLC / G_mapWTiles) * G_mapWTiles)) * G_tileSizeW) + G_tileSizeW;
      if(heroe->stateY == sy_land) {
         // Ani Idle
         setAniHeroe(heroe, 0);
      }
   }

   // Colisiones con tiles a la derecha
   if((heroe->stateY != sy_duck && (map[heroe->sensorRT] == 0x00 || map[heroe->sensorRT] == 0x05 || map[heroe->sensorRT] == 0x06 || map[heroe->sensorRT] == 0x07)) ||
      map[heroe->sensorRC] == 0x00 || map[heroe->sensorRC] == 0x05 || map[heroe->sensorRC] == 0x06 || map[heroe->sensorRC] == 0x07 ||
      map[heroe->sensorRD] == 0x00 || map[heroe->sensorRD] == 0x05 || map[heroe->sensorRD] == 0x06 || map[heroe->sensorRD] == 0x07) {
      heroe->x = ((heroe->sensorRC - ((heroe->sensorRC / G_mapWTiles) * G_mapWTiles)) * G_tileSizeW) - G_tileSizeW;
      if(heroe->stateY == sy_land) {
         // Ani Idle
         setAniHeroe(heroe, 0);
      }
   }

   if(map[heroe->sensorDL] == 0x08 || map[heroe->sensorDR] == 0x08) {   // HAY PINCHOS
      if(heroe->cooldown == 0) {
         heroe->health--;
         heroe->cooldown = G_Cooldown;
         drawHearts();
         redrawHearts = 1;
         // SFX
         if(heroe->id == G_heroe1) cpct_akp_SFXPlay(2, 15, 64, 0, 0, AY_CHANNEL_B); //nota que se toca: E-5 = MI5 = 64
         else cpct_akp_SFXPlay(2, 15, 59, 0, 0, AY_CHANNEL_B); //nota que se toca: B-4 = SI4 = 59
      }
   }
}

void interactWithItems(struct Heroe *heroe, u8 *map, u8 sensor) {
   u8 x, y, side, xDoor, yDoor;

   if(heroe->id == G_heroe1) side = G_left;
   else side = G_right;

   y = sensor / G_mapWTiles;
   x = sensor % G_mapWTiles;

   // Colisiona con items e interruptores
   if(map[sensor] == 0x01 || map[sensor] == 0x02) {  // POCION DE CURACION
      heroe->health++;
      drawHearts();
      redrawHearts = 1;
      changeTile(x, y, side, 0xFF);
      // SFX
      cpct_akp_SFXPlay(3, 15, 50, 0, 0, AY_CHANNEL_B); //nota que se toca: D-4 = RE4 = 50
   }
   else if(map[sensor] == 0x03) {  // POCION AMARILLA
      // Logica pocion amarilla
      changeTile(x, y, side, 0xFF);
      // SFX
      cpct_akp_SFXPlay(3, 15, 50, 0, 0, AY_CHANNEL_B); //nota que se toca: D-4 = RE4 = 50
   }
   else if(map[sensor] == 0x04) {  // LLAVE
      if(heroe->id == G_heroe1) {
         xDoor = doorLevel1 % G_mapWTiles;
         yDoor = doorLevel1 / G_mapWTiles;

         changeTile(xDoor, yDoor, G_left, 0x22);
         changeTile(xDoor+1, yDoor, G_left, 0x23);
         changeTile(xDoor, yDoor-1, G_left, 0x20);
         changeTile(xDoor+1, yDoor-1, G_left, 0x21);
      }
      else {
         xDoor = doorLevel2 % G_mapWTiles;
         yDoor = doorLevel2 / G_mapWTiles;

         changeTile(xDoor, yDoor, G_right, 0x26);
         changeTile(xDoor+1, yDoor, G_right, 0x27);
         changeTile(xDoor, yDoor-1, G_right, 0x24);
         changeTile(xDoor+1, yDoor-1, G_right, 0x25);
      }
      changeTile(x, y, side, 0xFF);
      // SFX
      cpct_akp_SFXPlay(4, 15, 76, 0, 0, AY_CHANNEL_B); //nota que se toca: E-6 = MI6 = 76
   }
}

void interactWithDoors(struct Heroe *heroe, u8 *map) {
   u8 x, y, side, xDoor, yDoor, xDoor2, yDoor2, i;

   if(heroe->id == G_heroe1) side = G_left;
   else side = G_right;

   y = heroe->sensorCC / G_mapWTiles;
   x = heroe->sensorCC % G_mapWTiles;

   // Colisiona con puerta nivel
   if(map[heroe->sensorCC] == 0x22 || map[heroe->sensorCC] == 0x23 || map[heroe->sensorCC] == 0x26 || map[heroe->sensorCC] == 0x27) {
      if ((cpct_isKeyPressed(Key_W) && heroe->id == G_heroe1) || (cpct_isKeyPressed(Key_CursorUp) && heroe->id == G_heroe2)) {
         heroe->readyNextLevel = 1;
      }
   }

   if(heroe->id == G_heroe1) {   // Jugador 1
      if (cpct_isKeyPressed(Key_W)) {
         if(heroe->upPressed == 0) {
            for(i=0; i<G_maxButtons; i++) {
               heroe->upPressed = 1;
               if(redButton[i][1] == 1) {
                  if(heroe->sensorCC == redDoor[i][0] || heroe->sensorCC == redDoor[i][0]+1 || heroe->sensorCC == redDoor[i][0]+G_mapWTiles || heroe->sensorCC == redDoor[i][0]+G_mapWTiles+1) {
                     heroe->x = (redDoor[i][1] % G_mapWTiles) * G_tileSizeW + 2;
                     heroe->y = (redDoor[i][1] / G_mapWTiles) * G_tileSizeH + 4;
                     // SFX ENTRAR PUERTA
                     cpct_akp_SFXPlay(8, 15, 24, 0, 0, AY_CHANNEL_A); //nota que se toca: C-3 = DO3 = 24
                  }
                  else if(heroe->sensorCC == redDoor[i][1] || heroe->sensorCC == redDoor[i][1]+1 || heroe->sensorCC == redDoor[i][1]+G_mapWTiles || heroe->sensorCC == redDoor[i][1]+G_mapWTiles+1) {
                     heroe->x = (redDoor[i][0] % G_mapWTiles) * G_tileSizeW + 2;
                     heroe->y = (redDoor[i][0] / G_mapWTiles) * G_tileSizeH + 4;
                     // SFX ENTRAR PUERTA
                     cpct_akp_SFXPlay(8, 15, 24, 0, 0, AY_CHANNEL_A); //nota que se toca: C-3 = DO3 = 24
                  }
               }
            }
         }
      }
      else {
         heroe->upPressed = 0;
      }
   }
   else {      // Jugador 2
      if (cpct_isKeyPressed(Key_CursorUp)) {
         if(heroe->upPressed == 0) {
            for(i=0; i<G_maxButtons; i++) {
               heroe->upPressed = 1;
               if(blueButton[i][1] == 1) {
                  if(heroe->sensorCC == blueDoor[i][0] || heroe->sensorCC == blueDoor[i][0]+1 || heroe->sensorCC == blueDoor[i][0]+G_mapWTiles || heroe->sensorCC == blueDoor[i][0]+G_mapWTiles+1) {
                     heroe->x = (blueDoor[i][1] % G_mapWTiles) * G_tileSizeW + 2;
                     heroe->y = (blueDoor[i][1] / G_mapWTiles) * G_tileSizeH + 4;
                     // SFX ENTRAR PUERTA
                     cpct_akp_SFXPlay(8, 15, 24, 0, 0, AY_CHANNEL_C); //nota que se toca: C-3 = DO3 = 24
                  }
                  else if(heroe->sensorCC == blueDoor[i][1] || heroe->sensorCC == blueDoor[i][1]+1 || heroe->sensorCC == blueDoor[i][1]+G_mapWTiles || heroe->sensorCC == blueDoor[i][1]+G_mapWTiles+1) {
                     heroe->x = (blueDoor[i][0] % G_mapWTiles) * G_tileSizeW + 2;
                     heroe->y = (blueDoor[i][0] / G_mapWTiles) * G_tileSizeH + 4;
                     // SFX ENTRAR PUERTA
                     cpct_akp_SFXPlay(8, 15, 24, 0, 0, AY_CHANNEL_C); //nota que se toca: C-3 = DO3 = 24
                  }
               }
            }
         }
      }
      else {
         heroe->upPressed = 0;
      }
   }

   // Botones azules
   if(heroe->id == G_heroe1) {   // Jugador 1
      for(i=0; i<G_maxButtons; i++) {
         // Si el boton se encuentra en el mapa...
         if(blueButton[i][0] != G_outsideMap) {
            if(blueButton[i][1] == 0) {   // Si el boton no esta pulsado...
               if(heroe->sensorCC == blueButton[i][0]) {  // Y estoy sobre el...
                  blueButton[i][1] = 1;   // Lo activo
                  changeTile(blueButton[i][0] % G_mapWTiles, blueButton[i][0] / G_mapWTiles, side, map[blueButton[i][0]]+1);

                  xDoor = blueDoor[i][0] % G_mapWTiles;
                  yDoor = blueDoor[i][0] / G_mapWTiles;
                  xDoor2 = blueDoor[i][1] % G_mapWTiles;
                  yDoor2 = blueDoor[i][1] / G_mapWTiles;

                  changeTile(xDoor, yDoor, G_right, map2[yDoor][xDoor]+4);
                  changeTile(xDoor+1, yDoor, G_right, map2[yDoor][xDoor+1]+4);
                  changeTile(xDoor, yDoor+1, G_right, map2[yDoor+1][xDoor]+4);
                  changeTile(xDoor+1, yDoor+1, G_right, map2[yDoor+1][xDoor+1]+4);

                  changeTile(xDoor2, yDoor2, G_right, map2[yDoor2][xDoor2]+4);
                  changeTile(xDoor2+1, yDoor2, G_right, map2[yDoor2][xDoor2+1]+4);
                  changeTile(xDoor2, yDoor2+1, G_right, map2[yDoor2+1][xDoor2]+4);
                  changeTile(xDoor2+1, yDoor2+1, G_right, map2[yDoor2+1][xDoor2+1]+4);

                  //SFX PULSAR
                  cpct_akp_SFXPlay(7, 15, 36, 0, 0, AY_CHANNEL_A); //nota que se toca: C-4 = DO4 = 36
               }
            }
            else if(blueButton[i][1] == 1) {   // Si el boton esta pulsado...
               if(heroe->sensorCC != blueButton[i][0]) {  // Y no estoy sobre el...
                  blueButton[i][1] = 0;   // Lo desactivo
                  changeTile(blueButton[i][0] % G_mapWTiles, blueButton[i][0] / G_mapWTiles, side, map[blueButton[i][0]]-1);

                  xDoor = blueDoor[i][0] % G_mapWTiles;
                  yDoor = blueDoor[i][0] / G_mapWTiles;
                  xDoor2 = blueDoor[i][1] % G_mapWTiles;
                  yDoor2 = blueDoor[i][1] / G_mapWTiles;

                  changeTile(xDoor, yDoor, G_right, map2[yDoor][xDoor]-4);
                  changeTile(xDoor+1, yDoor, G_right, map2[yDoor][xDoor+1]-4);
                  changeTile(xDoor, yDoor+1, G_right, map2[yDoor+1][xDoor]-4);
                  changeTile(xDoor+1, yDoor+1, G_right, map2[yDoor+1][xDoor+1]-4);

                  changeTile(xDoor2, yDoor2, G_right, map2[yDoor2][xDoor2]-4);
                  changeTile(xDoor2+1, yDoor2, G_right, map2[yDoor2][xDoor2+1]-4);
                  changeTile(xDoor2, yDoor2+1, G_right, map2[yDoor2+1][xDoor2]-4);
                  changeTile(xDoor2+1, yDoor2+1, G_right, map2[yDoor2+1][xDoor2+1]-4);

                  //SFX DESPULSAR
                  cpct_akp_SFXPlay(7, 15, 24, 0, 0, AY_CHANNEL_A); //nota que se toca: C-3 = DO3 = 24
               }
            }
         }
      }
   }
   else {   // Jugador 2
      for(i=0; i<G_maxButtons; i++) {
         // Si el boton se encuentra en el mapa...
         if(redButton[i][0] != G_outsideMap) {
            if(redButton[i][1] == 0) {   // Si el boton no esta pulsado...
               if(heroe->sensorCC == redButton[i][0]) {  // Y estoy sobre el...
                  redButton[i][1] = 1;   // Lo activo
                  changeTile(redButton[i][0] % G_mapWTiles, redButton[i][0] / G_mapWTiles, side, map[redButton[i][0]]+1);

                  xDoor = redDoor[i][0] % G_mapWTiles;
                  yDoor = redDoor[i][0] / G_mapWTiles;
                  xDoor2 = redDoor[i][1] % G_mapWTiles;
                  yDoor2 = redDoor[i][1] / G_mapWTiles;

                  changeTile(xDoor, yDoor, G_left, map1[yDoor][xDoor]+4);
                  changeTile(xDoor+1, yDoor, G_left, map1[yDoor][xDoor+1]+4);
                  changeTile(xDoor, yDoor+1, G_left, map1[yDoor+1][xDoor]+4);
                  changeTile(xDoor+1, yDoor+1, G_left, map1[yDoor+1][xDoor+1]+4);

                  changeTile(xDoor2, yDoor2, G_left, map1[yDoor2][xDoor2]+4);
                  changeTile(xDoor2+1, yDoor2, G_left, map1[yDoor2][xDoor2+1]+4);
                  changeTile(xDoor2, yDoor2+1, G_left, map1[yDoor2+1][xDoor2]+4);
                  changeTile(xDoor2+1, yDoor2+1, G_left, map1[yDoor2+1][xDoor2+1]+4);

                  //SFX PULSAR
                  cpct_akp_SFXPlay(7, 15, 36, 0, 0, AY_CHANNEL_C); //nota que se toca: C-4 = DO4 = 36
               }
            }
            else if(redButton[i][1] == 1) {   // Si el boton esta pulsado...
               if(heroe->sensorCC != redButton[i][0]) {  // Y no estoy sobre el...
                  redButton[i][1] = 0;   // Lo desactivo
                  changeTile(redButton[i][0] % G_mapWTiles, redButton[i][0] / G_mapWTiles, side, map[redButton[i][0]]-1);

                  xDoor = redDoor[i][0] % G_mapWTiles;
                  yDoor = redDoor[i][0] / G_mapWTiles;
                  xDoor2 = redDoor[i][1] % G_mapWTiles;
                  yDoor2 = redDoor[i][1] / G_mapWTiles;

                  changeTile(xDoor, yDoor, G_left, map1[yDoor][xDoor]-4);
                  changeTile(xDoor+1, yDoor, G_left, map1[yDoor][xDoor+1]-4);
                  changeTile(xDoor, yDoor+1, G_left, map1[yDoor+1][xDoor]-4);
                  changeTile(xDoor+1, yDoor+1, G_left, map1[yDoor+1][xDoor+1]-4);

                  changeTile(xDoor2, yDoor2, G_left, map1[yDoor2][xDoor2]-4);
                  changeTile(xDoor2+1, yDoor2, G_left, map1[yDoor2][xDoor2+1]-4);
                  changeTile(xDoor2, yDoor2+1, G_left, map1[yDoor2+1][xDoor2]-4);
                  changeTile(xDoor2+1, yDoor2+1, G_left, map1[yDoor2+1][xDoor2+1]-4);

                  //SFX DESPULSAR
                  cpct_akp_SFXPlay(7, 15, 24, 0, 0, AY_CHANNEL_C); //nota que se toca: C-3 = DO3 = 24
               }
            }
         }
      }
   }
}

// Dibuja los personajes
void drawHeroes() {
   u8* pvideomem;

   //Se dibuja el sprite del personaje 1
   if(heroe1.cooldown == 0 || heroe1.cooldown == 1 || heroe1.cooldown == 4 || heroe1.cooldown == 5 || heroe1.cooldown == 8 || heroe1.cooldown == 9 ||
      heroe1.cooldown == 12 || heroe1.cooldown == 13 || heroe1.cooldown == 16 || heroe1.cooldown == 17 || heroe1.cooldown == 20) {
      pvideomem = cpct_getScreenPtr(g_scrbuffers[1], G_offsetX_m1 + heroe1.x, G_offsetY + heroe1.y);
      cpct_drawSpriteMasked(heroe1.anim.frames[heroe1.anim.frame_id]->sprite, pvideomem, G_heroeW, G_heroeH);
   }

   //Se dibuja el sprite del personaje 2
   if(heroe2.cooldown == 0 || heroe2.cooldown == 1 || heroe2.cooldown == 4 || heroe2.cooldown == 5 || heroe2.cooldown == 8 || heroe2.cooldown == 9 ||
      heroe2.cooldown == 12 || heroe2.cooldown == 13 || heroe2.cooldown == 16 || heroe2.cooldown == 17 || heroe2.cooldown == 20) {
      pvideomem = cpct_getScreenPtr(g_scrbuffers[1], G_offsetX_m2 + heroe2.x, G_offsetY + heroe2.y);
      cpct_drawSpriteMasked(heroe2.anim.frames[heroe2.anim.frame_id]->sprite, pvideomem, G_heroeW, G_heroeH);
   }
}

void updateShots(struct Heroe *heroe, struct Shot *shots) {
   u8 i;

   for(i=0; i<G_maxShots; i++) {
      if(shots[i].active == 1) {
         // Cambiamos la variable en la que guardamos la posicion previa.
         // Usamos dos variables para saber donde limpiar el rastro en cada buffer
         swapPrePosShot(shots[i].preX, shots[i].preY);
         shots[i].preX[1] = shots[i].x;
         shots[i].preY[1] = shots[i].y;

         updateAnimation(&shots[i].anim, shots[i].nextAnim, 0);

         switch(shots[i].dir) {
            case sd_left:
               shots[i].x -= 2;
               if(shots[i].x > 200) { // Al ser unsigned no puedo poner <0
                  shots[i].active = 0;
                  if(shots[i].preX[0] != shots[i].preX[1]) { // Seguro por si acaba de disparar
                     shots[i].x = shots[i].preX[1];
                  }
                  else {
                     shots[i].drawable = 0; // si acaba de disparar, no hay que limpiar
                  }
               }
               break;
            case sd_right:
               shots[i].x += 2;
               if(shots[i].x > G_mapWBytes-4) {
                  shots[i].active = 0;
                  if(shots[i].preX[0] != shots[i].preX[1]) { // Seguro por si acaba de disparar
                     shots[i].x = shots[i].preX[1];
                  }
                  else {
                     shots[i].drawable = 0; // si acaba de disparar, no hay que limpiar
                  }
               }
               break;
            case sd_up:
               shots[i].y -= 4;
               if(shots[i].y > 200) { // Al ser unsigned no puedo poner <0
                  shots[i].active = 0;
                  if(shots[i].preY[0] != shots[i].preY[1]) { // Seguro por si acaba de disparar
                     shots[i].y = shots[i].preY[1];
                  }
                  else {
                     shots[i].drawable = 0; // si acaba de disparar, no hay que limpiar
                  }
               }
               break;
         }
         

         if(heroe->id == G_heroe1) {
            checkShotsCollision(&shots[i], &map1[0][0], G_left);
         }
         else {
            checkShotsCollision(&shots[i], &map2[0][0], G_right);
         }
         
      }
   }
}

void checkShotsCollision(struct Shot* shot, u8 *map, u8 side) {
   updateSensorShot(shot);

   if(map[shot->sensor1] == 0x00) {
      shot->active = 0;
   }
   else if(map[shot->sensor1] == 0x05) {
      shot->active = 0;
      changeTile(shot->sensor1%G_mapWTiles, shot->sensor1/G_mapWTiles, side, 0x06);
   }
   else if(map[shot->sensor1] == 0x06) {
      shot->active = 0;
      changeTile(shot->sensor1%G_mapWTiles, shot->sensor1/G_mapWTiles, side, 0x07);
   }
   else if(map[shot->sensor1] == 0x07) {
      shot->active = 0;
      changeTile(shot->sensor1%G_mapWTiles, shot->sensor1/G_mapWTiles, side, 0xFF);
   }
}

// Dibuja los disparos
void drawShots() {
   u8 *pvideomem, i;

   // Disparos de la chica
   for(i=0; i<G_maxShots; i++) {
      // Dibuja el disparo si esta vivo (activo)
      if(shots1[i].active == 1) {
         pvideomem = cpct_getScreenPtr(g_scrbuffers[1], G_offsetX_m1 + shots1[i].x, G_offsetY + shots1[i].y);
         cpct_drawSpriteMasked(shots1[i].anim.frames[shots1[i].anim.frame_id]->sprite, pvideomem, shots1[i].width, shots1[i].height);
      }
   }

   // Disparos del chico
   for(i=0; i<G_maxShots; i++) {
      // Dibuja el disparo si esta vivo (activo)
      if(shots2[i].active == 1) {
         pvideomem = cpct_getScreenPtr(g_scrbuffers[1], G_offsetX_m2 + shots2[i].x, G_offsetY + shots2[i].y);
         cpct_drawSpriteMasked(shots2[i].anim.frames[shots2[i].anim.frame_id]->sprite, pvideomem, shots2[i].width, shots2[i].height);
      }
   }
}

// Dibuja el borde del area de juego
void drawGameBorder() {
   u8* pvideomem;
   u8 i;

   // Filas
   for(i=0; i<20; i++) {   // Fila superior
      pvideomem = cpct_getScreenPtr(g_scrbuffers[1], i*G_tileSizeW, 4*G_tileSizeH);
      cpct_drawTileAligned4x8(G_tile01, pvideomem);
   }

   for(i=0; i<24; i++) {   // Fila inferior
      pvideomem = cpct_getScreenPtr(g_scrbuffers[1], i*G_tileSizeW, 24*G_tileSizeH);
      cpct_drawTileAligned4x8(G_tile01, pvideomem);
   }

   // Columnas
   for(i=0; i<19; i++) {   // Columna izquierda
      pvideomem = cpct_getScreenPtr(g_scrbuffers[1], 0, 5*G_tileSizeH+i*G_tileSizeH);
      cpct_drawTileAligned4x8(G_tile01, pvideomem);
   }

   for(i=0; i<19; i++) {   // Columna central izq
      pvideomem = cpct_getScreenPtr(g_scrbuffers[1], 9*G_tileSizeW, 5*G_tileSizeH+i*G_tileSizeH);
      cpct_drawTileAligned4x8(G_tile01, pvideomem);
   }

   for(i=0; i<19; i++) {   // Columna central der
      pvideomem = cpct_getScreenPtr(g_scrbuffers[1], 10*G_tileSizeW, 5*G_tileSizeH+i*G_tileSizeH);
      cpct_drawTileAligned4x8(G_tile01, pvideomem);
   }
   
   for(i=0; i<19; i++) {   // Columna derecha
      pvideomem = cpct_getScreenPtr(g_scrbuffers[1], 19*G_tileSizeW, 5*G_tileSizeH+i*G_tileSizeH);
      cpct_drawTileAligned4x8(G_tile01, pvideomem);
   }
}

// Dibuja un sprite en el tile indicado (coordenadas de tile, no en pixeles) en el mapa indicado (izquierdo o derecho)
void drawTile(u8 xTile, u8 yTile, u8 side) {
   u8 *pvideomem, *map, *sprTile, offSetX;

   if(side == G_left) {
      offSetX = G_offsetX_m1;
      map = *map1;
   }
   else {
      offSetX = G_offsetX_m2;
      map = *map2;
   }

   pvideomem = cpct_getScreenPtr(g_scrbuffers[1], xTile * G_tileSizeW + offSetX, yTile*G_tileSizeH+G_offsetY);

   sprTile = G_tileId[map[yTile*G_mapWTiles+xTile]];
   
   // Lo dibujamos
   cpct_drawTileAligned4x8_f(sprTile, pvideomem);
}

void changeTile(u8 xTile, u8 yTile, u8 side, u8 newValue) {
   u8 *map, *mapRedraw, i, found;
   found = 0;

   if(side == G_left) {
      map = *map1;
      mapRedraw = mapRedraw1;
   }
   else {
      map = *map2;
      mapRedraw = mapRedraw2;
   }

   for(i=0; i<G_NUM_REDRAW && found == 0; i++) {
      if(mapRedraw[i] == G_DONT_REDRAW) {
         found = 1;
         mapRedraw[i] = yTile*G_mapWTiles+xTile;
         map[yTile*G_mapWTiles+xTile] = newValue;
         drawTile(xTile, yTile, side);
      }
   }
}

void redrawTiles(u8 side) {
   u8 *mapRedraw, i, found;
   found = 0;

   if(side == G_left) {
      mapRedraw = mapRedraw1;
   }
   else {
      mapRedraw = mapRedraw2;
   }

   for(i=0; i<G_NUM_REDRAW && found == 0; i++) {
      if(mapRedraw[i] != G_DONT_REDRAW) {
         drawTile(mapRedraw[i]%G_mapWTiles, mapRedraw[i]/G_mapWTiles, side);
         mapRedraw[i] = G_DONT_REDRAW;
      }
      else {
         found = 1;
      }
   }
}

// Redibuja los tiles adyacentes al player (limpia su rastro)
void repaintBackgroundOverSprite(u8 x, u8 y, u8 side) {
   byte2tile2(&x, &y);

   // Ahora limpiamos el area de tiles adyacentes al jugador (3x3 tiles)

   // [x][-][-] <- Columna y
   drawTile(x, y, side);
   if(x+1 < G_mapWTiles) drawTile(x+1, y, side);
   if(x-1 >= 0) drawTile(x-1, y, side);

   // [-][x][-] <- Columna y+1
   if(y+1 < G_mapHTiles) {
      drawTile(x, y+1, side);
      if(x+1 < G_mapWTiles) drawTile(x+1, y+1, side);
      if(x-1 >= 0) drawTile(x-1, y+1, side);
   }

   // [-][-][x] <- Columna y+2
   if(y+2 < G_mapHTiles) {
      drawTile(x, y+2, side);
      if(x+1 < G_mapWTiles) drawTile(x+1, y+2, side);
      if(x-1 >= 0) drawTile(x-1, y+2, side);
   }
}

void repaintBackgroundOverShot(struct Shot *shots, u8 side) {
   u8 i, x, y;

   for(i=0; i<G_maxShots; i++) {
      if(shots[i].drawable > 0) {
         x = shots[i].preX[0];
         y = shots[i].preY[0];

         byte2tile2(&x, &y);

         // Ahora limpiamos el area de tiles adyacentes al disparo (2x2 tiles)

         // [x][-] <- Columna y
         drawTile(x, y, side);
         if(x+1 < G_mapWTiles) drawTile(x+1, y, side);

         // [-][x] <- Columna y+1
         if(y+1 < G_mapHTiles) {
            drawTile(x, y+1, side);
            if(x+1 < G_mapWTiles) drawTile(x+1, y+1, side);
         }

         if(shots[i].active == 0) {
            shots[i].drawable--;
         }
      }
   }
}

// Dibuja el mapa completo (Solo debe llamarse al principio de cada nivel)
void drawMap() {
   u8 x, y;

   for(y=0; y<G_mapHTiles; y++) {
      for(x=0; x<G_mapWTiles; x++) {
         drawTile(x, y, G_left);
         drawTile(x, y, G_right);
      }
   }
}

// Intercambia los buffers
void swapBuffers(u8** scrbuffers) {
   u8* aux; // Auxiliary pointer for making the change
   
   // Change what is shown on the screen (present backbuffer (1) is changed to 
   // front-buffer, so it is shown at the screen)
   // cpct_setVideoMemoryPage requires the 6 Most Significant bits of the address,
   // so we have to shift them 10 times to the right (as addresses have 16 bits)
   //
   cpct_setVideoMemoryPage( (u16)(scrbuffers[1]) >> 10 );
   
   // Once backbuffer is being shown at the screen, we switch our two 
   // variables to start using (0) as backbuffer and (1) as front-buffer
   aux = scrbuffers[0];
   scrbuffers[0] = scrbuffers[1];
   scrbuffers[1] = aux;
}

void swapPrePosShot(u8 *preX, u8 *preY) {
   u8 prePos;

   prePos = preX[0];
   preX[0] = preX[1];
   preX[1] = prePos;

   prePos = preY[0];
   preY[0] = preY[1];
   preY[1] = prePos;
}

// Dibuja el HUD
void drawHUD() {
   drawHUDBorder();
   drawHearts();
   drawLevel();
   drawPortraits();
   drawBulletsAndStars();
}

void redrawHUD() {
   if(redrawHearts == 1) {
      drawHearts();
      redrawHearts = 0;
   }
}

// DIBUJA EL NIVEL EN EL HUD
void drawLevel() {
   u8 *pvideomem;
   u8 aux;

   pvideomem = cpct_getScreenPtr(g_scrbuffers[1], 34, 8);  
   cpct_drawCharM0(pvideomem, 4, 0, 'N');

   if(level < 10) {
      pvideomem = cpct_getScreenPtr(g_scrbuffers[1], 38, 8);  
      cpct_drawCharM0(pvideomem, 4, 0, '0');

      if(level != 0) {  // comprobamos que no sea cero porque la funcion no puede pasarle un string que valga 0
         pvideomem = cpct_getScreenPtr(g_scrbuffers[1], 42, 8);  
         cpct_drawCharM0(pvideomem, 4, 0, level+'0');
      }
      else {
         pvideomem = cpct_getScreenPtr(g_scrbuffers[1], 42, 8);  
         cpct_drawCharM0(pvideomem, 4, 0, '0');
      }
   }
   else if(level < 100) {
      aux = level/10;
      pvideomem = cpct_getScreenPtr(g_scrbuffers[1], 38, 8);  
      cpct_drawCharM0(pvideomem, 4, 0, aux+'0');

      aux = level%10;
      pvideomem = cpct_getScreenPtr(g_scrbuffers[1], 42, 8);  
      cpct_drawCharM0(pvideomem, 4, 0, aux+'0');
   }
}

//DIBUJAR RETRATOS
void drawPortraits() {
   u8 *pvideomem; 

   pvideomem = cpct_getScreenPtr(g_scrbuffers[1], 2, 3);
   cpct_drawSprite(G_portraitR, pvideomem, 12, 25);          // Retrato chica

   pvideomem = cpct_getScreenPtr(g_scrbuffers[1], 66, 3);
   cpct_drawSprite(G_portraitB, pvideomem, 12, 25);          // Retrato chico

   pvideomem = cpct_getScreenPtr(g_scrbuffers[1], 15, 15);
   cpct_drawSprite(G_weaponR, pvideomem, 6, 12);             // Retrato baston chica

   pvideomem = cpct_getScreenPtr(g_scrbuffers[1], 59, 15);
   cpct_drawSprite(G_weaponB, pvideomem, 6, 12);             // Retrato baston chico
}

void drawBulletsAndStars() {
   u8 *pvideomem1, *pvideomem2, *pvideomem3;
   
   pvideomem1 = cpct_getScreenPtr(g_scrbuffers[1], 22, 18);
   pvideomem2 = cpct_getScreenPtr(g_scrbuffers[1], 26, 18);
   pvideomem3 = cpct_getScreenPtr(g_scrbuffers[1], 30, 18);

   //HEROE 1
   switch(heroe1.level) {
      case sl_3:
         cpct_drawSprite(G_starFull, pvideomem1, 4, 8);
         cpct_drawSprite(G_starFull, pvideomem2, 4, 8);
         cpct_drawSprite(G_starFull, pvideomem3, 4, 8);
      break;
      case sl_2:
         cpct_drawSprite(G_starFull, pvideomem1, 4, 8);
         cpct_drawSprite(G_starFull, pvideomem2, 4, 8);
         cpct_drawSprite(G_starEmpty, pvideomem3, 4, 8);
      break;
      case sl_1:
         cpct_drawSprite(G_starFull, pvideomem1, 4, 8);
         cpct_drawSprite(G_starEmpty, pvideomem2, 4, 8);
         cpct_drawSprite(G_starEmpty, pvideomem3, 4, 8);
      break;
   }

   pvideomem1 = cpct_getScreenPtr(g_scrbuffers[1], 54, 18);
   pvideomem2 = cpct_getScreenPtr(g_scrbuffers[1], 50, 18);
   pvideomem3 = cpct_getScreenPtr(g_scrbuffers[1], 46, 18);

   //HEROE 2
   switch(heroe2.level) {
      case sl_3:
         cpct_drawSprite(G_starFull, pvideomem1, 4, 8);
         cpct_drawSprite(G_starFull, pvideomem2, 4, 8);
         cpct_drawSprite(G_starFull, pvideomem3, 4, 8);
      break;
      case sl_2:
         cpct_drawSprite(G_starFull, pvideomem1, 4, 8);
         cpct_drawSprite(G_starFull, pvideomem2, 4, 8);
         cpct_drawSprite(G_starEmpty, pvideomem3, 4, 8);
      break;
      case sl_1:
         cpct_drawSprite(G_starFull, pvideomem1, 4, 8);
         cpct_drawSprite(G_starEmpty, pvideomem2, 4, 8);
         cpct_drawSprite(G_starEmpty, pvideomem3, 4, 8);
      break;
   }
}

// DIBUJAR CORAZONES
void drawHearts() {
   u8 *pvideomem1, *pvideomem2, *pvideomem3;
   
   pvideomem1 = cpct_getScreenPtr(g_scrbuffers[1], 16, 6);
   pvideomem2 = cpct_getScreenPtr(g_scrbuffers[1], 20, 6);
   pvideomem3 = cpct_getScreenPtr(g_scrbuffers[1], 24, 6);

   //HEROE 1
   switch(heroe1.health) {
      case 6:
         cpct_drawSprite(G_heartR_full, pvideomem1, 4, 8);
         cpct_drawSprite(G_heartR_full, pvideomem2, 4, 8);
         cpct_drawSprite(G_heartR_full, pvideomem3, 4, 8);
      break;
      case 5:
         cpct_drawSprite(G_heartR_full, pvideomem1, 4, 8);
         cpct_drawSprite(G_heartR_full, pvideomem2, 4, 8);
         cpct_drawSprite(G_heartR_half, pvideomem3, 4, 8);
      break;
      case 4: 
         cpct_drawSprite(G_heartR_full, pvideomem1, 4, 8);
         cpct_drawSprite(G_heartR_full, pvideomem2, 4, 8);
         cpct_drawSprite(G_heart_empty, pvideomem3, 4, 8);
      break;
      case 3:
         cpct_drawSprite(G_heartR_full, pvideomem1, 4, 8);
         cpct_drawSprite(G_heartR_half, pvideomem2, 4, 8);
         cpct_drawSprite(G_heart_empty, pvideomem3, 4, 8);
      break;
      case 2:
         cpct_drawSprite(G_heartR_full, pvideomem1, 4, 8);
         cpct_drawSprite(G_heart_empty, pvideomem2, 4, 8);
         cpct_drawSprite(G_heart_empty, pvideomem3, 4, 8);
      break;
      case 1:
         cpct_drawSprite(G_heartR_half, pvideomem1, 4, 8);
         cpct_drawSprite(G_heart_empty, pvideomem2, 4, 8);
         cpct_drawSprite(G_heart_empty, pvideomem3, 4, 8);
      break;
      case 0:
         cpct_drawSprite(G_heart_empty, pvideomem1, 4, 8);
         cpct_drawSprite(G_heart_empty, pvideomem2, 4, 8);
         cpct_drawSprite(G_heart_empty, pvideomem3, 4, 8);
      break;
   }

   pvideomem1 = cpct_getScreenPtr(g_scrbuffers[1], 60, 6);
   pvideomem2 = cpct_getScreenPtr(g_scrbuffers[1], 56, 6);
   pvideomem3 = cpct_getScreenPtr(g_scrbuffers[1], 52, 6);

   //HEROE 2
   switch(heroe2.health) {
      case 6:
         cpct_drawSprite(G_heartB_full, pvideomem1, 4, 8);
         cpct_drawSprite(G_heartB_full, pvideomem2, 4, 8);
         cpct_drawSprite(G_heartB_full, pvideomem3, 4, 8);
      break;
      case 5:
         cpct_drawSprite(G_heartB_full, pvideomem1, 4, 8);
         cpct_drawSprite(G_heartB_full, pvideomem2, 4, 8);
         cpct_drawSprite(G_heartB_half, pvideomem3, 4, 8);
      break;
      case 4:
         cpct_drawSprite(G_heartB_full, pvideomem1, 4, 8);
         cpct_drawSprite(G_heartB_full, pvideomem2, 4, 8);
         cpct_drawSprite(G_heart_empty, pvideomem3, 4, 8);
      break;
      case 3:
         cpct_drawSprite(G_heartB_full, pvideomem1, 4, 8);
         cpct_drawSprite(G_heartB_half, pvideomem2, 4, 8);
         cpct_drawSprite(G_heart_empty, pvideomem3, 4, 8);
      break;
      case 2:
         cpct_drawSprite(G_heartB_full, pvideomem1, 4, 8);
         cpct_drawSprite(G_heart_empty, pvideomem2, 4, 8);
         cpct_drawSprite(G_heart_empty, pvideomem3, 4, 8);
      break;
      case 1:
         cpct_drawSprite(G_heartB_half, pvideomem1, 4, 8);
         cpct_drawSprite(G_heart_empty, pvideomem2, 4, 8);
         cpct_drawSprite(G_heart_empty, pvideomem3, 4, 8);
      break;
      case 0:
         cpct_drawSprite(G_heart_empty, pvideomem1, 4, 8);
         cpct_drawSprite(G_heart_empty, pvideomem2, 4, 8);
         cpct_drawSprite(G_heart_empty, pvideomem3, 4, 8);
      break;
   }
}

// DIBUJAR EL BORDE DEL HUD
void drawHUDBorder() {
   u8* pvideomem;
   u8 i;

   //Marco del HUD
   pvideomem = cpct_getScreenPtr(g_scrbuffers[1], 0, 0);
   cpct_drawTileAligned4x8_f(G_border01, pvideomem); 

   pvideomem = cpct_getScreenPtr(g_scrbuffers[1], 0, 8);
   cpct_drawTileAligned4x8_f(G_border11, pvideomem); 
   pvideomem = cpct_getScreenPtr(g_scrbuffers[1], 0, 16);
   cpct_drawTileAligned4x8_f(G_border11, pvideomem); 

   pvideomem = cpct_getScreenPtr(g_scrbuffers[1], 0, 24);
   cpct_drawTileAligned4x8_f(G_border10, pvideomem);    

   for(i = 0; i < 7; i++) {
      pvideomem = cpct_getScreenPtr(g_scrbuffers[1], i*4+4, 0);
      cpct_drawSprite(G_border02, pvideomem, 4, 8); 

      pvideomem = cpct_getScreenPtr(g_scrbuffers[1], i*4+4, 24);
      cpct_drawSprite(G_border09, pvideomem, 4, 8); 

      pvideomem = cpct_getScreenPtr(g_scrbuffers[1], i*4+48, 0);
      cpct_drawSprite(G_border02, pvideomem, 4, 8); 

      pvideomem = cpct_getScreenPtr(g_scrbuffers[1], i*4+48, 24);
      cpct_drawSprite(G_border09, pvideomem, 4, 8); 
   }

   pvideomem = cpct_getScreenPtr(g_scrbuffers[1], 32, 0);
   cpct_drawTileAligned4x8_f(G_border03, pvideomem); 
   pvideomem = cpct_getScreenPtr(g_scrbuffers[1], 36, 0);
   cpct_drawTileAligned4x8_f(G_border04, pvideomem); 
   pvideomem = cpct_getScreenPtr(g_scrbuffers[1], 32, 8);
   cpct_drawTileAligned4x8_f(G_border05, pvideomem); 
   pvideomem = cpct_getScreenPtr(g_scrbuffers[1], 36, 8);
   cpct_drawTileAligned4x8_f(G_border06, pvideomem); 
   pvideomem = cpct_getScreenPtr(g_scrbuffers[1], 36, 16);
   cpct_drawTileAligned4x8_f(G_border07, pvideomem);
   pvideomem = cpct_getScreenPtr(g_scrbuffers[1], 32, 24);
   cpct_drawTileAligned4x8_f(G_border09, pvideomem);
   pvideomem = cpct_getScreenPtr(g_scrbuffers[1], 36, 24);
   cpct_drawTileAligned4x8_f(G_border08, pvideomem);

   pvideomem = cpct_getScreenPtr(g_scrbuffers[1], 40, 0);
   cpct_drawTileAligned4x8_f(G_border12, pvideomem);
   pvideomem = cpct_getScreenPtr(g_scrbuffers[1], 44, 0);
   cpct_drawTileAligned4x8_f(G_border13, pvideomem);
   pvideomem = cpct_getScreenPtr(g_scrbuffers[1], 44, 8);
   cpct_drawTileAligned4x8_f(G_border14, pvideomem);
   pvideomem = cpct_getScreenPtr(g_scrbuffers[1], 40, 8);
   cpct_drawTileAligned4x8_f(G_border15, pvideomem);
   pvideomem = cpct_getScreenPtr(g_scrbuffers[1], 76, 0);
   cpct_drawTileAligned4x8_f(G_border16, pvideomem);
   pvideomem = cpct_getScreenPtr(g_scrbuffers[1], 76, 24);
   cpct_drawTileAligned4x8_f(G_border17, pvideomem);
   pvideomem = cpct_getScreenPtr(g_scrbuffers[1], 44, 24); 
   cpct_drawTileAligned4x8_f(G_border09, pvideomem);
   pvideomem = cpct_getScreenPtr(g_scrbuffers[1], 40, 24); 
   cpct_drawTileAligned4x8_f(G_border20, pvideomem);
   pvideomem = cpct_getScreenPtr(g_scrbuffers[1], 40, 16); 
   cpct_drawTileAligned4x8_f(G_border18, pvideomem);
   pvideomem = cpct_getScreenPtr(g_scrbuffers[1], 76, 8); 
   cpct_drawTileAligned4x8_f(G_border19, pvideomem);
   pvideomem = cpct_getScreenPtr(g_scrbuffers[1], 76, 16); 
   cpct_drawTileAligned4x8_f(G_border19, pvideomem);
}

void checkNextLevel() {
   if(heroe1.readyNextLevel == 1 && heroe2.readyNextLevel == 1) {
      initGame();
   }
}

u8 tile2tile1(u8 x, u8 y) {
   return y*G_mapWTiles+x;
}