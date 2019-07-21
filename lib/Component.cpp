#include <iostream>
#include <string>
#include <vector>


#include "Component.hpp"
#include "GameObject.h"

using namespace std;

namespace obiectum {

    struct AssignmentException : public exception {
	    const char * what() const throw ()
        {
    	    return "Same instance of a Component cannot be assigned to more than one GameObject";
        }
    };


    class Component {
        private:

        GameObject* gameObject;
        bool isAssigned;

        static float deltaTime;

        public:

        virtual const string type;
        
        /*
            Constructors
         */
        Component() {
            isAssigned = false;
        }

        Component(GameObject* _gameObject) {
            gameObject = _gameObject;
            isAssigned = true;
        }

        /*
            Assigns the Component's parent GameObject
         */
        void Assign(GameObject* _gameObject) {
            if (!isAssigned) {
                gameObject = _gameObject;
                isAssigned = true;
            } else {
                throw AssignmentException();
            }
        }

        /*
            This function is called before the first draw time.
         */
        virtual void Setup(void) {

        }

        /*
            This function is called whenever the screen is ready to update.
         */
        virtual void Update(void) {

        }

    };
    /*
        Initializes all static variables for this class.
     */
    float Component::deltaTime = 0.0f;
}