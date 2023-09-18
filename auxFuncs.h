#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>

class BitArray;
BitArray operator^( BitArray v1, BitArray v2);
int hammingDistance(BitArray v1, BitArray v2);

class BitArray {
    public:
    std::vector<bool> bits = {};

    BitArray(std::string s, std::string enc) {
        if (enc.compare("base16") == 0) {
            fromBase16(s);
        }
        else if (enc.compare("base64") == 0) {
            fromBase64(s);
        }
        else if (enc.compare("ascii") == 0) {
            fromPlainText(s);
        }
    }

    BitArray(std::vector<bool> v) {
        bits = v;
    }

    int size() {
        return bits.size();
    }

    std::string toBase16() {
        // converts a bit array to a base16 string
        std::string str = "";
        int d = 0, pow2 = 1;
        if (bits.size() % 4 != 0) {
            for (int i = (bits.size() % 4) - 1; i>=0; i--) {
                d += bits[i]*pow2;
                pow2 = 2*pow2;
            }
            str += char(int('0') + d);
        }
        for (int i = bits.size() % 4; i < bits.size(); i += 4) {
            d = 8*bits[i] + 4*bits[i+1] + 2*bits[i+2] + bits[i+3];
            if (0 <= d && d <= 9) {
                str += char(int('0') + d);
            }
            else {
                str += char(int('a') + d - 10);
            }
        }
        return str;
    }

    std::string toBase64() {
        // converts a bit array to a base64 string
        std::string str = "";
        int d=0, pow2=1;
        if (bits.size() % 6 != 0) {
            for (int i = (bits.size() % 6) - 1; i>=0; i--) {
                d += bits[i]*pow2;
                pow2 = 2*pow2;
            }
            if (d <= 25) { str += char( int('A') + d); }
            else { str += char( int('a') + d - 26); }
        }
        for (int i = bits.size() % 6; i < bits.size(); i += 6) {
            d = 32*bits[i] + 16*bits[i+1] + 8*bits[i+2] + 4*bits[i+3] + 2*bits[i+4] + bits[i+5];
            if (0 <= d && d <= 25) { str += char(int('A') + d); }
            else if (26 <= d && d <= 51) { str += char(int('a') + d - 26); }
            else if (52 <= d && d <= 61) { str += char(int('0') + d - 52); }
            else if (d == 62) { str += '+'; }
            else if (d == 63) { str += '/'; }
        }
        return str;
    }

    std::string toPlainText() {
        // converts a bit array to plain text (assuming 8-bit encoding)
        std::string s = "";
        int d, pow2;
        for (int i = 0; i < bits.size(); i += 8) {
            d = 0;
            pow2 = 128;
            for (int j = 0; j < 8; j++) {
                d += pow2*bits[i+j];
                pow2 /= 2;
            }
            s += char(d);
        }
        return s;
    }

    float englishScore() {
        // assign a score to plain text
        std::string str = toPlainText();
        std::unordered_map <char, int> letterCount = {};
        std::unordered_map <char, float> letterFrequency = {}; // from wikipedia
        letterFrequency['a'] = 0.082;
        letterFrequency['b'] = 0.015;
        letterFrequency['c'] = 0.028;
        letterFrequency['d'] = 0.043;
        letterFrequency['e'] = 0.127;
        letterFrequency['f'] = 0.022;
        letterFrequency['g'] = 0.020;
        letterFrequency['h'] = 0.061;
        letterFrequency['i'] = 0.070;
        letterFrequency['j'] = 0.0015;
        letterFrequency['k'] = 0.0077;
        letterFrequency['l'] = 0.040;
        letterFrequency['m'] = 0.024;
        letterFrequency['n'] = 0.067;
        letterFrequency['o'] = 0.075;
        letterFrequency['p'] = 0.019;
        letterFrequency['q'] = 0.00095;
        letterFrequency['r'] = 0.060;
        letterFrequency['s'] = 0.063;
        letterFrequency['t'] = 0.091;
        letterFrequency['u'] = 0.028;
        letterFrequency['v'] = 0.0098;
        letterFrequency['w'] = 0.024;
        letterFrequency['x'] = 0.0015;
        letterFrequency['y'] = 0.020;
        letterFrequency['z'] = 0.00074;
        letterFrequency[' '] = (1-1/5.1)/5.1; // from average english word length (wolfram alpha)
        float score = 0;
        int nonPrintableCount = 0;
        for (int i = 0; i < str.size(); i++) {
            char c = str[i];
            if ( ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') || c == ' ') {
                letterCount[tolower(c)];
                letterCount[tolower(c)]++;
            }
            // Penalize non-printable characters (except LF and CR)
            else if ( int(c) == 10 or int(c) == 13) { }
            else if ( int(c) < 32 || int(c) > 126) {
                nonPrintableCount++;
            }
        }
        for (auto i = letterFrequency.begin(); i != letterFrequency.end();  i++) {
            char key = i -> first;
            float val = i -> second;
            score -= std::abs(letterCount[key]/(float)str.size() - val);
        }
        score -= 0.1*nonPrintableCount;
        return score;
    }

