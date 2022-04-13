#include <iostream>
#include <assert.h> // For assert tests

#include "Weight.h"

using namespace std;

int main() {
    cout << "Beginning Weight Class testing..." << endl;
    cout << "---------------------------------" << endl;

    /////////////// Constructor Testing //////////////////
    // Testing explicit constructor instantiation of a Weight object
    auto* exWeight = new Weight(Weight::POUNDS, 5);
    assert(exWeight->getUnitOfWeight() == Weight::POUNDS);
    assert(exWeight->getWeight() == 5);
    delete exWeight;

    // Testing explicit constructor with reversed argument order
    auto* exWeight2 = new Weight(7, Weight::KILOS);
    assert(exWeight2->getUnitOfWeight() == Weight::POUNDS);
    assert(exWeight2->getWeight() == 5);
    delete exWeight2;

    // Testing implicit default constructor instantiation of a Weight object
    auto* defWeight = new Weight();
    assert(defWeight->getUnitOfWeight() == Weight::DEFAULT_UNIT_OF_WEIGHT);
    assert(defWeight->getWeight() == Weight::UNKNOWN_WEIGHT);
    assert(defWeight->getMaxWeight() == Weight::UNKNOWN_WEIGHT);

    return 0;
}
