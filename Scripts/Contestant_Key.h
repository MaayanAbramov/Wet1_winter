//
// Created by maaya on 03/03/2024.
//

#ifndef WINTERAVLTREE_CONTESTANT_KEY_H
#define WINTERAVLTREE_CONTESTANT_KEY_H

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
#endif //WINTERAVLTREE_CONTESTANT_KEY_H
