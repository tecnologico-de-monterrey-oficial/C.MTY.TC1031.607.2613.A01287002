#include "processing.h"
#include <sstream>
#include <map>
#include <format>

//
// -- Parser class implementation --
//
Parser::Parser(const std::string &filename) {
    file.open(filename);
    if (!file.is_open()) {
        throw std::runtime_error("File not found: " + filename);
    }
}

Parser::~Parser() {
    if (file.is_open()) {
        file.close();
    }
}

bool Parser::findFile(const std::string &filename) {
    std::ifstream testFile(filename);
    return testFile.good();
}

void Parser::readFileInChunks(size_t chunkSize, std::function<void(const char*, size_t)> processChunk) {
    if (!file.is_open()) {
        throw std::runtime_error("File is not open for reading.");
    }

    file.clear();
    file.seekg(0);

    std::vector<char> buffer(chunkSize);
    while (file.read(buffer.data(), buffer.size()) || file.gcount() > 0) {
        processChunk(buffer.data(), file.gcount());
    }
}

// Saves files using readable representations of IP addresses and DayTimes, along with their corresponding responses.
void Parser::saveFile(const std::string &filename, const std::vector<uint32_t> &numericIPAddresses, const std::vector<uint64_t> &numericDayTimes, const std::vector<std::string> &responses) {
    std::ofstream outFile(filename);
    if (!outFile) {
        throw std::runtime_error("Could not open file for writing: " + filename);
    }

    for (size_t i = 0; i < numericIPAddresses.size(); ++i) {
        IPAddress ip = u32TpIP(numericIPAddresses[i]);
        DayTime dt = u64ToDayTime(numericDayTimes[i]);
        outFile << +ip.a << "." << +ip.b << "." << +ip.c << "." << +ip.d << " "
                << std::format("{:04}-{:02}-{:02} {:02}:{:02}:{:02}",
                    +dt.year, +dt.month, +dt.day, +dt.hour, +dt.minute, +dt.second) << " "
                << responses[i] << "\n";
    }
}

std::vector<uint32_t> Parser::readNumericIPAddresses(const std::string &filename, size_t chunkSize) {
    std::vector<uint32_t> ipAddresses;
    readFileInChunks(chunkSize, [&ipAddresses](const char* data, size_t count) {
        for (size_t i = 0; i < count; i += sizeof(uint32_t)) {
            uint32_t ip = *reinterpret_cast<const uint32_t*>(data + i);
            ipAddresses.push_back(ip);
        }
    });
    return ipAddresses;
}

std::vector<uint64_t> Parser::readNumericDayTimes(const std::string &filename, size_t chunkSize) {
    std::vector<uint64_t> dayTimes;
    readFileInChunks(chunkSize, [&dayTimes](const char* data, size_t count) {
        for (size_t i = 0; i < count; i += sizeof(uint64_t)) {
            uint64_t dt = *reinterpret_cast<const uint64_t*>(data + i);
            dayTimes.push_back(dt);
        }
    });
    return dayTimes;
}

DayTime Parser::parseLogLine(const std::string &line) {
    static const std::map<std::string, uint_least8_t> monthMap = {
        {"Jan", 1}, {"Feb", 2}, {"Mar", 3}, {"Apr", 4},
        {"May", 5}, {"Jun", 6}, {"Jul", 7}, {"Aug", 8},
        {"Sep", 9}, {"Oct", 10}, {"Nov", 11}, {"Dec", 12}
    };

    DayTime dt = {};
    std::istringstream iss(line);
    std::string monthStr, dayStr, yearStr, timeStr;

    iss >> monthStr >> dayStr >> yearStr >> timeStr;

    dt.month = monthMap.at(monthStr);
    dt.day = std::stoi(dayStr);
    dt.year = std::stoi(yearStr);

    std::replace(timeStr.begin(), timeStr.end(), ':', ' ');
    std::istringstream timeIss(timeStr);
    int h, m, s;
    timeIss >> h >> m >> s;
    dt.hour = h;
    dt.minute = m;
    dt.second = s;

    return dt;
}

uint32_t Parser::parseLogIP(const std::string &line) {
    std::istringstream iss(line);
    std::string token;
    // skip: MMM DD YYYY HH:MM:SS
    for (int i = 0; i < 4; i++) iss >> token;
    // read IP: a.b.c.d
    std::string ipStr;
    iss >> ipStr;
    std::replace(ipStr.begin(), ipStr.end(), '.', ' ');
    std::istringstream ipIss(ipStr);
    int a, b, c, d;
    ipIss >> a >> b >> c >> d;
    IPAddress ip = {(uint_least8_t)a, (uint_least8_t)b, (uint_least8_t)c, (uint_least8_t)d};
    return ipToInt(ip);
}

void Parser::readLogEntries(const std::string &filename, std::vector<uint32_t> &ips, std::vector<uint64_t> &daytimes, std::vector<std::string> &responses) {
    std::ifstream inFile(filename);
    if (!inFile) {
        throw std::runtime_error("Could not open file: " + filename);
    }

    std::string line;
    while (std::getline(inFile, line)) {
        if (line.empty()) continue;
        ips.push_back(parseLogIP(line));
        DayTime dt = parseLogLine(line);
        encodeDayTime(&dt);
        daytimes.push_back(daytimeToU64(&dt));

        // response is everything after the 4th token (MMM DD YYYY HH:MM:SS IP ...)
        std::istringstream iss(line);
        std::string token;
        for (int i = 0; i < 5; i++) iss >> token;
        std::string response;
        std::getline(iss, response);
        if (!response.empty() && response[0] == ' ') response.erase(0, 1);
        responses.push_back(response);
    }
}

void Parser::readOutputFile(const std::string &filename, std::vector<uint32_t> &ips, std::vector<uint64_t> &daytimes, std::vector<std::string> &responses) {
    std::ifstream inFile(filename);
    if (!inFile) {
        throw std::runtime_error("Could not open output file: " + filename);
    }

    std::string line;
    while (std::getline(inFile, line)) {
        if (line.empty()) continue;

        // Parse: a.b.c.d YYYY-MM-DD HH:MM:SS response
        std::istringstream iss(line);
        std::string ipStr, dateStr, timeStr;
        iss >> ipStr >> dateStr >> timeStr;

        // Parse IP: a.b.c.d
        std::replace(ipStr.begin(), ipStr.end(), '.', ' ');
        std::istringstream ipIss(ipStr);
        int a, b, c, d;
        ipIss >> a >> b >> c >> d;
        IPAddress ip = {(uint_least8_t)a, (uint_least8_t)b, (uint_least8_t)c, (uint_least8_t)d};
        ips.push_back(ipToInt(ip));

        // Parse DayTime: YYYY-MM-DD HH:MM:SS
        DayTime dt = {};
        dt.year   = std::stoi(dateStr.substr(0, 4));
        dt.month  = std::stoi(dateStr.substr(5, 2));
        dt.day    = std::stoi(dateStr.substr(8, 2));
        std::string combined = dateStr + " " + timeStr;
        dt.hour   = std::stoi(combined.substr(11, 2));
        dt.minute = std::stoi(combined.substr(14, 2));
        dt.second = std::stoi(combined.substr(17, 2));
        encodeDayTime(&dt);
        daytimes.push_back(daytimeToU64(&dt));

        // Response is everything after the datetime
        std::string response;
        std::getline(iss, response);
        if (!response.empty() && response[0] == ' ') response.erase(0, 1);
        responses.push_back(response);
    }
}

