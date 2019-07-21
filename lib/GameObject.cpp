#include <iostream>
#include <string>
#include <vector>

#include "Component.cpp"

using namespace std;

namespace obiectum {

    struct ComponentMissingException : public exception {
	    const char * what() const throw ()
        {
    	    return "The component could not be found for this GameObject.";
        }
    };

    struct GameObjectMetaData {
        string name;
        string type;
        
        GameObjectMetaData() {
            name = "Generic_GameObject";
            type = "GameObject";
        }
        GameObjectMetaData(string _name) {
            name = _name;
            type = _name;
        }
        GameObjectMetaData(string _name, string _type) {
            name = _name;
            type = _type;
        }
    };

    class GameObject {
        private:

        vector<Component*> components;

        public:

        GameObjectMetaData metaData;

        /*
            Constructors
         */
        GameObject() {}
        GameObject(GameObjectMetaData _metaData) {
            metaData = _metaData;
        }
        GameObject(string _name) {
            metaData = GameObjectMetaData(_name);
        }
        GameObject(string _name, string _type) {
            metaData = GameObjectMetaData(_name, _type);
        }

        /*
            Adds the new component to the array of components
         */
        void AddComponent(Component* _component) {
            //_component->Assign(this);
            components.push_back(_component);
        }

        Component* GetComponentByType(string _type) {
            for (int i = 0; i < components.size(); i++) {
                if (components[i]->type == _type) {
                    return components[i];
                }
            }
            throw ComponentMissingException();
        }

        template<class T>
        Component* GetComponentByType() {
            for (int i = 0; i < components.size(); i++)
            {
                if (dynamic_cast<T*>(components[i]) != nullptr)
                {
                    return components[i];
                }
            }
            return nullptr;
        } // RigidBody* rb = gameObject.GetComponentByType<RigidBody>();

        void updateComponents() {
            for (int i = 0; i < components.size(); i++) {
                components[i]->Update();
            }
        }


    };
}