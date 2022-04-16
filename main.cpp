#include <assert.h> // For assert tests
#include <iostream>
#include <sstream>
#include <string>

#include "Weight.h"

using namespace std;

int main() {
  cout << "Beginning Weight Class testing..." << endl;
  cout << "---------------------------------\n" << endl;
  /////////////// Constructor Testing //////////////////
  // Testing Constructor #1
  {
    auto *tw = new Weight();
    assert(tw->getWeight() == Weight::UNKNOWN_WEIGHT);
    assert(tw->getUnitOfWeight() == Weight::DEFAULT_UNIT_OF_WEIGHT);
    assert(tw->getMaxWeight() == Weight::DEFAULT_MAX_WEIGHT);
    delete tw;
  }
  // Testing Constructor #2
  {
    auto *tw = new Weight(3.14);
    assert(tw->getWeight() == 3.14F);
    assert(tw->getUnitOfWeight() == Weight::DEFAULT_UNIT_OF_WEIGHT);
    assert(tw->getMaxWeight() == Weight::DEFAULT_MAX_WEIGHT);
    delete tw;
  }
  // Testing Constructor #3
  {
    auto *tw = new Weight(Weight::KILOS);
    assert(tw->getWeight() == Weight::UNKNOWN_WEIGHT);
    assert(tw->getUnitOfWeight() == Weight::KILOS);
    assert(tw->getMaxWeight() == Weight::DEFAULT_MAX_WEIGHT);
    delete tw;
  }
  // Testing Constructor #4
  {
    auto *tw = new Weight(3.14, Weight::SLUGS);
    assert(tw->getWeight() == 3.14F);
    assert(tw->getUnitOfWeight() == Weight::SLUGS);
    assert(tw->getMaxWeight() == Weight::DEFAULT_MAX_WEIGHT);
    delete tw;
  }
  // Testing Constructor #5
  {
    auto *tw = new Weight(3.14, 48.7);
    assert(tw->getWeight() == (float)3.14);
    assert(tw->getUnitOfWeight() == Weight::DEFAULT_UNIT_OF_WEIGHT);
    assert(tw->getMaxWeight() == 48.7F);
    delete tw;
  }
  // Testing Constructor #6
  {
    auto *tw = new Weight(Weight::KILOS, 48.7);
    assert(tw->getWeight() == Weight::UNKNOWN_WEIGHT);
    assert(tw->getUnitOfWeight() == Weight::KILOS);
    assert(tw->getMaxWeight() == 48.7F);
    delete tw;
  }
  // Testing Constructor #7a
  {
    auto *tw = new Weight(1.23, Weight::POUNDS, 45.6);
    assert(tw->getWeight() == 1.23F);
    assert(tw->getUnitOfWeight() == Weight::POUNDS);
    assert(tw->getMaxWeight() == 45.6F);
    delete tw;
  }
  // Testing Constructor #7b
  {
    auto *tw = new Weight(-1.23, Weight::POUNDS, -45.6);
    assert(tw->getWeight() == Weight::UNKNOWN_WEIGHT);
    assert(tw->getUnitOfWeight() == Weight::POUNDS);
    assert(tw->getMaxWeight() == Weight::DEFAULT_MAX_WEIGHT);
    delete tw;
  }
  // Testing Constructor #7c
  {
    auto *tw = new Weight(11, Weight::POUNDS, 10);
    assert(tw->getWeight() == Weight::UNKNOWN_WEIGHT);
    assert(tw->getUnitOfWeight() == Weight::POUNDS);
    delete tw;
  }

  /////////////// Weight Unit Conversion Testing //////////////////
  {
    assert(Weight::convertWeight(1.0, Weight::POUNDS, Weight::POUNDS) == 1.0);
    assert(Weight::convertWeight(1.0, Weight::POUNDS, Weight::KILOS) ==
           Weight::KILOS_IN_A_POUND);
    assert(Weight::convertWeight(1.0, Weight::POUNDS, Weight::SLUGS) ==
           Weight::SLUGS_IN_A_POUND);

    assert(Weight::convertWeight(1.0, Weight::KILOS, Weight::KILOS) == 1.0);
    assert(Weight::convertWeight(1.0, Weight::KILOS, Weight::POUNDS) ==
           1 / Weight::KILOS_IN_A_POUND);
    assert(Weight::convertWeight(1.0, Weight::KILOS, Weight::SLUGS) ==
           1 / (Weight::KILOS_IN_A_POUND / Weight::SLUGS_IN_A_POUND));

    assert(Weight::convertWeight(1.0, Weight::SLUGS, Weight::SLUGS) == 1.0);
    assert(Weight::convertWeight(1.0, Weight::SLUGS, Weight::KILOS) ==
           (Weight::KILOS_IN_A_POUND / Weight::SLUGS_IN_A_POUND));
    assert(Weight::convertWeight(1.0, Weight::SLUGS, Weight::POUNDS) ==
           1 / Weight::SLUGS_IN_A_POUND);
  }

  /////////////// Weight Operator Testing //////////////////
  {
    // operator== testing
    auto *a = new Weight(1.0, Weight::POUNDS, 10.0);
    auto *b = new Weight(1.5, Weight::POUNDS, 10.0);
    assert(!(a == b)); // Should fail because a != b

    a->setWeight(b->getWeight()); //< Setting a's weight equal to b's weight
    assert(*a == *b);

    // operator< testing
    a->setWeight(a->getWeight() - 1.0);
    assert(*a < *b);

    // operator+= testing
    float addAmnt = 1.0;
    assert((*a += addAmnt).getWeight() == 1.5);

    // operator<< testing

    // POUNDS
    std::stringstream ss;
    ss << Weight::UnitOfWeight::POUNDS;
    assert(ss.str() == "lbs");
    ss.str("");
    ss.clear();

    // KILOS
    ss << Weight::UnitOfWeight::KILOS;
    assert(ss.str() == "kgs");
    ss.str("");
    ss.clear();

    // SLUGS
    ss << Weight::UnitOfWeight::SLUGS;
    assert(ss.str() == "slugs");
    ss.str("");
    ss.clear();

    delete a;
    delete b;
  }

  /////////////// Public Class Methods Testing //////////////////
  {
    // weightIsKnown() and setWeight() Testing
    auto *a = new Weight();
    assert(!a->weightIsKnown());
    a->setWeight(5.0);
    assert(a->weightIsKnown());
    assert(a->getWeight() == 5.0);

    // setWeight(float, UnitOfWeight) Testing
    float tAgainst = Weight::convertWeight(4.0, Weight::POUNDS, Weight::KILOS);
    a->setWeight(4.0, Weight::KILOS);
    assert(a->getWeight() == tAgainst);

    // getWeight(UnitOfWeight) Testing
    float testGetWeightSlugs =
        Weight::convertWeight(4.0, Weight::POUNDS, Weight::SLUGS);
    a->setWeight(4.0, Weight::POUNDS);
    assert(a->getWeight(Weight::SLUGS) == testGetWeightSlugs);

    // hasMaxWeight() and setMaxWeight() Testing
    assert(!a->hasMaxWeight());
    a->setMaxWeight(10.0);
    assert(a->hasMaxWeight());
    assert(a->getMaxWeight() == 10.0);

    // getUnitOfWeight() testing
    assert(a->getUnitOfWeight() == Weight::POUNDS);

    // weightIsValid() testing
    assert(a->weightIsValid(1.0));
    assert(!a->weightIsValid(500));
    assert(!a->weightIsValid(Weight::UNKNOWN_WEIGHT));

    // maxWeightIsValid() testing
    assert(a->maxWeightIsValid(1.0));
    assert(!a->maxWeightIsValid(500));
    assert(!a->maxWeightIsValid(Weight::UNKNOWN_WEIGHT));

    // validate() testing
    assert(a->validate());
    auto *b = new Weight();
    assert(!b->validate());
    b->setWeight(5.0);
    assert(!b->validate());
    b->setMaxWeight(5.5);
    assert(b->validate());

    // dump() Testing
    cout << "b->dump():" << endl;
    b->dump();

    delete a;
    delete b;
  }

  cout << "\n---------------------------------" << endl;
  cout << "End of Weight Class Testing" << endl;
  return 0;
}
