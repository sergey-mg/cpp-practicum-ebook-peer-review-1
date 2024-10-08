#include <iomanip>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

class Ebook {
   public:
    // лучше либо разделить этот метод, чтобы выполнение команд выполнялось
    // отдельно, либо переименовать метод, чтобы было понятно, что он также
    // выполняет команды, предпочтительнее 1-ый вариант
    void ReadRequest(const string& request) {
        if (request == "READ"s) {
            int user, page;
            cin >> user;
            cin >> page;
            // бессмысленный if-else
            // если взять for из if, и кол-во страниц будет 0, то отсчет так же
            // пойдет с 1(0 + 1 = 1) страницы, то есть тот же самый for, что и в
            // else
            if (user_pages_[user] != 0) {
                for (int i = user_pages_[user] + 1; i <= page; ++i) {
                    ++page_users_[i];
                }
            } else {
                for (int i = 1; i <= page; ++i) {
                    ++page_users_[i];
                }
                total_users_.insert(user);
            }
            user_pages_[user] = page;
        } else if (request == "CHEER"s) {
            int user;
            cin >> user;
            if (total_users_.count(user) == 0) {
                cout << 0 << endl;
            } else if (total_users_.count(user) == 1 &&
                       total_users_.size() == 1) {
                cout << 1 << endl;
            } else {
                double didnt_read =
                    total_users_.size() - page_users_[user_pages_[user]];
                cout << setprecision(6)
                     << didnt_read / (total_users_.size() - 1) << endl;
            }
        }
    }

   private:
    vector<int> user_pages_ = vector<int>(
        100000,
        0);  // небольшая "придирка": разряды в больших числах для более
             // удобного чтения лучше разделять символом ' (10'000, 1'000)
    vector<int> page_users_ = vector<int>(1000, 0);
    // стоит переименовать предыдущие две переменные и добавить в них to
    // (user_to_pages_, page_to_users_), тогда понятнее, что переменная по
    // номеру пользователя или страницы выдает соотвествующую информацию
    // (дословно пользователь к странице, страница к пользователю)
    unordered_set<int> total_users_;  // для этого лучше использовать просто
                                      // переменную int или size_t
};

int main() {
    Ebook ebook;
    // это чтение лучше вынести в функцию Read, а внутри нее уже выполнять
    // команды методами книги
    int request_count;
    cin >> request_count;
    for (int i = 0; i < request_count; ++i) {
        string request;
        cin >> request;
        ebook.ReadRequest(request);
    }
}
