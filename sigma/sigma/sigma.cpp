#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <string>
#include <fstream>

const int MAX_SIZE = 10; 
int SIZE, m;
std::string nazwaGracza;
int wygrane = 0;
int przegrane = 0;


void tworzeniePlanszy(std::vector<std::vector<char>>& board, std::vector<std::pair<int, int>>& lokalizacjaMin) {
    board.resize(SIZE, std::vector<char>(SIZE, '0'));
    
    srand(time(nullptr));

    while (lokalizacjaMin.size() < m) {
        int x = rand() % SIZE;
        int y = rand() % SIZE;
        if (board[x][y] == '0') {
            board[x][y] = '*';
            lokalizacjaMin.push_back({ x, y });
        }
    }
}


void pokazaniePlanszy(const std::vector<std::vector<char>>& board) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            std::cout << board[i][j] << " ";
        }
        std::cout << std::endl;
    }
}


int liczMiny(const std::vector<std::vector<char>>& board, int row, int col) {
    int count = 0;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            int newRow = row + i;
            int newCol = col + j;
            if (newRow >= 0 && newRow < SIZE && newCol >= 0 && newCol < SIZE) {
                if (board[newRow][newCol] == '*') {
                    ++count;
                }
            }
        }
    }
    return count;
}


bool checkWin(const std::vector<std::vector<char>>& board) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (board[i][j] == '0') {
                return false;
            }
        }
    }
    
    return true;
}


void ZapisPliku(const std::string& nazwaGracza, const std::string& nazwaPliku, int wygrane, int przegrane) {
    std::ofstream plik(nazwaPliku, std::ios::app);  

    if (plik.is_open()) {
        if (wygrane > 0) {
            plik << "Gracz " << nazwaGracza << " wygrał!" << std::endl;
        }
        else if (przegrane > 0) {
            plik << "Gracz " << nazwaGracza << " przegrał." << std::endl;
        }

        plik.close();
    }
    
}

int main() {
    setlocale(LC_CTYPE, "Polish");

    std::cout << "Podaj nazwe gracza : ";
    std::cin >> nazwaGracza;

    std::cout << "Podaj rozmiar planszy (maksymalnie " << MAX_SIZE << "): ";
    std::cin >> SIZE;

    if (SIZE > MAX_SIZE) {
        std::cout << "Zbyt duży rozmiar. Ustawiam rozmiar na maksymalny." << std::endl;
        SIZE = MAX_SIZE;
    }

    std::cout << "Podaj liczbę min: ";
    std::cin >> m;

    if (m >= SIZE * SIZE) {
        std::cout << "Zbyt duża liczba min. Ustawiam liczbę min na maksymalną możliwą." << std::endl;
        m = SIZE * SIZE - 1;
    }

    std::vector<std::vector<char>> board;
    std::vector<std::pair<int, int>> minesLocations;
    tworzeniePlanszy(board, minesLocations);

    int row, col;
    bool gameOver = false;

    while (!gameOver) {
        pokazaniePlanszy(board);
        std::cout << "Gracz : " << nazwaGracza << std::endl;
        std::cout << "Podaj wiersz i kolumnę (0-" << SIZE - 1 << "): ";
        std::cin >> row >> col;

        if (board[row][col] == '*') {
            std::cout << "Przegrałeś! Trafiono na minę!" << std::endl;
            przegrane++;
            ZapisPliku(nazwaGracza, "wyniki.txt", wygrane, przegrane);
            gameOver = true;
        }
        else {
            int minesCount = liczMiny(board, row, col);
            board[row][col] = minesCount + '0'; 
            std::cout << "Gracz : " << nazwaGracza << std::endl;
            std::cout << "Bezpieczne pole. Wokół są " << minesCount << " miny." << std::endl;

            
            if (checkWin(board)) {
                std::cout << "Gratulacje! Wygrałeś grę!" << std::endl;
                wygrane++;
                ZapisPliku(nazwaGracza, "wyniki.txt", wygrane, przegrane);
                gameOver = true;
            }
        }
    }

    return 0;
}