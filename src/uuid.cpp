#include <random>
#include <sstream>
#include <iomanip>

std::string generateUUIDv4() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<uint32_t> dis(0, 0xffffffff);

    uint32_t data[4] = { dis(gen), dis(gen), dis(gen), dis(gen) };

    std::stringstream ss;
    ss << std::hex << std::setfill('0')
       << std::setw(8) << data[0] << "-"
       << std::setw(4) << (data[1] >> 16) << "-"
       << std::setw(4) << ((data[1] & 0x0fff) | 0x4000) << "-" // version 4
       << std::setw(4) << ((data[2] & 0x3fff) | 0x8000) << "-" // variant 1
       << std::setw(4) << (data[2] >> 16)
       << std::setw(8) << data[3];
    return ss.str();
}
