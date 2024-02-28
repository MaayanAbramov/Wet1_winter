//
// Created by maaya on 19/02/2024.
//

#ifndef WINTERAVLTREE_CONTESTANT_H
#define WINTERAVLTREE_CONTESTANT_H


//
// Created by USER on 12/02/2024.
//
#include "AvlTree.h"
#include "wet1util.h"
#define TEAM_TYPE_INIT 5

class Contestant_Key{
public:
    int id;
    int strength;
    bool by_strength= false;

    explicit Contestant_Key(int mid=-2,int strength=-2,bool by_strength=false): id(mid),strength(strength),by_strength
    (by_strength){
//        assert(this->id!=-2);
//        assert(this->strength!=-2);
    }
    Contestant_Key(const Contestant_Key& other) =default;
    ~Contestant_Key()=default;
    friend bool operator<(const Contestant_Key& key1, const Contestant_Key& key2){
        assert(key1.by_strength == key2.by_strength);
        if (key1.by_strength==false){
            return key1.id<key2.id;
        }
        else {
            return key1.strength<key2.strength? true: key1.strength==key2.strength && key1.id < key2.id;
        }
    }
    friend bool operator>(const Contestant_Key& key1, const Contestant_Key& key2){
        assert(key1.by_strength == key2.by_strength);
        if (key1.by_strength==false){
            return key1.id>key2.id;
        }
        else {
            return key1.strength>key2.strength? true: key1.strength==key2.strength && key1.id > key2.id;
        }
    }
    bool operator==(const Contestant_Key& key2){
        assert(this->by_strength == key2.by_strength);
        if (this->by_strength==false){
            return this->id == key2.id;
        }
        else {
            return this->strength == key2.strength && this->id == key2.id;
        }
    }

};
class Contestant {
    int contestantId;
    int countryId;
    int strength;
    Sport sport;
    bool is_by_strength_sorted;
    Sport* teamsIParticipate;


public:
    Contestant();
    Contestant(int contestantId, int countryId, int strength, Sport sport, bool is_by_strength_sorted);
    Contestant(const Contestant& other);
    ~Contestant() = default;
    bool operator==(const Contestant& other) const;
    friend bool operator<(const Contestant& num1, const Contestant& num2);
    friend bool operator>(const Contestant& num1, const Contestant& num2);
    int get_contestantId() const;
    int get_countryId() const;
    int get_strength() const;
    Sport get_sport() const;
    bool get_is_by_strength_sorted() const;
    void set_is_by_strength_sorted(bool is_by_strength);
    Sport* get_teamsIParticipate(int index) const;
    void set_teamsIparticipate(int index, const Sport& sport);

};



#endif //WINTERAVLTREE_CONTESTANT_H
