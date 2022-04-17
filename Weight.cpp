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

/////////////////////////////////// Constants //////////////////////////////////////
const float Weight::UNKNOWN_WEIGHT = 0;
const float Weight::KILOS_IN_A_POUND = 0.453592;
const float Weight::SLUGS_IN_A_POUND = 0.031081;
const Weight::UnitOfWeight Weight::DEFAULT_UNIT_OF_WEIGHT = POUNDS;
const float Weight::DEFAULT_MAX_WEIGHT = 50;
const std::string Weight::POUND_LITERAL = "lbs";
const std::string Weight::SLUG_LITERAL = "slugs";
const std::string Weight::KILO_LITERAL = "kgs";

/////////////////////////////////// Static Methods //////////////////////////////////////
float Weight::fromKilogramsToPounds( float weightInKilos ) noexcept
{
	return weightInKilos / KILOS_IN_A_POUND;
}

float Weight::fromPoundsToKilograms( float weightInPounds ) noexcept
{
	return weightInPounds * KILOS_IN_A_POUND;
}

float Weight::fromSlugsToPounds( float weightInSlugs ) noexcept
{
	return weightInSlugs / SLUGS_IN_A_POUND;
}

float Weight::fromPoundsToSlugs( float weightInPounds ) noexcept
{
	return weightInPounds * SLUGS_IN_A_POUND;
}

float Weight::convertWeight( float fromWeight, Weight::UnitOfWeight fromUnit, Weight::UnitOfWeight toUnit ) noexcept
{
	switch( fromUnit )
	{
		case POUNDS:
			switch( toUnit )
			{
				case POUNDS:
					return fromWeight;
				case SLUGS:
					return fromPoundsToSlugs( fromWeight );
				case KILOS:
					return fromPoundsToKilograms( fromWeight );
				default:
					assert( 0 );
			}

		case SLUGS:
			switch( toUnit )
			{
				case POUNDS:
					return fromSlugsToPounds( fromWeight );
				case SLUGS:
					return fromWeight;
				case KILOS:
					return fromPoundsToKilograms( fromSlugsToPounds( fromWeight ));
				default:
					assert( 0 );
			}

		case KILOS:
			switch( toUnit )
			{
				case POUNDS:
					return fromKilogramsToPounds( fromWeight );
				case SLUGS:
					return fromPoundsToSlugs( fromKilogramsToPounds( fromWeight ));
				case KILOS:
					return fromWeight;
				default:
					assert( 0 );
			}
		default:
			assert( 0 );
	}
}

/////////////////////////////////// Class Constructors //////////////////////////////////////
// ↓ #1
Weight::Weight() noexcept : Weight( UNKNOWN_WEIGHT, DEFAULT_UNIT_OF_WEIGHT, UNKNOWN_WEIGHT )
{
}

// ↓ #2
Weight::Weight( float newWeight ) : Weight( newWeight, DEFAULT_UNIT_OF_WEIGHT, UNKNOWN_WEIGHT )
{
}

// ↓ #3
Weight::Weight( Weight::UnitOfWeight newUnitOfWeight ) noexcept : Weight( UNKNOWN_WEIGHT, newUnitOfWeight, UNKNOWN_WEIGHT )
{
}

// ↓ #4
Weight::Weight( float newWeight, Weight::UnitOfWeight newUnitOfWeight ) noexcept : Weight( newWeight, newUnitOfWeight, UNKNOWN_WEIGHT )
{
}

// ↓ #5
Weight::Weight( float newWeight, float newMaxWeight ) noexcept : Weight( newWeight, DEFAULT_UNIT_OF_WEIGHT, newMaxWeight )
{
}

// ↓ #6
Weight::Weight( UnitOfWeight newUnitOfWeight, float newMaxWeight ) noexcept : Weight( UNKNOWN_WEIGHT, newUnitOfWeight, newMaxWeight )
{
}

// ↓ #7
Weight::Weight( float newWeight, Weight::UnitOfWeight newUnitOfWeight, float newMaxWeight ) noexcept : _unitOfWeight{ newUnitOfWeight }
{
	if( maxWeightIsValid( newMaxWeight ))
	{
		_maxWeight = newMaxWeight;
		_bHasMax = true;
	}
	else
	{
		_maxWeight = DEFAULT_MAX_WEIGHT;
	}

	if( weightIsValid( newWeight ))
	{
		_weight = newWeight;
		_bIsKnown = true;
	}
	else
	{
		_weight = UNKNOWN_WEIGHT;
	}
}