    std::tuple<float, std::string, char> breakSingleCharXor() {
        // brute-force cypher encrypted with single-char xor
        float score, bestScore = -100;
        char bestKey;
        std::string bestString;
        for (int c = 0; c < 256 ; c++) {
            BitArray candidateKey = BitArray(std::string(1,char(c)), "ascii");
            BitArray candidateText = *this ^ candidateKey;
            score = candidateText.englishScore();
            if (score > bestScore) { 
                bestScore = score;
                bestKey = char(c);
                bestString = candidateText.toPlainText();
            }
        }
        return std::make_tuple(bestScore, bestString, bestKey);
    }

    int probableKeySize() {
        float dist, minDist = 1000;
        int key;
        for (int k = 2*8; k<=40*8; k += 8) {
            std::vector<bool> v1(bits.begin(), bits.begin() + 2*k);
            std::vector<bool> v2(bits.begin() + 2*k,bits.begin() + 4*k);
            dist = (float)hammingDistance(BitArray(v1), BitArray(v2))/k;
            if (dist < minDist) { minDist = dist; key = k; }
        }
        return key/8;
    }

    private:
    std::vector<bool> fromBase16(std::string str) {
        // converts a base16 string to a bit array
        bits.reserve(4*str.size());
        for (int i = 0; i < str.size(); i++) {
            char c = tolower(str[i]);
            int d;
            if ('0' <= c && c <= '9') { d = c - '0'; }
            else if ( 'a' <= c && c <= 'z') { d = c - 'a' + 10; }
            for (int pow2 = 8; pow2 > 0; pow2 /= 2) {
                bits.push_back(d / pow2);
                d = d % pow2;
            }
        }
        return bits;
    }

    std::vector<bool> fromBase64(std::string str) {
        // converts a base64 string to a bit array
        bits.reserve(6*str.size());
        for (int i = 0; i < str.size(); i++) {
            char c = str[i];
            int d;
            if ( 'A' <= c && c <= 'Z') { d = c - 'A'; }
            else if ('a' <= c && c <= 'z') { d = c - 'a' + 26; }
            else if ('0' <= c && c <= '9') { d = c - '0' + 52; }
            else if ( c == '+') { d = 62; }
            else if ( c == '/') { d = 63; }
            else if ( c == '=') { break; }
            for (int pow2 = 32; pow2 > 0; pow2 /= 2) {
                bits.push_back(d / pow2);
                d = d % pow2;
            }
        }
        return bits;
    }

    std::vector<bool> fromPlainText(std::string str) {
        // converts plain text to a bit array (assuming 8-bit encoding)
        int d;
        bits.reserve(8*str.size());
        for (int i = 0; i < str.size(); i++) {
            d = int(str[i]);
            for (int pow2 = 128; pow2 > 0; pow2 /= 2) {
                bits.push_back(d / pow2);
                d = d % pow2;
            }
        }
        return bits;
    }
};

BitArray operator^( BitArray v1, BitArray v2) {
    // Allows xor between BitArrays. If the sizes doesn't match,
    // the shortest vector is repeated.
    std::vector<bool> v = {};
    for (int i = 0; i < std::max(v1.size(), v2.size()); i++) {
        v.push_back(v1.bits[i % v1.size()] ^ v2.bits[i % v2.size()]);
    }
    return BitArray(v);
}

std::ostream& operator<<(std::ostream& os, BitArray v) {
    // Overload << to print vectors to stdout (mostly for debugging)
    for (int i = 0; i < v.size(); i++) {
        os << v.bits[i];
    }
    return os;
}

int hammingDistance( BitArray v1, BitArray v2) {
    int distance = 0;
    BitArray v3 = v1 ^ v2;
    for (int i = 0; i < v3.size(); i++) {
        distance += v3.bits[i];
    }
    return distance;
}