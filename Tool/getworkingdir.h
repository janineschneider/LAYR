#ifndef GETWORKINGDIR_H
#define GETWORKINGDIR_H

#include <stdio.h>  /** defines FILENAME_MAX */
#define WINDOWS  /** uncomment this line to use it for windows.*/
#ifdef WINDOWS
#include <direct.h>
#define getCurrentDir _getcwd
#else
#include <unistd.h>
#define getCurrentDir getcwd
#endif

#endif // GETWORKINGDIR_H
