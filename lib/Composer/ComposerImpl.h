#include "Composer.h"

#include <sstream>
#include "string.h"

template <typename T>
std::string to_string(const T &obj){
    std::stringstream ss;
    ss << obj;
    return ss.str();
}

class ComposerImpl : public Composer{
public:
    const char *composeSite(std::vector<std::string> messages){
        std::string t = "<html>\n"
                   "\n"
                   "<meta name=\"viewport\" content=\"width=device-width\">\n"
                   "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n"
                   " \n"
                   "<link rel=\"stylesheet\" href=\"materialize.min.css\">\n"
                   "<body>\n"
                   "<div class=\"container\">\n"
                   "  <h3>Notes</h3>\n"
                   "  <table>\n"
                   "    <thead>\n"
                   "      <tr>\n"
                   "          <th>Note</th>\n"
                   "          <th>Actions</th>\n"
                   "      </tr>\n"
                   "    </thead>\n"
                   "\n";
        std::string t2 = composeGetMessages(messages);
        std::string t3 = "    </table>\n"
                    "  </ul>\n"
                    "  <br> <br> \n"
                    "  <form action=\"/messages\" method=\"post\">\n"
                    "    <b>New note:</b> <input type=\"text\" name=\"note\">\n"
                    "    <input class=\"waves-light btn green\" type=\"submit\" value=\"Add note\" maxlength=\"50\">\n"
                    "  </form>\n"
                    "</div>\n"
                    "</body>\n"
                    "</html>";
        std::string out = t + t2 + t3;
        return out.c_str();
    };

    std::string composeGetMessages(std::vector<std::string> messages){
        std::string message;
        for (int i = 0; i < messages.size(); i++){
            message += composeMessage(messages.at(i), i);
        }
        return message;
    };

    std::string composeMessage(std::string msg, int id){
        char str[12];
        sprintf(str, "%d", id);
        std::string s = str;
        return "<tr>"
               "<form action=\"/messages/delete\" method=\"post\">"
               "<input type=\"hidden\" name=\"messageId\" value=" + s + "\"/>"
               "<td>" +
               msg + "</td>"
                     "<td><input type=\"submit\" class=\"waves-effect waves-light btn red\" value=\"DELETE\"></td>"
                     "</form>"
                     "</tr>";
    };
};
