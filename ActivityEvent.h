/*  This file is part of TSRE5.
 *
 *  TSRE5 - train sim game engine and MSTS/OR Editors. 
 *  Copyright (C) 2016 Piotr Gadecki <pgadecki@gmail.com>
 *
 *  Licensed under GNU General Public License 3.0 or later. 
 *
 *  See LICENSE.md or https://www.gnu.org/licenses/gpl.html
 */

#include <QString>
#include <QVector>
#include <QVariant>

#ifndef ACTIVITYEVENT_H
#define	ACTIVITYEVENT_H

class FileBuffer;
class QTextStream;

class ActivityEvent {

public:
    class Outcome {
    public:
        enum OutcomeCategory {
            CategoryNone = 0,
            CategoryEvent = 1,
            CategoryInfo = 2
        };
        
        enum OutcomeType {
            TypeNone = 0,
            TypeDisplayMessage = 1,
            TypeActivitySuccess = 2,
            TypeActivityFail = 3,
            TypeIncActLevel = 4,
            TypeDecActLevel = 5,
            TypeRestorAactLevel = 6,
            TypeActivateEvent = 7,
            TypeStartIgnoringSpeedLimits = 8,
            TypeStopIgnoringSpeedLimits = 9
        };
        
        static QMap<OutcomeType, QString> OutcomeTypeDescription;
        static QMap<QString, OutcomeType> OutcomeNameType;
        static QMap<OutcomeType, QString> OutcomeTypeName;
        static QMap<OutcomeType, OutcomeCategory> OutcomeTypeCategory;
        
        OutcomeType type;
        OutcomeCategory category;
        QVariant value;
        
        Outcome(OutcomeType t){
            this->type = t;
        }
        
        void load(FileBuffer* data);
        void save(QTextStream* out);
    };

    enum EventType {
        EventTypeNone = 0,
        EventTypeTime = 1,
        EventTypeLocation = 2,
        EventTypeAllstops = 3,
        EventTypePickupWagons = 4,
        EventTypeAssembleTrain = 5,
        EventTypeAssembleTrainAtLocation = 6,
        EventTypeDropoffWagonsAtLocation = 7,
        EventTypePickupPassengers = 8,
        EventTypeReachSpeed = 9,
        EventTypePickUp = 10
    };
    
    static QMap<EventType, QString> EventTypeDescription;
    static QMap<QString, EventType> EventNameType;
    static QMap<EventType, QString> EventTypeName;
    
    enum EventCategory {
        CategoryUndefined = 0,
        CategoryAction = 1,
        CategoryLocation = 2,
        CategoryTime = 3
    };
    
    EventCategory category = CategoryUndefined;
    EventType eventType = EventTypeNone;
    std::vector<unsigned int> wagonListId;
    std::vector<unsigned int> wagonListSidingItem;
    std::vector<std::string> wagonListDescription;

    int id = -99999;
    bool reversableEvent = false;
    int activationLevel = -99999;
    QString name;
    int time = -99999;
    int stationStop = -99999;
    float* location = NULL;
    int sidingItem = -99999;
    float speed = -99999;
    int triggerOnStop = -99999;
    QVector<int> pickupIdAndAmount;
    QString textToDisplayOnCompletionIfTriggered;
    QString textToDisplayOnCompletionIfNotTriggered;
    QString textToDisplayDescriptionOfTask;
    QVector<Outcome*> outcomes;
    //Outcome* outcome = NULL;
    
    ActivityEvent();
    ~ActivityEvent();
    void load(FileBuffer* data);
    void save(QTextStream* out);
};

#endif	/* ACTIVITYEVENT_H */
