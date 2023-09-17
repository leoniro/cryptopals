#include<vector>
#include<iostream>
#include<map>
#include<fstream>
using namespace std;

ostream& operator<<(ostream& os, const vector<bool>& vec) {
    // Overload << to print vectors to stdout (mostly for debugging)
    for (int i = 0; i < vec.size(); i++) {
        os << vec[i];
    }
    return os;
}

vector<bool> operator^( vector<bool> v1, vector<bool> v2) {
    // Allows xor between vectors. If the sizes doesn't match,
    // the shortest vector is repeated.
    vector <bool> v = {};
    for (int i = 0; i < max(v1.size(), v2.size()); i++) {
        v.push_back(v1[i % v1.size()] ^v2[i % v2.size()]);
    }
    return v;
}

vector<bool> fromBase64(string str) {
    // converts a base64 string to a bit array
    vector<bool> bitVector = {};
    bitVector.reserve(6*str.size());
    for (int i = 0; i < str.size(); i++) {
        char c = str[i];
        int d;
        if ( 'A' <= c && c <= 'Z') { d = c - 'A'; }
        else if ('a' <= c && c <= 'z') { d = c - 'a' + 26; }
        else if ('0' <= c && c <= '9') { d = c - '0' + 52; }
        else if ( c == '+') { d = 62; }
        else if (c == '/') { d = 63; }
        for (int pow2 = 32; pow2 > 0; pow2 /= 2) {
           bitVector.push_back(d / pow2);
           d = d % pow2;
        }
    }
    return bitVector;
}

vector<bool> fromBase16(string str) {
    // converts a base16 string to a bit array
    vector<bool> bitVector = {};
    bitVector.reserve(4*str.size());
    for (int i = 0; i < str.size(); i++) {
        char c = str[i];
        int d;
        if ('0' <= c && c <= '9') { d = c - '0'; }
        else if ( 'a' <= c && c <= 'z') { d = c - 'a' + 10; }
        for (int pow2 = 8; pow2 > 0; pow2 /= 2) {
           bitVector.push_back(d / pow2);
           d = d % pow2;
        }
    }
    return bitVector;
}

vector<bool> fromPlainText(string str) {
    // converts plain text to a bit array (assuming 8-bit encoding)
    int d;
    vector<bool> v;
    for (int i = 0; i < str.size(); i++) {
        d = int(str[i]);
        for (int pow2 = 128; pow2 > 0; pow2 /= 2) {
            v.push_back(d / pow2);
            d = d % pow2;
        }
    }
    return v;
}

string toBase64(vector<bool> v) {
    // converts a bit array to a base64 string
    string str = "";
    int d=0, pow2=1;
    if (v.size() % 6 != 0) {
        for (int i = (v.size() % 6) - 1; i>=0; i--) {
            d += v[i]*pow2;
            pow2 = 2*pow2;
        }
        if (d <= 25) { str += char( int('A') + d); }
        else { str += char( int('a') + d - 26); }
    }
    for (int i = v.size() % 6; i < v.size(); i += 6) {
        d = 32*v[i] + 16*v[i+1] + 8*v[i+2] + 4*v[i+3] + 2*v[i+4] + v[i+5];
        if (0 <= d && d <= 25) { str += char(int('A') + d); }
        else if (26 <= d && d <= 51) { str += char(int('a') + d - 26); }
        else if (52 <= d && d <= 61) { str += char(int('0') + d - 52); }
        else if (d == 62) { str += '+'; }
        else if (d == 63) { str += '/'; }
    }
    return str;
}

string toBase16(vector<bool> v) {
    // converts a bit array to a base16 string
    string str = "";
    int d=0, pow2=1;
    if (v.size() % 4 != 0) {
        for (int i = (v.size() % 4) - 1; i>=0; i--) {
            d += v[i]*pow2;
            pow2 = 2*pow2;
        }
        str += char(int('0') + d);
    }
    for (int i = v.size() % 4; i < v.size(); i += 4) {
        d = 8*v[i] + 4*v[i+1] + 2*v[i+2] + v[i+3];
        if (0 <= d && d <= 9) {
            str += char(int('0') + d);
        }
        else {
            str += char(int('a') + d - 10);
        }
    }
    return str;
}

