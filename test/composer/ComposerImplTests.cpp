#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "gmock/gmock-actions.h"

#include "ComposerImpl.h"
#include <algorithm>

using namespace testing;

TEST(composer, composeSite)
{
    //given
    ComposerImpl *composer = new ComposerImpl();

    vector<string> msgs;
    msgs.push_back("test1");
    msgs.push_back("test2");
    //when
    const char *messages = composer->composeSite(msgs);

    cout << messages;
    string messages3 = std::string(messages);
    //then
    string html = "<html>\n\n<metaname=\"viewport\"content=\"width=device-width\">\n<metaname=\"viewport\"content=\"width=device-width,initial-scale=1\">\n\n<linkrel=\"stylesheet\"href=\"materialize.min.css\">\n<body>\n<divclass=\"container\">\n<h3>Notes</h3>\n<table>\n<thead>\n<tr>\n<th>Note</th>\n<th>Actions</th>\n</tr>\n</thead>\n\n<tbody>\n<tr>\n<td>test1</td>\n<td><ahref=\"/messages\"method=\"DELETE\"class=\"waves-effectwaves-lightbtnred\">DELETE</a></td></tr>\n</tbody><tbody>\n<tr>\n<td>test2</td>\n<td><ahref=\"/messages\"method=\"DELETE\"class=\"waves-effectwaves-lightbtnred\">DELETE</a></td></tr>\n</tbody></table>\n</ul>\n<br><br>\n<formaction=\"/messages\"method=\"post\">\n<b>Newnote:</b><inputtype=\"text\"name=\"note\">\n<inputclass=\"waves-lightbtngreen\"type=\"submit\"value=\"Addnote\">\n</form>\n</div>\n</body>\n</html>";

    std::string::iterator end_pos2 = std::remove(messages3.begin(), messages3.end(), ' ');
    messages3.erase(end_pos2, messages3.end());
    ASSERT_EQ(messages3, html);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}