#ifndef APP_H
# define APP_H

class Pong
{
	public:
		Pong();
		void onRun();

	private:
		enum gameType {EXIT=0, COMPUTER=1, LOCAL=2, REMOTE=3};
		void onInit();
		int onMenu();
		void onCreateGame(int type);
		void onCleanup();
};

#endif
