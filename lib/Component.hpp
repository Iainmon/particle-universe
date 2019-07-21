#ifndef COMPONENT_H
#define COMPONENT_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace obiectum {

    struct AssignmentException : public exception {
	    const char * what() const throw ();
    };


    class Component {
        private:

        GameObject* gameObject;
        bool isAssigned;

        static float deltaTime;

        public:

        virtual const string type;
        
        Component() {}

        Component(GameObject* _gameObject);

        void Assign(GameObject* _gameObject);

        virtual void Setup(void);

        virtual void Update(void);
    };
}

#endif