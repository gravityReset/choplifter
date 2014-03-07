#ifndef COLLISION_H_INCLUDED
#define COLLISION_H_INCLUDED
#include "../image.h"
#include "../definitions.h"
#include "scroll.h"
#include "helico.h"
#include "decor.h"
#include "otages.h"
#include "enemi.h"
#include <SDL/SDL.h>


void verif_destruction_baseEn(BaseEn base[], MissileHeli mh[],MissileEn me[],Otage otg[],int* nbB);
void verif_otages_morts(MissileHeli mh[],MissileEn me[],Otage otg[]);
int otages_monte_helico(Helico* hl,Otage otg[]);
int verif_otages_baseAm(Helico* hl,Otage otg[],Background bg);
void verif_enemis_morts(MissileHeli mh[],MissileEn me[],Enemi en[],int *nbT);
void verif_missilesEn_helico(MissileEn me[],Helico* hl);
void colision_enemis_helico(Helico* hl,Enemi en[]);
#endif // COLLISION_H_INCLUDED
