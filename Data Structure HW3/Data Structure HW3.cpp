#include <iostream>
#include <list>
#include <forward_list>
#include <vector>
#include <algorithm>
#include <string>
#include <regex>

using namespace std;

// 定義書籍的結構體，每本書包含書名、作者和圖書編號
struct Book {
    string title;  // 書名
    string author; // 作者
    string id;     // 圖書編號
};

// 定義借閱者的結構體，每個借閱者包含姓名及其借閱的圖書編號列表
struct Borrower {
    string name;                // 借閱者的姓名
    vector<string> borrowedBooks; // 借閱者的圖書編號列表
};

// 檢查圖書編號是否符合格式要求
bool isValidBookID(const string& id) {
    // 使用正則表達式檢查編號格式 (例如 "A1234")
    regex pattern("^[A-Z][0-9]{4}$");
    return regex_match(id, pattern); // 如果匹配成功，返回 true，否則返回 false
}

// 添加新書籍到書籍列表
void addBook(list<Book>& books) {
    Book newBook; // 建立新書籍物件
    cout << "輸入書名: ";
    cin >> newBook.title; // 讀取書名
    cout << "輸入作者: ";
    cin >> newBook.author; // 讀取作者

    // 重複讀取直到輸入的圖書編號合法
    while (true) {
        cout << "輸入圖書編號 (首字為英文字母，後面為4位數字): ";
        cin >> newBook.id; // 讀取圖書編號
        if (isValidBookID(newBook.id)) break; // 編號合法則跳出循環
        cout << "無效的圖書編號，請重新輸入。\n";
    }

    // 將新書籍加入書籍列表
    books.push_back(newBook);
    cout << "書籍已添加。\n";
}

// 刪除指定圖書編號的書籍
void deleteBook(list<Book>& books) {
    string id;
    cout << "輸入要刪除的圖書編號: ";
    cin >> id; // 讀取要刪除的圖書編號

    // 使用 Lambda 表達式查找具有相同編號的書籍
    auto it = find_if(books.begin(), books.end(), [&id](const Book& b) { return b.id == id; });
    if (it != books.end()) {
        books.erase(it); // 找到則刪除書籍
        cout << "書籍已刪除。\n";
    }
    else {
        cout << "找不到指定的圖書編號。\n"; // 找不到則提示
    }
}

// 搜索圖書
void searchBook(const list<Book>& books) {
    string id;
    cout << "輸入要查詢的圖書編號: ";
    cin >> id; // 讀取要查詢的圖書編號

    // 使用 Lambda 表達式查找具有相同編號的書籍
    auto it = find_if(books.begin(), books.end(), [&id](const Book& b) { return b.id == id; });
    if (it != books.end()) {
        // 找到書籍，輸出其資訊
        cout << "書名: " << it->title << ", 作者: " << it->author << ", 圖書編號: " << it->id << endl;
    }
    else {
        cout << "找不到指定的圖書編號。\n";
    }
}

// 按圖書編號排序並列出所有書籍
void listBooks(const list<Book>& books) {
    // 建立副本，因為我們不想更改原始列表的順序
    list<Book> sortedBooks = books;

    // 使用 Lambda 表達式根據圖書編號排序
    sortedBooks.sort([](const Book& a, const Book& b) { return a.id < b.id; });

    cout << "所有書籍列表:\n";
    for (const auto& book : sortedBooks) {
        // 列出每本書籍的詳細資料
        cout << "書名: " << book.title << ", 作者: " << book.author << ", 圖書編號: " << book.id << endl;
    }
}

// 添加新借閱者
void addBorrower(forward_list<Borrower>& borrowers) {
    Borrower newBorrower; // 建立新借閱者物件
    cout << "輸入借閱者姓名: ";
    cin >> newBorrower.name; // 讀取借閱者姓名

    string bookID;
    cout << "輸入借閱的圖書編號 (輸入 '0' 結束): ";
    while (true) {
        cin >> bookID; // 讀取圖書編號
        if (bookID == "0") break; // 輸入 0 結束
        newBorrower.borrowedBooks.push_back(bookID); // 加入借閱的圖書編號
    }

    // 將新借閱者加入借閱者列表
    borrowers.push_front(newBorrower);
    cout << "借閱者已添加。\n";
}

