#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "gmock/gmock-actions.h"

#include "MessagesRepository.h"
#include "Composer.h"
#include "EndpointDispatcher.h"

using namespace testing;

class MockMessagesRepository : public MessagesRepository {
public:
    MOCK_METHOD1(add, bool(string));
    MOCK_METHOD1(remove, bool(int));
    MOCK_METHOD0(getAll, vector<string>(void));
    MOCK_METHOD0(clear, bool(void));
};

class MockComposer : public Composer {
public:
    MOCK_METHOD1(composeSite, const char *(vector<string>));
    MOCK_METHOD1(composeGetMessages, string(vector<string>));
    MOCK_METHOD2(composeMessage, string(string, int));
};

TEST(dispatcher, getMsgs) {
    //given
    MockMessagesRepository mockRepository;
    MockComposer mockComposer;
    EndpointDispatcher *dispatcher = new EndpointDispatcher(&mockRepository, &mockComposer);

    vector<string> mockMessages;
    string t1 = "test";
    mockMessages.push_back(t1);

    EXPECT_CALL(mockComposer, composeSite(mockMessages))
        .Times(1)
        .WillOnce(Return("<html><body>Wiadomosci: 1, 2</body></html>"));

    EXPECT_CALL(mockRepository, getAll())
        .Times(1)
        .WillOnce(Return(mockMessages));

    //when
    const char *messages = dispatcher->getMsgs();

    //then
    ASSERT_EQ(messages, "<html><body>Wiadomosci: 1, 2</body></html>");
}

TEST(dispatcher, postMsg) {
    //given
    MockMessagesRepository mockRepository;
    MockComposer mockComposer;
    EndpointDispatcher *dispatcher = new EndpointDispatcher(&mockRepository, &mockComposer);

    EXPECT_CALL(mockRepository, add("test"))
        .Times(1);

    //when
    dispatcher->postMsg("test");
}

TEST(dispatcher, removeMsg) {
    //given
    MockMessagesRepository mockRepository;
    MockComposer mockComposer;
    EndpointDispatcher *dispatcher = new EndpointDispatcher(&mockRepository, &mockComposer);

    EXPECT_CALL(mockRepository, remove(5))
        .Times(1);

    //when
    dispatcher->deleteMsg(5);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}