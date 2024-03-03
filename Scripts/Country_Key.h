//
// Created by maaya on 03/03/2024.
//

#ifndef WINTERAVLTREE_COUNTRY_KEY_H
#define WINTERAVLTREE_COUNTRY_KEY_H

class Country_Key{
    int id;
public:
    explicit Country_Key(int id=-1): id(id) {
        assert(this->id!=-1);
    }

    Country_Key(const Country_Key& key) =default;
    ~Country_Key()=default;
    bool operator==(const Country_Key& key2){
        return this->id == key2.id;
    }
    friend bool operator<(const Country_Key& key1, const Country_Key& key2){
        return key1.id < key2.id;
    }
    friend bool operator>(const Country_Key& key1, const Country_Key& key2){
        return key1.id > key2.id;
    }
};
#endif //WINTERAVLTREE_COUNTRY_KEY_H
