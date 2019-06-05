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
    string actualHtml = std::string(messages);
    //then
    string expectedHtml = "<html>\n\n<metaname=\"viewport\"content=\"width=device-width\">\n<metaname=\"viewport\"content=\"width=device-width,initial-scale=1\">\n\n<linkrel=\"stylesheet\"href=\"materialize.min.css\">\n<body>\n<divclass=\"container\">\n<h3>Notes</h3>\n<table>\n<thead>\n<tr>\n<th>Note</th>\n<th>Actions</th>\n</tr>\n</thead>\n\n<tr><formaction=\"/messages/delete\"method=\"post\"><inputtype=\"hidden\"name=\"messageId\"value=0\"/><td>test1</td><td><inputtype=\"submit\"class=\"waves-effectwaves-lightbtnred\"value=\"DELETE\"></td></form></tr><tr><formaction=\"/messages/delete\"method=\"post\"><inputtype=\"hidden\"name=\"messageId\"value=1\"/><td>test2</td><td><inputtype=\"submit\"class=\"waves-effectwaves-lightbtnred\"value=\"DELETE\"></td></form></tr></table>\n</ul>\n<br><br>\n<formaction=\"/messages\"method=\"post\">\n<b>Newnote:</b><inputtype=\"text\"name=\"note\">\n<inputclass=\"waves-lightbtngreen\"type=\"submit\"value=\"Addnote\">\n</form>\n</div>\n</body>\n</html>";

    std::string::iterator end_pos2 = std::remove(actualHtml.begin(), actualHtml.end(), ' ');
    actualHtml.erase(end_pos2, actualHtml.end());
    ASSERT_EQ(expectedHtml, actualHtml);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}