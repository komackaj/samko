#include <libsamko/stringutils.h>

using namespace std;

vector<string> split(const string& str, string separator) {
    vector<string> ret;
    size_t start = 0, end = 0;
    while ((end = str.find(separator, start)) != string::npos) {
        if (end > start)
            ret.push_back(str.substr(start, end - start));
        start = end + separator.size();
    }

    if (start < str.size())
        ret.push_back(str.substr(start));
    return ret;
}