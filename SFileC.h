#ifndef SFILEC_H
#define	SFILEC_H

#include "FileBuffer.h"

class SFile;

class SFileC {
public:
    struct fvertex {
        unsigned short arg1;
        unsigned short point;
        unsigned short normal;
        unsigned short arg2;
        unsigned short arg3;
        unsigned short material;
        unsigned short uvpoint;
    };

    static void szukajsekcjic(int szukane, FileBuffer* bufor);
    static void odczytajpunktyc(FileBuffer* bufor, SFile* pliks);
    static void odczytajuvpunktyc(FileBuffer* bufor, SFile* pliks);
    static void odczytajnormalnec(FileBuffer* bufor, SFile* pliks);
    static void odczytajmatricesc(FileBuffer* bufor, SFile* pliks);
    static void odczytajimagesc(FileBuffer* bufor, SFile* pliks);
    static void odczytajtexturesc(FileBuffer* bufor, SFile* pliks);
    static void odczytajvtx_statesc(FileBuffer* bufor, SFile* pliks);
    static void odczytajprim_statesc(FileBuffer* bufor, SFile* pliks);
    static void odczytajloddc(FileBuffer* bufor, SFile* pliks);
private:

};

#endif	/* SFILEC_H */

