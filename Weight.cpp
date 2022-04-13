///////////////////////////////////////////////////////////////////////////////
///         University of Hawaii, College of Engineering
/// @brief  ee205_lab12a_fatCat - EE 205 - Spr 2022
///
/// @file Weight.cpp
/// @version 1.0
///
/// @author Caleb Mueller <mc61@hawaii.edu>
/// @date   11_Apr_2022
///////////////////////////////////////////////////////////////////////////////
#include "Weight.h"

const std::string Weight::POUND_LITERAL = "LBS";

Weight::Weight(Weight::UnitOfWeight unitOfWeight, float weight):_unitOfWeight{unitOfWeight}, _weight{weight}{}

Weight::UnitOfWeight Weight::getUnitOfWeight() const noexcept {
    return _unitOfWeight;
}

float Weight::getWeight() const noexcept {
    return _weight;
}

float Weight::getMaxWeight() const noexcept {
    return _maxWeight;
}