// 刪除借閱者
void deleteBorrower(forward_list<Borrower>& borrowers) {
    string name;
    cout << "輸入要刪除的借閱者姓名: ";
    cin >> name; // 讀取要刪除的借閱者姓名

    // 使用 Lambda 表達式查找並移除借閱者
    borrowers.remove_if([&name](const Borrower& b) { return b.name == name; });
    cout << "借閱者已刪除。\n";
}

// 搜索借閱者
void searchBorrower(const forward_list<Borrower>& borrowers) {
    string name;
    cout << "輸入要查詢的借閱者姓名: ";
    cin >> name; // 讀取要查詢的借閱者姓名

    // 使用 Lambda 表達式查找具有相同姓名的借閱者
    auto it = find_if(borrowers.begin(), borrowers.end(), [&name](const Borrower& b) { return b.name == name; });
    if (it != borrowers.end()) {
        cout << "借閱者姓名: " << it->name << ", 借閱圖書編號: ";
        for (const auto& id : it->borrowedBooks) cout << id << " "; // 列出所有借閱的圖書編號
        cout << endl;
    }
    else {
        cout << "找不到指定的借閱者。\n";
    }
}

// 列出所有借閱者及其借閱的圖書
void listBorrowers(const forward_list<Borrower>& borrowers) {
    cout << "所有借閱者列表:\n";
    for (const auto& borrower : borrowers) {
        cout << "借閱者姓名: " << borrower.name << ", 借閱圖書編號: ";
        for (const auto& id : borrower.borrowedBooks) cout << id << " "; // 列出所有借閱的圖書編號
        cout << endl;
    }
}

// 主函式 - 提供操作選單
int main() {
    // 初始化測試資料
    list<Book> books = {
        {"紅樓夢", "曹雪芹", "A1234"}, {"西遊記", "吳承恩", "B2345"},
        {"水滸傳", "施耐庵", "B3456"}, {"三國演義", "羅貫中", "C4567"},
        {"金瓶梅", "蘭陵笑笑生", "C5678"}, {"聊齋志異", "蒲松齡", "D6789"},
        {"儒林外史", "吳敬梓", "D7890"}, {"封神演義", "許仲琳", "E8901"},
        {"鏡花緣", "李汝珍", "E9012"}, {"老殘遊記", "劉鶚", "F0123"}
    };
    forward_list<Borrower> borrowers = {
        {"小明", {"A1234", "B2345"}}, {"小華", {"C4567"}},
        {"小美", {"D6789", "E8901"}}, {"小強", {"F0123"}},
        {"小麗", {"B3456", "C5678"}}
    };

    int choice;
    while (true) {
        // 顯示操作選單
        cout << "\n圖書館管理系統:\n";
        cout << "1. 添加新書籍\n";
        cout << "2. 刪除書籍\n";
        cout << "3. 搜索書籍\n";
        cout << "4. 列出所有書籍\n";
        cout << "5. 添加新借閱者\n";
        cout << "6. 刪除借閱者\n";
        cout << "7. 搜索借閱者\n";
        cout << "8. 列出所有借閱者\n";
        cout << "0. 退出\n";
        cout << "選擇操作: ";
        cin >> choice; // 讀取使用者的選擇

        // 根據選擇呼叫對應的函式
        switch (choice) {
        case 1: addBook(books); break;
        case 2: deleteBook(books); break;
        case 3: searchBook(books); break;
        case 4: listBooks(books); break;
        case 5: addBorrower(borrowers); break;
        case 6: deleteBorrower(borrowers); break;
        case 7: searchBorrower(borrowers); break;
        case 8: listBorrowers(borrowers); break;
        case 0: return 0; // 結束程式
        default: cout << "無效的選擇。\n"; break;
        }
    }
}
