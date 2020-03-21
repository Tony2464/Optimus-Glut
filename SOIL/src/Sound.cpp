#include <stdio.h>
#include <windows.h>
#include "../fmod/fmod.h"

int main(int argc, char const *argv[])
{

    FMOD_SYSTEM *sys;
    FMOD_SOUND *sound;
    FMOD_RESULT resultat;
    FMOD_CHANNEL *channel;

    FMOD_System_Create(&sys);
    FMOD_System_Init(sys, 1, FMOD_INIT_NORMAL, NULL);

    /* On ouvre la musique */
    resultat = FMOD_System_CreateSound(sys, "../../sounds/jesuisoptimus.mp3", FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, &sound);

    if (resultat != FMOD_OK)
    {
        fprintf(stderr, "Impossible de lire le fichier mp3\n");
    }

    /* On joue la musique */
    FMOD_System_PlaySound(sys, FMOD_CHANNEL_FREE, sound, 0, NULL);

    Sleep(4000);
    FMOD_Sound_Release(sound);
    FMOD_System_Close(sys);

    return 0;
}
