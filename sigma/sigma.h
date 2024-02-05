
void tworzeniePlanszy(std::vector<std::vector<char>>& board, std::vector<std::pair<int, int>>& lokalizacjaMin) {
    board.resize(SIZE, std::vector<char>(SIZE, '0'));

    srand(time(nullptr));

    while (lokalizacjaMin.size() < MINES) {
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
            plik << "Gracz " << nazwaGracza << " wygra³!" << std::endl;
        }
        else if (przegrane > 0) {
            plik << "Gracz " << nazwaGracza << " przegra³." << std::endl;
        }

        plik.close();
    }
    
}