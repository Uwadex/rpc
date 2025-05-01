#include "test.pb.h"
#include <iostream>
#include <string>
using namespace fixbug;
int main()
{
    GetFriendListResponse response;
    ResultCode* result = response.mutable_result();
    result->set_errcode(0);
    result->set_errmsg("ok");
    User* user = response.add_friend_list();
    user->set_name("zhangsan");
    user->set_age(18);
    user->set_sex(User::MAN);
    User* user2 = response.add_friend_list();
    user2->set_name("lisi");
    user2->set_age(20);
    user2->set_sex(User::WOMEN);
    std::cout << response.friend_list_size() << std::endl;
    return 0;
}