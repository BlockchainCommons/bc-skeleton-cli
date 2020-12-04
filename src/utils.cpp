//
//  utils.cpp
//
//  Copyright © 2020 by Blockchain Commons, LLC
//  Licensed under the "BSD-2-Clause Plus Patent License"
//

#include "utils.hpp"

#include <math.h>
#include <stdexcept>
#include <sstream>
#include <chrono>

using namespace std;

string data_to_hex(const ByteVector& in) {
    auto hex = "0123456789abcdef";
    string result;
    for(auto c: in) {
        result.append(1, hex[(c >> 4) & 0xF]);
        result.append(1, hex[c & 0xF]);
    }
    return result;
}

uint8_t hex_digit_to_bin(char hex) {
    if (hex >= '0' && hex <= '9') {
        return hex - '0';
    } else if (hex >= 'A' && hex <= 'F') {
        return hex - 'A' + 10;
    } else if (hex >= 'a' && hex <= 'f') {
        return hex - 'a' + 10;
    } else {
        throw runtime_error("Invalid hex digit");
    }
}

ByteVector hex_to_data(const string& hex) {
    ByteVector result;

    auto len = hex.length();
    if(len % 2 != 0) {
        throw runtime_error("Hex string must have even number of characters.");
    }
    auto count = len / 2;
    result.reserve(count);
    for(auto i = 0; i < count; i++) {
        auto b1 = hex_digit_to_bin(hex[i * 2]);
        auto b2 = hex_digit_to_bin(hex[i * 2 + 1]);
        result.push_back((b1 << 4) | b2);
    }

    return result;
}

string join(const StringVector &strings, const string &separator) {
    ostringstream result;
    bool first = true;
    for(auto s: strings) {
        if(!first) {
            result << separator;
        }
        result << s;
        first = false;
    }
    return result.str();
}

StringVector split(const string& s, const char& separator) {
	StringVector result;
	string buf;

	for(auto c: s) {
		if(c != separator) {
            buf += c;
        } else if(c == separator && buf.length() > 0) {
            result.push_back(buf);
            buf = "";
        }
	}

	if(buf != "") {
        result.push_back(buf);
    }

	return result;
}

string to_lower(const string& s) {
    string out;
    transform(s.begin(), s.end(), back_inserter(out), ::tolower);
    return out;
}

bool has_prefix(const string& s, const string& prefix) {
    if(s.length() < prefix.length()) return false;
    return string(s.begin(), s.begin() + prefix.length()) == prefix;
}

string take(const string &s, size_t count) {
    auto first = s.begin();
    auto c = min(s.size(), count);
    auto last = first + c;
    return string(first, last);
}

string drop(const string& s, size_t count) {
    if(count >= s.length()) { return ""; }
    return string(s.begin() + count, s.end());
}

StringVector partition(const string& s, size_t size) {
    StringVector result;
    auto remaining = s;
    while(remaining.length() > 0) {
        result.push_back(take(remaining, size));
        remaining = drop(remaining, size);
    }
    return result;
}

int days_since_epoch() {
    using namespace std::chrono;
    auto today = system_clock::now();
    auto time_since = today.time_since_epoch();
    typedef duration<int, ratio<60*60*24>> days;
    return duration_cast<days>(time_since).count();
}
