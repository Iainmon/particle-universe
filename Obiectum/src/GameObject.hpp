#pragma once

#include <iostream>
#include <string>
#include <vector>


using namespace std;

namespace obiectum {

    struct ComponentMissingException : public exception {
	    const char * what() const throw ();
    };

    struct GameObjectMetaData {
        string name;
        string type;
        
        GameObjectMetaData();
        GameObjectMetaData(string _name);
        GameObjectMetaData(string _name, string _type);
    };

    class Component;

    class GameObject {
        private:

        vector<Component*> components;

        public:

        GameObjectMetaData metaData;

        /*
            Constructors
         */
        GameObject();
        GameObject(GameObjectMetaData _metaData);
        GameObject(string _name);
        GameObject(string _name, string _type);


        void AddComponent(Component* _component);

        Component* GetComponentByType(string _type);

        template<class T>
        Component* GetComponentByType();

        void updateComponents();
    };
}