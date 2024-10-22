class Solution:
    def reformatDate(self, date: str) -> str:
        values = date.split(' ')
        
        # month to MM 
        convertMonth = {
            "Jan" : "01", 
            "Feb" : "02", 
            "Mar" : "03", 
            "Apr" : "04", 
            "May" : "05", 
            "Jun" : "06", 
            "Jul" : "07", 
            "Aug" : "08", 
            "Sep" : "09", 
            "Oct" : "10", 
            "Nov" : "11", 
            "Dec" : "12"
        }

        dayString = values[0]
        # get all first numeric characters
        day = ""
        for c in dayString:
            if c.isnumeric():
                day += c
            else: break
        if len(day) == 1:
            day = "0"+day

        ret = str(values[2]) + "-" + convertMonth[values[1]] + "-" + day
        return ret
        