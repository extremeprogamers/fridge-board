#include "Composer.h"

class ComposerImpl : public Composer
{
public:
    const char *composeSite(vector<string> messages) {
        string t = "<html>\n"
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
        string t2 = composeGetMessages(messages);
        string t3 = "    </table>\n"
                    "  </ul>\n"
                    "  <br> <br> \n"
                    "  <form action=\"/messages\" method=\"post\">\n"
                    "    <b>New note:</b> <input type=\"text\" name=\"note\">\n"
                    "    <input class=\"waves-light btn green\" type=\"submit\" value=\"Add note\">\n"
                    "  </form>\n"
                    "</div>\n"
                    "</body>\n"
                    "</html>";
        string out = t + t2 + t3;
        return out.c_str();
    };

    string composeGetMessages(vector<string> messages) {
        string message;
        for (auto &element : messages)
        {
            message += composeMessage(element);
        }
        return message;
    };

    string composeMessage(string msg) {
        return "            <tbody>\n"
               "                <tr>\n"
               "                    <td>" +
               msg + "</td>\n"
                     "<td><a href=\"/messages\" method=\"DELETE\" class=\"waves-effect waves-light btn red\">DELETE</a></td>"
                     "                </tr>\n"
                     "            </tbody>";
    };

    const char *composeAdd(string msg, bool added) { 
        return "";
     };

    const char *composeRemoved(string msg, bool removed) { 
        return "";
    };
};