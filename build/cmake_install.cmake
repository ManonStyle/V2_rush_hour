# Install script for directory: /home/gg/Bureau/projet/v2_rush_hour

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX ".")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/gg/Bureau/projet/v2_rush_hour/build/lib/libgame.a")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/gg/Bureau/projet/v2_rush_hour/build/lib" TYPE STATIC_LIBRARY FILES "/home/gg/Bureau/projet/v2_rush_hour/build/libgame.a")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/gg/Bureau/projet/v2_rush_hour/build/include/piece.h;/home/gg/Bureau/projet/v2_rush_hour/build/include/game.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/gg/Bureau/projet/v2_rush_hour/build/include" TYPE FILE FILES
    "/home/gg/Bureau/projet/v2_rush_hour/piece.h"
    "/home/gg/Bureau/projet/v2_rush_hour/game.h"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  if(EXISTS "$ENV{DESTDIR}/home/gg/Bureau/projet/v2_rush_hour/jeu" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/gg/Bureau/projet/v2_rush_hour/jeu")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/home/gg/Bureau/projet/v2_rush_hour/jeu"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/gg/Bureau/projet/v2_rush_hour/jeu")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/gg/Bureau/projet/v2_rush_hour" TYPE EXECUTABLE FILES "/home/gg/Bureau/projet/v2_rush_hour/build/jeu")
  if(EXISTS "$ENV{DESTDIR}/home/gg/Bureau/projet/v2_rush_hour/jeu" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/gg/Bureau/projet/v2_rush_hour/jeu")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/home/gg/Bureau/projet/v2_rush_hour/jeu")
    endif()
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  if(EXISTS "$ENV{DESTDIR}/home/gg/Bureau/projet/v2_rush_hour/test_piece" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/gg/Bureau/projet/v2_rush_hour/test_piece")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/home/gg/Bureau/projet/v2_rush_hour/test_piece"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/gg/Bureau/projet/v2_rush_hour/test_piece")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/gg/Bureau/projet/v2_rush_hour" TYPE EXECUTABLE FILES "/home/gg/Bureau/projet/v2_rush_hour/build/test_piece")
  if(EXISTS "$ENV{DESTDIR}/home/gg/Bureau/projet/v2_rush_hour/test_piece" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/gg/Bureau/projet/v2_rush_hour/test_piece")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/home/gg/Bureau/projet/v2_rush_hour/test_piece")
    endif()
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  if(EXISTS "$ENV{DESTDIR}/home/gg/Bureau/projet/v2_rush_hour/test_game" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/gg/Bureau/projet/v2_rush_hour/test_game")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/home/gg/Bureau/projet/v2_rush_hour/test_game"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/gg/Bureau/projet/v2_rush_hour/test_game")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/gg/Bureau/projet/v2_rush_hour" TYPE EXECUTABLE FILES "/home/gg/Bureau/projet/v2_rush_hour/build/test_game")
  if(EXISTS "$ENV{DESTDIR}/home/gg/Bureau/projet/v2_rush_hour/test_game" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/gg/Bureau/projet/v2_rush_hour/test_game")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/home/gg/Bureau/projet/v2_rush_hour/test_game")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/gg/Bureau/projet/v2_rush_hour/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
