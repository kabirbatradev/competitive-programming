class Solution {
public:
    string reformatDate(string date) {

        istringstream s(date);

        string day; s >> day;
        string month; s >> month;
        string year; s >> year;

        map<string, string> convertMonth = {
            {"Jan", "01"},
            {"Feb", "02"},
            {"Mar", "03"},
            {"Apr", "04"},
            {"May", "05"},
            {"Jun", "06"},
            {"Jul", "07"},
            {"Aug", "08"},
            {"Sep", "09"},
            {"Oct", "10"},
            {"Nov", "11"},
            {"Dec", "12"}
        };

        string dayString = "";
        for (char c : day) {
            if ('0' <= c && c <= '9') dayString += c;
            else break;
        }
        if (dayString.length() == 1) dayString = "0"+dayString;

        return year + "-" + convertMonth[month] + "-" + dayString;
        
    }
};