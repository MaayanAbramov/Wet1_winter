//
// Created by maaya on 03/03/2024.
//

#ifndef WINTERAVLTREE_TEAM_KEY_H
#define WINTERAVLTREE_TEAM_KEY_H

class Team_Key{
    int id;
public:
    explicit Team_Key(int id=-1): id(id) {
        assert(this->id!=-1);
    }
    Team_Key(const Team_Key& key) =default;
    ~Team_Key()=default;
    friend bool operator<(const Team_Key& key1, const Team_Key& key2){
        return key1.id < key2.id;
    }
    friend bool operator>(const Team_Key& key1, const Team_Key& key2){
        return key1.id > key2.id;
    }
    bool operator==(const Team_Key& key2){
        return this->id == key2.id;
    }
};
#endif //WINTERAVLTREE_TEAM_KEY_H
