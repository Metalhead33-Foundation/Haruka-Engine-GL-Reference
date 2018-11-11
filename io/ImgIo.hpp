#ifndef IMGIO_HPP
#define IMGIO_HPP
#include "FreeImageIoExt.hpp"
#include "../abstract/AbstractImageContainer.hpp"

Abstract::sImageContainer createFromImage(Abstract::sFIO reada);
Abstract::sImageContainer createFromDDS(Abstract::sFIO reada);
Abstract::sAnimatedImageContainer createFromGIF(Abstract::sFIO reada);
Abstract::sAnimatedImageContainer createFromWEBP(Abstract::sFIO reada);

#endif // IMGIO_HPP
