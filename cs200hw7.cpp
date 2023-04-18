#include <iostream>
#include <vector>
#include <map>

// Some structs

struct playerInfo
{
	char playerName[81];
	char playerID;
	char playerCharacter;
};

std::vector<playerInfo> createPlayers(int numPlayers);
std::map<std::pair<int, int>, char> createBoard(int boardWidth, int boardHeight);
void displayBoard(std::map<std::pair<int, int>, char>& board, int boardWidth, int boardHeight);
void playerMove(std::map<std::pair<int, int>, char>& board, std::vector<playerInfo>& players, playerInfo activePlayer, int boardWidth, int boardHeight);
bool checkForWin(std::map<std::pair<int, int>, char>& board, playerInfo activePlayer, int boardWidth, int boardHeight);


int main()
{
	std::cout << "Let's player Connect 4!" << std::endl;

	int numPlayers;
	std::cout << "Enter the number of players: ";
	std::cin >> numPlayers;

	std::vector<playerInfo> players = createPlayers(numPlayers);

	int boardWidth, boardHeight;

	std::cout << "How wide would you like the board to be? ";
	std::cin >> boardWidth;

	std::cout << "How tall would you like the board to be? ";
	std::cin >> boardHeight;

	std::map<std::pair<int, int>, char> board = createBoard(boardWidth, boardHeight);

	bool GameOver = false;

	int activePlayerIndex = 0;

	while (!GameOver)
	{
		playerInfo activePlayer = players[activePlayerIndex];

		displayBoard(board, boardWidth, boardHeight);

		playerMove(board, players, activePlayer, boardWidth, boardHeight);

		if (checkForWin(board, activePlayer, boardWidth, boardHeight))
		{
			displayBoard(board, boardWidth, boardHeight);
			std::cout << "Congratulations " << activePlayer.playerName << ", you won!" << std::endl;
			GameOver = true;
		}

		activePlayerIndex++;
		if (activePlayerIndex >= numPlayers)
			activePlayerIndex = 0;
	}
	

}

std::vector<playerInfo> createPlayers(int numPlayers)
{
	std::vector<playerInfo> players(numPlayers);

	for (int i = 0; i < numPlayers; i++)
	{
		std::cout << "Enter player " << i + 1 << " name: ";
		std::cin >> players[i].playerName;

		std::cout << "Enter character for player " << i + 1 << " that will be used to idetify there turn : ";
		std::cin >> players[i].playerCharacter;

		players[i].playerID = i + 1;
 	}

	return players;
}

std::map<std::pair<int, int>, char> createBoard(int boardWidth, int boardHeight)
{
	std::map<std::pair<int, int>, char> board;

	// Initialize the board to all zeros
	for (int i = 0; i < boardHeight; i++) {
		for (int j = 0; j < boardWidth; j++) {
			board[{i, j}] = '*';
		}
	}

	return board;
}

void displayBoard(std::map<std::pair<int, int>, char>& board, int BOARDWIDTH, int BOARDHEIGHT)
{
	for (int row = 0; row < BOARDHEIGHT; row++) {
		for (int col = 0; col < BOARDWIDTH; col++) {

			if (col == 0) {
				std::cout << "\n";
			}

			std::cout << board[{row, col}] << " ";
		}
	}

	std::cout << std::endl;
}

void playerMove(std::map<std::pair<int, int>, char>& board, std::vector<playerInfo>& players, playerInfo activePlayer, int boardWidth, int boardHeight)
{
	std::cout << std::endl;
	int dropChoice;

	std::cout << activePlayer.playerName << "'s Turn " << std::endl;
	std::cout << "Please enter a number between 1 & " << boardWidth << std::endl;
	std::cin >> dropChoice;

	int length = boardHeight;
	bool movePlaced = false;

	while (!movePlaced) {
		if (board[{length, dropChoice - 1}] == '*') {
			board[{length, dropChoice - 1}] = activePlayer.playerCharacter;
			movePlaced = true;
		}
		else if (length > 1)
			--length;
		else {
			std::cout << "That row is full, please enter a new row" << std::endl;
			std::cin >> dropChoice;
			length = boardHeight;
		}
	}
	


}

bool checkForWin(std::map<std::pair<int, int>, char>& board, playerInfo activePlayer, int boardWidth, int boardHeight)
{
	char playerChar = activePlayer.playerCharacter;

	// Check for horizontal win
	for (int row = 0; row < boardHeight; row++) {
		for (int col = 0; col <= boardWidth - 4; col++) {
			if (board[{row, col}] == playerChar &&
				board[{row, col + 1}] == playerChar &&
				board[{row, col + 2}] == playerChar &&
				board[{row, col + 3}] == playerChar) {
				return true;
			}
		}
	}

	// Check for vertical win
	for (int row = 0; row <= boardHeight - 4; row++) {
		for (int col = 0; col < boardWidth; col++) {
			if (board[{row, col}] == playerChar &&
				board[{row + 1, col}] == playerChar &&
				board[{row + 2, col}] == playerChar &&
				board[{row + 3, col}] == playerChar) {
				return true;
			}
		}
	}

	// Check for diagonal win (top-left to bottom-right)
	for (int row = 0; row <= boardHeight - 4; row++) {
		for (int col = 0; col <= boardWidth - 4; col++) {
			if (board[{row, col}] == playerChar &&
				board[{row + 1, col + 1}] == playerChar &&
				board[{row + 2, col + 2}] == playerChar &&
				board[{row + 3, col + 3}] == playerChar) {
				return true;
			}
		}
	}

	// Check for diagonal win (bottom-left to top-right)
	for (int row = 3; row < boardHeight; row++) {
		for (int col = 0; col <= boardWidth - 4; col++) {
			if (board[{row, col}] == playerChar &&
				board[{row - 1, col + 1}] == playerChar &&
				board[{row - 2, col + 2}] == playerChar &&
				board[{row - 3, col + 3}] == playerChar) {
				return true;
			}
		}
	}

	return false;
}
