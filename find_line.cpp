#include <iostream>
#include <cstring>
#include<vector>

#define NMAX 100

struct bor_vertex {
    int next_vertex[NMAX], vertex_number;
    bool leaf;
    int par;
    char symble;
    int link;
    int go_to[NMAX];
};

bor_vertex bor[NMAX+1];
std::vector<std::string> all_lines;
int size;

void init() {
    bor[0].par = bor[0].link = -1;
    memset(bor[0].next_vertex, 255, sizeof bor[0].next_vertex);
    memset(bor[0].go_to, 255, sizeof bor[0].go_to);
    size = 1;
}

void add_string (const std::string& s) {
    int vertex = 0;
    memset (bor[size].next_vertex, 255, sizeof bor[size].next_vertex);
    memset (bor[size].go_to, 255, sizeof bor[size].go_to);
    for (size_t i = 0; i < s.length(); ++i) {
        char letter = s[i]-'a';
        if (bor[vertex].next_vertex[letter] == -1) {
            bor[size].link = -1;
            bor[size].par = vertex;
            bor[size].symble = letter;
            bor[vertex].next_vertex[letter] = size++;
        }
        vertex = bor[vertex].next_vertex[letter];
    }
    bor[vertex].leaf = true;
    all_lines.push_back(s);
    bor[vertex].vertex_number = all_lines.size() - 1;
}

int go_to (int vertex, char letter);

int get_link (int vertex) {
    if (bor[vertex].link == -1) {
        if (vertex == 0 || bor[vertex].par == 0) {
            bor[vertex].link = 0;
        } else {
            bor[vertex].link = go_to(get_link(bor[vertex].par), bor[vertex].symble);
        }
    }
    return bor[vertex].link;
}

int go_to (int vertex, char letter) {
    if (bor[vertex].go_to[letter] == -1) {
        if (bor[vertex].next_vertex[letter] != -1) {
            bor[vertex].go_to[letter] = bor[vertex].next_vertex[letter];
        } else {
            bor[vertex].go_to[letter] = vertex == 0 ? 0 : go_to(get_link(vertex), letter);
        }
    }
    return bor[vertex].go_to[letter];
}

void check_it(int vertex,int num) {
    for (int u = vertex; u != 0; u = get_link(u)) {
        if (bor[u].leaf) {
            std::cout << num - all_lines[bor[u].vertex_number].length() + 1 << " " << all_lines[bor[u].vertex_number] << std::endl;
        }
    }
}

void find_all_lines(const std::string& text) {
    int letter = 0;
    for (int i = 0; i < text.length(); i++) {
        letter = go_to(letter, text[i]-'a');
        check_it(letter, i + 1);
    }
}

int main() {
    std::string Enter, Find_it;
    int Number;
    std::cout << "Enter the text:" << std::endl;
    std::cin >> Enter;
    std::cout << "The number of lines you are looking for:" << std::endl;
    std::cin >> Number;
    std::cout << "Enter each of them via tabs:" << std::endl;
    init();
    for (int i = 0; i < Number; i++) {
        std::cin >> Find_it;
        add_string(Find_it);
    }
    std::cout << "The number of the first character of the found line in the text:" << std::endl;
    find_all_lines(Enter);
}