string toPlainText(vector<bool> v) {
    // converts a bit array to plain text (assuming 8-bit encoding)
    string s = "";
    int d, pow2;
    for (int i = 0; i < v.size(); i += 8) {
        d = 0;
        pow2 = 128;
        for (int j = 0; j < 8; j++) {
            d += pow2*v[i+j];
            pow2 /= 2;
        }
        s += char(d);
    }
    return s;
}

float scorePlainText(string str) {
    map <char, float> letterFrequency; // from wikipedia
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
    float score = 0;
    int spaces = 0;
    for (int c = 0; c < str.size(); c++) {
        // Penalize non-printable characters (except LF and CR)
        if ( int(str[c]) == 10 or int(str[c]) == 13) {
            score += 0;
        }
        else if ( int(str[c]) < 32 || int(str[c]) > 126) {
            score -= 0.1;
        }
        // Spaces are counted and scored at the end
        else if ( str[c] == ' ')  {
            spaces++;
        }
        // use letter frequency as score for letters a-z and A-Z
        else if ( 'a' <= str[c] && str[c] <= 'z' ) {
            score += letterFrequency[str[c]];
        }
        else if ( 'A' <= str[c] && str[c] <= 'Z' ) {
            score += letterFrequency[tolower(str[c])];
        }
    }
    // average english word length is 5.1 according to Wolfram Alpha, penalize deviation
    // could be improved by checking double spaces, maybe later
    score -= abs((float)(str.size() - spaces)/(spaces+1) - 5.1)/str.size();
    return score;
}

int hammingDistance(vector<bool> v1, vector<bool> v2) {
    int distance = 0;
    vector<bool> v = v1 ^ v2;
    for (int i = 0; i<v.size(); i++) {
        distance += v[i];
    }
    return distance;
}

int main() {
    // challenge 1:
    /*
    string x64 = "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t";
    string x16 = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
    */

    // challenge 2:
    /*
    string s1 = "1c0111001f010100061a024b53535009181c";
    string s2 = "686974207468652062756c6c277320657965";
    string s3 = "746865206b696420646f6e277420706c6179";
    */

    // challenge 3:
    
    /* string s1 = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
    vector<bool> v2, v1 = fromBase16(s1);
    float score, maxScore = -100;
    string s, bestText;
    for (int c = 0; c < 256; c++) {
        s = string(1, char(c));
        v2 = fromPlainText(s);
        string plainText = toPlainText(v1 ^ v2);
        score = scorePlainText(plainText);
        if (score > maxScore) { maxScore = score; bestText = plainText; }
        cout << plainText << " " << score << endl;
    }
    cout << maxScore << " " << bestText << endl;
    */

    // challenge 4:
    /* string line, bestString, s, plainText;
    float score, bestScore = -100;
    ifstream inputFile;
    inputFile.open("4.txt");
    vector<bool> vLine, vChar;
    while ( getline(inputFile, line) ) {
        vLine = fromBase16(line);
        for (int c = 0; c < 256; c++) {
            s = string(1, char(c));
            vChar = fromPlainText(s);
            plainText = toPlainText(vLine ^ vChar);
            score = scorePlainText(plainText);
            if (score > bestScore) { bestScore = score; bestString = plainText; }
        }
    }
    inputFile.close();
    cout << bestScore << " " << bestString << endl; */

    // challenge 5:
    /* string str = "Burning 'em, if you ain't quick and nimble\nI go crazy when I hear a cymbal";
    string key = "ICE";
    string expected = "0b3637272a2b2e63622c2e69692a23693a2a3c6324202d623d63343c2a26226324272765272a282b2f20430a652e2c652a3124333a653e2b2027630c692b20283165286326302e27282f";
    vector<bool> vStr = fromPlainText(str);
    vector<bool> vKey = fromPlainText(key);
    string cypher = toBase16(vStr ^ vKey);
    cout << cypher << endl;
    cout << cypher.compare(expected) << endl; */

    // challenge 6:
    string s1 = "this is a test";
    string s2 = "wokka wokka!!!";
    vector<bool> v1 = fromPlainText(s1);
    vector<bool> v2 = fromPlainText(s2);
    cout << hammingDistance(v1,v2) << endl;


}