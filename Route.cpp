#include "Route.h"
#include "GLUU.h"
#include "Tile.h"
#include "GLMatrix.h"
#include "TerrainLib.h"
#include "Game.h"

Route::Route() {
    this->trackDB = new TDB((Game::root + "/routes/" + Game::route + "/" + Game::route + ".tdb"));
    this->ref = new Ref((Game::root + "/routes/" + Game::route + "/" + Game::route + ".ref"));
}

Route::Route(const Route& orig) {
}

Route::~Route() {
}

WorldObj* Route::getObj(int x, int z, int uid) {
    Tile *tTile;
    try {
        tTile = tile.at((x)*10000 + z);
        return tTile->getObj(uid);
    } catch (const std::out_of_range& oor) {
        return new WorldObj();
    }
}

void Route::transalteObj(int x, int z, float px, float py, float pz, int uid) {
    Tile *tTile;
    try {
        tTile = tile.at((x)*10000 + z);
        tTile->transalteObj(px,py,pz,uid);
    } catch (const std::out_of_range& oor) {

    }
}

void Route::render(GLUU *gluu, float * playerT, float* playerW, float* target, float fov, bool selection) {
    int mintile = -2;
    int maxtile = 2;

    if (!selection) {
        TerrainLib::render(gluu, playerT, playerW, target, fov);
        trackDB->renderAll(gluu, playerT);
        trackDB->renderLines(gluu, playerT);
    }
    //for (var key in this.tile){
    //    this.tile[key].inUse = false;
    // }
    Tile *tTile;
    for (int i = mintile; i <= maxtile; i++) {
        for (int j = maxtile; j >= mintile; j--) {
            try {
                tTile = tile.at((playerT[0] + i)*10000 + playerT[1] + j);
                if (tTile->loaded == -2) continue;
            } catch (const std::out_of_range& oor) {
                tile[(playerT[0] + i)*10000 + playerT[1] + j] = new Tile(playerT[0] + i, playerT[1] + j);
            }
            tTile = tile[(playerT[0] + i)*10000 + playerT[1] + j];
            //tTile->inUse = true;
            if (tTile->loaded == 1) {
                gluu->mvPushMatrix();
                Mat4::translate(gluu->mvMatrix, gluu->mvMatrix, 2048 * i, 0, 2048 * j);
                tTile->render(playerT, playerW, target, fov, selection);
                gluu->mvPopMatrix();
            }
        }
    }
    /*
    for (var key in this.tile){
       if(this.tile[key] === undefined) continue;
       if(this.tile[key] === null) continue;
       //console.log(this.tile[key].inUse);
       if(!this.tile[key].inUse){
           //console.log("a"+this.tile[key]);
           this.tile[key] = undefined;
       } else {
           this.tile[key].inUse = false;
       }
    }*/
}

WorldObj* Route::placeObject(int x, int z, float* p){
    float q[4];
    q[0] = 0;
    q[1] = 0;
    q[2] = 0;
    q[3] = 1;
    placeObject(x, z, p, (float*)&q, ref->selected);
}

WorldObj* Route::placeObject(int x, int z, float* p, float* q){
    placeObject(x, z, p, (float*)&q, ref->selected);
}

WorldObj* Route::placeObject(int x, int z, float* p, float* q, Ref::RefItem* r){
    Tile *tTile;
    try {
        tTile = tile.at((x)*10000 + z);
    } catch (const std::out_of_range& oor) {
        tile[(x)*10000 + z] = new Tile(x, z);
    }
    if (tTile->loaded == -2){
        if(TerrainLib::isLoaded(x, z)){
            tTile->initNew();
        } else {
            return NULL;
        }
    }
    if (tTile->loaded == 1) {
        //float pozWW[3];
        //pozWW[2] = pozW[2];
        //for(int j = -1000; j < 1000; j+=10)
        //for(int i = -1000; i < 1000; i+=50){
        //pozWW[0] = pozW[0] + i;
        //pozWW[2] = pozW[2] + j;
        return tTile->placeObject(p, q, r);
        //}
    }
    return NULL;
}

void Route::save(){
    qDebug() << "save";
    for (auto it = tile.begin(); it != tile.end(); ++it) {
        //console.log(obj.type);
        Tile* tTile = (Tile*) it->second;
        if (tTile->loaded == 1 && tTile->modified){
            tTile->save();
            tTile->modified = false;
        }
    }
}