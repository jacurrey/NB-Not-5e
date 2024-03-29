/*  This file is part of TSRE5.
 *
 *  TSRE5 - train sim game engine and MSTS/OR Editors. 
 *  Copyright (C) 2016 Piotr Gadecki <pgadecki@gmail.com>
 *
 *  Licensed under GNU General Public License 3.0 or later. 
 *
 *  See LICENSE.md or https://www.gnu.org/licenses/gpl.html
 */

#ifndef LEVELCROBJ_H
#define	LEVELCROBJ_H

#include "WorldObj.h"
#include <QString>
#include "FileBuffer.h"

class TrackItemObj;

class LevelCrObj : public WorldObj {
public:
    static float MaxPlacingDistance;
    
    LevelCrObj();
    LevelCrObj(const LevelCrObj& o);
    WorldObj* clone();
    virtual ~LevelCrObj();
    void loadingFixes();
    bool containsTrackItem(int tdbId, int id);
    void addTrackItemIdOffset(unsigned int trackOffset, unsigned int roadOffset);
    void getTrackItemIds(QVector<int> &ids, int tdbId);
    void load(int x, int y);
    void set(QString sh, QString val);
    void set(int sh, FileBuffer* data);
    void set(QString sh, FileBuffer* data);
    void save(QTextStream* out);
    void setSensitivityActivateLevel(float val);
    void setSensitivityMinimunDistance(float val);
    void setTimingInitialWarning(float val);
    void setTimingSeriousWarning(float val);
    void setTimingAnimationLength(float val);
    void setCrashProbability(float val);
    void setInvisible(bool val);
    void setSilentMstsHax(bool val);
    void setSoundFileName(QString val);
    QString getSoundFileName();
    float getSensitivityActivateLevel();
    float getSensitivityMinimunDistance();
    float getTimingInitialWarning();
    float getTimingSeriousWarning();
    float getTimingAnimationLength();
    float getCrashProbability();
    bool isInvisibleEnabled();
    bool isSilentMstsHaxEnabled();
    bool allowNew();
    bool isTrackItem();
    ErrorMessage* checkForErrors();
    void deleteTrItems();
    void initTrItems(float* tpos);
    int getDefaultDetailLevel();
    bool select(int value);
    void deleteSelectedTrItem();
    void translate(float px, float py, float pz);
    void render(GLUU* gluu, float lod, float posx, float posz, float* playerW, float* target, float fov, int selectionColor, int renderMode);
private:
    int selectionValue = 0;
    int levelCrParameters[2];
    float crashProbability = 0;
    unsigned int levelCrData[2];
    float levelCrTiming[3];
    QVector<int> trItemId;
    //int *trItemId = NULL;
    int trItemIdCount = 0;
    TrackItemObj* pointer3d = NULL;
    TrackItemObj* pointer3dSelected = NULL;
    QVector<float*> drawPositions;
    float* drawPosition = NULL;
    QString ORTSSoundFileName;
    void renderTritems(GLUU* gluu, int selectionColor);
    bool getSimpleBorder(float* border);
    bool getBoxPoints(QVector<float> &points);
};

#endif	/* LEVELCROBJ_H */

