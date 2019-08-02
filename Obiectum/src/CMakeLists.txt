cmake_minimum_required(VERSION 2.8.9)
project (obiectum)

add_library (obiectum 
  Component.hpp
  Component.cpp
  GameObject.hpp
  GameObject.cpp
  Hierarchy.hpp
  Hierarchy.cpp
  physics/Vector.hpp
  physics/Vector.cpp
  physics/Color.hpp
  physics/Color.cpp
  components/Components.hpp
  components/RigidBody.cpp
  components/Transform.cpp
  components/Drawable.cpp
  Obiectum.hpp)

install (TARGETS obiectum DESTINATION bin)
install (FILES Obiectum.hpp DESTINATION include)