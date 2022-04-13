#include <iostream>
#include <assert.h> // For assert tests

#include "Weight.h"

using namespace std;

int main() {
    cout << "Beginning Weight Class testing..." << endl;
    cout << "---------------------------------" << endl;

    // Testing explicit constructor instantiation of a Weight object
    Weight* exWeight = new Weight(Weight::POUNDS, 5);
    assert(exWeight->getUnitOfWeight() == Weight::POUNDS);
    assert(exWeight->getWeight() == 5);
    delete exWeight;

    // Testing implicit default constructor instantiation of a Weight object
    Weight* defWeight = new Weight();
    assert(defWeight->getUnitOfWeight() == Weight::DEFAULT_UNIT_OF_WEIGHT);
    assert(defWeight->getWeight() == Weight::UNKNOWN_WEIGHT);
    assert(defWeight->getMaxWeight() == Weight::UNKNOWN_WEIGHT);

    return 0;
}
