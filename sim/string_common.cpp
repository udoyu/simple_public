#include "string_common.h"
#include <fstream>
using namespace std;

namespace sim {

std::string StrLoadFile(const std::string& file)
{
    string str,tmp;
    ifstream fi(file);
    if (!fi.is_open())
        return "";
    while (getline(fi, tmp))
    {
        str += tmp;
    }
    fi.close();
    return str;
}

std::string StrReplace(const std::string& s,
    const std::string& str,
    const std::string& dst,
    size_t count)
{
    string dest;
    dest.reserve(s.length());
    size_t start_pos = 0;
    size_t end_pos = 0;
    size_t str_len = str.length();
    size_t i = 0;
    while (++i<=count)
    {
        end_pos = s.find(str, start_pos);
        if (end_pos == string::npos) break;
        cout<<"start_pos="<<start_pos<<"end_pos="<<end_pos<<endl;
        dest.append(s, start_pos, end_pos - start_pos);
        dest.append(dst);
        start_pos = end_pos + str_len;
        cout<<"i="<<i<<endl;
    }
    dest.append(s, start_pos, s.length()-start_pos);
    return dest;
}

std::string StrToLow(char* s, const size_t len)
{
    std::string d(s, len);
    size_t i = -1; 
    while (++i<len) if(d[i]>='A' && d[i]<='Z') d[i] += 32; 
    return d;
}

std::string StrToUp(char* s, const size_t len)
{
    std::string d(s, len);
    size_t i = -1; 
    while (++i<len) if(d[i]>='a' && d[i]<='z') d[i] -= 32; 
    return d;
}

std::string url_decode(const std::string& path)
{
    int i, j;  char percentcode[3];
    std::string s;
    for (i = j = 0; path[i] != '\0'; i++, j++)
    {
        if (path[i] == '%')
        {
            percentcode[0] = path[++i];
            percentcode[1] = path[++i];
            percentcode[2] = '\0';
            //path[j] = (char) strtol (percentcode, (char **) 0, 16);
            s += (char) strtol (percentcode, (char **) 0, 16);
        }
        else
        {
            //path[j] = path[i];
            s += path[i];
        }
    }
    //path[j] = path[i];
    return s;    
}

int split(const std::string &src, const char ch, std::vector<std::string> &dest)
{
    size_t offset = 0, lastset = 0;
    while (lastset < src.length())
    {
        offset = src.find(ch, lastset);
        if (string::npos == offset)
        {
            dest.push_back(src.substr(lastset, src.length()-lastset)); 
            lastset = offset + 1;
            break;
        }
        dest.push_back(src.substr(lastset, offset-lastset));

        lastset = offset + 1;
    }
    return lastset;
}

}
