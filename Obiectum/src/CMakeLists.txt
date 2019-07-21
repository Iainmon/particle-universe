cmake_minimum_required(VERSION 2.8.9)
project (obiectum)

add_library (obiectum 
  Component.hpp
  Component.cpp
  GameObject.hpp
  GameObject.cpp
  Hierarchy.hpp
  Hierarchy.cpp
  Obiectum.hpp)

install (TARGETS obiectum DESTINATION bin)
install (FILES Obiectum.hpp DESTINATION include)