/////////////////////////////////// Operators //////////////////////////////////////
bool Weight::operator==( const Weight &rhs ) const
{
	float lhs_weight = ( _bIsKnown ) ? getWeight( Weight::POUNDS ) : 0;
	float rhs_weight = ( rhs._bIsKnown ) ? rhs.getWeight( Weight::POUNDS ) : 0;
	return lhs_weight == rhs_weight;
}

bool Weight::operator<( const Weight &rhs ) const
{
	float lhs_weight = ( _bIsKnown ) ? getWeight( Weight::POUNDS ) : 0;
	float rhs_weight = ( rhs._bIsKnown ) ? rhs.getWeight( Weight::POUNDS ) : 0;
	return lhs_weight < rhs_weight;
}

Weight &Weight::operator+=( float &rhs_weight )
{
	float lhs_weight = ( _bIsKnown ) ? getWeight( Weight::POUNDS ) : 0;
	float sum = lhs_weight + rhs_weight;
	if( !weightIsValid( sum ))
	{
		throw invalid_argument( PROGRAM_NAME
		                        " += operation results is an invalid weight!" );
	}
	setWeight( sum );
	return *this;
}

std::ostream &operator<<( std::ostream &lhs_stream, const Weight::UnitOfWeight rhsUnit )
{
	switch( rhsUnit )
	{
		case Weight::POUNDS:
			return lhs_stream << Weight::POUND_LITERAL;
		case Weight::KILOS:
			return lhs_stream << Weight::KILO_LITERAL;
		case Weight::SLUGS:
			return lhs_stream << Weight::SLUG_LITERAL;
		default:
			throw out_of_range( "The unit can’t be mapped to a string" );
	}
}

/////////////////////////////////// Public Class Methods //////////////////////////////////////
bool Weight::weightIsKnown() const noexcept
{
	return ( weightIsValid( _weight ));
}

bool Weight::hasMaxWeight() const noexcept
{
	return ( maxWeightIsValid( _maxWeight ));
}

float Weight::getWeight() const noexcept
{
	return _bIsKnown ? _weight : 0;
}

float Weight::getWeight( Weight::UnitOfWeight weightUnits ) const noexcept
{
	if( _bIsKnown )
	{
		return convertWeight( _weight, _unitOfWeight, weightUnits );
	}
	return 0; // (!_bisKnown)
}

float Weight::getMaxWeight() const noexcept
{
	return _maxWeight;
}

Weight::UnitOfWeight Weight::getUnitOfWeight() const noexcept
{
	return _unitOfWeight;
}

void Weight::setWeight( float newWeight )
{
	if( weightIsValid( newWeight ))
	{
		_bIsKnown = true;
		_weight = newWeight;
	}
}

void Weight::setWeight( float newWeight, Weight::UnitOfWeight weightUnits )
{
	if( weightIsValid( newWeight ))
	{
		float convertedWeight = convertWeight( newWeight, getUnitOfWeight(), weightUnits );
		_weight = convertedWeight;
	}
}

bool Weight::weightIsValid( float checkWeight ) const noexcept
{
	return ( checkWeight > 0 && checkWeight != UNKNOWN_WEIGHT && checkWeight <= _maxWeight );
}

bool Weight::maxWeightIsValid( float checkMaxWeight ) const noexcept
{
	return ( checkMaxWeight > 0 && checkMaxWeight < DEFAULT_MAX_WEIGHT );
}

bool Weight::validate() const noexcept
{
	return ( weightIsValid( _weight ) && maxWeightIsValid( _maxWeight ));
}

void Weight::dump() const noexcept
{
	std::cout << "Weight: " << _weight << " " << _unitOfWeight << ", ";
	std::cout << "Max Weight: " << _maxWeight << " " << _unitOfWeight << std::endl;
}

void Weight::setMaxWeight( float newMaxWeight )
{
	// Can only set _maxWeight if it isn't already set    ↓
	if( maxWeightIsValid( newMaxWeight ) && !maxWeightIsValid( _maxWeight ))
	{
		_maxWeight = newMaxWeight;
	}
}
