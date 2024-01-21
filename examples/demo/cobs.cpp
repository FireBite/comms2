#include <iostream>

#include "Comms2/protocols/datalink/COBS.h"

using std::cout, std::cin, std::endl;

using namespace Comms2;

int main() {
    // Prepare data
    etl::vector<uint8_t, 16> data = {0x11, 0x00, 0x00, 0x00};
    etl::vector<uint8_t, 16> originalData = data;
    
    cout << "Original data: ";
    for (auto& byte : data)
    {
        cout << std::hex << (int)byte << " ";
    }
    cout << endl << endl;

    // Encode data with COBS algorithm
    Error res = COBS::encode(data);

    cout << "Encode result: " << ErrorStatusToString(res) << endl;
    cout << "Encoded data:  ";
    for (auto& byte : data)
    {
        cout << std::hex << (int)byte << " ";
    }
    cout << endl << endl;

    // Decode data with COBS algorithm
    res = COBS::decode(data);

    cout << "Decode result: " << ErrorStatusToString(res) << endl;
    cout << "Decoded data:  ";
    for (auto& byte : data)
    {
        cout << std::hex << (int)byte << " ";
    }
    cout << endl;

    // Compare original data with decoded data
    cout << endl << "Original data and decoded data are " << (originalData == data ? "equal" : "not equal") << endl;

    return 0;
}