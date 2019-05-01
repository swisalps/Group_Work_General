#include "GameController.cpp"
#include <omp.h>



class ParallelSolitare {
	public:
		int totalGames;
		
		
		
		
		

			ParallelSolitare() {
				totalGames = 5000;
				int maxThreads = omp_get_max_threads();
				
				double gamesWon = 0;
				int totalMoves = 0;
				srand(time(NULL));
	#pragma omp parallel for reduction (+: gamesWon, totalMoves)
				for (int i = 0; i < totalGames; ++i) {
					GameController* game = new GameController();
					int* gamesStats = game->run();
					if (gamesStats[0] == 1)
						gamesWon++;
					totalMoves = totalMoves + gamesStats[1];
					delete game;
				}
			double winPerc = (gamesWon / totalGames + 0.0)*100.0;
			double averageMoves = totalMoves / totalGames;
			cout << "Maximum number of available threads " << maxThreads << endl;
			cout << "Played " << totalGames << " and won " << gamesWon << " for a win percentage of: " << winPerc << "%" << endl;
			cout << "Average moves made per winning game: " << averageMoves << endl;
			
			
					

		}

};
int main()
{
	auto start = std::chrono::high_resolution_clock::now();
	ParallelSolitare* solitare = new ParallelSolitare();
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::seconds>(stop - start);
	cout << "Total execution Time: " << duration.count() << " seconds\n";

	delete solitare;
	system("pause");

	return 0;
}